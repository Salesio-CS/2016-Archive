int val = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(10,OUTPUT); //PWMA
  analogWrite(10,100);
  pinMode(12,OUTPUT); //AIN2
  pinMode(13,OUTPUT); //AIN1

  pinMode(11,OUTPUT); //PWMB
  analogWrite(11,100);
  pinMode(14,OUTPUT); //BIN1
  pinMode(15,OUTPUT); //BIN2

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0) val=Serial.read();
  if(val==1){ digitalWrite(12,HIGH); }//点灯
  if(val==2){ digitalWrite(13,HIGH); }//点灯
  if(val==3){ digitalWrite(14,HIGH); }//点灯
  if(val==4){ digitalWrite(15,HIGH); }//点灯
  if(val==0)
  {
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    digitalWrite(14,LOW);
    digitalWrite(15,LOW);
  }
}
