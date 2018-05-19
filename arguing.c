#ifndef V
#define V 3
#endif

#ifndef C
#define C 3
#endif

unsigned int RESULT[C];

struct result { unsigned int arr[C]; };

#include "include/arguing.h"

int main(int argc, char *argv[]) {
    unsigned int VOTES[V][C]; // array of preferential votes (votes x preference ranks)
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int tmp[C];
    for (i = 0; i < V; i++) {
        for (k = 0; k < C; k++) {
            tmp[k] = 0;
        }
        for (j = 0; j < C; j++) {
            VOTES[i][j] = nondet_uint();
            assume (0 <= VOTES[i][j] && VOTES[i][j] < C); // the value C translates to no candidate
            for (k = 0; k < C; k++) {
                if (VOTES[i][j] == k) {
                    assume (tmp[k] == 0);
                    tmp[k] = 1;
                }
            }
        }
        //assume (VOTES[i][0] < C);
    }

    struct result r = voting2(VOTES, V);
    for (i = 0; i < C; i++) {
        RESULT[i] = r.arr[i];
    }
    arguing(VOTES, RESULT, V);

    assert (0);
    return 0;
}
