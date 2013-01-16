#include <LiquidCrystal.h>

int led = 13;
int contador=0;

int add = 3;
int start = 4;
int select = 5;
int prognumber=0;

int line = 0;
int var = 0;

#define DELAY_OFFSET 11  
#define BEEP_PIN 2  
void beep(unsigned long hz, unsigned long ms);  

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
 
void menu();
void LCDclear();
void LCDfirst();

void first();
 
void setup () {
    Serial.begin(9600);

    pinMode(led, OUTPUT);     
    pinMode(add, INPUT);
    pinMode(start, INPUT);
 
    pinMode(BEEP_PIN, OUTPUT);   
    
    lcd.clear();                    //clear the LCD during setup
    lcd.begin(16,2);                //define the columns (16) and rows (2)

    lcd.setCursor(0,0);            //move the cursor to the 2nd line
    lcd.print("RESORTES");          //print...
    lcd.setCursor(0,1);            //move the cursor to the 2nd line
    lcd.print("Y ESPIRALES");          //print...
    delay(1000);                   //wait...

    menu();
    
}
 
void loop(){} 
 
void menu() {
  
//    Serial.println("loop");
  
  int bt1 = digitalRead(add);
  int bt2 = digitalRead(start);
  int bt3 = digitalRead(select);

    delay(30);                   //wait...

  if(bt1 == 1){ var = 1; }
  else if (bt2 == 1) { var = 2; }
  else if (bt3 == 1) { var = 3; }
  
  
 /*
    Serial.println(bt1);
    Serial.println(bt2);
    Serial.println(bt3);
   */ 
//    Serial.println(var);
   
  switch (var) {
    case 1:
        lcd.print("unox");
        Serial.println("unox");
        break;
    case 2:
        lcd.print("ds");
        Serial.println("ds");
        break;
    case 3:
        lcd.print("tres");
        Serial.println("tres");
        break;
    default: 
        Serial.println("mnu");
        // si nada coincide, ejecuta el "default"
      // el "default" es opcional
      break;
  }
  
  
  
}


void menux() {
  
  
  
  /*
  
  int bt1 = digitalRead(add);
  int bt2 = digitalRead(start);
  int bt3 = digitalRead(select);
  
  switch (var) {                  
  case 1:                                
  lcd.print("PRESIONE 1 PARA");  
  
    break;                              
  case 2:
  lcd.print("PRESIONE 1 PARA");  
    break;
  case 3:
  lcd.print("PRESIONE 1 PARA");  
    break;
  case 4:
  lcd.print("PRESIONE 1 PARA");  
    break;
  default:
    lcd.clear();                    //clear the LCD during setup  
    lcd.setCursor(0,0);            //move the cursor to the 2nd line
    lcd.print("PRESIONE");          //print...
    lcd.setCursor(0,1);            //move the cursor to the 2nd line
    lcd.print(bt1);          //print...  
    lcd.print(bt2);          //print...  
    lcd.print(bt3);          //print...  

  }
 
 */
}


