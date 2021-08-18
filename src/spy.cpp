
#include <SPI.h>
#include <Ethernet.h>
#include "pinprog.h"
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};


// Set the static IP address to use if the DHCP fails to assign

void init_spy() {
    //Ethernet.init(10);  // Most Arduino shields
   // Serial.println("Started Spy...");
   IPAddress ip(10, 10, 0, 10+getModuleId());

   Ethernet.begin(mac, ip);
   if (Ethernet.hardwareStatus() == EthernetNoHardware) {
       Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
   }
   if (Ethernet.linkStatus() == LinkOFF) {
       Serial.println("Ethernet cable is not connected.");
   }

}
EthernetClient client;

void step_spy() {
    Serial.println(Ethernet.localIP());

    client.connect("10.10.0.1", 80);
}


//mosi 51
// scs 10
