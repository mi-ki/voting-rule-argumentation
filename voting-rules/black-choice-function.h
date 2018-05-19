struct result condorcet_voting(unsigned int votes[V][C]) {
    struct result r;
    unsigned int i = 0;
    unsigned int j = 0;
    int ci = 0;
    int cj = 0;
    unsigned int found = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    int score[C][C]; // 1, 0 or -1
    int condorcet[C];

    for (i = 0; i < C; i++) {
        r.arr[i] = 0;
    }
    for (i = 0; i < C; i++) {
        for (j = 0; j < C; j++) {
            score[i][j] = 0;
        }
        condorcet[i] = 0;
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
        condorcet[i] = 1;
        for (j = 0; j < C; j++) {
            if (i != j && score[i][j] != 1) {
                condorcet[i] = 0;
            }
        }
    }

    int max = 0;
    for (i = 0; i < C; i++) {
        if (max < condorcet[i]) {
            max = condorcet[i];
            for (j = 0; j < C; j++) {
                r.arr[j] = 0;
            }
            r.arr[i] = 1;
        } else if (max == condorcet[i]) {
            r.arr[i] = 1;
        }
    }
    return r;
}

struct result borda_voting(unsigned int votes[V][C]) {
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

struct result election_function(unsigned int votes[V][C]) {
    RULE[0] = "BLACK";
    unsigned int i = 0;
    unsigned int cnt = 0;

    struct result r = condorcet_voting(votes);
    for (i = 0; i < C; i++) {
        if (r.arr[i] == 1) {
            cnt++;
        }
    }

    if (cnt == 1) {
        return r;
    } else {
        return borda_voting(votes);
    }
}
