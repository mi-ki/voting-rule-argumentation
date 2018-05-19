unsigned int SIMP_VOTES[V][C];
unsigned int SIMP_RESULT[C];
unsigned int V_SIMP;

unsigned int simplify(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int rep, unsigned int print, unsigned int negated, unsigned int blocking) {
    unsigned int simp[V];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int s = 0;
    for (i = 0; i < V; i++) {
        simp[i] = 0;
    }

    assume (1 < rep);
    assume (rep <= numVotes);

    unsigned int sub = numVotes / rep;
    assume (numVotes % rep == 0);
    unsigned int reps[sub];
    for (i = 0; i < sub; i++) {
        reps[i] = 0;
    }
    for (i = 0; i < numVotes; i++) {
        simp[i] = nondet_uint();
        assume (0 <= simp[i]);
        assume (simp[i] < sub);
        s = simp[i];
        reps[s]++;
        for (j = 0; j < numVotes; j++) {
            if (simp[i] == simp[j]) {
                for (k = 0; k < C; k++) {
                    if (votes[i][k] != votes[j][k] && !blocking) { return 0; }
                    assume (votes[i][k] == votes[j][k]);
                }
            }
        }
    }
    for (i = 0; i < sub; i++) {
        if (reps[i] != rep && !blocking) { return 0; }
        assume (reps[i] == rep);
    }

    unsigned int votes2[V][C];

    for (i = 0; i < numVotes; i++) {
        for (j = 0; j < C; j++) {
            s = simp[i];
            votes2[s][j] = votes[i][j];
        }
    }
    for (i = 0; i < sub; i++) {
        if (votes2[i][0] == 0 && !blocking) { return 0; }
        assume (votes2[i][0] != 0);
    }

    // FIXME: Beware that other properties may not be assumed for smaller ballot boxes due to fixed bounds
    struct result elect2 = voting2(votes2, sub);
    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        assume (negated || elect2.arr[i] == res[i]);
        if (elect2.arr[i] != res[i]) {
            exists = 1;
        }
    }
    assume (!negated || exists);

    if (print) {
        for (i = 0; i < sub; i++) {
            for (j = 0; j < C; j++) {
                SIMP_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = sub; i < V; i++) {
            for (j = 0; j < C; j++) {
                SIMP_VOTES[i][j] = votes2[i][j];
            }
        }
        for (i = 0; i < C; i++) {
            SIMP_RESULT[i] = elect2.arr[i];
        }
        V_SIMP = sub;
        return 1;
    }
    return 0;
}
