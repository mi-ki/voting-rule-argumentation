void consistency(unsigned int votes[V][C], unsigned int numVotes) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int sep = nondet_uint();
    assume (0 < sep && sep < numVotes);

    unsigned int votes1[V][C];
    for (i = 0; i < sep; i++) {
        for (j = 0; j < C; j++) {
            votes1[i][j] = votes[i][j];
        }
    }
    for (i = sep; i < V; i++) {
        for (j = 0; j < C; j++) {
            votes1[i][j] = C;
        }
    }

    unsigned int votes2[V][C];
    for (i = sep; i < numVotes; i++) {
        for (j = 0; j < C; j++) {
            votes2[i - sep][j] = votes[i][j];
        }
    }
    for (i = numVotes; i < V; i++) {
        for (j = 0; j < C; j++) {
            votes2[i][j] = C;
        }
    }

    struct result elect1 = voting2(votes1, sep);
    struct result elect2 = voting2(votes2, numVotes - sep);

    unsigned int intersection[C];
    unsigned int nonempty = 0;
    for (i = 0; i < C; i++) {
        if (elect1.arr[i] == 1 && elect1.arr[i] == elect2.arr[i]) {
            intersection[i] = 1;
            nonempty = 1;
        } else {
            intersection[i] = 0;
        }
    }

    if (nonempty == 1) {
        struct result elect = voting2(votes, numVotes);
        for (i = 0; i < C; i++) {
            assume (elect.arr[i] == intersection[i]);
        }
    }
}
