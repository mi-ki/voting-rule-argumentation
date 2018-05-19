#!/bin/bash
OUTFILE="$1"
POSTFIX="$2"

cat $OUTFILE | grep 'V'"$POSTFIX" | sed -r 's/\([0-9]*\)//' | sed 's/l\]/\]/g' | sed 's/u\]/\]/g' | sed 's/l $//g' | sed 's/u $//g' | sed 's/\"\|=//g' | sed 's/V'"$POSTFIX"'//g' | tr -d ' '
