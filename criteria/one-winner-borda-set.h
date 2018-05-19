void one_winner_set(unsigned int votes[V][C], unsigned int numVotes) {
    //unsigned int *a = malloc(C*sizeof(unsigned int));
    struct result a;
    unsigned int tmp[C];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int exists = 0;

    for (i = 0; i < C; i++) {
        a.arr[i] = nondet_uint();
        assume (0 <= a.arr[i] && a.arr[i] <= 1);
        if (a.arr[i] == 1) {
            exists = 1;
        }
    }
    assume (exists);

    struct result elect = voting2(votes, numVotes);
    for (i = 0; i < C; i++) {
        assume (a.arr[i] == elect.arr[i]);
    }
}
