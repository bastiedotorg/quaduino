//
// Created by bastian on 07.07.21.
//

#include <Arduino.h>
#include "rs485.h"

//Serial serialIn1, serialIn2,serialIn3, serialOut;


MESSAGE prepareMessageUint64(UINT64* payload, MESSAGE_TYPE messageType){
    MESSAGE data;
    data.payload.asUint = *payload;
    data.messageStatus = MESSAGE_NEW;
    data.messageType = messageType;
    data.crc = crc8((UINT8*)payload, MESSAGE_LENGTH);
    return data;
}
MESSAGE prepareMessageSint64(SINT64* payload, MESSAGE_TYPE messageType){
    MESSAGE data;
    data.payload.asInt = *payload;
    data.crc = crc8((UINT8*)payload, MESSAGE_LENGTH);
    data.messageStatus = MESSAGE_NEW;
    data.messageType = messageType;
    return data;
}
MESSAGE prepareMessageString(SINT8* payload, MESSAGE_TYPE messageType){

    MESSAGE data;
    for (UINT8 i = 0; i < 8; i++) {
        data.payload.asString[i] = payload[i];
    }
    data.messageStatus = MESSAGE_NEW;
    data.messageType = messageType;
    data.crc = crc8((UINT8*)payload, MESSAGE_LENGTH);
    return data;
}

UINT8 crc8(UINT8 const* data, UINT8 len)
{
    if (data == nullptr)
        return 0;
    UINT8 crc = 0x00;
    UINT8 const *end = data + len;
    while (data < end)
        crc = crc8_table[crc ^ *data++];
    return crc;
}

SINT8 sendMessage(UINT8* message) {
    for(UINT8 i=0;i<MESSAGE_LENGTH;i++) {
        if(Serial.availableForWrite() > 0) {
            Serial.write(message[i]);
        } else {
            return TRANSMIT_ERR;
        }
    }
    return TRANSMIT_OK;
}

SINT8 sendMessageUint64(UINT64 payload, MESSAGE_TYPE messageType){
    MESSAGE msg = prepareMessageUint64(&payload, messageType);
    return sendMessage((UINT8*) &msg);
}
#define MODULE_1 0
#define MODULE_2 1
#define MODULE_3 2

SINT8 receiveMessage(UINT8 moduleId, MESSAGE* buffer) {
    switch(moduleId) {
        case MODULE_1:
            return Serial1.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        case MODULE_2:
            return Serial2.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        case MODULE_3:
            return Serial3.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        default:
            return TRANSMIT_ERR;
            break;
    }
}

MESSAGE messageBuffer[3][MESSAGE_TYPE_COUNT];

MESSAGE getSamplingMessage(UINT8 target, MESSAGE_TYPE messageType) {
    return messageBuffer[target][messageType];
}

MESSAGE receiveQueuingMessage(UINT8 target, MESSAGE_TYPE messageType) {
    MESSAGE tmpBuf;
    tmpBuf = messageBuffer[target][messageType];
    messageBuffer[target][messageType].messageStatus = MESSAGE_CONSUMED;
    return tmpBuf;
}

void cyclicCheckMessages() {
    MESSAGE tmpBuf;

    for(UINT8 i=0;i<3;i++) {
        if(receiveMessage(i, &tmpBuf) == 2) {
            messageBuffer[i][tmpBuf.messageType] = tmpBuf;
            if(crc8((UINT8* const) tmpBuf.payload.asString, MESSAGE_LENGTH) == tmpBuf.crc) {
                messageBuffer[i][tmpBuf.messageType].messageStatus = MESSAGE_NEW;
            } else {
                messageBuffer[i][tmpBuf.messageType].messageStatus = MESSAGE_CORRUPTED;
            }
        }
    }
}

void rs485Init(){
    // set Serial to output and activate
    pinMode(RS485_ACTIVATION_PIN_OUT, OUTPUT);

    // set rs485 to read
    pinMode(RS485_ACTIVATION_PIN_IN_1, OUTPUT);
    pinMode(RS485_ACTIVATION_PIN_IN_2, OUTPUT);
    pinMode(RS485_ACTIVATION_PIN_IN_3, OUTPUT);

    // set rs485 to write (serial)
    digitalWrite(RS485_ACTIVATION_PIN_OUT, HIGH);

    // set rs485 to read (serial1-3)
    digitalWrite(RS485_ACTIVATION_PIN_IN_1, LOW);
    digitalWrite(RS485_ACTIVATION_PIN_IN_2, LOW);
    digitalWrite(RS485_ACTIVATION_PIN_IN_3, LOW);


    Serial.setTimeout(RS485_TIMEOUT);
    Serial1.setTimeout(RS485_TIMEOUT);
    Serial2.setTimeout(RS485_TIMEOUT);
    Serial3.setTimeout(RS485_TIMEOUT);

    Serial.begin(RS485_BAUD_RATE);

    Serial1.begin(RS485_BAUD_RATE);
    Serial2.begin(RS485_BAUD_RATE);
    Serial3.begin(RS485_BAUD_RATE);
}

