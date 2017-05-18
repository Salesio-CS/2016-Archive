// LR 0 - 335 - 671  Left - Center - Right
// UD 0 - 330 - 671  Down - Center - Up
// +-100以上でモーター作動
// +-100から+-85まで普通速度
// +-255から高速

// Joy stick threshold
#define STOP 75
#define DEF 175
#define FAST 275
#define TURN_R 175
#define TURN_L -175
#define REVERSE -75
#define REV_DEF -175
#define REV_FAST -275

// Send value
#define F_STRAIGHT 0
#define D_STRAIGHT 1
#define S_STRAIGHT 2
#define RIGHT 3
#define LEFT 4
#define S_BACK 5
#define D_BACK 6
#define F_BACK 7
#define R_STOP 9

int UDOffset(int value);
int LROffset(int value);

void setup() {
  Serial.begin(115200);
}


void loop() {
  int LR, UD;
  LR = analogRead(0);
  UD = analogRead(1);

  if(!(UDOffset(UD) < STOP)){          // 走り始める条件(前方向)

    if(UDOffset(UD) > FAST){           // 高速
      if(LROffset(LR) > TURN_R){       // 右折
        Serial.println("Right");
        Serial.write(RIGHT);
      }else if(LROffset(LR) < TURN_L){ // 左折
        Serial.println("Left");
        Serial.write(LEFT);
      }else{                           // それ以外は直進
        Serial.println("Straight-Fast");
        Serial.write(F_STRAIGHT);
      }

    }else if(UDOffset(UD) > DEF){      // 通常速度
      if(LROffset(LR) > TURN_R){       // 右折
        Serial.println("Right");
        Serial.write(RIGHT);
      }else if(LROffset(LR) < TURN_L){ // 左折
        Serial.println("Left");
        Serial.write(LEFT);
      }else{                           // それ以外は直進
        Serial.println("Straight-Default");
        Serial.write(D_STRAIGHT);
      }
    }else{                             // 低速
      if(LROffset(LR) > TURN_R){       // 右折
        Serial.println("Right");
        Serial.write(RIGHT);
      }else if(LROffset(LR) < TURN_L){ // 左折
        Serial.println("Left");
        Serial.write(LEFT);
      }else{                           // それ以外は直進
        Serial.println("Straight-Slow");
        Serial.write(S_STRAIGHT);
      }
    }

  }else if(UDOffset(UD) < REVERSE){    // 後退
    if(UDOffset(UD) < REV_FAST){       // 高速
      Serial.println("Back-fast");
      Serial.write(F_BACK);
    }else if(UDOffset(UD) < REV_DEF){
      Serial.println("Back-Default");  // 通常速度
      Serial.write(D_BACK);
    }else{                             // 低速
      Serial.println("Back-Slow");
      Serial.write(S_BACK);
    }
  }else{
    Serial.println("Stop");
    Serial.write(R_STOP);              // 停止
  }
  delay(200);
}

int UDOffset(int value){
  return (value - 330);
}

int LROffset(int value){
  return (value - 335);
}
