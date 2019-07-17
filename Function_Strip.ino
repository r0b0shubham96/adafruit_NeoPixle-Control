#include <WS2812FX.h>


#define LED_PIN    6  // digital pin used to drive the LED strip
#define LED_COUNT 150  // number of LEDs on the strip


WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

int A;         //<===S0A0Z10C1M0P
int Z;
int M;
int S;
int i;
uint32_t C[] = {RED,GREEN,BLUE,WHITE,BLACK,YELLOW,CYAN,MAGENTA,PURPLE,ORANGE,ULTRAWHITE,NEON} ;



void setStrip( int P,  int S,  int A,  int Z,  int M, uint32_t CP) 
{
  
  ws2812fx.init();
  ws2812fx.setBrightness(255);
   
  ws2812fx.setSegment(S,  A,  Z,  M, CP, 1000, false);
 

  ws2812fx.start();
}


void setup() {
  Serial.begin(115200);
  Serial.println("Ready to change color");
}

void loop() 
{
{
  ws2812fx.service();
}

if (Serial.available() > 0)
{     
char c = Serial.read(); //read the first byte
if (c == 'S') 
{
S = Serial.parseInt(); //get the INT     
}
if (c == 'A') 
{
A = Serial.parseInt(); //get the INT     
}
if (c == 'Z') 
{
Z = Serial.parseInt(); //get the INT     
}

if (c == 'C')
{
  i = Serial.parseInt();
}
if (c == 'M') 
{
M = Serial.parseInt(); //get the INT    
}
if (c == 'P')
{
setStrip(Serial.parseInt(), S, A, Z, M, C[i]);
}
}
}
