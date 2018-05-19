#!/bin/bash
STRING="$1"

echo -e " "$STRING" " | sed 's/-D //g' | sed 's/DOM=0 //g' | sed 's/ANON=0 //g' | sed 's/COND=0 //g' | sed 's/SYMCANC=0 //g' | sed 's/FVSC=0 //g' | sed 's/ELEM=0 //g' | sed 's/CYCL=0 //g' | sed 's/CANC=0 //g' | sed 's/REINF=0 //g' | sed 's/REINF_SUB=0 //g' | sed 's/SIMP=0 //g' | sed 's/MAJ=0 //g' | sed 's/WEAK_MAJO=0 //g' | sed 's/=1 / /g' | sed 's/=1/ /g' | sed 's/DOM=-1/!DOM/g' | sed 's/ANON=-1/!ANON/g' | sed 's/COND=-1/!COND/g' | sed 's/SYMCANC=-1/!SYMCANC/g' | sed 's/FVSC=-1/!FVSC/g' | sed 's/ELEM=-1/!ELEM/g' | sed 's/CYCL=-1/!CYCL/g' | sed 's/CANC=-1/!CANC/g' | sed 's/REINF=-1/!REINF/g' | sed 's/REINF_SUB=-1/!REINF_SUB/g' | sed 's/SIMP=-1/!SIMP/g' | sed 's/MAJ=-1/!MAJ/g' | sed 's/WEAK_MAJO=-1/!WEAK_MAJO/g' | sed 's/FVSC/FvsC/g'
