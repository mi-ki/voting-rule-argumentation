#!/bin/bash
TIMESTAMP="# Timestamp: "$(date +'%Y-%m-%d %H:%M:%S %Z')
CBMC='./backends/cbmc'
VERSION="# CBMC Version: "$($CBMC -version)
FILE="arguing.c"


RULES=$1
PROPS=$2
c=$3
v=$4
GLUCOSE=$5
OPT=$6
OPTS=''
while [ -n "$6" ]
do
    OPTS=$OPTS" ${6}" && shift;
done


cntOpts=`echo -e "$OPTS" | grep -o - | wc -l`
cntOpts=$(($cntOpts / 2))
if [[ $GLUCOSE != "" ]]
then
    cntOpts=$(($cntOpts + 1))
fi
if [[ $cntOpts != "" ]] && (( "1" < "$cntOpts" ))
then
    cntOpts="s"
else
    cntOpts=""
fi
if [ -n "$OPTS" ]
then
    printOpts=`echo -e "?$OPTS" | sed -e 's/?\s--//g'`
    if [[ $GLUCOSE != "" ]]
    then
        printOpts=`echo -e " --$printOpts"`
    fi
fi
printOptsGl="$printOpts"
if [[ $GLUCOSE != "" ]]
then
    printOptsGl="glucose$printOpts"
fi
if [ -n "$OPTS" ] || [[ $GLUCOSE != "" ]]
then
    printOpts=`echo -e "$printOptsGl" | sed 's/\s\(.*\)--/\1 and /' | sed 's/--/, /g'`
    PRINT_OPTS=`echo -e "$printOpts" | sed -e 's/and/,/g' | sed 's/[[:space:]]*,/,/g'`
    printOpts=`echo -e "$printOpts" | sed 's/./\U&/g' | sed 's/ AND / and /g'`
    OPT_OUT=" with the option"$cntOpts" "$printOpts
else
    OPT_OUT=''
fi
if [ -n "$OPTS" ] || [[ $GLUCOSE != "" ]]
then
    OPTIONS='\n'"# Further Options: "$PRINT_OPTS
else
    OPTIONS=''
fi


if [[ $FILE == "" ]]
then
    echo -e "No file specified. Now terminating."
    exit
fi
if [[ $RULES == "" ]]
then
    echo -e "No voting rules specified. Now terminating."
    exit
fi
if [[ $PROPS == "" ]]
then
    echo -e "No properties specified. Now terminating."
    exit
fi
if [[ $c == "" ]] || (( "$c" <= "0" ))
then
    echo -e "No valid candidate number specified. Now terminating."
    exit
fi
if [[ $v == "" ]] || (( "$v" <= "0" ))
then
    echo -e "No valid voter number specified. Now terminating."
    exit
fi
if [ ${FILE: -2} == ".c" ]
then
    FILE="${FILE%%.*}"
fi
F=$FILE.c
if [ ! -f $F ]
then
    echo -e $F" is not a valid file. Now terminating."
    exit
fi


OUTFILE="$FILE.out"


DOM=`./scripts/printPropertyNumber.sh $PROPS "DOM"`
ANON=`./scripts/printPropertyNumber.sh $PROPS "ANON"`
COND=`./scripts/printPropertyNumber.sh $PROPS "COND"`
SYMCANC=`./scripts/printPropertyNumber.sh $PROPS "SYMCANC"`
FVSC=`./scripts/printPropertyNumber.sh $PROPS "FVSC"`
ELEM=`./scripts/printPropertyNumber.sh $PROPS "ELEM"`
CYCL=`./scripts/printPropertyNumber.sh $PROPS "CYCL"`
CANC=`./scripts/printPropertyNumber.sh $PROPS "CANC"`
REINF=`./scripts/printPropertyNumber.sh $PROPS "REINF"`
REINF_SUB=`./scripts/printPropertyNumber.sh $PROPS "REINF_SUB"`
SIMP=`./scripts/printPropertyNumber.sh $PROPS "SIMP"`
MAJ=`./scripts/printPropertyNumber.sh $PROPS "MAJ"`
WEAK_MAJO=`./scripts/printPropertyNumber.sh $PROPS "WEAK_MAJO"`
NO_BLOCKING=`./scripts/printPropertyNumber.sh $PROPS "NO_BLOCKING"`

