#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

// Here's how to control the LEDs from any two pins:
#define DATAPIN1   6
#define DATAPIN2   5
int letters[][8][8] = {
  // lettera A dall'alto verso il basso
  {
    {0,1,2,3,4,5,6,7}, 
    {0,2},             
    {0,2},      
    {0,2},
    {0,2},
    {0,2},
    {0,2},
    {0,1,2,3,4,5,6,7}
  },
  // lettera B
  {
    {0,1,2,3,4,5,6,7}, //0/ ******** 
    {0,1,2,3,4,5,6,7}, //1/ ********
    {0,3,7},           //2/ *  *   *
    {0,3,7},           //3/ *  *   *
    {0,3,7},           //4/ *  *   * 
    {0,3,7},           //5/ *  *   * 
    {1,3,6},           //6/  * *  *
    {2,4,5} 
  },
  // lettera C
  {
    {0,1,2,3,4,5,6,7},
    {0,7},
    {0,7},
    {0,7},
    {0,7},
    {0,7},
    {0,7},
    {0,7}
  },
  // lettera D
  {
    {0,1,2,3,4,5,6,7},
    {0,7},
    {0,7},
    {0,7},
    {0,7},
    {1,6},
    {2,5},
    {3,4}
  }
};

//messaggio da scrivere nell'orologio
String message1 = "ABCD";

String message2 = "ABAB";


//numero del carattere corrente del messaggio
int cn1 = 0;
//numero del carattere precedente a quello corrente
int lcn1 = 0;

int cn2 = 0;
int lcn2 = 0;

//linea del carattere corrente da stampare
int row1 = 0;

//linea del carattere precedente a quello corrente
int lrow1 = 0;

int row2 = 7;
int lrow2 = 7;

//dichiaro il pin da cui leggero il valore della fotoresistenza
int pc = A0;

int columnsLength = 8;

//Creo l'oggetto che mi permette di potere controllare la striscia di led
// Parametro 1 = numero di led della striscia 
// Parametro 2 = pin con cui commandare la striscia
// Parametro 3 = tipo di led 
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers) 
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products) 
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(30,DATAPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(25,DATAPIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cStrip1 = strip1;
Adafruit_NeoPixel cStrip2 = strip2;

boolean sc = true;
void setup() {
  Serial.begin(9600);
  //richiamo begin per poter preparare i pin dei led
  strip1.begin();
  strip2.begin();
  cStrip1 = strip1;
  cStrip2 = strip2;
}

void loop(){
  int photocell = analogRead(pc);
  //Serial.println(photocell);
  if(photocell > 900){
    if(sc){
      cStrip1 = strip1;
      cStrip2 = strip2;
    }
    else{
      cStrip1 = strip2;
      cStrip2 = strip1;
    }
    sc = !sc;
    for(int i = 0; i < 32; i++){
        if(i%8 == 0){
            offAllLeds();
            delay(1);
        }
        writeRow();
    }
    offAllLeds();
  }
}

//metodo che riceve il carattere per cui si ritornerà la posizione nell'array
//se il carattere non c'è nell'array verrà ritornato un numero negativo
int getCharPosition(char c){
  int r = -1;
  if(c == 'A') r = 0;
  else if(c == 'B') r = 1;
  else if(c == 'C') r = 2;
  else if(c == 'D') r = 3;
  return r;
}

void writeRow(){
  //posizione nell'array letters del carattere corrente
  int cp1 = getCharPosition(message1.charAt(cn1));
  int cp2 = getCharPosition(message2.charAt(cn2));
  
  //posizione nell'array letters del carattere precedente a quello corrente
  int lcp1 = getCharPosition(message1.charAt(lcn1));
  int lcp2 = getCharPosition(message2.charAt(lcn2));
  
  //spengo la linea pecedente
  if(lcp1 >= 0){
    for(int j = 0; j < columnsLength; j++){
      //if(!(j != 0 && letters[lcp1][lrow1][j] == 0)){
        cStrip1.setPixelColor(cStrip1.numPixels()-8+letters[lcp1][lrow1][j], 0,0,0);
      //}
    }
  }
  cStrip1.show();
  if(lcp2 >= 0){
    for(int j = columnsLength-1; j >= 0; j--){
      if(!(j != 0 && letters[lcp2][lrow2][j] == 0)){
        cStrip2.setPixelColor(cStrip2.numPixels()-1-letters[lcp2][lrow2][j], 0, 0, 0);
      }
    }
  }
  cStrip2.show();
    
  //accendo la linea corrente
  if(cp1 >= 0){
    for(int j = 0; j < columnsLength; j++){
      if(!(j != 0 && letters[cp1][row1][j] == 0)){
        cStrip1.setPixelColor(cStrip1.numPixels()-8+letters[cp1][row1][j], 255, 0, 0);
      }
    }
  }
  cStrip1.show();
  //accendo la linea corrente
  if(cp2 >= 0){
    for(int j = columnsLength-1; j >= 0; j--){
      if(!(j != 0 && letters[cp2][row2][j] == 0)){
        cStrip2.setPixelColor(cStrip2.numPixels()-1-letters[cp2][row2][j], 255, 0, 0);
      }
    }
  }
  //applico i dati alla striscia
  cStrip2.show();
  //metto in memoria la linea corrente
  lrow1 = row1;
  lrow2 = row2;
  
  //passo alla prossima riga
  row1++;
  row2--;
  
  //metto in memoria il numero del carattere corrente
  lcn1 = cn1;
  lcn2 = cn2;
  
  //se ho finito di disegnare il carattere passo al prossimo
  if(sizeof(letters[cp1])/sizeof(letters[cp1][0]) == row1){
    //passo al prossimo carattere
    cn1++;
    //torno alla riga iniziale
    row1 = 0;
    //Serial.println("        ");
    //se ho finito il messaggio lo riscrivo
    if(message1.length() == cn1){
      cn1 = 0;
    }
  }
  if(0 == row2){
    //passo al prossimo carattere
    cn2++;
    //torno alla riga iniziale
    row2 = 7;

    //se ho finito il messaggio lo riscrivo
    if(message2.length() == cn2){
      cn2 = 0;
    }
  }
}

void offAllLeds(){ 
    for(int j = cStrip1.numPixels()-8; j < cStrip1.numPixels(); j++){
       cStrip1.setPixelColor(j, 0, 0, 0);
    }
    for(int j = cStrip2.numPixels()-8; j < cStrip2.numPixels(); j++){
       cStrip2.setPixelColor(j, 0, 0, 0);
    }
    cStrip1.show();
    cStrip2.show();
}
