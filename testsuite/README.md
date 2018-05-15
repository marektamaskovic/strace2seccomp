Testing information
===================
Here are located information about testing, how to test st2se and how to get testsuite.

Sources of binaries used in testing
-----------------------------------

_Used sources are from official project pages and repositories._

| Package | Target binary | Sources |
| ------- | ------------- |:-------:|
| findutils | `find` | [_source_](https://ftp.gnu.org/pub/gnu/findutils/findutils-4.6.0.tar.gz) |
| coreutils | `cp` | [_source_](https://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz) |
| usbguard  | `usbguard` | [_source_](https://github.com/USBGuard/usbguard/archive/usbguard-0.7.2.tar.gz) |

Script subcommands
------------------

- `./setEnv prep` - downloads, extracts and configures sources
- __TODO__ `./setEnv applyPolicy` - generates strace, runs st2se, patch sources
- `./setEnv make` - make binaries
- __TODO__ `./setEnv test` - run tests
