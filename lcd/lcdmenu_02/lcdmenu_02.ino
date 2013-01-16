#include <LiquidCrystal.h>

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

int starterbutton = 3;
int menuButton = 4;
int menudelaycount=0;
int led=13;
  int distance = 100;
  int programnumber=0;
//  int starterbutton=0;

void menu();
//void lcd.clear();
void LCDfirst();
void LCDsecond();
void LCDmenudisplay();

void first();
void second();
void third();
void fourth();

void setup() {
  Serial.begin(9600);  
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);   
  Menu();
}

void loop() {
  //nothing to loop but is required in every sketch.
}

void Menu(){            

//  int bt1 = digitalRead(sel);
//  int bt2 = digitalRead(start);  
  
  
  Serial.println("MENU:");
  Serial.println(programnumber);
  
  if(programnumber == 1) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(4);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }  
  
  lcd.clear();  
  lcd.setCursor(0,0);   
  lcd.print("Program Menu"); 
//  LCDsecond();     
  switch (programnumber) {                  
  case 1:                     
    lcd.setCursor(0,1);     
    lcd.print("PRIMERO"); 
//    LCDthird();
//    lcd.print(distance);
//    lcd.print("m");    
    break;                               
  case 2:
    lcd.setCursor(0,1);   
    lcd.print("SEGUNDO");
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    break;
  case 3:
    lcd.setCursor(0,1);     
    lcd.print("TERCERO");
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  default:
    lcd.setCursor(0,1);   
    lcd.print("INICIO");
//    LCDthird();
//    lcd.print(distance);
//    lcd.print("m");
  }



//  if(bt1 == 1) { Serial.println("boton1"); }
/*
  while(digitalRead(sel) == HIGH){}
  delay(5);
  while(digitalRead(sel) == LOW){}
  */
  /*
  if(digitalRead(sel) == LOW){
    Serial.println("boxn 1 ld");
  } else {
    Serial.println("bx 1 dasGH");
  }
  */

  lcd.print(" >");
  while(digitalRead(starterbutton) == HIGH){}
  delay(5);
  while(digitalRead(starterbutton) == LOW){}
  menudelaycount = 0;
    while(menudelaycount <500){
    delay(1);
    menudelaycount++;
    if(digitalRead(starterbutton) == LOW){
      programnumber++;
    if(programnumber > 3){
      programnumber = 1;
    }
    Menu();
    }
  }
  

  
 switch (programnumber) { //if the button is not let go within the menu time stated above then it does not loop back and then selects the subroutine from this switch case:
     case 1:
       Serial.println("Fill Func");
       fillMenu();
       break;
     case 2:
        Serial.println("Delay Func");
       break;
     case 3:
        Serial.println("Pulse Func");
       break;
     default:
        Serial.println("Default Race");
     }
}

int FillDelay = 0;

void fillMenu()
{ 
   FillDelay = FillDelay +3000;
   Serial.println(FillDelay);
   
   Serial.println("Next >");    
   while(digitalRead(menuButton) == HIGH){} 
     delay(5);
   while(digitalRead(menuButton) == LOW){} 
     menudelaycount = 0; 
   while(menudelaycount <500){ 
   delay(1);
   menudelaycount++;
   if(digitalRead(menuButton) == LOW){ 
     //programnumber++; 
   if(FillDelay > 120000){
     FillDelay = 0;
   }
   fillMenu(); 
  }
 }
   Serial.print("Fill Delay set @ ");
   Serial.print(FillDelay);
}
