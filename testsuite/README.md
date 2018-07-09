# ﻿Testing information


__--> This page is under development <--__

Here are located information about testing, how to test st2se and how to get testsuite.

## Sources of binaries used in testing

_Used sources are from official project pages and repositories._

| Package   | Target binary | Sources |
| --------- | ------------- |:-------:|
| coreutils | `cp`    | [_source_](https://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz)            |
| findutils | `find`        | [_source_](https://ftp.gnu.org/pub/gnu/findutils/findutils-4.6.0.tar.gz)       |
| usbguard  | `usbguard`    | [_source_](https://github.com/USBGuard/usbguard/archive/usbguard-0.7.2.tar.gz) |
| testovac | `testovac` | [_source_](https://github.com/tammar96/ISA-testovac/releases/download/untagged-7d8ed3a74b854254df64/testovac.tar) |

## `./setEnv.sh`
`./setEnv.sh` is a script which will setup environment for testing. It is simple bash script controlled with subcommands.

![alt text][architecture]
[architecture]: https://github.com/tammar96/IBP/raw/source_dev/testsuite/resources/architecture.png "Architecture of ./setEnv.sh"

## Script subcommands

- `$ ./setEnv help` - print this help
- `$ ./setEnv prep` - downloads, extracts and configures sources
- ~~`$ ./setEnv applyPolicy`~~ - generates strace, runs st2se, patch sources __NOT WORKING__
- `$ ./setEnv make` - make binaries
- `$ ./setEnv test` - run tests
- `$ ./setEnv clean` - removes downloaded packages and temporary files
- `$ ./setEnv revertPatches` - revert previously applied patches
- `$ ./setEnv straceON` - turn on strace logging
- `$ ./setEnv straceOFF` - turn off strace logging
