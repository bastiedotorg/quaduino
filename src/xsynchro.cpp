//
// Created by bastie on 10/21/20.
//
#include "database.h"
#include "ostime.h"
#include "rs485.h"
#include "datatypes.h"

#define NUM_LANES 4
#define SYN_DEFAULT -1
#define CORRECT_SYN_MESSAGE 15

typedef struct {
    bool fail;
    bool navail;
} TT_STATE;

typedef struct {
    bool off;
    bool iso;
} TT_STATUS;

SINT64 getSynMessage(int lane) {
    MESSAGE synMsg;
    receiveMessage(lane, &synMsg);
    return synMsg.payload.asInt;
}

void transmitSynMessage() {
    sendMessageUint64(CORRECT_SYN_MESSAGE, XSYNCHRO);
}

void xsynchro(TT_STATUS *status, TT_STATE *zsyn) {
    int i;
    unsigned long ct;
    int xsyn[NUM_LANES];
    bool presyn_end = false;
    bool syn_end = false;
    int nCorrect = 0;
    int nStatusOk = 0;
    int nCorrectMin = 0;
    long TOPreSyn = 1000;
    long TOSyn = 800;

    ct = get_time();
    for (i = 0; i < NUM_LANES; i++) {
        zsyn[i].fail = true;
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
            xsyn[i] = (int) getSynMessage(i);
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
        nCorrectMin = 1;
    } else if (nStatusOk >= 2) {
        nCorrectMin = 1;
    }

    while (!syn_end) {
        for (i = 0; i < NUM_LANES; i++) {
            xsyn[i] = (int) getSynMessage(i);

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
        if(zsyn[i].fail == false) { // sf(i) hat korrekt synchronisiert
            zsyn[i].navail = false;
            zsyn[i].fail = false;
        } else if(zsyn[i].fail && xsyn[i] == SYN_DEFAULT) { // sf(i) hat kein xsyn gesendet -> stromlos
            zsyn[i].navail = true;
            zsyn[i].fail = false;
        } else { // sf(i) hat korrumpiertes xsyn gesendet
            zsyn[i].navail = true;
            zsyn[i].fail = true;
        }
    }
}

void job_xsynchro() {
    int i;
    TT_STATE state[NUM_LANES];
    TT_STATUS status[NUM_LANES];
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