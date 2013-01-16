#include <LiquidCrystal.h>

int led = 13;
int contador=0;
int bx=0;
int tiempo=1800; // 1800 = 30 minutos
char mostrar;

int h=0;
int m=0;
int s=0;
int m2=0;
int s2=0;

int add = 3;
int start = 4;
 
int var = 0;

#define DELAY_OFFSET 11  
#define BEEP_PIN 2  
void beep(unsigned long hz, unsigned long ms);  
    
LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
 
void setup () {
    Serial.begin(9600);

    pinMode(led, OUTPUT);     
    pinMode(add, INPUT);
    pinMode(start, INPUT);
 
    pinMode(BEEP_PIN, OUTPUT);   
    
//    lcd.print("RESORTES Y ESPIRALES");

                //wait...
    lcd.clear();                    //clear the LCD during setup
    lcd.begin(16,2);                //define the columns (16) and rows (2)
    lcd.setCursor(4,0);            //move the cursor to 2nd line, 4th column
    lcd.print("RESORTES");          //print...
    lcd.setCursor(2,1);            //move the cursor to 2nd line, 4th column
    lcd.print("& ESPIRALES");          //print...
    delay(2000);
    lcd.clear();                    //clear the LCD during setup
    
}
 
void loop () {
 
  int bt1 = digitalRead(add);
  int bt2 = digitalRead(start);

  if(bt1 == 1) {
    var = 1;
    //lcd.clear(); 
    if(bx == 0) { 
      contador = 0;
      delay(1000);
    } else {
      if(contador == 0) { contador = tiempo; } else { contador = contador + tiempo; }
      delay(1000);
    }
  }
  
  if(bt2 == 1) { 
    if(contador !=0){
      var = 2; 
      bx=0;
    }
  }
  
  if(var == 0) var = 1;
  
  /*
  Serial.println(bt1);  
  Serial.println(bt2);  
  */

  Serial.println(bx);  

  
  switch (var) {
     case 1:
       if(bx == 0) { 
         lcd.clear(); 
       }     
       bx = bx +1;
       Serial.println(contador);
       lcd.setCursor(2,0);            //move the cursor to 2nd line, 4th column
       //lcd.autoscroll();
       lcd.print("TIEMPO TOTAL");          //print...
       lcd.setCursor(4,1);            //move the cursor to 2nd line, 4th column

       m=contador/60;
       h=m/60;
       m2=m%60;
       s2=contador%60%60%60;
       if(h < 10) lcd.print("0"); 
       lcd.print(h);          //print...
       lcd.print(":");          //print...
       if(m2 < 10) lcd.print("0"); 
       lcd.print(m2);          //print...
       lcd.print(":");          //print...
       if(s2 < 10) lcd.print("0"); 
       lcd.print(s2);          //print...
      
       break;
     case 2:
       if(bx == 0) { 
         lcd.clear(); 
       }     
       bx = bx +1;
     
       contador = contador -1;
       Serial.println(contador);
       lcd.setCursor(0,1);            //move the cursor to 2nd line, 4th column

       lcd.setCursor(4,0);            //move the cursor to 2nd line, 4th column
       lcd.print("RESTANTE");          //print...
       lcd.setCursor(4,1);            //move the cursor to 2nd line, 4th column
       
       m=contador/60;
       h=m/60;
       m2=m%60;
       s2=contador%60%60%60;
       if(h < 10) lcd.print("0"); 
       lcd.print(h);          //print...
       lcd.print(":");          //print...
       if(m2 < 10) lcd.print("0"); 
       lcd.print(m2);          //print...
       lcd.print(":");          //print...
       if(s2 < 10) lcd.print("0"); 
       lcd.print(s2);          //print...
       
       
       delay(1000);         
       if(contador == 0) { 
         var = 3;
         lcd.clear(); 
       }
       break;
     case 3:
       Serial.println("Stop");
       /*
       beep(440, 250);  
       delay(750);  
       */
       bx = 0;
       lcd.setCursor(3,0);            //move the cursor to 2nd line, 4th column
       lcd.print("COMPLETADO");          //print...
       lcd.setCursor(0,1);            //move the cursor to 2nd line, 4th column
       lcd.print("PRESIONE INICIO");          //print...       
       
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(20);               // wait for a second
      digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(20);               // wait for a second       
       break;
    default:
      //lcd.print("seleccione");          //print...
 
//    break;
      Serial.println("");
  }    
    

}

void beep(unsigned long hz, unsigned long ms) {  
    // reference: 440hz = 2273 usec/cycle, 1136 usec/half-cycle  
    unsigned long us = (500000 / hz) - DELAY_OFFSET;  
    unsigned long rep = (ms * 500L) / (us + DELAY_OFFSET);  
    for (int i = 0; i < rep; i++) {  
        digitalWrite(BEEP_PIN, HIGH);  
        delayMicroseconds(us);  
        digitalWrite(BEEP_PIN, LOW);  
        delayMicroseconds(us);  
    }  
}
