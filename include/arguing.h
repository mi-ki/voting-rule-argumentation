#include <stdlib.h>
#include "cbmc.h"

void arguing(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes);

#ifndef NO_BLOCKING // How many axioms shall be blocking (i.e., precondition must hold). -1 for all, 0 for (at least) none, otherwise minimal number
#define NO_BLOCKING -1
#endif

struct result election_function(unsigned int votes[V][C]);

char* RULE[1] = { "" }; // Analyzed voting rules

#include RULES

#ifndef DOM       // (Pareto) Dominance
#define DOM 0
#endif

#ifndef ANON      // Anonymity
#define ANON 0
#endif

#ifndef COND      // Condorcet winner
#define COND 0
#endif

#ifndef SYMCANC   // Symmetric cancellation
#define SYMCANC 0
#endif

#ifndef FVSC      // The Fishburn-versus-Condorcet axiom
#define FVSC 0
#endif

#ifndef ELEM      // Elementary profile
#define ELEM 0
#endif

#ifndef CYCL      // Cyclic profile
#define CYCL 0
#endif

#ifndef CANC      // Cancellation
#define CANC 0
#endif

#ifndef REINF     // Reinforcement/Consistency
#define REINF 0
#endif

#ifndef REINF_SUB // Reinforcement subtraction
#define REINF_SUB 0
#endif

#ifndef SIMP // Simplify
#define SIMP 0
#endif

#ifndef MAJ // Majority
#define MAJ 0
#endif

#ifndef WEAK_MAJO // Weak majority
#define WEAK_MAJO 0
#endif

#include "criteria/dominance-borda-set.h"
#include "criteria/anonymity-borda-set.h"
#include "criteria/condorcet-winner-borda-set.h"
#include "criteria/reinforcement-borda-set.h"
#include "criteria/symmetric-cancellation-borda-set.h"
#include "criteria/fishburnVersusCondorcet-borda-set.h"
#include "criteria/elementary-profile-borda-set.h"
#include "criteria/cyclic-profile-borda-set.h"
#include "criteria/cancellation-borda-set.h"
#include "criteria/reinforcement-subtract-borda-set.h"
#include "criteria/simplify-borda-set.h"
#include "criteria/majority-borda-set.h"
#include "criteria/weak-majority-borda-set.h"

void dom(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (C == 1) { return; }

    unsigned int dom = nondet_uint();
    unsigned int pareto = nondet_uint();
    assume (0 <= dom && dom < C);
    assume (0 <= pareto && pareto < C);
    assume (dom != pareto);

    dominance(votes, res, dom, pareto, numVotes, 0, blocking);
}

void neg_dom(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (C == 1) { return; }

    unsigned int dom = nondet_uint();
    unsigned int pareto = nondet_uint();
    assume (0 <= dom && dom < C);
    assume (0 <= pareto && pareto < C);
    assume (dom != pareto);

    dominance(votes, res, dom, pareto, numVotes, 1, blocking);
}

void anon(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }

    unsigned int v2[V][C];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int tmp[C];

    unsigned int perm[V];
    unsigned int exists = 0;

    unsigned int print = 0;

    for (i = 0; i < V; i++) {
        perm[i] = 0; // is later overwritten in anonymity-function
    }
    for (i = 0; i < numVotes; i++) {
        for (j = 0; j < C; j++) {
            v2[i][j] = 0; // is later overwritten in anonymity-function
        }
    }

    print = nondet_uint();
    assume (print == 0 || print == 1);

    print = anonymity(votes, res, v2, perm, numVotes, print, 0, blocking);

    assume (print);
}

void neg_anon(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }

    unsigned int v2[V][C];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int tmp[C];

    unsigned int perm[V];
    unsigned int exists = 0;
    for (i = 0; i < numVotes; i++) {
        perm[i] = nondet_uint();
        assume (0 <= perm[j] && perm[i] < numVotes);
        exists = exists || (perm[i] != i);
        for (j = 0; j < numVotes; j++) {
            assume (i == j || perm[i] != perm[j]);
        }
    }
    assume (exists);

    unsigned int print = 0;

    for (i = 0; i < numVotes; i++) {
        for (j = 0; j < C; j++) {
            v2[perm[i]][j] = votes[i][j];
        }
    }

    print = anonymity(votes, res, v2, perm, numVotes, 1, 1, blocking);
    assume (print);
}

void cond(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    condorcet_winner(votes, res, winner, numVotes, 0, blocking);
}

void neg_cond(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    condorcet_winner(votes, res, winner, numVotes, 1, blocking);
}

void reinf(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }
    unsigned int sep = nondet_uint();
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int print = 0;
    unsigned int hasPrinted = 0;

    print = 1;

    print = reinforcement(votes, res, sep, numVotes, print, 0, blocking);
    assume (print);
}

void neg_reinf(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }
    unsigned int sep = nondet_uint();
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int print = 0;

    print = reinforcement(votes, res, sep, numVotes, 1, 1, blocking);
    assume (print);
}

void symCanc(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes % 2 != 0) { return; }
    symmetric_cancellation(votes, res, numVotes, 0, blocking);
}

