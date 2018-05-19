struct result election_function(unsigned int votes[V][C]) {
    RULE[0] = "COPELAND";
    struct result r;
    unsigned int i = 0;
    unsigned int j = 0;
    int ci = 0;
    int cj = 0;
    unsigned int found = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    int score[C][C]; // 1, 0 or -1
    int copeland[C];

    for (i = 0; i < C; i++) {
        r.arr[i] = 0;
    }
    for (i = 0; i < C; i++) {
        for (j = 0; j < C; j++) {
            score[i][j] = 0;
        }
        copeland[i] = 0;
    }

    for (i = 0; i < C; i++) {
        for (j = 0; j < C; j++) {
            ci = 0;
            cj = 0;
            for (k = 0; k < V && i != j; k++) {
                found = 0;
                for (l = 0; l < C; l++) {
                    if (!found && votes[k][l] == i) {
                        ci++;
                        cj--;
                        found = 1;
                    } else if (!found && votes[k][l] == j) {
                        cj++;
                        ci--;
                        found = 1;
                    }
                }
            }
            if (ci < cj) {
                score[i][j] = -1;
            } else if (cj < ci) {
                score[i][j] = 1;
            }
        }
    }

    for (i = 0; i < C; i++) {
        for (j = 0; j < C; j++) {
            copeland[i] += score[i][j];
        }
    }

    int max = -1 * C;
    for (i = 0; i < C; i++) {
        if (max < copeland[i]) {
            max = copeland[i];
            for (j = 0; j < C; j++) {
                r.arr[j] = 0;
            }
            r.arr[i] = 1;
        } else if (max == copeland[i]) {
            r.arr[i] = 1;
        }
    }
    return r;
}
