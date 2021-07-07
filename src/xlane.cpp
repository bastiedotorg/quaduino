//
// Created by bastie on 10/21/20.
//
#define NUM_LANES 4
#include "database.h"
#include "xlane.h"

void xLaneInit() {
    int i;
    for(i=0;i<NUM_LANES;i++) {

    }
}

void xLaneSend(int laneId, long data) {

}

void xLaneReceive(int laneId) {
    int val;
    val = 1;
    writeDBindi(X_XLANE, val);
}