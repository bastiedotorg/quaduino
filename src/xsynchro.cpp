//
// Created by bastie on 10/21/20.
//
#include "database.h"
#include "ostime.h"

#define NUM_LANES 4
#define SYN_DEFAULT -1
#define CORRECT_SYN_MESSAGE 15

typedef struct T_STATE {
    bool fail;
    bool navail;
};

typedef struct T_STATUS {
    bool off;
    bool iso;
};

bool getSynMessage(int lane) {
    return true;
}

void transmitSynMessage() {
    int i;
    for (i = 0; i < NUM_LANES; i++) {

    }
}

void xsynchro(T_STATUS *status, T_STATE *zsyn) {
    int i;
    unsigned long ct;
    int xsyn[NUM_LANES];
    bool zsynfail[NUM_LANES];
    bool presyn_end = false;
    bool syn_end = false;
    int nCorrect = 0;
    int nStatusOk = 0;
    int nCorrectMin = 0;
    long TOPreSyn = 200;
    long TOSyn = 100;

    ct = get_time();


    for (i = 0; i < NUM_LANES; i++) {
        zsynfail[i] = true;
        xsyn[i] = SYN_DEFAULT;
        if (!status[i].off && !status[i].iso) {
            nStatusOk++;
        }
    }
    if (nStatusOk >= 3) {
        nCorrectMin = 2;
    } else if (nStatusOk == 2) {
        nCorrectMin = 1;
    }
    while (!presyn_end) {
        //ct++;
        for (i = 0; i < NUM_LANES; i++) {
            xsyn[i] = getSynMessage(i);
            if (xsyn[i] == CORRECT_SYN_MESSAGE) {
                zsyn[i].fail = false;
                nCorrect++;
            }
        }
        if (nCorrect >= nCorrectMin || get_time() - ct > TOPreSyn) {
            presyn_end = true;
        }
    }

    transmitSynMessage();
    ct = get_time();
    if (nStatusOk >= 4) {
        nCorrectMin = 2;
    } else if (nStatusOk >= 2) {
        nCorrectMin = 1;
    }

    while (!syn_end) {
        for (i = 0; i < NUM_LANES; i++) {
            xsyn[i] = getSynMessage(i);
            if (xsyn[i] == CORRECT_SYN_MESSAGE) {
                zsyn[i].fail = false;
                nCorrect++;
            }
        }
        if (nCorrect >= nCorrectMin || get_time() - ct > TOSyn) {
            syn_end = true;
        }
    }
    for(i=0;i<NUM_LANES;i++) {
        if(!zsynfail[i]) { // sf(i) hat korrekt synchronisiert
            zsyn[i].navail = false;
            zsyn[i].fail = false;
        } else if(zsynfail[i] && xsyn[i] == SYN_DEFAULT) { // sf(i) hat kein xsyn gesendet -> stromlos
            zsyn[i].navail = true;
            zsyn[i].fail = false;
        } else { // sf(i) hat korrumpiertes xsyn gesendet
            zsyn[i].navail = true;
            zsyn[i].fail = false;
        }
    }
}

void job_xsynchro() {
    int i;
    T_STATE state[NUM_LANES];
    T_STATUS status[NUM_LANES];
    for (i = 0; i < NUM_LANES; i++) {
        status[i].off = readDBcss(STATUS_OFF_1 + i);
        status[i].iso = readDBcss(STATUS_ISO_1 + i);
    }
    xsynchro(status, state);
    for (i = 0; i < NUM_LANES; i++) {
        writeDBindi(Z_SYN_FAIL_1+i, state[i].fail);
        writeDBindi(Z_SYN_NAVAIL_1+i, state[i].navail);
    }
}