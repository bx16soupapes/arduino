

//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(2, 3); // RX, TX

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

char A;

int add = 3;
int start = 4;
int select = 5;

int op = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.begin(9600);
  lcd.print("INICIANDO. xxx ..");
    
  //nuevo
  // set the data rate for the SoftwareSerial port to Raspberry Pi
//  mySerial.begin(9600);
  
  
  
}



void loop() {
    // Comprobamos que llegan datos al puerto serie
 // if (Serial.available()) {
    // Esperamos un poco para que llege todo el mensaje
    delay(100);
    // Limpiamos la pantalla
    lcd.clear();
    
  int bt1 = digitalRead(add);
  int bt2 = digitalRead(start);
  int bt3 = digitalRead(select);

  if(bt1 == 1){ op = 1; }
  else if (bt2 == 1) { op = 2; }
  else if (bt3 == 1) { op = 3; }
    
    // Leemos los datos hasta aciar el buffer
    while (op > 0) {
      //A = Serial.read();
      Serial.println(op);
      // escrimos en el LCD
//      lcd.print(op);
      
      if(op == 1) { 
    lcd.setCursor(0,1);            //move the cursor to the 2nd line
    lcd.print("Y ESPIRALES");          //print...        
      }
      
      if(op == 2) { 
    lcd.setCursor(0,0);            //move the cursor to the 2nd line
    lcd.print("Y CEMB");          //print...        
      }     
     
      if(op == 3) { 
    lcd.setCursor(3,0);            //move the cursor to the 2nd line
    lcd.print("CLAUCA");          //print...        
      }         

      break;

      
    }
  //}
}


