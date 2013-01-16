#include <LiquidCrystal.h>

int led = 13;
int contador=0;
int bx=0;

int boton1 = 2;
int boton2 = 3;
int boton3 = 4;
int boton4 = 5;
int boton5 = 6;

int modo=0; //automatico manual 
 
int var = 0;
int subvar=0;

int h=0;
int m=0;
int s=0;
int m2=0;
int s2=0;

    
LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
 
void setup () {
    Serial.begin(9600);

    pinMode(led, OUTPUT);     
    pinMode(boton1, INPUT);
    pinMode(boton2, INPUT);
    pinMode(boton3, INPUT);
    pinMode(boton4, INPUT);
    pinMode(boton5, INPUT);
 
    lcd.clear();                    //clear the LCD during setup
    lcd.begin(16,2);  
/*
    lcd.setCursor(4,0);            //move the cursor to 2nd line, 4th column
    lcd.print("BIENVENIDO");          //print...
    lcd.setCursor(2,1);            //move the cursor to 2nd line, 4th column
    lcd.print("CLAU");          //print...
    delay(1000);
    lcd.clear();                    //clear the LCD during setup
*/    
}
 
void loop () {
 
  int bt1 = digitalRead(boton1);

  if(bt1 == 1) {
    bx=0;
    var = var++;
    delay(1000);
  }

/*  
  if(bt2 == 1) {
    bx=0; 
    var = var--;
    if(var < 1) var = 3;
    delay(1000);
  }
  */
  if(var > 3) var = 1;
  if(var == 0) var = 1; // por defecto al caso 1

  switch (var) {
     case 1:
       if(bx == 0) { 
         lcd.clear(); 
       }     
       bx = bx +1;
       lcd.setCursor(0,0);
       lcd.print("RIEGO #1");          //print...
       riego1();
       break;
     case 2:
       Serial.println("menu2");
       if(bx == 0) { 
         lcd.clear(); 
       }     
       bx = bx +1;
       lcd.setCursor(0,0);
       lcd.print("RIEGO #2");

       break;
     case 3:
       Serial.println("menu3");
       
       if(bx == 0) { 
         lcd.clear(); 
       }     
       bx = bx +1;
       lcd.setCursor(0,0);
       lcd.print("RIEGO #3");
    
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

  char* subtitulo; // ok


void riego1(){
  int bt2 = digitalRead(boton2); // PARA MENU SECUNDARIO
  if(bt2 == 1) {
    bx=0;
    subvar = subvar++;
    delay(1000);
  }
  if(subvar > 3) subvar = 1;
  if(subvar == 0) subvar = 1; // por defecto al caso 1
  
  int bt3 = digitalRead(boton3);
  int bt4 = digitalRead(boton4);
      
  if(bt3 == 1) { //TOGGLE
    bx=0; 
    if(subvar == 1){
      if(modo == 0) { modo = 1; } else { modo = 0; }
    }
    
    delay(1000);
  }
  
  Serial.print("modo:");
  Serial.println(modo);
  
  switch (subvar) {
    case 1:
      if(modo == 0) { 
        subtitulo="MODO: AUTOMATICO";
      } else {
        subtitulo="MODO: MANUAL";
      }
      xm();
      break;
    case 2:
      //char* sub1="INICIO ";
      //char* sub2="x";
      //subtitulo +=sub1;
      String sub1,sub2;
      sub1= String("INICIO ");
      sub2= String("tiempo");
      subtitulo = sub1;
      
      xm();
      break;
    case 3:
      subtitulo="FIN 02:30:00";
      xm();    
      break;            
    default: 
      Serial.println("");
  }   
    
}


void xm(){
      if(bx == 0) { 
        lcd.clear(); 
      }     
      bx = bx +1; 
      lcd.setCursor(0,1);
      lcd.print(subtitulo);  
}