void neg_symCanc(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes % 2 != 0) { return; }
    symmetric_cancellation(votes, res, numVotes, 1, blocking);
}

void fvsC(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    fishburn_versus_condorcet(votes, res, numVotes, 0, blocking);
}

void neg_fvsC(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    fishburn_versus_condorcet(votes, res, numVotes, 1, blocking);
}

void elem(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes != 2) { return; }
    if (C == 1) { return; }
    elementary_profile(votes, res, numVotes, 0, blocking);
}

void neg_elem(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes != 2) { return; }
    if (C == 1) { return; }
    elementary_profile(votes, res, numVotes, 1, blocking);
}

void cycl(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes != C) { return; }
    unsigned int cycle[C+1];
    unsigned int i = 0;
    unsigned int k = 0;
    unsigned int tmp[C];

    for (k = 0; k < C; k++) {
        tmp[k] = 0;
        cycle[k] = nondet_uint();
        assume (0 <= cycle[k]);
        assume (cycle[k] < C);
    }
    cycle[C] = cycle[0];
    for (i = 0; i < C; i++) {
        for (k = 0; k < C; k++) {
            if (cycle[i] == k) {
                assume (tmp[k] == 0);
                tmp[k] = 1;
            }
        }
    }

    cyclic_profile(votes, res, cycle, numVotes, 0, blocking);
}

void neg_cycl(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (numVotes != C) { return; }
    unsigned int cycle[C+1];
    unsigned int i = 0;
    unsigned int k = 0;
    unsigned int tmp[C];

    for (k = 0; k < C; k++) {
        tmp[k] = 0;
        cycle[k] = nondet_uint();
        assume (0 <= cycle[k]);
        assume (cycle[k] < C);
    }
    cycle[C] = cycle[0];
    for (i = 0; i < C; i++) {
        for (k = 0; k < C; k++) {
            if (cycle[i] == k) {
                assume (tmp[k] == 0);
                tmp[k] = 1;
            }
        }
    }

    cyclic_profile(votes, res, cycle, numVotes, 1, blocking);
}

void canc(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    cancellation(votes, res, numVotes, 0, blocking);
}

void neg_canc(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    cancellation(votes, res, numVotes, 1, blocking);
}

void reinf_sub(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }
    unsigned int sep = nondet_uint();
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int print = 0;
    unsigned int hasPrinted = 0;

    print = 1;

    print = reinforcement_subtract(votes, res, sep, numVotes, print, 0, blocking);
    assume (print);
}

void neg_reinf_sub(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    if (V == 1) { return; }
    unsigned int sep = nondet_uint();
    assume (0 < sep && sep * 2 <= numVotes);

    unsigned int print = 0;

    print = reinforcement_subtract(votes, res, sep, numVotes, 1, 1, blocking);
    assume (print);
}

void simp(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int rep = nondet_uint();
    assume (0 < rep);
    assume (rep <= numVotes);
    assume (numVotes % rep == 0);
    if (numVotes < 2) { return; }
    assume (rep != 1);

    unsigned int print = 0;

    print = simplify(votes, res, numVotes, rep, 1, 0, blocking);
    assume (print);
}

void neg_simp(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int rep = nondet_uint();
    assume (0 < rep);
    assume (rep <= numVotes);
    assume (numVotes % rep == 0);
    if (numVotes < 2) { return; }
    assume (rep != 1);

    unsigned int print = 0;
    unsigned int hasPrinted = 0;

    print = 1;

    print = simplify(votes, res, numVotes, rep, print, 1, blocking);
    assume (print);
}

void maj(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    majority(votes, res, winner, numVotes, 0, blocking);
}

void neg_maj(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    majority(votes, res, winner, numVotes, 1, blocking);
}

void weak_majo(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    weak_majority(votes, res, winner, numVotes, 0, blocking);
}

void neg_weak_majo(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes, unsigned int blocking) {
    unsigned int winner = nondet_uint();
    assume (0 <= winner && winner < C);

    weak_majority(votes, res, winner, numVotes, 1, blocking);
}

