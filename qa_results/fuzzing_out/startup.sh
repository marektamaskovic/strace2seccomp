#! /usr/bin/bash

afl-fuzz -i inputFiles -o outputFiles -M fuzzer_master -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s01 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s02 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s03 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s04 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s05 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s06 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s07 -- ./st2se @@
afl-fuzz -i inputFiles -o outputFiles -S fuzzer_s08 -- ./st2se @@
