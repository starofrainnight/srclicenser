#!/usr/bin/env python
# -*- coding: utf-8 -*-

import click
import pathlib
import chardet
import logging

def load_file(file_path):
    with open(file_path, "rb") as f:
        content = f.read()

    # Detect original charset
    charset = chardet.detect(content)
    if charset["encoding"] == "gb2312":
        charset["encoding"] = "gbk"

    content = content.decode(charset["encoding"])
    lines = content.splitlines()

    return (lines, charset)

@click.command()
@click.argument('target')
@click.option('--license', default=None,
    help='The license file we want to insert.')
def main(target, license):
    """
    Program that replace license inside source files.

    TARGET: The specific directory or source file needs to be parse
    """

    comment_marks = {
        "c":["\n/* %s\n *", " * %s", " *\n * %s */\n"],
        "cpp":["\n// %s\n//", "// %s", "//\n// %s\n"],
        "sh":["\n# %s\n#", "# %s", "#\n# %s\n"],
        "python":['"""%s\n', "%s", "\n%s\n"],
    }

    comment_mark = comment_marks['cpp']

    begin_mark = "LICENSE_BEGIN"
    end_mark = "LICENSE_END"

    if license is None:
        license_file_path = "LICENSE"
    else:
        license_file_path = license

    if not pathlib.Path(license_file_path).exists():
        logging.error("License file \"%s\" not found!" % license_file_path)
        return -1

    source_file_path = target

    license_lines, license_charset = load_file(license_file_path)
    source_lines, source_charset = load_file(source_file_path)

    insert_begin_index = 0
    if source_lines[0].startswith(r"#!"):
        insert_begin_index = 1

    generated_source_head_lines = source_lines[0:insert_begin_index]

    # Normally the license won't start at line more than 5 lines.
    # We search the begin line index
    source_license_begin = -1
    for i in range(insert_begin_index, min(5, len(source_lines))):
        if begin_mark in source_lines[i]:
            source_license_begin = i
            break

    # This source don't have any license, we just insert the license
    if source_license_begin < 0:
        tail_index = insert_begin_index
    else:
        tail_index = (source_license_begin +
         len(license_lines) +
         len(comment_mark[0].splitlines()) +
         len(comment_mark[2].splitlines()))

    # Strip down the first empty lines on tail
    for i in range(tail_index, len(source_lines)):
        if len(source_lines[i].strip()) <= 0:
            continue

        break

    generated_source_tail_lines = source_lines[i:]

    # Parse the license lines to fit for the source file format
    generated_license = [
        comment_mark[0] % begin_mark
    ]

    for aline in license_lines:
        generated_license.append(comment_mark[1] % aline)

    generated_license.append(comment_mark[2] % end_mark)

    generated_source_lines = generated_source_head_lines + generated_license + generated_source_tail_lines

    # Output generated file with original encodings
    with open(source_file_path, "wb") as f:
        f.write("\n".join(generated_source_lines).encode(source_charset["encoding"]))

    return 0

if __name__ == "__main__":
    main()
