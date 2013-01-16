// NECIRrcv
// Joe Knapp   jmknapp AT gmail DOT com

//#include "WProgram.h"
//#include "NECIRrcv.h"

#ifndef NECIRrcv_h
#define NECIRrcv_h

//#include "WConstants.h"

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define CLKFUDGE 5      // fudge factor for clock interrupt overhead
#define CLKMAX 256      // max value for clock (timer 2)
#define PRESCALE 8      // timer2 clock prescale
#define SYSCLOCK 16000000  // main Arduino clock
#define CLKSPERUSEC (SYSCLOCK/PRESCALE/1000000)   // timer clocks per microsecond

#define MAXBUF 8       // IR command code buffer length (circular buffer)

// IR detector output is active low
#define MARK  0
#define SPACE 1

#define NBITS 32         // bits in IR code

#define BLINKLED 13

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// clock timer reset value
#define INIT_TIMER_COUNT2 (CLKMAX - USECPERTICK*CLKSPERUSEC + CLKFUDGE)
#define RESET_TIMER2 TCNT2 = INIT_TIMER_COUNT2

// pulse parameters -- nominal usec
#define STARTNOM      9000
#define SPACENOM      4500
#define BITMARKNOM    620
#define ONESPACENOM   1600
#define ZEROSPACENOM  480
#define RPTSPACENOM   2180

#define TOLERANCE 20  // percent
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

// pulse parameters (tick counts)
#define STARTMIN (int)((STARTNOM/USECPERTICK)*LTOL) // start MARK
#define STARTMAX (int)((STARTNOM/USECPERTICK)*UTOL) 
#define SPACEMIN (int)((SPACENOM/USECPERTICK)*LTOL) 
#define SPACEMAX (int)((SPACENOM/USECPERTICK)*UTOL) 
#define BITMARKMIN (int)((BITMARKNOM/USECPERTICK)*LTOL-2) // extra tolerance for low counts
#define BITMARKMAX (int)((BITMARKNOM/USECPERTICK)*UTOL+2) 
#define ONESPACEMIN (int)((ONESPACENOM/USECPERTICK)*LTOL) 
#define ONESPACEMAX (int)((ONESPACENOM/USECPERTICK)*UTOL) 
#define ZEROSPACEMIN (int)((ZEROSPACENOM/USECPERTICK)*LTOL-2) 
#define ZEROSPACEMAX (int)((ZEROSPACENOM/USECPERTICK)*UTOL+2) 
#define RPTSPACEMIN (int)((RPTSPACENOM/USECPERTICK)*LTOL) 
#define RPTSPACEMAX (int)((RPTSPACENOM/USECPERTICK)*UTOL) 

// receiver states
#define IDLE     1
#define STARTH   2
#define STARTL   3
#define BIT      4
#define ONE      5
#define ZERO     6
#define STOP     7
#define BITMARK  8
#define RPTMARK  9

// macros
#define GETIR(X) ((byte)digitalRead(X))    // used to read IR pin
#define nextstate(X) (irparams.rcvstate = X)

// state machine variables irparams
static volatile struct {
  byte rcvstate ;          // IR receiver state
  byte bitcounter ;        // bit counter
  byte irdata ;            // MARK or SPACE read from IR input pin
  byte fptr ;              // irbuf front pointer
  byte rptr ;              // irbuf rear pointer
  byte irpin ;             // pin for IR data from detector
  byte blinkflag ;         // TRUE to enable blinking of pin 13 on IR processing
  unsigned int timer ;     // state timer
  unsigned long irmask ;   // one-bit mask for constructing IR code
  unsigned long ircode ;   // IR code
  unsigned long irbuf[MAXBUF] ;    // circular buffer for IR codes
} irparams ;

// main class
class NECIRrcv
{
  public:
    NECIRrcv(int irpin);
    unsigned long read();
    void begin();
    int available() ;
    void flush() ;
    void blink13(int blinkflag) ;
  private:
} ;
#endif



/*********************************************/


NECIRrcv::NECIRrcv(int irpin)
{
  irparams.irpin = irpin ;
}

// initialization
void NECIRrcv::begin() {
  // setup pulse clock timer interrupt
  TCCR2A = 0;  // normal mode

  //Prescale /8 (16M/8 = 0.5 microseconds per tick)
  // Therefore, the timer interval can range from 0.5 to 128 microseconds
  // depending on the reset value (255 to 0)
  cbi(TCCR2B,CS22) ;
  sbi(TCCR2B,CS21) ;
  cbi(TCCR2B,CS20) ;

  //Timer2 Overflow Interrupt Enable
  sbi(TIMSK2,TOIE2) ;

  RESET_TIMER2;

  sei();  // enable interrupts
  
  // initialize state machine variables
  irparams.rcvstate = IDLE ;
  irparams.bitcounter = 0 ;
  irparams.ircode = 0 ;
  irparams.fptr = 0 ;
  irparams.rptr = 0 ;
  irparams.blinkflag = 0 ;

  // set pin modes
  pinMode(irparams.irpin, INPUT) ;
}

