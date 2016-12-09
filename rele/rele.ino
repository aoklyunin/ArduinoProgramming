int pins [] = {13,12,11,10,9,8,7,6};

int inBytes[10];
int inPos = -1;
// второй двигатель

void setup()
{
// инициализируем все пины для управления двигателями как outputs

Serial.begin(9600);
for(int i=0;i<8;i++){
pinMode(pins[i], OUTPUT);
digitalWrite(pins[i],LOW);
//Serial.println(pins[i]);
}
 digitalWrite(pins[0],HIGH);


}


void rele(){
  for(int i=0;i<8;i++){   
    digitalWrite(pins[i],LOW);
  }
  int n =inBytes[1]-'0'-1;
  if(n>=0&&n<8){    
    digitalWrite(pins[n],HIGH);
  }
  //Serial.println(String(n));
  
}


void processComm(){
  switch(inBytes[0]){
   case 'r':
      rele();
      break;       
 }
  inPos = -1;
}

void loop() {  
  while (Serial.available() > 0) {  //если пришли данные
    char incomingByte = Serial.read(); // считываем байт
    if(incomingByte=='r')
      inPos = 0;
    inBytes[inPos++]=incomingByte;

    if (incomingByte=='/')
       processComm();
    
  }
  delay(1000);
  
}
