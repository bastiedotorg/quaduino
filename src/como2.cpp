//
// Created by bastie on 10/21/20.
//

#include "xlane.h"
#define NUM_LANES 4

bool confirm(bool yindi, long c, long cmax, long climit, long cinc, long cdec) {
    if (yindi) {
        c = c + cinc;
    } else {
        c = c - cdec;
    }
    if (c > cmax) {
        c = cmax;
    } else if (c < 0) {
        c = 0;
    }

    return c >= climit;
}

void xtransmit_data_step1(long x) {
    int i;
    for(i=0;i<NUM_LANES;i++) {
        xLaneSend(i, x);
    }
}