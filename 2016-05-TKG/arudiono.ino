
//転送レートを9600に設定する
void setup() {
Serial.begin(9600);
}

//距離を取り続ける
void loop() {

//センサの値(電圧)を読み取る
int value = analogRead(A0);

//センサの値(電圧)をcmに変換する。
float V_out = (float)value * 5 / 1024;
float distance = (V_out - 0.55)/0.033;
float distance2 = 55 - distance;

//値を転送
Serial.println(distance2);
//0.1秒おきに転送
delay(100);
}