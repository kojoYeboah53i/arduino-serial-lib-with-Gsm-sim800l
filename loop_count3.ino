/*
*  Read the readme.txt file for details about the project.
*
*
*/
#include <SoftwareSerial.h>


SoftwareSerial mySerial(11, 10); // RX, TX


char data;
int open_ = 8;
int close_ = 7;
int third = 9;
String stringOne, stringTwo;

void send_sms( String barrier_off) ;
void send_sms1( String barrier_off) ;
void send_sms2( String barrier_off) ;

void reboot();
void spit_all() ;
int sms_sensorValue ;
int sms_sensorValue1 ;
int sms_sensorValue2 ;

bool sms_is_present = false;
bool sms_is_present1 = false;
bool sms_is_present2 = false;
bool sms_start = false;
bool sms_start1 = false;
bool sms_start2 = false;
bool msg = false;
bool msg_power = false;
bool msg_control = false;
bool sent = false;
bool is_sent = false;
bool is_sent_power = false;

bool is_sent_control = false;

int sensorValue ;
int sensorValue1 ;
int sensorValue2 ;
int sensorValue3 ;
bool is_present = false;
bool is_present1 = false;
bool is_present2 = false;
bool is_present3 = false;
bool start = false;
bool start1 = false;
bool start2 = false;
bool start3 = false;


const int clear_pins[] = {2, 3, 4, 5, A3, A4, A5  };
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  for (int i = 0; i < 9 ; i++){
    pinMode(clear_pins[i], INPUT_PULLUP);
  }
       pinMode(13, OUTPUT);
  pinMode(third, OUTPUT);
  pinMode(open_, OUTPUT);
  pinMode(close_, OUTPUT);

  digitalWrite(open_, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(close_, HIGH);
  digitalWrite(third, HIGH);

  Serial.println("Ready !!!");

  delay(10000);





  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("AT");
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }

        
  mySerial.println("AT+CMGF=0"); // Configuring TEXT mode
  delay(2000);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  
  sms_sensorValue = digitalRead(A4);

  if (sms_sensorValue == 0) {
//    Serial.println("ECG power restored at destination-B1 B1");
    send_sms("destination-B1 B1 System Turned On");
    spit_all();
    send_sms1("destination-B1 B1 System Turned On");
    spit_all();
    send_sms2("destination-B1 B1 System Turned On");

    sms_sensorValue = "";
  }
  delay(5000);
  sms_sensorValue2 = digitalRead(A3);

  if (sms_sensorValue2 == 0) {
//    Serial.println("destination-B1 B1 Control Box has been closed");
    send_sms("destination-B1 B1 Control Box has been closed");
    spit_all();
    send_sms1("destination-B1 B1 Control Box has been closed");
    spit_all();
    send_sms2("destination-B1 B1 Control Box has been closed");

    sms_sensorValue2 = "";
  }
  delay(10000);
  sms_sensorValue1 = digitalRead(A5);

  if (sms_sensorValue1 == 0) {
//    Serial.println("destination-B1 B1 barrier turned on ");
    send_sms("destination-B1 B1 barrier turned on ");
    spit_all();
    send_sms1("destination-B1 B1 barrier turned on ");
    spit_all();
    send_sms2("destination-B1 B1 barrier turned on ");

    sms_sensorValue1 = "";
  }

  // sms_sensorValue = digitalRead(A5);


  sms_is_present = true;

  sms_is_present1 = true;

  sms_is_present2 = true;

  is_sent = true;

  is_sent_power = true;

  is_sent_control = true;
  Serial.println("ready to try");


}