// return next IR code from buffer, or -1 if none
unsigned long NECIRrcv::read()
{
  unsigned long ircode ;
  if (irparams.fptr != irparams.rptr) {
    ircode = irparams.irbuf[irparams.rptr] ;
    irparams.rptr = (irparams.rptr + 1) % MAXBUF ;
    return((unsigned long)ircode) ;
  }
  else
    return((unsigned long)-1) ;
}

// return number of IR codes in buffer
int NECIRrcv::available()
{
  int n ;
  n = irparams.fptr - irparams.rptr ; 
  if (n < 0)
    n += MAXBUF ;
  return(n) ;
}

// enable/disable blinking of pin 13 on IR processing
void NECIRrcv::blink13(int blinkflag)
{
  irparams.blinkflag = blinkflag ;
  if (blinkflag)
    pinMode(BLINKLED, OUTPUT) ;
}

// flush IR code buffer
void NECIRrcv::flush()
{
  irparams.rptr = irparams.fptr ;
}

// IR receiver state machine (TIMER2 interrupt) 
ISR(TIMER2_OVF_vect)
{
  RESET_TIMER2 ;

  irparams.irdata = GETIR(irparams.irpin) ;
  
  if (irparams.blinkflag && (irparams.rcvstate != IDLE))
    PORTB |= B00100000 ;  // turn pin 13 LED on
  
  // process current state
  switch(irparams.rcvstate) {
    case IDLE:
      if (irparams.irdata == MARK) {  // got some activity
          nextstate(STARTH) ;
          irparams.timer = 0 ;
      }
      break ;
    case STARTH:   // looking for initial start MARK
      // entered on MARK
      if (irparams.irdata == SPACE) {   // MARK ended, check time
        if ((irparams.timer >= STARTMIN) && (irparams.timer <= STARTMAX)) {
          nextstate(STARTL) ;  // time OK, now look for start SPACE
          irparams.timer = 0 ;
        }
        else
          nextstate(IDLE) ;  // bad MARK time, go back to IDLE
      }
      else
        irparams.timer++ ;  // still MARK, increment timer
      break ;
    case STARTL:
      // entered on SPACE
      if (irparams.irdata == MARK) {  // SPACE ended, check time
        if ((irparams.timer >= SPACEMIN) && (irparams.timer <= SPACEMAX)) {
          nextstate(BITMARK) ;  // time OK, check first bit MARK 
          irparams.timer = 0 ;
          irparams.bitcounter = 0 ;  // initialize ircode vars
          irparams.irmask = (unsigned long)0x1 ;
          irparams.ircode = 0 ;
        }
        else if ((irparams.timer >= RPTSPACEMIN) && (irparams.timer <= RPTSPACEMAX)) {  // not a start SPACE, maybe this is a repeat signal
          nextstate(RPTMARK) ;   // yep, it's a repeat signal
          irparams.timer = 0 ;
        }
        else
          nextstate(IDLE) ;  // bad start SPACE time, go back to IDLE
      }
      else {   // still SPACE
        irparams.timer++ ;    // increment time
        if (irparams.timer >= SPACEMAX)  // check against max time for SPACE
          nextstate(IDLE) ;  // max time exceeded, go back to IDLE
      }
      break ;
    case RPTMARK:
      irparams.timer++ ;  // measuring MARK
      if (irparams.irdata == SPACE) {  // MARK ended, check time
        if ((irparams.timer >= BITMARKMIN) && (irparams.timer <= BITMARKMAX))
          nextstate(IDLE) ;  // repeats are ignored here, just go back to IDLE
        else
          nextstate(IDLE) ;  // bad repeat MARK time, go back to IDLE
      }
      break ;
    case BITMARK:
      irparams.timer++ ;   // timing MARK
      if (irparams.irdata == SPACE) {   // MARK ended, check time
        if ((irparams.timer < BITMARKMIN) || (irparams.timer > BITMARKMAX))
          nextstate(IDLE) ;  // bad MARK time, go back to idle
        else {
          irparams.rcvstate = BIT ;  // MARK time OK, go to BIT
          irparams.timer = 0 ;
        }
      }
      break ;
    case BIT:
      irparams.timer++ ; // measuring SPACE
      if (irparams.irdata == MARK) {  // bit SPACE ended, check time
        if ((irparams.timer >= ONESPACEMIN) && (irparams.timer <= ONESPACEMAX)) {
          nextstate(ONE) ;   // SPACE matched ONE timing
          irparams.timer = 0 ;
        }
        else if ((irparams.timer >= ZEROSPACEMIN) && (irparams.timer <= ZEROSPACEMAX)) {
          nextstate(ZERO) ;  // SPACE matched ZERO timimg
          irparams.timer = 0 ;
        }
        else
          nextstate(IDLE) ;  // bad SPACE time, go back to IDLE
      }
      else {  // still SPACE, check against max time
        if (irparams.timer > ONESPACEMAX)
          nextstate(IDLE) ;  // SPACE exceeded max time, go back to IDLE
      }
      break ;
    case ONE:
      irparams.ircode |= irparams.irmask ;  // got a ONE, update ircode
      irparams.irmask <<= 1 ;  // set mask to next bit
      irparams.bitcounter++ ;  // update bitcounter
      if (irparams.bitcounter < NBITS)  // if not done, look for next bit
        nextstate(BITMARK) ;
      else
        nextstate(STOP) ;  // done, got NBITS, go to STOP
      break ;
    case ZERO:
      irparams.irmask <<= 1 ;  // got a ZERO, update mask
      irparams.bitcounter++ ;  // update bitcounter
      if (irparams.bitcounter < NBITS)  // if not done, look for next bit
        nextstate(BITMARK) ;
      else
        nextstate(STOP) ;  // done, got NBITS, go to STOP
      break ;
    case STOP:
      irparams.timer++ ;  //measuring MARK
      if (irparams.irdata == SPACE) {  // got a SPACE, check stop MARK time
        if ((irparams.timer >= BITMARKMIN) && (irparams.timer <= BITMARKMAX)) {
          // time OK -- got an IR code
          irparams.irbuf[irparams.fptr] = irparams.ircode ;   // store code at fptr position
          irparams.fptr = (irparams.fptr + 1) % MAXBUF ; // move fptr to next empty slot
        }
        nextstate(IDLE) ;  // finished with this code, go back to IDLE
      }
      break ;
  }
  // end state processing

  if (irparams.blinkflag)
    PORTB &= B11011111 ;  // turn pin 13 LED off
}








