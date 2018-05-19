void symmetric_cancellation(unsigned int votes1[V][C], unsigned int res[C], unsigned int numVotes, unsigned int negated, unsigned int blocking) { // symmetric cancellation criterion
    assume (numVotes % 2 == 0);
    unsigned int counted[V];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    for (k = 0; k < V; k++) {
        counted[k] = 0;
    }

    for (i = 0; i < numVotes; i++) {
        k = nondet_uint();
        assume (0 <= k && k < numVotes);
        assume (k != i);
        assume (counted[k] == 0);
        counted[k] = 1;
        for (j = 0; j < C; j++) {
            if (votes1[i][j] != votes1[k][C-j-1] && !blocking) { return; }
            assume (votes1[i][j] == votes1[k][C-j-1]);
        }
    }

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        assume (negated || res[i] == 1);
        if (res[i] != 1) {
            exists = 1;
        }
    }
    assume (!negated || exists);
}
