//
// Created by bastian on 07.07.21.
//

#include <Arduino.h>
#include "rs485.h"

//Serial serialIn1, serialIn2,serialIn3, serialOut;

/**
 * creates a message ready to be sended via RS485 for payloads of UINT64 type
 *
 * @param payload defines the UINT64 payload to be sended
 * @param messageType defines type of message (e.g. synchronisation message)
 * @return MESSAGE including an UINT64 payload and a message type with generated crc
 */
MESSAGE prepareMessageUint64(UINT64* payload, MESSAGE_TYPE messageType){
    MESSAGE data;
    data.payload.asUint = *payload;
    data.messageStatus = MESSAGE_NEW;
    data.messageType = messageType;
    data.crc = crc8((UINT8*)payload, MESSAGE_LENGTH);
    return data;
}

/**
 * creates a message ready to be sended via RS485 for payloads of SINT64 type
 *
 * @param payload defines the SINT64 payload to be sended
 * @param messageType defines type of message (e.g. synchronisation message)
 * @return MESSAGE including an SINT64 payload and a message type with generated crc
 */
MESSAGE prepareMessageSint64(SINT64* payload, MESSAGE_TYPE messageType){
    MESSAGE data;
    data.payload.asInt = *payload;
    data.crc = crc8((UINT8*)payload, MESSAGE_LENGTH);
    data.messageStatus = MESSAGE_NEW;
    data.messageType = messageType;
    return data;
}

/**
 * creates a message ready to be sended via RS485 for payloads of SINT8 type
 *
 * @param payload defines the SINT8 payload to be sended
 * @param messageType defines type of message (e.g. synchronisation message)
 * @return MESSAGE including an SINT8 payload and a message type with generated crc
 */
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


/**
 * creates crc8 for a new message
 */
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


/**
 * sends a prepared message via RS485 on SERIAL3 port
 *
 * @param message message which is sended
 * @return -1 if sending was not succesful, 1 if sending was succesful
 */
SINT8 sendMessage(UINT8* message) {
    for(UINT8 i=0;i<MESSAGE_LENGTH;i++) {
        if(Serial1.availableForWrite() > 0) {
            Serial1.write(message[i]);
        } else {
            Serial.println("error!");
            return TRANSMIT_ERR;
        }
    }
    return TRANSMIT_OK;
}


/**
 * prepares and sends a message with UINT64 payload
 *
 * @param payload UINT64 payload
 * @param messageType defines the type of the message
 * @return -1 if sending was not succesful, 1 if sending was succesful
 */
SINT8 sendMessageUint64(UINT64 payload, MESSAGE_TYPE messageType){
    MESSAGE msg = prepareMessageUint64(&payload, messageType);
    return sendMessage((UINT8*) &msg);
}
#define MODULE_1 0
#define MODULE_2 1
#define MODULE_3 2


/**
 * recieves a message from a defined module connected to one of the Serial inputs
 *
 * @param moduleId defines from which module connected to Serial inputs 1-3 the message is read
 * @param buffer buffer in which the read message is written
 * @return -1 for transmission error and otherwise it returns the number of bytes placed in buffer
 */
SINT8 receiveMessage(UINT8 moduleId, MESSAGE* buffer) {
    buffer->payload.asInt = -1;
    buffer->messageStatus = MESSAGE_EMPTY;

    switch(moduleId) {
        case MODULE_1:
            return Serial2.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        case MODULE_2:
            return Serial3.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        case MODULE_3:
            return Serial.readBytes((SINT8*) buffer, MESSAGE_LENGTH);
            break;
        default:
            return TRANSMIT_ERR;
            break;
    }
}

MESSAGE messageBuffer[3][MESSAGE_TYPE_COUNT];


/**
 * reads a message from the messageBuffer at a certain target and a certain message type
 *
 * @param target module ID from which the message was recieved
 * @param messageType type of the message
 * @return message read from messageBuffer
 */
MESSAGE getSamplingMessage(UINT8 target, MESSAGE_TYPE messageType) {
    return messageBuffer[target][messageType];
}


/**
 * reads a recieved message from messageBuffer send from a target module and with a certain message type
 *
 * @param target module ID from which the message was send
 * @param messageType type of the message (e.g. synchronisation message)
 * @return message read from the buffer
 */
MESSAGE receiveQueuingMessage(UINT8 target, MESSAGE_TYPE messageType) {
    MESSAGE tmpBuf;
    tmpBuf = messageBuffer[target][messageType];
    messageBuffer[target][messageType].messageStatus = MESSAGE_CONSUMED;
    return tmpBuf;
}


/**
 *
 */
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

/**
 * initializes rs485 communication via Serial 1-3 by 3 steps:
 * 1. set rs485 to read (serial 1 & 2) and write (serial3)
 * 2. set timeout for serial1-3
 * 3. Serial.begin with defined baud rate for Serial1-3
 *
 */
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

