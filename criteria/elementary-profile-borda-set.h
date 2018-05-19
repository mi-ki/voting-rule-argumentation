void elementary_profile(unsigned int votes1[V][C], unsigned int res[C], unsigned int numVotes, unsigned int negated, unsigned int blocking) { // elementary profile criterion
    assume (numVotes == 2);
    unsigned int p = nondet_uint();
    unsigned int isWinner = 0;
    assume (0 < p);
    assume (p < C);
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < p; i++) {
//      tmp[i] = votes1[0][i];
//      Probably not necessary as borda requires every preference to be assigned uniquely.
        if (votes1[1][p - i - 1] != votes1[0][i] && !blocking) { return; }
        assume (votes1[1][p - i - 1] == votes1[0][i]);
    }
    for (i = p; i < C; i++) {
        if (votes1[1][C - i + p - 1] != votes1[0][i] && !blocking) { return; }
        assume (votes1[1][C - i + p - 1] == votes1[0][i]);
//      for (j = 0; j < p; j++) {
//          assume (tmp[j] != votes1[0][j]);
//      } Probably also not necessary for the very same reason
    }

    unsigned int exists = 0;
    for (i = 0; i < C; i++) {
        isWinner = 0;
        for (j = 0; j < p; j++) {
            if (votes1[0][j] == i) {
                isWinner = 1;
            }
        }
        if (isWinner == 1) {
            assume (negated || res[i] == 1);
            if (res[i] != 1) {
                exists = 1;
            }
        } else {
            assume (negated || res[i] == 0);
            if (res[i] != 0) {
                exists = 1;
            }
        }
    }
    assume (!negated || exists);
}