// look for IR codes and print them as they are received







#define IRPIN 4    // pin that IR detector is connected to

NECIRrcv ir(IRPIN) ;

/* LED */

int ledpin = 13;
boolean encendido;
boolean rebotes;
/* LED */


void setup()
{
  pinMode(ledpin, OUTPUT);
  encendido =false;
  rebotes =true;
  
  Serial.begin(9600) ;
  Serial.println("NEC IR code reception") ;
  ir.begin() ;
  
  
  
}

void loop()
{
  unsigned long ircode ;
  
  while (ir.available()) {
    ircode = ir.read() ;
    Serial.print("got code: 0x") ;
    Serial.println(ircode,HEX) ;
    
    
  if (ircode == 0xF708BD00) //Si el boton de power... apagamos el led
     {
        Serial.print(" SOURCE ") ;
        
        
     }
     else if (ircode == 0xEA15BD00) Serial.print(" UNO ") ;
     else if (ircode == 0xE916BD00) Serial.print(" DOS ") ;
     else if (ircode == 0xE817BD00) Serial.print(" TRES ") ;

     else if (ircode == 0xE619BD00) Serial.print(" CUATRO ") ;
     else if (ircode == 0xFB04BD00) Serial.print(" CINCO ") ;
     else if (ircode == 0xFD02BD00) Serial.print(" DISPLAY ") ;

     
     // LED
  
if (ircode ==0xF708BD00 && encendido ==false && rebotes ==true){
  digitalWrite(ledpin, HIGH);
  encendido =true;
  rebotes =false;
  delay (ircode ==0xF708BD00);
 }
else if (ircode ==0xF708BD00 && encendido ==true && rebotes ==true){
  digitalWrite(ledpin, LOW);
  encendido =false;
  rebotes =false;
  delay (ircode ==0xF708BD00);
}
else if (ircode == 0xF708BD00 && rebotes ==false){
  rebotes =true;
}
  
      
     // LED
     
    
    
  }
}


/*

#include <IRremote.h>
#define RECV_PIN 12 //indicamos el pin por el que recibimos los datos del sensor TSOP1838
boolean encendido;  //Variable donde compruebo si el led esta encendido o no
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
     Serial.begin(9600);
     pinMode(13,OUTPUT);  //Pin 13 como salida
     encendido=0;  //indicamos estado inicial (apagado);
     irrecv.enableIRIn(); // Iniciamos la recepcion
}

void loop()
{
    //Si tenemos datos de lectura debido a que se pulsa una tecla en el mando
    if (irrecv.decode(&results))
    {
        //Mostramos por puerte serie dicho codigo en Hexadecimal(para depuracion)
   Serial.print("Codigo: 0x") ;
   Serial.println(results.value,HEX) ;
   //Comprobamos si es la TECLA 1
   if(results.value==0x2FC827D)
   {
        //Comprobamos si esta encendido el led, si lo esta lo apagamos
             if(encendido==1)
             {
                   digitalWrite(13,LOW);
                   encendido=0;
             }
            //si no, lo encendemos
            else
            {
                  digitalWrite(13,HIGH);
                  encendido=1;
            }
        }
        delay(50); //retardo de 50 ms para evitar que el codigo se lea dos veces en una pulsacion
        irrecv.resume(); // Recibimos el siguiente valor del sensor
    }
}

*/

