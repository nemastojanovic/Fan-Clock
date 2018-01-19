#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
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
String message = "ABCD";

//numero del carattere corrente del messaggio
int cn = 0;
//numero del carattere precedente a quello corrente
int lcn = 0;

bool inverted = false; 

//linea del carattere corrente da stampare
int row = 0;

//linea del carattere precedente a quello corrente
int lrow = 0;

//pin da cui comando i led 
#define PIN 6


//numero del pin di lettura della ventola  
int rt = 2;

//colore dei led
uint32_t color;

 
//Creo l'oggetto che mi permette di potere controllare la striscia di led
// Parametro 1 = numero di led della striscia 
// Parametro 2 = pin con cui commandare la striscia
// Parametro 3 = tipo di led 
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers) 
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products) 
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(rt, INPUT_PULLUP);
  Serial.begin(9600);
  //creo interrupt in modo che ogni volta che il pin della ventola è a uno "disegno"
  attachInterrupt(digitalPinToInterrupt(rt), writeRow, RISING);
  //richiamo begin per poter preparare i pin dei led
  strip.begin();
  //setto la luminosità dei led
  strip.setBrightness(50);
  //setto il colore che dovrannò avere i led
  setColor(180,20,60);
}

void loop(){
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
  int cp = getCharPosition(message.charAt(cn));
  
  //posizione nell'array letters del carattere precedente a quello corrente
  int lcp = getCharPosition(message.charAt(lcn));

  //spengo la linea pecedente
  if(lcp >= 0){
    setColor(0,0,0);
    onLeds(letters[lcp][lrow], sizeof(letters[lcp][lrow])/sizeof(letters[lcp][lrow][0]));
  }
  
  //accendo la linea corrente
  if(cp >= 0){
    printRow(letters[cp][row], sizeof(letters[cp][row])/sizeof(letters[cp][row][0]));
    //accendo tutti i led della linea contenuti nella array
    setColor(180,20,60);
    onLeds(letters[cp][row], sizeof(letters[cp][row])/sizeof(letters[cp][row][0]));
  }
  //metto in memoria la linea corrente
  lrow = row;
  //passo alla prossima riga
  row++;
  //metto in memoria il numero del carattere corrente
  lcn = cn;
  //se ho finito di disegnare il carattere passo al prossimo
  if(sizeof(letters[cp])/sizeof(letters[cp][0]) == row){
    //passo al prossimo carattere
    cn++;
    //torno alla riga iniziale
    row = 0;
    Serial.println("        ");
    //se ho finito il messaggio lo riscrivo
    if(message.length() == cn){
      cn = 0;
    }
  }
}

//metodo per acendere un certo numero di led
void onLeds(int leds[], int len){
    if(strip.numPixels() >= len){
      //passo tutti i led uno a uno
      for(int j = 0; j < len; j++){
          if(!(j != 0 && leds[j] == 0)){
            strip.setPixelColor(leds[j], color);
          }
      }
      //applico i dati alla striscia
      strip.show();
    }
}

//metodo per settare il colore corrente
void setColor(int r,int g, int b){
  color = strip.Color(r, g, b);
}

//metodo per stampare le linee in modo da avere
//anche una stampa a terminale
void printRow(int num[], int len){
  int old = -1;
   for(int i = 0; i < len; i++){
    if((i > 0 && num[i] != 0) || i == 0){
      for(int j = 0; j < num[i]-old-1; j++){
        Serial.print(" ");
      }
      Serial.print("*");
      old = num[i];
    }
   }
   Serial.println("");
}


