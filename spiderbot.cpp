#include <Servo.h> //Servo Bibliothek einbinden

Servo sensorservo; //Servo Obejekt erstellen
int pos = 90; //Variable für Servoposition
int trigPin=2; //Trigger an Pin 2
int echoPin=4; //Echo an Pin 4
int richtungA           =12; //Richtung Motor A an Pin 12
int pwmA                =3; //Geschwindigkeit Motor A an Pin 3
int bremseA             =9; //Bremse Motor A an Pin 9
int richtungB           =13; //Richtung Motor B an Pin 13
int pwmB                =11; //Geschwindigkeit Motor B an Pin 11
int bremseB             =8; //Bremse Motor B an Pin 8
int geschwindigkeit_A   =255; //Maximalgeschwindigkeit Motor A festlegen
int geschwindigkeit_B   =255; //Maximalgeschwindigkeit Motor B festlegen

void setup() {
pinMode(richtungA, OUTPUT); //Richtung A als Output definieren
pinMode(richtungB, OUTPUT); //Richtung B als Output definieren
pinMode(bremseA, OUTPUT); //Bremse A als Output definieren
pinMode(bremseB, OUTPUT); //Bremse B als Output definieren analogWrite(pwmA, geschwindigkeit_A); //Wert geschwindigkeit_A auf Pin 3 schreiben
analogWrite(pwmB, geschwindigkeit_B); //Wert geschwindigkeit_B auf Pin 11 schreiben
Serial.begin (9600); //serielle Kommunikation starten
pinMode(trigPin,OUTPUT); //Trigger als Output deklarieren
pinMode(echoPin,INPUT); //Echo als Input deklarieren
sensorservo.attach(5); //Sensorservo an Pin 5

digitalWrite(bremseA, HIGH);  //Motor A aus
digitalWrite(bremseB, HIGH);  //Motor B aus
}

void loop() {

for (pos = 60; pos <= 110; pos += 1) {  //Servo von 65 auf 115 Grad in 1 Grad Schritten 
   sensorservo.write(pos); //Wert an Servo 
    delay(8); //8ms bis zum Erreichen der Endposition 
  }
   
  for (pos = 110; pos >= 60; pos -= 1) {  //Servo von 115 auf 65 Grad in 1 Grad Schritten 
    sensorservo.write(pos); //Wert an Servo
    delay(8); //8ms bis zum Erreichen der Endposition
  }   
  
long duration,distance;              
digitalWrite(trigPin,LOW); //Trigger auf LOW setzen
delayMicroseconds(2); //2ms warten
digitalWrite(trigPin,HIGH); //Trigger auf HIGH setzen
delayMicroseconds(10); //10ms warten
digitalWrite(trigPin,LOW); //Trigger auf LOW setzen
duration = pulseIn(echoPin, HIGH); //Echo Zeit messen
distance=(duration/2)*0.03432; //Zeit in cm umrechnen
if (distance<50) { //Wenn Entfernung kleiner als 50cm...
    digitalWrite(bremseA, HIGH); //Motor A aus
    digitalWrite(bremseB, HIGH); //Motor B aus
    delay(500); //500ms warten
    digitalWrite(bremseA, LOW); //Bremse A lösen
    digitalWrite(bremseB, LOW); //Bremse B lösen
    digitalWrite(richtungA ,LOW); //Motor A rückwärts
    digitalWrite(richtungB ,LOW); //Motor B rückwärts
    delay(5000); //fünf Sekunden warten
    
    digitalWrite(richtungA ,LOW); //Motor A vorwärts
    digitalWrite(richtungB ,HIGH); //Motor B vorwärts
    delay(10000); //eine Sekunde warten
    digitalWrite(bremseA, HIGH); //Motor A aus
    digitalWrite(bremseB, HIGH); //Motor B aus
   }
else { //ansonsten
    delay(2000); //2 Sekunden warten
    digitalWrite(richtungA ,HIGH); //Motor A Vorwärts
    digitalWrite(richtungB ,HIGH); //Motor B Vorwärts
    digitalWrite(bremseA, LOW); //Bremse A lösen
    digitalWrite(bremseB, LOW); //Bremse B lösen
  }
}
