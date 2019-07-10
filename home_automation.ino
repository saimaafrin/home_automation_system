#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial Bluetooth(8,9);
LiquidCrystal lcd(12,11,7,6,5,4);

int Data, LDR;
bool ldr_on = false;

void setup() {
  Bluetooth.begin(9600);
  lcd.begin(16,2);

  pinMode(A0, INPUT);

  pinMode(13,OUTPUT); //LED CONTROL    
  pinMode(10, OUTPUT); //FAN CONTROL
  pinMode(2, OUTPUT); // FAN LOW PIN
  pinMode(3, OUTPUT); // FAN HIGH PIN
  
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("LED:OFF");
  lcd.setCursor(9,0);
  lcd.print("LDR:OFF");
  lcd.setCursor(0, 1);
  lcd.print("FAN:OFF");
  
  
}
void loop() {
  digitalWrite(10,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  LDR = analogRead(A0);
  Serial.println(LDR);
  delay(100);
  if( LDR < 200 && ldr_on == false ) {
      digitalWrite(13,HIGH);
      Bluetooth.println("LDR On! ");
      lcd.setCursor(13, 0);
      lcd.print("ON ");
      ldr_on = true;
  } else if ( LDR >= 200 && ldr_on == true ) {
      digitalWrite(13 , LOW);
      Bluetooth.println("LDR Off! ");
      lcd.setCursor(13, 0);
      lcd.print("OFF");
      ldr_on = false;
  }

  if ( Bluetooth.available() ) {
    Data = Bluetooth.read();

    // LIGHT
    if(Data == 'A') {
      digitalWrite(13,HIGH);
      Bluetooth.println("LED On! ");
      lcd.setCursor(4, 0);
      lcd.print("ON ");
    } else if(Data == 'B') {
      digitalWrite(13 , LOW);
      Bluetooth.println("LED Off! ");
      lcd.setCursor(4, 0);
      lcd.print("OFF");
    }
    
    //FAN
    if(Data=='C'){
      digitalWrite(2,HIGH);
      Bluetooth.println("FAN On!");
      lcd.setCursor(4, 1); 
      lcd.print("ON ");
      delay(100);  
    }
    //FAN OFF
    if(Data=='D'){
      digitalWrite(4,LOW);
      Bluetooth.println("FAN Off! ");
      lcd.setCursor(5, 1);
      lcd.print("OFF");
      delay(100); 
    }
  }
}
