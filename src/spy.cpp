
#include <SPI.h>
#include <Ethernet.h>
#include "pinprog.h"
#include "database.h"
#include <ArduinoJson.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

#define SPY_SERVER "10.10.0.100"
#define SPY_PORT 8081
// Set the static IP address to use if the DHCP fails to assign

/**
 * Set the static IP address to use if the DHCP fails to assign
 */
EthernetClient client;
void init_spy() {
    //Ethernet.init(10);  // Most Arduino shields
   // Serial.println("Started Spy...");
   IPAddress ip(10, 10, 0, 10+getModuleId());
   mac[0] = 0xDE + getModuleId();

   Ethernet.begin(mac, ip);
   if (Ethernet.hardwareStatus() == EthernetNoHardware) {
   }
   if (Ethernet.linkStatus() == LinkOFF) {
   }
    client.setConnectionTimeout(50);
}

/**
 *
 */
void step_spy() {
    long* pData;
    StaticJsonDocument<256> doc;
    long size, i;
    String requestBody;
    JsonArray dbc = doc.createNestedArray("dbc");
    JsonArray dbi = doc.createNestedArray("dbi");
    doc["ip"] = Ethernet.localIP();
    if(client.connect(SPY_SERVER, SPY_PORT)) {
        for(i=0;i<16;i++) {
            dbi.add(readDBindi(i));
        }
        for(i=0;i<16;i++) {
            dbc.add(readDBcss(i));
        }
        serializeJson(doc, requestBody);
        client.println("POST /spy HTTP/1.1");
        client.print("Host: ");
        client.println(SPY_SERVER);
        client.println("Content-Type: application/json;charset=utf-8");
        client.println("Connection: close");
        client.print("Content-Length: ");
        client.println(requestBody.length());
        client.println();
        client.println(requestBody);
        client.println();
        client.flush();
        client.stop();
    }

}


//mosi 51
// scs 10
