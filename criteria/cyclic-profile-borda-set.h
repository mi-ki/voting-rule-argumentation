void cyclic_profile(unsigned int votes1[V][C], unsigned int res[C], unsigned int cycle[C+1], unsigned int numVotes, unsigned int negated, unsigned int blocking) { // cyclic profile criterion
    assume (numVotes == C);
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int exists = 0;
    unsigned int cnt = 0;
    unsigned int start[V];
    for (i = 0; i < V; i++) {
        start[i] = 0;
    }

    for (i = 0; i < C; i++) {
        exists = 0;
        for (j = 0; j < numVotes; j++) {
            if (cycle[i] == votes1[j][0]) {
                exists = 1;
                start[j] = i;
            }
        }
        if (!exists && !blocking) { return; }
        assume (exists);
    }

    for (i = 0; i < numVotes; i++) {
        j = start[i];
        assume (votes1[i][0] == cycle[j]); // This should always hold
        for (cnt = 0; cnt < C; cnt++) {
            if (votes1[i][cnt] != cycle[j] && !blocking) { return; }
            assume (votes1[i][cnt] == cycle[j]);
            j = (j < C-1) ? (j+1) : 0;
        }
    }

    exists = 0;
    for (i = 0; i < C; i++) {
        assume (negated || res[i] == 1);
        if (res[i] != 1) {
            exists = 1;
        }
    }
    assume (!negated || exists);
}
