void fishburn_versus_condorcet(unsigned int votes1[V][C], unsigned int res[C], unsigned int numVotes, unsigned int negated, unsigned int blocking) { // FvsC criterion
    if (numVotes != 101) { return; }
    assume (numVotes == 101);
    if (C != 9) { return; }
    assume (C == 9); // a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7, w=8

    unsigned int tmp[C];
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < 31; i++) {
        if (votes1[i][0] != 0 && !blocking) { return; }
        assume (votes1[i][0] == 0); // a
        if (votes1[i][1] != 1 && !blocking) { return; }
        assume (votes1[i][1] == 1); // b
        if (votes1[i][2] != 2 && !blocking) { return; }
        assume (votes1[i][2] == 2); // c
        if (votes1[i][3] != 3 && !blocking) { return; }
        assume (votes1[i][3] == 3); // d
        if (votes1[i][4] != 4 && !blocking) { return; }
        assume (votes1[i][4] == 4); // e
        if (votes1[i][5] != 8 && !blocking) { return; }
        assume (votes1[i][5] == 8); // w
        if (votes1[i][6] != 6 && !blocking) { return; }
        assume (votes1[i][6] == 6); // g
        if (votes1[i][7] != 7 && !blocking) { return; }
        assume (votes1[i][7] == 7); // h
        if (votes1[i][8] != 5 && !blocking) { return; }
        assume (votes1[i][8] == 5); // f
    }
    for (i = 0; i < 19; i++) {
        j = i+31;
        if (votes1[j][0] != 0 && !blocking) { return; }
        assume (votes1[j][0] == 0); // a
        if (votes1[j][1] != 1 && !blocking) { return; }
        assume (votes1[j][1] == 1); // b
        if (votes1[j][2] != 2 && !blocking) { return; }
        assume (votes1[j][2] == 2); // c
        if (votes1[j][3] != 3 && !blocking) { return; }
        assume (votes1[j][3] == 3); // d
        if (votes1[j][4] != 4 && !blocking) { return; }
        assume (votes1[j][4] == 4); // e
        if (votes1[j][5] != 5 && !blocking) { return; }
        assume (votes1[j][5] == 5); // f
        if (votes1[j][6] != 6 && !blocking) { return; }
        assume (votes1[j][6] == 6); // g
        if (votes1[j][7] != 7 && !blocking) { return; }
        assume (votes1[j][7] == 7); // h
        if (votes1[j][8] != 8 && !blocking) { return; }
        assume (votes1[j][8] == 8); // w
    }
    for (i = 0; i < 10; i++) {
        j = i+50;
        if (votes1[j][0] != 5 && !blocking) { return; }
        assume (votes1[j][0] == 5); // f
        if (votes1[j][1] != 8 && !blocking) { return; }
        assume (votes1[j][1] == 8); // w
        if (votes1[j][2] != 0 && !blocking) { return; }
        assume (votes1[j][2] == 0); // a
        if (votes1[j][3] != 7 && !blocking) { return; }
        assume (votes1[j][3] == 7); // h
        if (votes1[j][4] != 6 && !blocking) { return; }
        assume (votes1[j][4] == 6); // g
        if (votes1[j][5] != 4 && !blocking) { return; }
        assume (votes1[j][5] == 4); // e
        if (votes1[j][6] != 3 && !blocking) { return; }
        assume (votes1[j][6] == 3); // d
        if (votes1[j][7] != 2 && !blocking) { return; }
        assume (votes1[j][7] == 2); // c
        if (votes1[j][8] != 1 && !blocking) { return; }
        assume (votes1[j][8] == 1); // b
    }
    for (i = 0; i < 10; i++) {
        j = i+60;
        if (votes1[j][0] != 6 && !blocking) { return; }
        assume (votes1[j][0] == 6); // g
        if (votes1[j][1] != 8 && !blocking) { return; }
        assume (votes1[j][1] == 8); // w
        if (votes1[j][2] != 0 && !blocking) { return; }
        assume (votes1[j][2] == 0); // a
        if (votes1[j][3] != 7 && !blocking) { return; }
        assume (votes1[j][3] == 7); // h
        if (votes1[j][4] != 5 && !blocking) { return; }
        assume (votes1[j][4] == 5); // f
        if (votes1[j][5] != 4 && !blocking) { return; }
        assume (votes1[j][5] == 4); // e
        if (votes1[j][6] != 3 && !blocking) { return; }
        assume (votes1[j][6] == 3); // d
        if (votes1[j][7] != 2 && !blocking) { return; }
        assume (votes1[j][7] == 2); // c
        if (votes1[j][8] != 1 && !blocking) { return; }
        assume (votes1[j][8] == 1); // b
    }
    for (i = 0; i < 10; i++) {
        j = i+70;
        if (votes1[j][0] != 7 && !blocking) { return; }
        assume (votes1[j][0] == 7); // h
        if (votes1[j][1] != 8 && !blocking) { return; }
        assume (votes1[j][1] == 8); // w
        if (votes1[j][2] != 0 && !blocking) { return; }
        assume (votes1[j][2] == 0); // a
        if (votes1[j][3] != 5 && !blocking) { return; }
        assume (votes1[j][3] == 5); // f
        if (votes1[j][4] != 6 && !blocking) { return; }
        assume (votes1[j][4] == 6); // g
        if (votes1[j][5] != 4 && !blocking) { return; }
        assume (votes1[j][5] == 4); // e
        if (votes1[j][6] != 3 && !blocking) { return; }
        assume (votes1[j][6] == 3); // d
        if (votes1[j][7] != 2 && !blocking) { return; }
        assume (votes1[j][7] == 2); // c
        if (votes1[j][8] != 1 && !blocking) { return; }
        assume (votes1[j][8] == 1); // b
    }
    for (i = 0; i < 21; i++) {
        j = i+80;
        if (votes1[j][0] != 7 && !blocking) { return; }
        assume (votes1[j][0] == 7); // h
        if (votes1[j][1] != 6 && !blocking) { return; }
        assume (votes1[j][1] == 6); // g
        if (votes1[j][2] != 5 && !blocking) { return; }
        assume (votes1[j][2] == 5); // f
        if (votes1[j][3] != 8 && !blocking) { return; }
        assume (votes1[j][3] == 8); // w
        if (votes1[j][4] != 0 && !blocking) { return; }
        assume (votes1[j][4] == 0); // a
        if (votes1[j][5] != 4 && !blocking) { return; }
        assume (votes1[j][5] == 4); // e
        if (votes1[j][6] != 3 && !blocking) { return; }
        assume (votes1[j][6] == 3); // d
        if (votes1[j][7] != 2 && !blocking) { return; }
        assume (votes1[j][7] == 2); // c
        if (votes1[j][8] != 1 && !blocking) { return; }
        assume (votes1[j][8] == 1); // b
    }

    unsigned int exists = 0;
    assume (negated || res[0] == 1); // elect candidate a
    if (res[0] != 1) {
        exists = 1;
    }
    for (i = 1; i < C; i++) {
        assume (negated || res[i] == 0); // all others should not be elected
        if (res[i] != 0) {
            exists = 1;
        }
    }
    assume (!negated || exists);
}
