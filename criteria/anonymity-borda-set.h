unsigned int ANON_VOTES[V][C];
unsigned int ANON_RESULT[C];
unsigned int V_ANON;

unsigned int anonymityCheck(unsigned int votes1[V][C], unsigned int res[C], unsigned int votes2[V][C], unsigned int perm[V], unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < numVotes; i++) {
        for (j = 0; j < C; j++) {
            assume (votes1[i][j] == votes2[perm[i]][j]);
        }
    }

    struct result elect2 = voting2(votes2, numVotes);

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        if (res[i] != elect2.arr[i]) {
            exists = 1;
        }
        assume (negated || !exists);
    }
    assume (!negated || exists);

    if (print) {
        for (i = 0; i < numVotes; i++) {
            for (j = 0; j < C; j++) {
                ANON_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = numVotes; i < V; i++) {
            for (j = 0; j < C; j++) {
                ANON_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            ANON_RESULT[i] = elect2.arr[i];
        }
        V_ANON = numVotes;
        return 1;
    }
    return 0;
}

unsigned int anonRec(unsigned int votes1[V][C], unsigned int res[C],
                     unsigned int votes2[V][C], unsigned int perm[V],
                     unsigned int index, unsigned int numVotes,
                     unsigned int print, unsigned int negated,
                     unsigned int blocking) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int exists = 0;
    unsigned int descend = 1;

    unsigned int printNow = nondet_uint();
    assume (printNow == 0 || printNow == 1);
    unsigned int hasPrinted = 0;

    if (index == numVotes) {
        for (i = numVotes; i < V; i++) {
            perm[i] = 0;
        }
        exists = 0;
        for (i = 0; i < numVotes; i++) {
            exists = (exists || (perm[i] != i));

            for (j = 0; j < numVotes; j++) {
                if (i != j && perm[i] == perm[j]) {
                    descend = 0;
                }
            }
            for (j = 0; j < C && descend; j++) {
                votes2[perm[i]][j] = votes1[i][j];
            }
        }

        printNow = (printNow && print);
        assume (hasPrinted == 0 || printNow == 0);

        if (exists && descend) {
            printNow = anonymityCheck(votes1, res, votes2, perm, numVotes, printNow, negated, blocking);
        } else {
            printNow = 0;
        }

        return (printNow || hasPrinted);
    }
    for (i = 0; i < numVotes; i++) {
        descend = 1;
        perm[index] = i;
        for (j = 0; j < index; j++) {
            if (perm[index] == perm[j]) {
                descend = 0;
            }
        }

        printNow = nondet_uint();
        assume (printNow == 0 || printNow == 1);
        printNow = (printNow && print);
        assume (hasPrinted == 0 || printNow == 0);

        if (descend) {
            printNow = anonRec(votes1, res, votes2, perm, index + 1, numVotes, printNow, negated, blocking);
        } else {
            printNow = 0;
        }
        hasPrinted = (printNow || hasPrinted);
    }
    return hasPrinted;
}

unsigned int anonymity(unsigned int votes1[V][C], unsigned int res[C], unsigned int votes2[V][C], unsigned int perm[V], unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    if (negated) {
        print = anonymityCheck(votes1, res, votes2, perm, numVotes, print, negated, blocking);
    } else {
        print = anonRec(votes1, res, votes2, perm, 0, numVotes, print, negated, blocking);
    }
    return print;
}
