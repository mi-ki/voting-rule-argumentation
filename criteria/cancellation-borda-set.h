void cancellation(unsigned int votes1[V][C], unsigned int res[C], unsigned int numVotes, unsigned int negated, unsigned int blocking) { // cancellation criterion
    unsigned int i = 0;
    unsigned int j = 0;

    unsigned int a = 0;
    unsigned int b = 0;

    unsigned int domA[V]; // for determining for each voter whether a dominates b
    unsigned int domB[V]; // for determining for each voter whether b dominates a
    for (i = 0; i < V; i++) {
        domA[i] = 0;
        domB[i] = 0;
    }
    unsigned int aPos = 0;
    unsigned int bPos = 0;

    for (a = 0; a < C; a++) {
        for (b = 0; b < C; b++) {
            if (a != b) {
                for (i = 0; i < numVotes; i++) {
                    aPos = 0;
                    bPos = 0;
                    domA[i] = 0;
                    domB[i] = 0;
                    for (j = 0; j < C; j++) {
                        if (votes1[i][j] == a) {
                            aPos = j+1;
                        }
                        if (votes1[i][j] == b) {
                            bPos = j+1;
                        }
                    }
                    if (0 < aPos && (bPos == 0 || aPos < bPos)) {
                        domA[i] = 1;
                        domB[i] = 0;
                    } else if (0 < bPos && (aPos == 0 || bPos < aPos)) {
                        domB[i] = 1;
                        domA[i] = 0;
                    } else {
                        domA[i] = 0;
                        domB[i] = 0;
                    }
                }
            }
            aPos = 0;
            bPos = 0;
            for (i = 0; i < numVotes; i++) {
                if (domA[i] == 1) {
                    aPos++;
                }
                if (domB[i] == 1) {
                    bPos++;
                }
            }
            if (aPos != bPos && !blocking) { return; }
            assume (aPos == bPos);
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
