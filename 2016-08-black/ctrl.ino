int Ain0 = A0;
int Ain1 = A1;

int val0 = 0;
int val1 = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  val0 = analogRead(Ain0);
  val1 = analogRead(Ain1);

  if(val0 >= 0 && val0 <= 100){
    //Serial.println(1);
    Serial.write(1);
  }
  else if(val0 <= 1025 && val0 >= 900){
    //Serial.println(2);
    Serial.write(2);
  }else if(val1 >= 0 && val1 <= 100){
    //Serial.println(3);
    Serial.write(3);
  }else if(val1 <= 1025 && val1 >= 900){
    //Serial.println(4);
    Serial.write(4);
  }else{
    //Serial.println(0);
    Serial.write(0);
  }

  //delay(1);
}
