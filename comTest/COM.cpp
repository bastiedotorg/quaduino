#include <Arduino.h>
#include "COM.h"

#define AKTPIN_OUT    5   //RS485 Modul an RX/TX     
#define AKTPIN_IN_1   2   //RS485 Modul an RX1/TX1
#define AKTPIN_IN_2   3   //RS485 Modul an RX2/TX2
#define AKTPIN_IN_3   4   //Rs485 Modul an RX3/TX3


nachricht initalizeMsg(unsigned int payload){
  nachricht message;
  message.einAus = payload;
  return message;
  }

int sendMsg(unsigned int payload){
  
  nachricht msg;
  msg = initalizeMsg(payload);
  
  if(Serial.availableForWrite()>sizeof(msg.statusB)){
    Serial.write(msg.statusB,sizeof(msg.statusB));
    Serial.flush();
    }
    return 0;
  }

int readMsg(int ModulId){       //ModulId meint hier noch die RS485 Module (Modul 1 = Rs485 Modul an RX1/TX1 etx.)
  nachricht message;

  if(ModulId == 1){  
    
      if(Serial1.readBytes(message.statusB, sizeof(message.statusB)) == 2){
        return message.einAus;
        }
         
  }else if (ModulId == 2){  
    
      if(Serial2.readBytes(message.statusB, sizeof(message.statusB)) == 2){
        return message.einAus;
        }
         
  }else if(ModulId == 3){ 

      if(Serial2.readBytes(message.statusB, sizeof(message.statusB)) == 2){
        return message.einAus;
        }      
  }           
}
void rs485Init(){      //Muss im "Setup" im "main" aufgerufen werden 

  pinMode(AKTPIN_OUT, OUTPUT);
  pinMode(AKTPIN_IN_1, OUTPUT);
  pinMode(AKTPIN_IN_2, OUTPUT);
  pinMode(AKTPIN_IN_3, OUTPUT);

  digitalWrite(AKTPIN_OUT, HIGH);
  digitalWrite(AKTPIN_IN_1, LOW);
  digitalWrite(AKTPIN_IN_2, LOW);
  digitalWrite(AKTPIN_IN_3, LOW);

  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
    
  }
