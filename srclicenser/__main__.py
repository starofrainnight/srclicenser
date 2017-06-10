#!/usr/bin/env python
# -*- coding: utf-8 -*-

import click
import pathlib
import chardet
import logging
import shutil
from .import licensers


def load_file(file_path):
    with open(file_path, "rb") as f:
        content = f.read()

    # Detect original charset
    charset = chardet.detect(content)
    if charset["encoding"] == "gb2312":
        charset["encoding"] = "gbk"

    lines = []
    if charset["encoding"] is not None:
        content = content.decode(charset["encoding"])
        lines = content.splitlines()

    return (lines, charset)


@click.command()
@click.argument('target')
@click.option('--license', default=None,
              help='The license file we want to insert.')
@click.option('--style', default="cpp",
              help='Which comment style apply to sources, defult to "cpp"')
def main(target, license, style):
    """
    Program that replace license inside source files.

    TARGET: The specific source file needs to be parse
    """

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

    if len(source_lines) <= 0:
        logging.warn(
            "Source file does not have any content : \"%s\" !" % source_file_path)
        return 0

    licenser = licensers.create_licenser(
        style, source_lines, license_lines, license_lines)

    parsed_source_lines = licenser.parse()

    if parsed_source_lines is not None:
        # Output generated file with original encodings

        parsed_source_content = "\n".join(parsed_source_lines)

        # Before write to specific file, we backup it first
        shutil.copyfile(source_file_path, "%s.bak" % source_file_path)

        try:
            with open(source_file_path, "wb") as f:
                f.write(parsed_source_content.encode(
                    source_charset["encoding"]))
        except:
            # If any exception happened, we restore old backup
            shutil.copyfile("%s.bak" % source_file_path, source_file_path)
            raise

    return 0

if __name__ == "__main__":
    main()
