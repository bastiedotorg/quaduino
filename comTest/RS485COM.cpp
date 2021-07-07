//Communication via RS485 for QUADUINO

#include <Arduino.h>
#include "RS485COM.h"

void rs485comWrite(unsigned int msg, byte toID){
  Serial.write(toID);
  Serial.write(msg);
}


unsigned int rs485comRecieve(byte myID){
    if (Serial1.available()){
      if (myID == Serial1.read()){
        return Serial.read();
      }else {
        return 0;
      }
    }else if (Serial2.available()){
      if(myID == Serial2.read()){
        return Serial.read();
      }else{
        return 0;
      }
    }else if (Serial3.available()){
      if (myID == Serial3.read()){
        return Serial3.read();
      }else{
        return 0;
      }
    }
}
