# strace2seccomp - Bachelor thesis



## About
This bachelor thesis is focused on an automatic generation of seccomp rules from
strace logs. The output is generated in C/C++ syntax. Input can be optimized
with three optimization algorithms. One is called strict, and it will produce
1:1 output compared to input. Another one is called minimax or weak. This
algorithm will provide on the output only extremes as border values for
allowance interval.  The last one is called advanced which implements DBSCAN
algorithm for clustering. The thesis can be found in another
[branch](./blob/thesis/testsuite/)

## Usage

	Usage:
		st2se [OPTION] filename ...

	Generic options:
	    -h [--help]								: print this message
	    -v [--verbose]						: turn on verbose mode
	    -d [--debug]							: turn on debug mode
	    -t [--tracing]						: turn on debug mode
	    -A [--analyze-grammar]		: analyze grammar
	    -o FILE [--output=FILE]	: set output file

	Configuration options:
	    -w [--weak]								: use weak algotirthm
	    -s [--strict]							: use strict algotirthm
	    -a [--advanaced]					: use advanced algotirthm
	    --prolog										: generate function prolog
	    --thread										: add filter synchronization among threads/processes

## Examples

	./st2se -v -w --output=source.cpp filename1 filename2

In this case, we can see that verbose mode is turned on and minimax algorithm
was chosen for the optimizer. The output of the program will be stored in
`source.cpp`. Files `filename1` and `filename2` will be used as input.

	./st2se -w --output=source.cpp filename --thread --prolog

This command diverges only in the output format. The `--thread` will generate
support for multithread or multiprocess applications and `--prolog` switch
ensures that the filter will be located in function. This behavior is helpful
for copy&paste output into an existing program.

	./st2se -A

When we want to check if the grammar in the parser is correct, we can use a
built-in tool in parser library. This tool of the parser can be turned on with
switch `-A`. On standard output will be printed number of found issues.

## Testing
Information about testsuite and how to run tests is located
[here](./blob/source/testsuite/README.md)

## Possible extensions
- Go language support
- implement other algorithms
