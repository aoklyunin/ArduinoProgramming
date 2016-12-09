#include "DHT.h"

#define DHTPIN A5     // what digital pin we're connected to
#define DHTPIN2 A0     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
int inBytes[10];
int inPos = -1;

int en1 = 10;
int en2 = 9;
int en3 = 6;
int en4 = 3;


int ina1 = 13;
int inb1 = 12;
int ina2 = 8;
int inb2 = 11;

int ina3 = 7;
int inb3 = 5;
int ina4 = 2;
int inb4 = 4;


// второй двигатель

void setup()
{
// инициализируем все пины для управления двигателями как outputs

pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(en3, OUTPUT);
pinMode(en4, OUTPUT);



analogWrite(en1, 90);
analogWrite(en2, 90);
analogWrite(en3, 90);
analogWrite(en4, 90);


pinMode(ina1, OUTPUT);
pinMode(inb1, OUTPUT);
pinMode(ina2, OUTPUT);
pinMode(inb2, OUTPUT);
pinMode(ina3, OUTPUT);
pinMode(inb3, OUTPUT);
pinMode(ina4, OUTPUT);
pinMode(inb4, OUTPUT);


digitalWrite(inb1, LOW);
digitalWrite(ina1, HIGH);
digitalWrite(inb2, LOW);
digitalWrite(ina2, HIGH);
digitalWrite(inb3, LOW);
digitalWrite(ina3, HIGH);
digitalWrite(inb4, LOW);
digitalWrite(ina4, HIGH);




Serial.begin(9600);

dht.begin();
pinMode(A4, OUTPUT);
digitalWrite(A4,LOW);
pinMode(A3, OUTPUT);
digitalWrite(A3,HIGH);

dht2.begin();
pinMode(A1, OUTPUT);
digitalWrite(A1,LOW);
pinMode(A2, OUTPUT);
digitalWrite(A2,HIGH);
}


void drive(){
  int val;
  if(inBytes[2]=='1') val=HIGH;
  else val = LOW;
  
  switch(inBytes[1]){
    case '1':
      digitalWrite(inb1, LOW);
      digitalWrite(ina1, val);
      analogWrite(en1,inBytes[3]);
      Serial.println('1');
    break;
    case '2':
      digitalWrite(inb2, LOW);
      digitalWrite(ina2, val);
      analogWrite(en2,inBytes[3]);
      Serial.println('2');
    break;
    case '3':
      digitalWrite(inb3, LOW);
      digitalWrite(ina3, val);
      analogWrite(en3,inBytes[3]);
      Serial.println('3');

    break;
    case '4':
      digitalWrite(inb4, LOW);
      digitalWrite(ina4, val);
      analogWrite(en4,inBytes[3]);
      Serial.println('4');
    break;    
  }
}


void processComm(){
  switch(inBytes[0]){
   case 'd':
      drive();
      break;       
 }
  inPos = -1;
}

void dispTemp(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    return;
  }
  Serial.print("h1");
  Serial.print(String(h));
  Serial.print("/t1");
  Serial.print(String(t));
  Serial.print("/");

  h = dht2.readHumidity();
 // Read temperature as Celsius (the default)
  t = dht2.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    return;
  }
  Serial.print("h2");
  Serial.print(String(h));
  Serial.print("/t2");
  Serial.print(String(t));
  Serial.println("/");
}

void loop() {
  
  while (Serial.available() > 0) {  //если пришли данные
    char incomingByte = Serial.read(); // считываем байт
    if(incomingByte=='d')
      inPos = 0;
    inBytes[inPos++]=incomingByte;

    if (incomingByte=='/')
      processComm();
    
  }
  dispTemp();
  delay(2000);
  
}
