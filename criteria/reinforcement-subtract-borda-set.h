unsigned int REINF_SUB_A_VOTES[V][C];
unsigned int REINF_SUB_A_RESULT[C];
unsigned int V_REINF_SUB_A;
unsigned int REINF_SUB_B_VOTES[V][C];
unsigned int REINF_SUB_B_RESULT[C];
unsigned int V_REINF_SUB_B;

struct subsubset { unsigned int arr[V]; };

unsigned int reinforcementSubtractCheck(unsigned int votes[V][C], unsigned int res[C], struct subsubset sub, unsigned int sep, unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int s = 0;
    unsigned int taken[V];
    unsigned int rest[V - sep];
    for (i = 0; i < V; i++) {
        taken[i] = 0;
    }

    unsigned int votes1[V][C];
    for (i = 0; i < sep; i++) {
        s = sub.arr[i];
        taken[s] = 1;
        for (j = 0; j < C; j++) {
            votes1[i][j] = votes[s][j];
        }
    }
    for (i = sep; i < V; i++) {
        for (j = 0; j < C; j++) {
            votes1[i][j] = C;
        }
    }

    for (i = 0, j = 0; i < numVotes; i++) {
        if (taken[i] == 0) {
            rest[j] = i;
            j++;
        }
    }

    unsigned int votes2[V][C];
    for (i = 0; i < numVotes - sep; i++) {
        s = rest[i];
        for (j = 0; j < C; j++) {
            votes2[i][j] = votes[s][j];
        }
    }
    for (i = numVotes - sep; i < V; i++) {
        for (j = 0; j < C; j++) {
            votes2[i][j] = C;
        }
    }

    struct result elect = voting2(votes1, sep);
    unsigned int full = 1;
    for (i = 0; i < C; i++) {
        if (elect.arr[i] == 0) {
            full = 0;
        }
    }

    if (!full && !blocking) { return 0; }
    assume (full);

    struct result elect2 = voting2(votes2, numVotes - sep);

    unsigned int nonemptyOutcome = 0;
    for (i = 0; i < C; i++) {
        if (elect2.arr[i] != 0) {
            nonemptyOutcome = 1;
        }
    }
    if (!nonemptyOutcome && !blocking) { return 0; }
    assume (nonemptyOutcome);

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        assume (negated || res[i] == elect2.arr[i]);
        if (res[i] != elect2.arr[i]) {
            exists = 1;
        }
    }
    assume (!negated || exists);

    if (print) {
        for (i = 0; i < sep; i++) {
            for (j = 0; j < C; j++) {
                REINF_SUB_A_VOTES[i][j] = votes1[i][j];
            }
        }
        for (i = sep; i < V; i++) {
            for (j = 0; j < C; j++) {
                REINF_SUB_A_VOTES[i][j] = votes1[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            REINF_SUB_A_RESULT[i] = elect.arr[i];
        }
        V_REINF_SUB_A = sep;

        unsigned int diff = numVotes - sep;
        for (i = 0; i < diff; i++) {
            for (j = 0; j < C; j++) {
                REINF_SUB_B_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = diff; i < V; i++) {
            for (j = 0; j < C; j++) {
                REINF_SUB_B_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            REINF_SUB_B_RESULT[i] = elect2.arr[i];
        }
        V_REINF_SUB_B = diff;
        return 1;
    }
    return 0;
}

unsigned int reinforceSubRec(unsigned int votes[V][C], unsigned int res[C], struct subsubset sub,
                             unsigned int start, unsigned int end, unsigned int index,
                             unsigned int sep, unsigned int numVotes,
                             unsigned int print, unsigned int negated, unsigned int blocking) {
    unsigned int i = 0;

    unsigned int printNow = nondet_uint();
    assume (printNow == 0 || printNow == 1);
    unsigned int hasPrinted = 0;

    if (index == sep) {
        printNow = (printNow && print);
        assume (hasPrinted == 0 || printNow == 0);

        printNow = reinforcementSubtractCheck(votes, res, sub, sep, numVotes, printNow, negated, blocking);

        return (printNow || hasPrinted);
    }
    for (i = start; i <= end && sep - index <= end - i + 1; i++) {
        sub.arr[index] = i;

        printNow = nondet_uint();
        assume (printNow == 0 || printNow == 1);
        printNow = (printNow && print);
        assume (hasPrinted == 0 || printNow == 0);

        printNow = reinforceSubRec(votes, res, sub, i + 1, end, index + 1, sep, numVotes, printNow, negated, blocking);
        hasPrinted = (printNow || hasPrinted);
    }
    return hasPrinted;
}

unsigned int reinforcement_subtract(unsigned int votes[V][C], unsigned int res[C], unsigned int sep, unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int i = 0;
    unsigned int s = 0;
    struct subsubset sub;
    unsigned int taken[V];
    for (i = 0; i < V; i++) {
        taken[i] = 0;
    }

    if (negated) {
        for (i = 0; i < sep; i++) {
            s = nondet_uint();
            assume (0 <= s && s < sep);
            sub.arr[i] = s;
            assume (taken[s] == 0);
            taken[s] = 1;
        }
        print = reinforcementSubtractCheck(votes, res, sub, sep, numVotes, print, negated, blocking);
    } else {
        print = reinforceSubRec(votes, res, sub, 0, numVotes - 1, 0, sep, numVotes, print, negated, blocking);
    }
    return print;
}
