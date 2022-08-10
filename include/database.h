//
// Created by bastie on 10/21/20.
//

#ifndef QUADIUNO_DATABASE_H
#define QUADIUNO_DATABASE_H
#define DATAPOOL_SIZE 200
extern long DATAPOOL[DATAPOOL_SIZE];

void initDB();
long getDB(long*);

void writeDB(long position, long value);
void writeDBindi(long position, long value);
void writeDBcss(long position, long value);
void writeDBrbc(long position, long value);

long readDB(long position);
long readDBindi(long position);
long readDBcss(long position);
long readDBrbc(long position);


enum DBPOSITIONS {
    DB_INDI = 0,
    DB_RBC = 100,
    DB_CSS = 160
};


enum DBPOSITIONS_INDI {
    Z_SYN_FAIL_1,
    Z_SYN_FAIL_2,
    Z_SYN_FAIL_3,
    Z_SYN_FAIL_4,
    Z_SYN_NAVAIL_1,
    Z_SYN_NAVAIL_2,
    Z_SYN_NAVAIL_3,
    Z_SYN_NAVAIL_4,
    X_XLANE,
    SENSOR_1,
    SENSOR_2,
    SENSOR_3
};


enum DBPOSITIONS_CSS {
    STATUS_OFF_1,
    STATUS_OFF_2,
    STATUS_OFF_3,
    STATUS_OFF_4,
    STATUS_ISO_1,
    STATUS_ISO_2,
    STATUS_ISO_3,
    STATUS_ISO_4,
    STATUS_OFF_1_NEW,
    STATUS_OFF_2_NEW,
    STATUS_OFF_3_NEW,
    STATUS_OFF_4_NEW,
    STATUS_ISO_1_NEW,
    STATUS_ISO_2_NEW,
    STATUS_ISO_3_NEW,
    STATUS_ISO_4_NEW,

};

#endif //QUADIUNO_DATABASE_H
