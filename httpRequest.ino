#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void makeHttpsRequest(){
      mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
    delay(wait);
    while (mySerial.available())
    {
        Serial.write(mySerial.read());
    }

    mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
    delay(wait);
    while (mySerial.available())
    {
        Serial.write(mySerial.read());
    }

    mySerial.println("AT+SAPBR=1,1");
    delay(10000);
    while (mySerial.available())
    {
        Serial.write(mySerial.read());
    }
    mySerial.println("AT+SAPBR=2,1");
    delay(5000);
    while (mySerial.available())
    {
        Serial.write(mySerial.read());
    }

       delay(4000);
    {
        Serial.write(mySerial.read());
    }
    mySerial.print(("AT+HTTPPARA=\"URL\",\"http://example.com/rest-api?getrequest="));
    mySerial.print(server_message);
    mySerial.println("\"");
    {
        Serial.write(mySerial.read());
    }

    mySerial.println("AT+HTTPACTION=0");
    delay(2000);
    {
        Serial.write(mySerial.read());
    }
}