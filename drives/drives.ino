char incomingByte;  // входящие данные
int  LED = 12;      // LED подключен к 12 пину
//первый двигатель
int in1_1 = 9;
int in1_2 = 8;
// второй двигатель
int in2_1 = 10;
int in2_2 = 11;
// третий двигатель
int in3_1 = 5;
int in3_2 = 4;
// четвёртый двигатель
int in4_1 = 6;
int in4_2 = 7;


void setup() {
  Serial.begin(9600); // инициализация порта
  pinMode(LED, OUTPUT);
  pinMode(in1_1, OUTPUT);
  pinMode(in1_2, OUTPUT);
  pinMode(in2_1, OUTPUT);
  pinMode(in2_2, OUTPUT);
  pinMode(in3_1, OUTPUT);
  pinMode(in3_2, OUTPUT);
  pinMode(in4_1, OUTPUT);
  pinMode(in4_2, OUTPUT);

  digitalWrite(in1_1, LOW);
  digitalWrite(in1_2, HIGH);
  digitalWrite(in2_1, LOW);
  digitalWrite(in2_2, HIGH);
  digitalWrite(in3_1, LOW);
  digitalWrite(in3_2, HIGH);
  digitalWrite(in4_1, LOW);
  digitalWrite(in4_2, HIGH);    
  
  // Настраиваем цифровой пин 9 на вывод
  pinMode(A0, OUTPUT);
   // Устанавливаем скорость вращения мотора
  analogWrite(A0, 120);    
      
}


int inBytes[10];
int inPos = -1;

void led(){
  if (inBytes[1]=='1')
    digitalWrite(LED,HIGH);
  else
    digitalWrite(LED,LOW);
  
}

void drive(){
  int val;
  if(inBytes[2]=='1') val=HIGH;
  else val = LOW;
  switch(inBytes[1]){
    case '1':
      digitalWrite(in1_1, LOW);
      digitalWrite(in1_2, val);
      Serial.println('1');
    break;
    case '2':
      digitalWrite(in2_1, LOW);
      digitalWrite(in2_2, val);
      Serial.println('2');
    break;
    case '3':
      digitalWrite(in3_1, LOW);
      digitalWrite(in3_2, val);
     Serial.println('3');

    break;
    case '4':
      digitalWrite(in4_1, LOW);
      digitalWrite(in4_2, val);
      Serial.println('4');
    break;    
  }

  
}


void processComm(){
  switch(inBytes[0]){
    case 'l':
      led();
      break;
   case 'd':
      drive();
      break;   

    
 }
  inPos = -1;
}

void loop() {
  while (Serial.available() > 0) {  //если пришли данные
    incomingByte = Serial.read(); // считываем байт
    if(incomingByte=='d'||incomingByte=='l')
      inPos = 0;
    inBytes[inPos++]=incomingByte;

    if (incomingByte=='/')
      processComm();
  }
  delay(100);
  
}

