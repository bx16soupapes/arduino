
/*
 -------------------------------------- 
  LCD 16x2 - Menu
 --------------------------------------
 
 La LCD que vamos a utilizar es de caracteres (16x2) esto corresponde 
 a 16 columnas y 2 filas y funciona gracias a un Hitachi HD44780 driver.
 
 En este tutorial vamos a hacer un Menu para controlar salidas leer

entradas e imprimir Anuncios.
 
  El circuito:
 * LCD RS pin va conectado al digital pin 12
 * LCD Enable pin conectado al digital pin 11
 * LCD D4 pin conectado al digital pin 5
 * LCD D5 pin conectado al digital pin 4
 * LCD D6 pin conectado al digital pin 3
 * LCD D7 pin conectado al digital pin 2
 * LCD R/W pin conectado a ground
 * los dos ultimos a +5V and ground
 * El cable de la LCD VO va conectado a la referencia del potenciometro
 
*/
  int menu;              
  int salida;                         //Conexion led, buzzer.
  int fotocelda;                      //Conexion Fotocelda
  String AnuncioMenu;                 //Anuncio de impresion LCD 
 
  //Funciones
  void Estado();                      //Funcion Estado de las salidas
  void Anuncio();                     //Funcion para visualizar Mensaje
  void Menu ();                       //Funcion para visualizar el Menu
 
#include <LiquidCrystal.h>            //incluimos la libreria LCD
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//inicializamos los pines 
LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

//------------------------------------
//Funcion principal
//------------------------------------
 
void setup() {
   Serial.begin(9600);
  pinMode   (13,OUTPUT);              //Led como salida
  pinMode    (3,OUTPUT);              //Buzzer como salida
  lcd.begin     (16, 2);              //Configuramos el tamaño de la LCD
  digitalWrite(15,HIGH);              //Resistancia de PullUp A1 pulsador
}
 
//------------------------------------
//Funcion ciclicla
//------------------------------------
 
void loop() {
 
  menu = analogRead (0);              //iguardamos la posicion del potencio 
  menu = map(menu,0,1023,0,3);        //Escalamos el valor para que sea Menu
 
  switch (menu)  {                    //Valoramos el estadp del Menu
 
    case 0 :                          //si el valor de escala es igual a 0:
      AnuncioMenu = "LED";            //cargamos la impresion
      Menu();                         //Vamos al la funicion Menu
      salida = 13;                    //Seleccionamos al led como salida
      Estado ();                      //Vamos al la funicion Estado
    break;                            //Retorno
 
    case 1 :                          //si el valor de escala es igual a 1:
      AnuncioMenu = "Buzzer";         //cargamos la impresion
      Menu();                         //Vamos al la funicion Menu
      salida = 6;                     //Seleccionamos al buzzer como salida
      Estado ();                      //Vamos al la funicion Menu  
    break;                            //Retorno
 
    case 2 :                          //si el valor de escala es igual a 2:
      AnuncioMenu = "Fotocelda";      //cargamos la impresion
      Menu();                         //Vamos al la funicion Menu
      fotocelda = analogRead (2);     //Cargamos el valor de la fotocelda

      lcd.setCursor(0, 1);            //Asignamos la posicion de impresion

      lcd.print(fotocelda);           //imprimimos el valor de la fotocelda

    break;                            //Retorno
 
    case 3 :                          //si el valor de escala es igual a 3:
      AnuncioMenu =" Tutorial T03AA ";//cargamos la impresion
      Menu();                         //Vamos al la funicion Estado
      Anuncio();                      //Vamos al la funicion anincio
      break;                          //Retorno
  }
 
  delay(300);                         //Retardo entre impresiones
  lcd.clear();                        //Borramos todo de la pantalla
}
 
void Menu ()  {                       //Funcion de Impresion del Menu
 
  lcd.setCursor(0, 0);                //Asignamos la posicion de impresion
  lcd.print(AnuncioMenu);             //imprimimos el Menu
    Serial.println(AnuncioMenu);
}
 
void Estado()  {                      //Funcion de valoracion ON/OFF salidas
 
  int buton = digitalRead(15);        //A1 como entada digital del pulsador 
 
  if (buton == HIGH) {                //Valoracion estado del pulsador
 
  digitalWrite(salida,HIGH);          //Encendemos la salida
  lcd.setCursor(5, 1);                //Asignamos la posicion de impresion
  lcd.print("ON");                    //Impresion del estado de la salida
  }
 
  else {
 
  digitalWrite(salida,LOW);           //Apagamos la salida  
  lcd.setCursor(0, 1);                //Asignamos la posicion de impresion
  lcd.print("OFF");                   //Impresion del estado de la salida
  } 
}
 
void Anuncio()  {
 
  lcd.setCursor(0, 1);                //Asignamos la posicion de impresion
  lcd.print("  Menu LCD  ;D");        //imprimimos en la LCD
}
 
//Fin programa