BLOCK_STRING="-D NO_BLOCKING="$NO_BLOCKING

PROP_STRING="-D DOM="$DOM" -D ANON="$ANON" -D COND="$COND" -D SYMCANC="$SYMCANC" -D FVSC="$FVSC" -D ELEM="$ELEM" -D CYCL="$CYCL" -D CANC="$CANC" -D REINF="$REINF" -D REINF_SUB="$REINF_SUB" -D SIMP="$SIMP" -D MAJ="$MAJ" -D WEAK_MAJO="$WEAK_MAJO


unw=$(( $c < $v ? $v : $c ))
unw=$(( $unw * $unw ))
BOUNDS="-D C="$c" -D V="$v" --unwind "$(( $unw + 2 ))
rule=""
if [[ $RULES == "borda.h" ]]
then
    rule="BORDA"
fi
if [[ $RULES == "black.h" ]]
then
    rule="BLACK"
fi
if [[ $RULES == "copeland.h" ]]
then
    rule="COPELAND"
fi
RULES='"'"$RULES"'"'
RULES="-D RULES="$RULES
p=`./scripts/printProperties.sh "$PROP_STRING" | sed 's/^[ \t]*//;s/[ \t]*$//' | sed 's/ /, /g'`


echo -e "Starting verification for "$c" candidates and "$v" voters"'\n'"for the property/-ies "$p$OPT_OUT"."'\n''\n'"This might take a while ..."
start=$(date +%s.%3N)
timeout 30m $CBMC --trace $RULES $BOUNDS $PROP_STRING $BLOCK_STRING $OPTS $FILE.c &> $OUTFILE
end=$(date +%s.%3N)
echo -e "... VERIFICATION FINISHED!"


if [[ $rule == "" ]]
then
    rule=`tac $OUTFILE | grep " RULE\[" | head -n 1 | sed 's/" ([0-9]*)//' | sed 's/  RULE\[0l\]="//'`
fi
var=`cat $OUTFILE | grep " variables" | head -n 1 | sed -r 's/([0-9]*) variables, ([0-9]*) clauses/\1/'`
cla=`cat $OUTFILE | grep " clauses" | head -n 1 | sed -r 's/([0-9]*) variables, ([0-9]*) clauses/\2/'`
variables=''
if [ "$var" != "" ]
then
    variables=", Variables: "$var
else
    variables=""
fi
clauses=''
if [ "$cla" != "" ]
then
    clauses=", Clauses: "$cla
else
    clauses=""
fi
sec=`cat $OUTFILE | grep 'Runtime decision procedure:' | tail -n 1 | sed -r 's/^.* ([0-9]*.[0-9]*)s*$/\1/' | sed -r 's/s//'`
sec2=$(echo "$end - $start" | bc)
if [[ $sec2 == .* ]]
then
    sec2="0"$sec2
fi
succ=`cat $OUTFILE | grep "VERIFICATION SUCCESSFUL" | sed -r 's/UCCESSFUL//' | sed -r 's/VERIFICATION //'`
err=`cat $OUTFILE | grep "VERIFICATION FAILED" | sed -r 's/RIFICATION FAILED//' | sed -r 's/V//'`
echo -e '\n'"############################################################"
echo -e $TIMESTAMP'\n'$VERSION$OPTIONS
echo -e "############################################################"
echo -e '\n'"############################################################"
echo -e "Candidates: "$c", Voters: "$v
echo -e "Time: "$sec2" seconds"$variables$clauses'\n'


if [ "$err" == "" ]
then
    if [ "$succ" == "" ]
    then
        echo -e "VERIFICATION TIMED OUT."
    else
        echo -e "PROPERTIES FOUND TO BE INCONSISTENT FOR GIVEN BOUNDS."
    fi
    if [ "$rule" != "" ]
    then
        echo -e '\n'"Voting Rule: "$rule
    fi
    ./scripts/printProperties.sh '\n'"Checked Properties: $PROP_STRING "
    echo -e ""
