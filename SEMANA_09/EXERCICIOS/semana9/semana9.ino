#include <LiquidCrystal_I2C.h>

#define SDA 4
#define SCL 5

LiquidCrystal_I2C LCD(0x27, 16, 2);

String password;
bool passwordIsSet = false;

bool comparePasswords(int *pass1, int *pass2);
void copyPasswords(int *pass1, int *pass2);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  pinMode(RGB_BUILTIN, OUTPUT);
}

void loop() {
    if(passwordIsSet){
      Serial.println("Digite a senha:");
    }
    else{
      Serial.println("Cadastre uma senha de 4 digitos:");
    }
    while (Serial.available() == 0) {  
    }

    String try_password = Serial.readString();
    if(try_password.length() != 5) // 4 digitos + "\n"
      Serial.println("Senha digitada inválida!");
    else{
      if(passwordIsSet){
        if(try_password == password){
          Serial.println("Senha correta!");
          lcd.setCursor(0,0);
          lcd.print("Senha correta!");
          neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0);
          delay(1000);
          digitalWrite(RGB_BUILTIN, LOW);
          lcd.clear();
        }
        else{
          Serial.println("Senha errada!");
          lcd.setCursor(0,0);
          lcd.print("Senha errada!");
          neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); // red
          delay(1000);
          digitalWrite(RGB_BUILTIN, LOW);
          lcd.clear();
        }
      }
      else{
        password = try_password;
        passwordIsSet = true;
        Serial.println("Senha cadastrada!");
      }
    }
}

bool comparePasswords(char *pass1, char *pass2){
  for(int i=0; i<4; i++){
    if(pass1[i] != pass2[i])
      return false;
  }
  return true;
}

void copyPasswords(char *pass1, char *pass2){
  for(int i=0; i<4; i++){
    pass1[i] = pass2[i];
  }
}
