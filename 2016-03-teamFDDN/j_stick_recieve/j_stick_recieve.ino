// Recieved value
#define F_STRAIGHT 0
#define D_STRAIGHT 1
#define S_STRAIGHT 2
#define RIGHT 3
#define LEFT 4
#define S_BACK 5
#define D_BACK 6
#define F_BACK 7
#define R_STOP 9

// use port
#define L_MOTOR 10 // use PWM
#define R_MOTOR 11 // use PWM
#define L_CONTROL 8
#define R_CONTROL 9

// motor power
#define SLOW 50
#define MIDDLE 155
#define TOP 255
#define STOP 0

void setup() {
  Serial.begin(115200);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);
  pinMode(L_CONTROL, OUTPUT);
  pinMode(R_CONTROL, OUTPUT);
}

void loop() {
  int Control = 0;

  Control = Serial.read();
  Serial.println(Control);

  switch(Control){
    case F_STRAIGHT:
      digitalWrite(L_CONTROL, LOW);
      digitalWrite(R_CONTROL, LOW);
      analogWrite(L_MOTOR, TOP);
      analogWrite(R_MOTOR, TOP);
      break;

    case D_STRAIGHT:
      digitalWrite(L_CONTROL, LOW);
      digitalWrite(R_CONTROL, LOW);
      analogWrite(L_MOTOR, MIDDLE);
      analogWrite(R_MOTOR, MIDDLE);
      break;

    case S_STRAIGHT:
      digitalWrite(L_CONTROL, LOW);
      digitalWrite(R_CONTROL, LOW);
      analogWrite(L_MOTOR, SLOW);
      analogWrite(R_MOTOR, SLOW);
      break;

    case RIGHT:
      digitalWrite(L_CONTROL, LOW);
      digitalWrite(R_CONTROL, HIGH);
      analogWrite(L_MOTOR, TOP);
      analogWrite(R_MOTOR, SLOW);
      break;

    case LEFT:
      digitalWrite(L_CONTROL, HIGH);
      digitalWrite(R_CONTROL, LOW);
      analogWrite(L_MOTOR, SLOW);
      analogWrite(R_MOTOR, TOP);
      break;

    case S_BACK:
      digitalWrite(L_CONTROL, HIGH);
      digitalWrite(R_CONTROL, HIGH);
      analogWrite(L_MOTOR, SLOW);
      analogWrite(R_MOTOR, SLOW);
      break;

    case D_BACK:
      digitalWrite(L_CONTROL, HIGH);
      digitalWrite(R_CONTROL, HIGH);
      analogWrite(L_MOTOR, MIDDLE);
      analogWrite(R_MOTOR, MIDDLE);
      break;

    case F_BACK:
      digitalWrite(L_CONTROL, HIGH);
      digitalWrite(R_CONTROL, HIGH);
      analogWrite(L_MOTOR, TOP);
      analogWrite(R_MOTOR, TOP);
      break;

    case R_STOP:
      digitalWrite(L_CONTROL, LOW);
      digitalWrite(R_CONTROL, LOW);
      analogWrite(L_MOTOR, STOP);
      analogWrite(R_MOTOR, STOP);
      break;
  }
}
