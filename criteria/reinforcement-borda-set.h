unsigned int REINF_A_VOTES[V][C];
unsigned int REINF_A_RESULT[C];
unsigned int V_REINF_A;
unsigned int REINF_B_VOTES[V][C];
unsigned int REINF_B_RESULT[C];
unsigned int V_REINF_B;

struct subset { unsigned int arr[V]; };

unsigned int reinforcementCheck(unsigned int votes[V][C], unsigned int res[C], struct subset sub, unsigned int sep, unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int s = 0;
    unsigned int taken[V];
    unsigned int rest[V];
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

    struct result elect1 = voting2(votes1, sep);
    struct result elect2 = voting2(votes2, numVotes - sep);

    unsigned int nonemptySubset = 0;
    for (i = 0; i < C; i++) {
        if (elect1.arr[i] == elect2.arr[i] && elect1.arr[i] != 0) {
            nonemptySubset = 1;
        }
    }
    if (!nonemptySubset && !blocking) { return 0; }
    assume (nonemptySubset);

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        if (elect1.arr[i] == elect2.arr[i]) {
            assume (negated || res[i] == elect1.arr[i]);
            if (res[i] != elect1.arr[i]) {
                exists = 1;
            }
        }
        if (elect1.arr[i] != elect2.arr[i]) {
            assume (negated || res[i] == 0);
            if (res[i] != 0) {
                exists = 1;
            }
        }
    }
    assume (!negated || exists);

    if (print) {
        for (i = 0; i < sep; i++) {
            for (j = 0; j < C; j++) {
                REINF_A_VOTES[i][j] = votes1[i][j];
            }
        }
        for (i = sep; i < V; i++) {
            for (j = 0; j < C; j++) {
                REINF_A_VOTES[i][j] = votes1[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            REINF_A_RESULT[i] = elect1.arr[i];
        }
        V_REINF_A = sep;

        unsigned int diff = numVotes - sep;
        for (i = 0; i < diff; i++) {
            for (j = 0; j < C; j++) {
                REINF_B_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = diff; i < V; i++) {
            for (j = 0; j < C; j++) {
                REINF_B_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            REINF_B_RESULT[i] = elect2.arr[i];
        }
        V_REINF_B = diff;
        return 1;
    }
    return 0;
}

unsigned int reinforceRec(unsigned int votes[V][C], unsigned int res[C], struct subset sub,
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

        printNow = reinforcementCheck(votes, res, sub, sep, numVotes, printNow, negated, blocking);

        return (printNow || hasPrinted);
    }
    for (i = start; i <= end && sep - index <= end - i + 1; i++) {
        sub.arr[index] = i;

        printNow = nondet_uint();
        assume (printNow == 0 || printNow == 1);
        printNow = (printNow && print);
        assume (hasPrinted == 0 || printNow == 0);

        printNow = reinforceRec(votes, res, sub, i + 1, end, index + 1, sep, numVotes, printNow, negated, blocking);
        hasPrinted = (printNow || hasPrinted);
    }
    return hasPrinted;
}

unsigned int reinforcement(unsigned int votes[V][C], unsigned int res[C], unsigned int sep, unsigned int numVotes, unsigned int print, unsigned int negated, unsigned int blocking) {
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int i = 0;
    unsigned int s = 0;
    struct subset sub;
    unsigned int taken[V];
    for (i = 0; i < V; i++) {
        taken[i] = 0;
    }

    for (i = 0; i < sep; i++) {
        s = nondet_uint();
        assume (0 <= s && s < sep);
        sub.arr[i] = s;
        assume (taken[s] == 0);
        taken[s] = 1;
    }
    print = reinforcementCheck(votes, res, sub, sep, numVotes, print, negated, blocking);
    return print;
}
