#!/usr/bin/env python
# -*- coding: utf-8 -*-

from setuptools import setup

with open('README.rst') as readme_file, open('HISTORY.rst') as history_file:
    long_description = (readme_file.read() + "\n\n" + history_file.read())

requirements = [
    'Click>=6.0',
    'chardet',
]

test_requirements = [
    # TODO: put package test requirements here
]

setup(
    name='srclicenser',
    version='0.2.1',
    description="A tool that make sure there have a license header at top of "
                "source files",
    long_description=long_description,
    author="Hong-She Liang",
    author_email='starofrainnight@gmail.com',
    url='https://github.com/starofrainnight/srclicenser',
    packages=[
        'srclicenser',
    ],
    package_dir={'srclicenser':
                 'srclicenser'},
    entry_points={
        'console_scripts': [
            'srclicenser=srclicenser.__main__:main'
        ]
    },
    include_package_data=True,
    install_requires=requirements,
    license="MIT License",
    zip_safe=False,
    keywords='srclicenser',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Natural Language :: English',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
    ],
    test_suite='tests',
    tests_require=test_requirements
)
