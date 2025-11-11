#!/usr/bin/env python3
#
# Determine info about the Python install and write shell code to stdout, to
# set env variables.  This will set the variables PY_LDFLAGS, PY_CFLAGS and
# PY_INC_PATH.
#
# The python3-config tool is used as the source of this info. In theory we
# could use sysconfig as well but the setup-python action from github appears
# to patch python3-config but not patch the sysconfig info.
#
# Usage:
#   eval $(python3 get-py-env.py)

import os
import re
import subprocess


def get_output(cmd):
    rv = subprocess.run(
        cmd,
        capture_output=True,  # Capture stdout and stderr
        text=True,  # Decode output as text (UTF-8)
        check=True,  # Raise an error if the command fails
    )
    return rv.stdout


def extract_flags(cmd, prefix):
    flags = []
    for part in get_output(cmd).split():
        part = part.strip()
        if part.startswith(prefix):
            flags.append(part)
    return ' '.join(flags)


def find_python_h():
    """Find the include path that has Python.h contained inside.
    We could use INCLUDEPY from sysconfig but github patches
    python3-config but not the sysconfig info (after moving the
    install).
    """
    c_flags = extract_flags(['python3-config', '--cflags'], '-I')
    for part in c_flags.split():
        m = re.search(r'-I(\S+)', part)
        if not m:
            continue
        inc_path = m.group(1)
        if os.path.exists(os.path.join(inc_path, 'Python.h')):
            return inc_path
    raise SystemExit('cannot find Python.h')


def main():
    ld_flags = extract_flags(['python3-config', '--ldflags'], '-L')
    c_flags = extract_flags(['python3-config', '--cflags'], '-I')
    include_path = find_python_h()
    print(f'PY_LDFLAGS="{ld_flags}"')
    print(f'PY_CFLAGS="{c_flags}"')
    print(f'PY_INC_PATH="{include_path}"')


if __name__ == '__main__':
    main()
