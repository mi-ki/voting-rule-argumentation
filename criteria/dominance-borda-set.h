void dominance(unsigned int votes1[V][C], unsigned int res[C], unsigned int dom, unsigned int pareto, unsigned int numVotes, unsigned int negated, unsigned int blocking) { // dominance criterion
    assume (0 <= dom && dom < C);
    assume (0 <= pareto && pareto < C);
    assume (dom != pareto);

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int dominated[V]; // for determining for each voter whether dom is dominated by pareto
    for (int i = 0; i < V; i++) {
        dominated[i] = 0;
    }
    unsigned int p = C;
    unsigned int d = C;
    unsigned int paretoAlwaysDominated = 1;
    for (i = 0; i < numVotes; i++) {
        p = C;
        d = C;
        for (j = 0; j < C; j++) {
            if (votes1[i][j] == pareto) {
                p = j;
            }
            if (votes1[i][j] == dom) {
                d = j;
            }
        }
        if (p != C && (d == C || p < d)) {
            dominated[i] = 1;
        } else {
            dominated[i] = 0;
        }
        if (d == C || (p != C && d >= p)) {
            paretoAlwaysDominated = 0;
        }
    }

    if (paretoAlwaysDominated && !blocking) { return; }
    assume (!paretoAlwaysDominated);

    for (i = 0; i < numVotes; i++) {
        if (dominated[i] != 1 && !blocking) { return; }
        assume (dominated[i] == 1);
    }

    assume ( negated || res[dom] == 0);
    assume ( !negated || res[dom] != 0);
}
