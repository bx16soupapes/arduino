#include <LiquidCrystal.h>

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
  
int down = 3;
int select = 4;
int up = 5;

void setup() {
  Serial.begin(9600);  
  lcd.begin(16, 2);
  menu();
}

void loop() {
  //nothing to loop but is required in every sketch.
}


void menu() {
  while(digitalRead(up) == HIGH or digitalRead(down) == HIGH or digitalRead(select) == HIGH){};
  delay(50);
  LCDclear();
  LCDfirst();
  if(prognumber > 1){
  prognumber--;
  }
  else{
    prognumber == 1;
  }
  LCDmenudisplay();
  LCDsecond();
  prognumber++;
  LCDmenudisplay();
  if(line == 1){
//    lcd.print(0xFE);////lcd.print  
//    lcd.print(143);
    lcd.print("<");
  }
  else {
//    lcd.print(0xFE);
//    lcd.print(207);
    lcd.print("<");
  }
  while(digitalRead(up) == LOW && digitalRead(down) == LOW && digitalRead(select) == LOW){}
  if(digitalRead(down) == HIGH){
  line++;
  if(line > 2){
  line = 2;
  prognumber++;
  if(prognumber > 4){
  prognumber = 5;
  }
  }
  menu();
  }
  else if(digitalRead(up) == HIGH){
  line--;
  if(line < 1){
  line = 1;
  prognumber--;
  }
  menu();
  }
  else if(digitalRead(select) == HIGH){
  if(line == 1){
    prognumber--;
  }
  switch (prognumber) {                  
  case 1:                                
    first(); 
    break;                              
  case 2:
    second();
    break;
  case 3:
    third();
    break;
  case 4:
    fourth();
    break;
  case 5:
    fifth();
    break;
  default:
    first();
  }
  }
}

void LCDmenudisplay() {
  switch (prognumber) {                  
  case 1:                
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("First");  
    break;                              
  case 2:
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("Second");
    break;
  case 3:
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("Third");
    break;
  case 4:
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("Fourth");
    break;
  case 5:
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("Fifth");
    break;
  default:
//    lcd.clear();  
//    lcd.setCursor(0,0);   
    lcd.print("First");
  }
  
}

void first() {
//  digitalWrite(13, HIGH);
  menu();
}

void second() {
  digitalWrite(13, HIGH);  
  delay(500);
  digitalWrite(13, LOW);  
  menu();
}

void third() {
  menu();
}

void fourth() {
  menu();
}

void fifth() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  menu();
}


