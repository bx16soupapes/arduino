

//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(2, 3); // RX, TX

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

char A;

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
  if (Serial.available()) {
    // Esperamos un poco para que llege todo el mensaje
    delay(100);
    // Limpiamos la pantalla
    lcd.clear();
    // Leemos los datos hasta aciar el buffer
    while (Serial.available() > 0) {
      A = Serial.read();
      // escrimos en el LCD
      lcd.print(A);
      
      if(A == '1') { 
    lcd.setCursor(0,1);            //move the cursor to the 2nd line
    lcd.print("Y ESPIRALES");          //print...        
      }
      
    }
  }
}


