//Communication via RS485 for QUADUINO

#ifndef QUADUINO_SIMPLEX_RS485COM_H
#define QUADUINO_SIMPLEX_RS485COM_H

void rs485comWrite(unsigned int msg, byte toID);
// Sends a message (int msg)
//to a defined reciever (byte ID)

unsigned int rs485comRecieve(byte myID);

#endif
