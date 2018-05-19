struct result election_function(unsigned int votes[V][C]) {
    RULE[0] = "BORDA";
    struct result r;
    unsigned int res[C];
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < C; i++) {
        r.arr[i] = 1;
    }
    for (i = 0; i < C; i++) {
        res[i] = 0;
    }
    for (i = 0; i < V; i++) {
        for (j = 0; j < C; j++) {
            if (votes[i][j] < C) {
                res[votes[i][j]] += (C - j) - 1;
            }
        }
    }
    unsigned int max = 0;
    for (i = 0; i < C; i++) {
        if (max < res[i]) {
            max = res[i];
            for (j = 0; j < C; j++) {
                r.arr[j] = 0;
            }
            r.arr[i] = 1;
        } else if (max == res[i]) {
            r.arr[i] = 1;
        }
    }
    return r;
}
