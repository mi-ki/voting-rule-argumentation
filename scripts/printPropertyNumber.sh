#!/bin/bash
PROPS="$1"
STRING="$2"


TMP=`cat $PROPS`

if [[ $STRING == "CANC" ]]
then
    TMP=`cat $PROPS  | grep -v "SYMCANC"`
fi
if [[ $STRING == "REINF" ]]
then
    TMP=`cat $PROPS  | grep -v "REINF\_SUB"`
fi


TMP=`cat $PROPS | grep "$STRING   " | sed 's/.*\(.\)/\1/' | sed -r 's/Y/1/' | sed -r 's/N/-1/'`
if [[ $TMP != "1" ]] && [[ $TMP != "-1" ]] && [[ $TMP != "0" ]]
then
    TMP=0
fi

if [[ $STRING == "NO\_BLOCKING" ]]
then
    TMP==`cat $PROPS | grep "$STRING   " | sed 's/.*\(.\)/\1/' | sed -r 's/Y/-1/' | sed -r 's/N/0/'`
    if [[ $TMP == "" ]] || (( "$TMP" < "0" )) || (( "13" < "$TMP" ))
    then
        TMP=-1
    fi
fi

echo -e $TMP