void loop() {
  sensorValue = digitalRead(2);
  sensorValue1 = digitalRead(3);
  sensorValue2 = digitalRead(4);
  sensorValue3 = digitalRead(5);

  if (Serial.available()) {

    stringOne = Serial.readString();
    stringOne.trim();


    if  (stringOne == "open") {
      digitalWrite(open_, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(close_, HIGH);
      digitalWrite(third, HIGH);
      delay(1000);                       // wait for a second
      digitalWrite(open_, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println("o");
    }

    if  (stringOne == "close") {
      digitalWrite(close_, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(open_, HIGH);
      digitalWrite(third, HIGH);
      delay(1000);                       // wait for a second
      digitalWrite(close_, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println("c");
    }

      digitalWrite(13, LOW);


    if  (stringOne == "third") {
      digitalWrite(close_, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(open_, LOW);
      digitalWrite(third, LOW);
      delay(1000);  
      digitalWrite(third, HIGH);
      Serial.println("t");
    }

  }
  {
    if (sensorValue > 0) {
      start = true;
      is_present = true;


      // digitalWrite(13, HIGH);
      //   delay(3000);

    } else {
      digitalWrite(13, LOW);
      is_present = false;

    }

     if (sensorValue1 > 0) {

      start1 = true;
      is_present1 = true;
   


    } else {
      digitalWrite(13, LOW);
      is_present1 = false;

    }


    if (sensorValue2 > 0) {

      start2 = true;
      is_present2 = true;


      // digitalWrite(13, HIGH);
      //   delay(3000);


    } else {
      digitalWrite(13, LOW);
      is_present2 = false;
    }

 if (sensorValue3 > 0) {

      start3 = true;
      is_present3 = true;

      // digitalWrite(13, HIGH);
      //   delay(3000);

    } else {
      digitalWrite(13, LOW);
      is_present3 = false;

    }
//sends count only after sensor stops reading 
    if (start && !is_present ) {
      start = false;
      Serial.println("a");
         digitalWrite(13, HIGH);
        delay(3000);
      sensorValue = -1;
      sensorValue1 = -1;
      sensorValue2 = -1;
      sensorValue3 = -1;
   
    }

    if (start1 && !is_present1 ) {
      start1 = false;
      Serial.println("b");
        digitalWrite(13, HIGH);
        delay(3000);
      sensorValue = -1;
      sensorValue1 = -1;
      sensorValue2 = -1;
      sensorValue3 = -1;
    }

    if (start2 && !is_present2 ) {
      start2 = false;
      Serial.println("q");
        digitalWrite(13, HIGH);
        delay(3000);
      sensorValue = -1;
      sensorValue1 = -1;
      sensorValue2 = -1;
      sensorValue3 = -1;
    }

    if (start3 && !is_present3 ) {
      start3 = false;
      Serial.println("d");
        digitalWrite(13, HIGH);
        delay(3000);
      sensorValue = -1;
      sensorValue1 = -1;
      sensorValue2 = -1;
      sensorValue3 = -1;
    }


  }

  sms_sensorValue = digitalRead(A5);


  if (sms_sensorValue == 0) {
    //     spit_all();
    msg = true;  //connected
    //  is_sent = true;
    sms_start = true;
    sms_is_present = true;  //loop break
    digitalWrite(13, HIGH);

  } else {
    digitalWrite(13, LOW);
    sms_is_present = false; //loop break

    is_sent = false;   //connected
    msg = false;
  }

  if (sms_start && !sms_is_present ) {
    sms_start = false;
    delay(5000);
//    Serial.println("destination-B1 B1 barrier turned off ");
    send_sms(" destination-B1 B1 barrier turned off ");
    delay(5000);
    spit_all() ;
    send_sms1(" destination-B1 B1 barrier turned off ");
    spit_all() ;
    delay(5000);
    send_sms2(" destination-B1 B1 barrier turned off ");

    sms_sensorValue = "";
  }

  if ( msg && !is_sent) {


//    Serial.println("barrier turned on ");
    send_sms("destination-B1 B1 barrier turned on ");
    delay(5000);
    spit_all();
    send_sms1("destination-B1 B1 barrier turned on ");
    delay(5000);
    spit_all();
    send_sms2("destination-B1 B1 barrier turned on ");


    is_sent = true;
  }


  sms_sensorValue1 = digitalRead(A4);


  if (sms_sensorValue1 == 0) {

    msg_power = true;  //connected

    sms_start1 = true;
    sms_is_present1 = true;  //loop break
    digitalWrite(13, HIGH);

  } else {
    digitalWrite(13, LOW);
    sms_is_present1 = false; //loop break

    is_sent_power = false;   //connected
    msg_power = false;
  }

  if (sms_start1 && !sms_is_present1 ) {
    sms_start1 = false;

//    Serial.println("Light off at destination-B1 and running on UPS");
    send_sms("Light off at destination-B1 B1 and running on UPS");
    delay(5000);
    spit_all() ;
    send_sms1("Light off at destination-B1 B1 and running on UPS");
    delay(5000);
    spit_all() ;
    send_sms2("Light off at destination-B1 B1 and running on UPS");

    sms_sensorValue1 = "";
  }

  if ( msg_power && !is_sent_power) {


//    Serial.println("ECG power restored at destination-B1 B1");
    send_sms("ECG power restored at destination-B1 B1");
    delay(5000);
    spit_all();
    send_sms1("ECG power restored at destination-B1 B1");
    delay(5000);
    spit_all();
    send_sms2("ECG power restored at destination-B1 B1");



    is_sent_power = true;
  }

  sms_sensorValue2 = digitalRead(A3);


  if (sms_sensorValue2 == 0) {
    msg_control = true;  //connected

    sms_start2 = true;
    sms_is_present2 = true;  //loop break
    digitalWrite(13, HIGH);

  } else {
    digitalWrite(13, LOW);
    sms_is_present2 = false; //loop break

    is_sent_control = false;   //connected
    msg_control = false;
  }

  if (sms_start2 && !sms_is_present2 ) {
    sms_start2 = false;

//    Serial.println("destination-B1 B1 Control Box has been tempared with");
    send_sms("destination-B1 B1 Control Box has been tempared with");
    delay(5000);
    // reboot();
    spit_all() ;

    send_sms1("destination-B1 B1 Control Box has been tempared with");
    delay(5000);
    spit_all() ;
    send_sms2("destination-B1 B1 Control Box has been tempared with");

    sms_sensorValue2 = "";
  }
  //   reboot();
  if ( msg_control && !is_sent_control) {


//    Serial.println("destination-B1 B1 Control Box has been closed");
    send_sms("destination-B1 B1 Control Box has been closed");
    spit_all();
    delay(5000);
    send_sms1("destination-B1 B1 Control Box has been closed");
    spit_all();
    delay(5000);
    send_sms2("destination-B1 B1 Control Box has been closed ");

    // spit_all() ;// reboot();
    is_sent_control = true;
  }
  //  spit_all();

}


void send_sms( String barrier_off) {
  /****************************************************************/
  /*********************/
  //send text message
  /***********************/
       Serial.println("#");

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.println("AT+CMGS=\"+233244769694\"");
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.print(barrier_off); //text content
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.write(26);

  //reboot() ;
}



void send_sms1( String barrier_off) {
  /****************************************************************/
  /*********************/
  //send text message
  /***********************/

     Serial.println("#");

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.println("AT+CMGS=\"+233542235971\"");
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.print(barrier_off); //text content
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.write(26);

  //reboot() ;
}



void send_sms2( String barrier_off) {
  /****************************************************************/
  /*********************/
  //send text message
  /***********************/

     Serial.println("#");

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.println("AT+CMGS=\"+233203401300\"");
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.print(barrier_off); //text content
  delay(200);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  mySerial.write(26);

  //reboot() ;
}

void reboot() {

  mySerial.println("AT+CFUN=0");
  delay(2000);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }

  mySerial.println("AT+CFUN=1");
  delay(2000);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}

void spit_all() {

  mySerial.println("AT");
  delay(2000);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }

  mySerial.println("AT");
  delay(2000);
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}
