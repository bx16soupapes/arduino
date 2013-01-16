#include <LiquidCrystal.h>

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

int rly1Pin =  13;
int rly2Pin =  13;
int rly3Pin =  13;
int rly4Pin =  13;
int prognumber = 1;
int line = 1;

int down = 3;
int select = 4;
int up = 5;

void menu();
void LCDclear();
void LCDfirst();
void LCDsecond();
void LCDmenudisplay();

void first();
void second();
void third();
void fourth();

void setup() {
  lcd.begin(16, 2);
  menu();
}

void loop() {
  //nothing to loop but is required in every sketch.
}

void LCDclear(){
  lcd.print(0xFE);      
  lcd.clear();
}

void LCDfirst(){
  lcd.print(0xFE);
lcd.setCursor(0, 0); // bottom left
}
void LCDsecond(){
  lcd.print(0xFE);
lcd.setCursor(0, 1); // bottom left
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
//  lcd.print(0xFE);
//  lcd.print(143);
  lcd.print(" <");
  }
  else {
//  lcd.print(0xFE);
//  lcd.print(207);
  lcd.print(" <");
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
  default:
    first();
  }
  }
}

void LCDmenudisplay() {
  switch (prognumber) {                  
  case 1:                                
    lcd.print("First");  
    break;                              
  case 2:
    lcd.print("Second");
    break;
  case 3:
    lcd.print("Third");
    break;
  case 4:
    lcd.print("Fourth");
    break;
  }
  
}

void first() {
  digitalWrite(13, HIGH);
  menu();
}

void second() {
    digitalWrite(13, HIGH);
  menu();
}

void third() {
    digitalWrite(13, HIGH);
  menu();
}
void fourth() {
    digitalWrite(13, HIGH);
  menu();
}


