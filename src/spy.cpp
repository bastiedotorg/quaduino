
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};


// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 10, 0, 10);

void init_spy() {
    Ethernet.init(10);  // Most Arduino shields
   // Serial.println("Started Spy...");
   if (Ethernet.begin(mac) == 0) {
       Serial.println("Failed to configure Ethernet using DHCP");
       // Check for Ethernet hardware present
       // try to congifure using IP address instead of DHCP:
       Ethernet.begin(mac, ip);
   } else {
       Serial.print("  DHCP assigned IP ");
       Serial.println(Ethernet.localIP());
   }

}


//mosi 51
// scs 10
