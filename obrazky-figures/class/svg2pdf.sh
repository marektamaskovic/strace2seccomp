#! /bin/bash

EXEC='algo'
HIGH='arg_sc'
LOW='params'
OPTI='optimizer'

rsvg-convert -f pdf "$EXEC.svg" -o "$EXEC.pdf"
rsvg-convert -f pdf "$HIGH.svg" -o "$HIGH.pdf"
rsvg-convert -f pdf "$LOW.svg"  -o "$LOW.pdf"
#rsvg-convert -f pdf "$OPTI.svg" -o "$OPTI.pdf"

#ps2pdf -i "$EXEC.pdf" -o "$EXEC.pdf"
#ps2pdf -i "$HIGH.pdf" -o "$HIGH.pdf"
#ps2pdf -i "$LOW.pdf" -o "$LOW.pdf"
