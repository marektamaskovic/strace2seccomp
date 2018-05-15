#! /usr/bin/env python3

import argparse
from subprocess import call

def prepare(args):
    print('prepare was emitted')
    call(['./prepare.sh'])

def generate(args):
    print('generate was emitted')

def customize(args):
    print('customize was emitted')

def makeBinaries(args):
    print('makeBinaries was emitted')

def test(args):
    print('test was emitted')

def main():
    parser = argparse.ArgumentParser(prog='test_config')

    subparser = parser.add_subparsers(help='subparsers help')

    parser_prepare = subparser.add_parser('prepare')
    parser_prepare.set_defaults(func=prepare)

    parser_generate = subparser.add_parser('generate')
    parser_generate.set_defaults(func=generate)

    parser_customize = subparser.add_parser('customize')
    parser_customize.set_defaults(func=customize)

    parser_makeBinaries = subparser.add_parser('makeBinaries')
    parser_makeBinaries.set_defaults(func=makeBinaries)

    parser_test = subparser.add_parser('test')
    parser_test.set_defaults(func=test)

    args = parser.parse_args()
    args.func(args)

if __name__ == '__main__':
    main()
