//In diesem Sketch sendet ein Arduino MEGA über die erste Serielle
//Schnittstelle (RX0/TX0) die über RS485 Konverter an einem RS485 Bus
//angeschlossen ist.
//An gleichem RS485 BUS sind die drei anderen Seriellen Schnittstellen
//ebenfalls über RS485 Konverter angeschlossen
//und empfangen die gesendeten Daten. Anhand von je einer LED
//pro empfangender Seriellen Schnittstelle (also insgesamt 3 LEDs)
//kann festgestellt werden, ob an allen Seriellen Schnittstellen
//etwas empfangen wird.

//MASTER_CODE
//Pins zur Sende/Empfang schaltung der Module
const int sendModAkt = 2; //Modul das sendet
const int empfModRX1 = 3; //Modul das empfängt
const int empfModRX2 = 4; //Modul das empfängt
const int empfModRX3 = 5; //Modul das empfängt

//Leds zur Anzeige ob auf dem entsprechenden Modul empfangen wird
const int ledPinRX1 = 26; // LED für Modul das auf TX1/RX1 verbunden ist
const int ledPinRX2 = 28; // LED für Modul das auf TX2/RX2 verbunden ist
const int ledPinRX3 = 30; // LED für Modul das auf TX3/RX3 verbunden ist



void setup() {
  // put your setup code here, to run once:
  pinMode(sendModAkt, OUTPUT);
  pinMode(empfModRX1, OUTPUT);
  pinMode(empfModRX2, OUTPUT);
  pinMode(empfModRX3, OUTPUT);

  pinMode(ledPinRX1, OUTPUT);
  pinMode(ledPinRX2, OUTPUT);
  pinMode(ledPinRX3, OUTPUT);

  digitalWrite(sendModAkt, HIGH);
  digitalWrite(empfModRX1, LOW);
  digitalWrite(empfModRX2, LOW);
  digitalWrite(empfModRX3, LOW);

  delay(10);

  //Starten der Seriellen Übertragung an allen 4 Seriellen
  //Schnittstellen
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  delay(10);



}

void loop() {

  Serial.write(HIGH);//HIGH wird auf RX0/TX0 geschrieben

  //Falls Daten auf dem RS 485 von den anderen Seriellen Schnitstellen
  //empfangen wird, wird der empfangene Wert auf den PIN für die LED
  // der ensprechenden Seriellen Schnittstelle geschrieben.

  if(Serial1.available()){
    digitalWrite(ledPinRX1, Serial1.read());
    }
  if(Serial2.available()){
    digitalWrite(ledPinRX2, Serial2.read());
    }
  if(Serial3.available()){
    digitalWrite(ledPinRX3, Serial3.read());
    }
    delay(500);

  Serial.write(LOW);//LOW wird auf RX0/TX0 geschrieben

  //Falls Daten auf dem RS 485 von den anderen Seriellen Schnitstellen
  //empfangen wird, wird der empfangene Wert auf den PIN für die LED
  // der ensprechenden Seriellen Schnittstelle geschrieben.

  if(Serial1.available()){
    digitalWrite(ledPinRX1, Serial1.read());
    }
  if(Serial2.available()){
    digitalWrite(ledPinRX2, Serial2.read());
    }
  if(Serial3.available()){
    digitalWrite(ledPinRX3, Serial3.read());
    }
    delay(500);
}
