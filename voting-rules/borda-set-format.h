struct result voting(unsigned int votes[V][C]) {
    RULE[0] = "NONE";
    struct result r;
    unsigned int tmp[C];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    for (i = 0; i < V; i++) {
        for (k = 0; k < C; k++) {
            tmp[k] = 0;
        }
        for (j = 0; j < C; j++) {
            assume (0 <= votes[i][j]);
            assume (votes[i][j] <= C);
            for (k = 0; k < C; k++) {
                if (votes[i][j] == k) {
                    assume (tmp[k] == 0);
                    tmp[k] = 1;
                }
            }
        }
        assume (votes[i][0] < C);
    }
    for (i = 0; i < C; i++) {
        r.arr[i] = 0;
    }
    r = election_function(votes);

    for (i = 0; i < C; i++) {
        assume (0 <= r.arr[i]);
        assume (r.arr[i] <= 1);
    }

    return r;
}

struct result voting2(unsigned int votes[V][C], unsigned int numVotes) {
    RULE[0] = "NONE";
    struct result r;
    unsigned int tmp[C];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    for (i = 0; i < numVotes; i++) {
        for (k = 0; k < C; k++) {
            tmp[k] = 0;
        }
        for (j = 0; j < C; j++) {
            assume (0 <= votes[i][j]);
            assume (votes[i][j] <= C);
            for (k = 0; k < C; k++) {
                if (votes[i][j] == k) {
                    assume (tmp[k] == 0);
                    tmp[k] = 1;
                }
            }
        }
        assume (votes[i][0] < C);
    }
    for (i = numVotes; i < V; i++) {
        for (j = 0; j < C; j++) {
            votes[i][j] = C;
        }
    }
    for (i = 0; i < C; i++) {
        r.arr[i] = 0;
    }
    r = election_function(votes);

    for (i = 0; i < C; i++) {
        assume (0 <= r.arr[i]);
        assume (r.arr[i] <= 1);
    }

    return r;
}
