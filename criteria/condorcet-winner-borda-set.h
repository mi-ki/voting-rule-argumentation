void condorcet_winner(unsigned int votes1[V][C], unsigned int res[C], unsigned int winner, unsigned int numVotes, unsigned int negated, unsigned int blocking) { // condorcet winner criterion
    assume (0 <= winner && winner < C);

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    int defeat[C]; // for calculating times when winner defeats according candidate
    int counted[C]; // for considering unranked candidates for condorcet winner
    unsigned int found = 0;
    for (i = 0; i < C; i++) {
        defeat[i] = 0;
        counted[i] = 0;
    }

    for (i = 0; i < numVotes; i++) {
        found = 0;
        for (j = 0; j < C; j++) {
            if (votes1[i][j] == winner) {
                found = 1;
            }
            if (votes1[i][j] != C) {
                if (votes1[i][j] != winner) {
                    if (found) {
                        defeat[votes1[i][j]]++;
                    } else {
                        defeat[votes1[i][j]]--;
                    }
                }
                counted[votes1[i][j]] = 1;
            }
        }
        for (k = 0; k < C; k++) {
            if (counted[k] == 0 && found && k != winner) {
                defeat[k]++;
            }
            counted[k] = 0;
        }
    }
    for (i = 0; i < C; i++) {
        if (defeat[i] <= 0 && i != winner && !blocking) { return; }
        assume (0 < defeat[i] || i == winner);
    }

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        if (i != winner) {
            assume (negated || res[i] == 0);
            if (res[i] != 0) {
                exists = 1;
            }
        }
    }
    assume (negated || res[winner] == 1);
    if (res[winner] != 1) {
        exists = 1;
    }
    assume (!negated || exists);
}
