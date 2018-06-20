# ﻿Testing information


__! This page is under development !__

Here are located information about testing, how to test st2se and how to get testsuite.

## Sources of binaries used in testing

_Used sources are from official project pages and repositories._

| Package   | Target binary | Sources |
| --------- | ------------- |:-------:|
| findutils | `find`        | [_source_](https://ftp.gnu.org/pub/gnu/findutils/findutils-4.6.0.tar.gz)       |
| coreutils | `cp`, `rm`    | [_source_](https://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz)            |
| usbguard  | `usbguard`    | [_source_](https://github.com/USBGuard/usbguard/archive/usbguard-0.7.2.tar.gz) |

## Script subcommands

- `$ ./setEnv help` - print this help
- `$ ./setEnv prep` - downloads, extracts and configures sources
- `$ ./setEnv applyPolicy` - generates strace, runs st2se, patch sources
- `$ ./setEnv make` - make binaries
- `$ ./setEnv test` - run tests
- `$ ./setEnv clean` - removes downloaded packages and temporary files
- `$ ./setEnv revertPatches` - revert previously applied patches
