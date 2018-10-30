#!/bin/bash
FILE="argue.sh"
RULES="../rules.h"
PROPS="properties.in"
GLUCOSE=""
c=$1
v=$2
OPT=$3

/bin/bash $FILE $RULES $PROPS $c $v $GLUCOSE $OPT