void arguing(unsigned int votes[V][C], unsigned int res[C], unsigned int numVotes) {
    unsigned int props = 0;
    unsigned int sum = 0;

    unsigned int blockDom = nondet_uint();
    assume (0 <= blockDom && blockDom <= 1);
    if (DOM) {
        props++;
    } else {
        assume (blockDom == 0);
    }
    sum += blockDom;

    unsigned int blockAnon = nondet_uint();
    assume (0 <= blockAnon && blockAnon <= 1);
    if (ANON) {
        props++;
    } else {
        blockAnon = 0;
    }
    sum += blockAnon;
    unsigned int blockCond = nondet_uint();
    assume (0 <= blockCond && blockCond <= 1);
    if (COND) {
        props++;
    } else {
        blockCond = 0;
    }
    sum += blockCond;
    unsigned int blockSymCanc = nondet_uint();
    assume (0 <= blockSymCanc && blockSymCanc <= 1);
    if (SYMCANC) {
        props++;
    } else {
        blockSymCanc = 0;
    }
    sum += blockSymCanc;
    unsigned int blockFvsC = nondet_uint();
    assume (0 <= blockFvsC && blockFvsC <= 1);
    if (FVSC) {
        props++;
    } else {
        blockFvsC = 0;
    }
    sum += blockFvsC;
    unsigned int blockElem = nondet_uint();
    assume (0 <= blockElem && blockElem <= 1);
    if (ELEM) {
        props++;
    } else {
        blockElem = 0;
    }
    sum += blockElem;
    unsigned int blockCycl = nondet_uint();
    assume (0 <= blockCycl && blockCycl <= 1);
    if (CYCL) {
        props++;
    } else {
        blockCycl = 0;
    }
    sum += blockCycl;
    unsigned int blockCanc = nondet_uint();
    assume (0 <= blockCanc && blockCanc <= 1);
    if (CANC) {
        props++;
    } else {
        blockCanc = 0;
    }
    sum += blockCanc;
    unsigned int blockReinf = nondet_uint();
    assume (0 <= blockReinf && blockReinf <= 1);
    if (REINF) {
        props++;
    } else {
        blockReinf = 0;
    }
    sum += blockReinf;
    unsigned int blockReinfSub = nondet_uint();
    assume (0 <= blockReinfSub && blockReinfSub <= 1);
    if (REINF_SUB) {
        props++;
    } else {
        blockReinfSub = 0;
    }
    sum += blockReinfSub;
    unsigned int blockSimp = nondet_uint();
    assume (0 <= blockSimp && blockSimp <= 1);
    if (SIMP) {
        props++;
    } else {
        blockSimp = 0;
    }
    sum += blockSimp;
    unsigned int blockMaj = nondet_uint();
    assume (0 <= blockMaj && blockMaj <= 1);
    if (MAJ) {
        props++;
    } else {
        blockMaj = 0;
    }
    sum += blockMaj;
    unsigned int blockWeakMaj = nondet_uint();
    assume (0 <= blockWeakMaj && blockWeakMaj <= 1);
    if (WEAK_MAJO) {
        props++;
    } else {
        blockWeakMaj = 0;
    }
    sum += blockWeakMaj;
    unsigned int blocking = nondet_uint();
    assume (0 <= blocking && blocking <= props);
    assume (sum == blocking);

    unsigned int number = 0;
    if (NO_BLOCKING < 0 || props < NO_BLOCKING) {
        number = props;
    } else {
        number = NO_BLOCKING;
    }
    assume (blocking == number);

    if (DOM) {
        if (0 < DOM) dom(votes, res, numVotes, blockDom);
        if (DOM < 0) neg_dom(votes, res, numVotes, blockDom);
    }
    if (ANON) {
        if (0 < ANON) anon(votes, res, numVotes, blockAnon);
        if (ANON < 0) neg_anon(votes, res, numVotes, blockAnon);
    }
    if (COND) {
        if (0 < COND) cond(votes, res, numVotes, blockCond);
        if (COND < 0) neg_cond(votes, res, numVotes, blockCond);
    }
    if (SYMCANC) {
        if (0 < SYMCANC) symCanc(votes, res, numVotes, blockSymCanc);
        if (SYMCANC < 0) neg_symCanc(votes, res, numVotes, blockSymCanc);
    }
    if (FVSC) {
        if (0 < FVSC) fvsC(votes, res, numVotes, blockFvsC);
        if (FVSC < 0) neg_fvsC(votes, res, numVotes, blockFvsC);
    }
    if (ELEM) {
        if (0 < ELEM) elem(votes, res, numVotes, blockElem);
        if (ELEM < 0) neg_elem(votes, res, numVotes, blockElem);
    }
    if (CYCL) {
        if (0 < CYCL) cycl(votes, res, numVotes, blockCycl);
        if (CYCL < 0) neg_cycl(votes, res, numVotes, blockCycl);
    }
    if (CANC) {
        if (0 < CANC) canc(votes, res, numVotes, blockCanc);
        if (CANC < 0) neg_canc(votes, res, numVotes, blockCanc);
    }
    if (REINF) {
        if (0 < REINF) reinf(votes, res, numVotes, blockReinf);
        if (REINF < 0) neg_reinf(votes, res, numVotes, blockReinf);
    }
    if (REINF_SUB) {
        if (0 < REINF_SUB) reinf_sub(votes, res, numVotes, blockReinfSub);
        if (REINF_SUB < 0) neg_reinf_sub(votes, res, numVotes, blockReinfSub);
    }
    if (SIMP) {
        if (0 < SIMP) simp(votes, res, numVotes, blockSimp);
        if (SIMP < 0) neg_simp(votes, res, numVotes, blockSimp);
    }
    if (MAJ) {
        if (0 < MAJ) maj(votes, res, numVotes, blockMaj);
        if (MAJ < 0) neg_maj(votes, res, numVotes, blockMaj);
    }
    if (WEAK_MAJO) {
        if (0 < WEAK_MAJO) weak_majo(votes, res, numVotes, blockWeakMaj);
        if (WEAK_MAJO < 0) neg_weak_majo(votes, res, numVotes, blockWeakMaj);
    }
}
