//
// Created by bastie on 10/21/20.
//
#include "database.h"

long DATAPOOL[DATAPOOL_SIZE];

/**
 * writes data to the database at a certain position
 *
 * @param position position in the database where the value shall be written
 * @param value value to be written to the database
 */
void writeDB(long position, long value) {
    DATAPOOL[position] = value;
}

/**
 * writes data to the DBindi at a certain position
 *
 * @param position position within the DBindi where the value shall be written
 * @param value value to be written to the database
 */
void writeDBindi(long position, long value) {
    DATAPOOL[DB_INDI + position] = value;
}

/**
 * writes data to the DBcss at a certain position
 *
 * @param position position within the DBcss where the value shall be written
 * @param value value to be written to the database
 */
void writeDBcss(long position, long value) {
    DATAPOOL[DB_CSS + position] = value;
}

/**
 * writes data to the DBrbc at a certain position
 *
 * @param position position within the DBrbc where the value shall be written
 * @param value value to be written to the database
 */
void writeDBrbc(long position, long value) {
    DATAPOOL[DB_RBC + position] = value;
}

/**
 * reads data from the database at a certain position
 *
 * @param position position from which the data is read
 * @return data read from the database
 */
long readDB(long position) {
    return DATAPOOL[position];
}

/**
 * reads data from the DBindi at a certain position
 *
 * @param position position within DBindi where the data is read
 * @return data read from DBindi
 */
long readDBindi(long position) {
    return readDB(DB_INDI + position);
}

/**
 * reads data from DBcss at a certain position
 *
 * @param position position within DBcss where the data is read
 * @return data read from DBcss
 */
long readDBcss(long position) {
    return readDB(DB_CSS + position);
}

/**
 * reads data from DBrbc at a certain position
 *
 * @param position position within DBrbc where the data is read
 * @return data read from DBrbc
 */
long readDBrbc(long position) {
    return readDB(DB_RBC + position);
}

/**
 * initializes the database by writing 0 at every database position
 */
void initDB() {
    long i;
    for (i = 0; i < DATAPOOL_SIZE; i++) {
        DATAPOOL[i] = 0;
    }
}