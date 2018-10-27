#include <SoftwareSerial.h>
SoftwareSerial SIM900A(2,3);

int trigPin = 9;    
int echoPin = 8;  
 
long duration, distance ;

/////////////////////////////////////////////////////////////
void setup() {
  
  Serial.begin (9600);
  SIM900A.begin(9600);
   
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    
}
 
void loop()
{  
//sensor 1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  distance = (duration/2) / 29.1;
  
 // inches = (duration/2) / 74; 
  Serial.print("Smart BIN Height : ");
  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(distance);
  Serial.print("cm   ");
  Serial.println("(The Height is not accurate Bin height)");
  delay(3000); 

  
// the selection of distance - to the if statement
  if ( distance <20 && 0< distance )
    SendMessage();

    if (SIM900A.available()>0)
   Serial.write(SIM900A.read());
}

  void SendMessage()
{
  Serial.println ("SIM900A Ready");
  
  //Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"0775501374\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content -> SMS send to the number");
  SIM900A.println("Bin is full.....pleace remove it....!");// Messsage content
  delay(100);
  //Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  //Serial.println ("Message has been sent ->SMS Selesai dikirim");
  delay(5000);
}

