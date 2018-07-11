#! /bin/bash

EXEC='exec_speed'
HIGH='high_freq'
LOW='low_freq'

rsvg-convert -f pdf "$1/$EXEC.svg" -o "$1/$EXEC.pdf"
rsvg-convert -f pdf "$1/$HIGH.svg" -o "$1/$HIGH.pdf"
rsvg-convert -f pdf "$1/$LOW.svg"  -o "$1/$LOW.pdf"
