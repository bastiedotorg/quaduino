//
// Created by bastie on 10/21/20.
//
#include "database.h"

long DATAPOOL[DATAPOOL_SIZE];

void writeDB(long position, long value) {
    DATAPOOL[position] = value;
}

void writeDBindi(long position, long value) {
    DATAPOOL[DB_INDI + position] = value;
}

void writeDBcss(long position, long value) {
    DATAPOOL[DB_CSS + position] = value;
}

void writeDBrbc(long position, long value) {
    DATAPOOL[DB_RBC + position] = value;
}

long readDB(long position) {
    return DATAPOOL[position];
}

long readDBindi(long position) {
    return readDB(DB_INDI + position);
}

long readDBcss(long position) {
    return readDB(DB_CSS + position);
}

long readDBrbc(long position) {
    return readDB(DB_RBC + position);
}

void initDB() {
    long i;
    for (i = 0; i < DATAPOOL_SIZE; i++) {
        DATAPOOL[i] = 0;
    }
}