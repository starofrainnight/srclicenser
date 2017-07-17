# -*- coding: utf-8 -*-

#
# Copyright 2017, Hong-She Liang <starofrainnight@gmail.com>.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


'''
A series licensers use for handle how to insert or replace license
'''

import copy


class Licenser(object):
    '''
    The basic licenser class
    '''

    def __init__(self, source, from_license, to_license):
        self._source = source
        self._from_license = from_license
        self._to_license = to_license

    def _skip_header_block(self):
        '''
        All files could provide a shellscript comment at the beginning of file
        that indicate how to parse the file:

        @code{.sh}
        #!/bin/sh
        @codeend

        @return The line index after header block
        '''

        if ((len(self._source) > 0)
                and (self._source[0].strip().startswith("#!"))):
            return 1

        return 0

    def _find_next_block(self, index):
        '''
        Find the license block from line index

        @return Return index area may contained license :
        [line begin index, line end index). If there does not have next block,
        None will be return.
        '''

        begin_index = -1
        end_index = -1
        comment_mark = None

        # Find begin index
        while index < len(self._source):
            line = self._source[index].strip()
            for mark in self.comment_marks:
                if line.startswith(mark[0]):
                    begin_index = index
                    comment_mark = mark
                    break

            if comment_mark is not None:
                break

            index += 1

        # Find end index
        while index < len(self._source):
            line = self._source[index].strip()
            if len(comment_mark) >= 2:
                if line.startswith(comment_mark[1]):
                    end_index = index + 1
                    break
            else:
                if not line.startswith(comment_mark[0]):
                    end_index = index
                    break

            index += 1

        # If there have only have one line comment
        if (begin_index >= 0) and (end_index < 0) and (len(self._source) > 0):
            end_index = len(self._source)

        if (begin_index >= 0) and (end_index >= 0):
            return (begin_index, end_index)
        else:
            return None

    def _styled_license(self, license):
        '''
        Wrap license with specific language comment style
        '''

        out_license = []
        out_license.append(self.wrapper_marks[0])
        for line in license:
            line = self.wrapper_marks[1] % line
            out_license.append(line.strip())
        out_license.append(self.wrapper_marks[2])

        return out_license

    def _find_license_block(self, index):
        '''
        Find the license block from source

        @return Return index area may contained license :
        [line begin index, line end index). If there does not have next block,
        None will be return.
        '''

        block = (0, index)
        while True:
            block = self._find_next_block(block[1])
            if block is None:
                break

            begin_index, end_index = block

            # This block lines fewer than license we want to find, skip this
            # block
            if (end_index - begin_index) < len(self._from_license):
                continue

            for i in range(begin_index, end_index):

                # Try to compare with whole license from this line
                is_found_license = True
                compare_i = i
                for j in range(0, len(self._from_license)):
                    source_line = self._source[compare_i]
                    from_line = self._from_license[j]

                    if from_line not in source_line:
                        is_found_license = False
                        break

                    compare_i += 1

                if not is_found_license:
                    continue

                # Found license in this block
                return block

        return None

    def parse(self):
        '''
        Parse source replacement

        @return If there already have correct license, we return None.
        Otherwise source with target license will be return.
        '''

        parsed_source = copy.deepcopy(self._source)
        next_search_index = self._skip_header_block()
        block = self._find_license_block(next_search_index)
        if block is None:
            block = self._find_next_block(next_search_index)
            if (block is not None) and (block[0] <= next_search_index):
                next_search_index = block[1]

            styled_license = self._styled_license(self._to_license)
            parsed_source[next_search_index:next_search_index] = [""]
            next_search_index += 1
            parsed_source[next_search_index:next_search_index] = styled_license
            next_search_index += len(styled_license)
            parsed_source[next_search_index:next_search_index] = [""]
        elif self._from_license == self._to_license:
            # Though we found license, but the from license and to license is
            # the same, that means there already have the license we want to
            # insert!
            return None
        else:
            parsed_source[block[0]:block[1]] = (
                self._styled_license(self._to_license))

        return parsed_source


class CLicenser(Licenser):
    '''
    C Licenser
    '''

    tag = "c"
    wrapper_marks = ["/*", " * %s", " */"]
    comment_marks = [["/*", "*/"], ["//"]]

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


class CppLicenser(CLicenser):
    '''
    C++ Licenser
    '''

    tag = "cpp"
    wrapper_marks = ["//", "// %s", "//"]

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


class ShLicenser(Licenser):
    '''
    ShellScript Licenser
    '''

    tag = "sh"
    wrapper_marks = ["#", "# %s", "#"]
    comment_marks = [["#"]]

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


class PythonLicenser(Licenser):
    '''
    Python Licenser
    '''

    tag = "python"
    wrapper_marks = ["#", "# %s", "#"]
    comment_marks = [["#"]]

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


def get_licenser_classes():
    '''
    Get all licenser classes

    @return Return a dict contained licenser classes with their tags as key.
    '''

    import sys
    import inspect

    members = inspect.getmembers(
        sys.modules[__name__],
        lambda member: inspect.isclass(
            member) and member.__module__ == __name__
    )

    classes_dict = dict()
    for name, member in members:
        if not name.endswith("Licenser"):
            continue

        if name == "Licenser":
            continue

        classes_dict[member.tag] = member

    return classes_dict


def create_licenser(tag, *args, **kwargs):
    '''
    Create licenser by it's tag
    '''

    return get_licenser_classes()[tag](*args, **kwargs)