else
    echo -e "PROPERTIES SATISFIABLE FOR GIVEN BOUNDS."
    if [ "$rule" != "" ]
    then
        echo -e '\n'"Voting Rule: "$rule
    fi
    ./scripts/printProperties.sh '\n'"Satisfied Properties: $PROP_STRING "
    echo -e '\n'"EXAMPLE:"'\n'"Input is given as ranked ballots and output as a set of"
    echo -e "all elected candidates (here denoted as YES). Candidates"
    echo -e "and voters have small or capital letters respectively."'\n'
    echo -e "==========================================="
    echo -e "===================VOTES==================="
    echo -e "==========================================="
    ./scripts/printVotes.sh $OUTFILE $c $v

    if [[ $ANON == "1" ]] || [[ $ANON == "-1" ]]
    then
        echo -e ''
        echo -e "============VOTES FOR ANONYMITY============"
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_ANON'`
        ./scripts/printVotes.sh $OUTFILE $c $v_prop 'ANON_'
    fi
    if [[ $REINF == "1" ]] || [[ $REINF == "-1" ]]
    then
        echo -e ''
        echo -e "==========VOTES FOR REINFORCEMENT=========="
        echo -e "-----FIRST PROFILE-----"
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_REINF_A'`
        ./scripts/printVotes.sh $OUTFILE $c $v_prop 'REINF_A_'

        echo -e "----SECOND PROFILE----"
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_REINF_B'`
        ./scripts/printVotes.sh $OUTFILE $c $v_prop 'REINF_B_'
    fi
    if [[ $REINF_SUB == "1" ]] || [[ $REINF_SUB == "-1" ]]
    then
        echo -e ''
        echo -e "====VOTES FOR REINFORCEMENT SUBTRACTION===="
        echo -e "-----FIRST PROFILE-----"
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_REINF_SUB_A'`
        ./scripts/printVotes.sh $OUTFILE $c $v_prop 'REINF_SUB_A_'

        echo -e "----SECOND PROFILE----"
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_REINF_SUB_B'`
        ./scripts/printVotes.sh $OUTFILE $c $v_prop 'REINF_SUB_B_'
    fi
    if [[ $SIMP == "1" ]] || [[ $SIMP == "-1" ]]
    then
        echo -e ''
        echo -e "=============VOTES FOR SIMPLIFY============="
        v_prop=`./scripts/printVoteNumber.sh $OUTFILE '_SIMP'`
        if [ "$v_prop" != "" ]
        then
            ./scripts/printVotes.sh $OUTFILE $c $v_prop 'SIMP_'
        fi
    fi


    echo -e ''
    echo -e "==========================================="
    echo -e "==============ELECTION RESULT=============="
    echo -e "==========================================="
    ./scripts/printResult.sh $OUTFILE $c

    if [[ $ANON == "1" ]] || [[ $ANON == "-1" ]]
    then
        echo -e ''
        echo -e "============RESULT FOR ANONYMITY============"
        ./scripts/printResult.sh $OUTFILE $c "ANON_"
    fi
    if [[ $REINF == "1" ]] || [[ $REINF == "-1" ]]
    then
        echo -e ''
        echo -e "=========RESULTS FOR REINFORCEMENT========="
        echo -e "------FIRST RESULT------"
        ./scripts/printResult.sh $OUTFILE $c "REINF_A_"
        echo -e ''
        echo -e "-----SECOND RESULT-----"
        ./scripts/printResult.sh $OUTFILE $c "REINF_B_"
    fi
    if [[ $REINF_SUB == "1" ]] || [[ $REINF_SUB == "-1" ]]
    then
        echo -e ''
        echo -e "=RESULTS FOR REINFORCEMENT SUBTRACTION="
        echo -e "------FIRST RESULT------"
        ./scripts/printResult.sh $OUTFILE $c "REINF_SUB_A_"
        echo -e ''
        echo -e "-----SECOND RESULT-----"
        ./scripts/printResult.sh $OUTFILE $c "REINF_SUB_B_"
    fi
    if [[ $SIMP == "1" ]] || [[ $SIMP == "-1" ]]
    then
        echo -e ''
        echo -e "============RESULT FOR SIMPLIFY============"
        ./scripts/printResult.sh $OUTFILE $c "SIMP_"
    fi

    echo -e ''
fi
echo -e "############################################################"
#cat $OUTFILE
rm $OUTFILE
