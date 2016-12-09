int T1 = A5;
int T2 = A4;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void showT(){
  double val = analogRead(T1);
  double voltage = val*5.0/1024;
  double temp = voltage*100 - 273.15;
  Serial.print("t1"+String(temp)+"/");
  val = analogRead(T2);
  voltage = val*5.0/1024;
  temp = voltage*100 - 273.15;
  Serial.println("t2"+String(temp)+"/");
}


void loop() {
  // put your main code here, to run repeatedly:
 showT();
 delay(100);
}
