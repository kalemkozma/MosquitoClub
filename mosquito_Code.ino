///--------------link to stepper code --https://www.youtube.com/watch?v=HDxrrG1RFaw&t=977s

#include <IRremote.h>
#include <Servo.h>

#include <Adafruit_NeoPixel.h>

// project - mosquito night club with a closing door and gas(off spray) compenent(it is just a prototype the "gas com")
#define IR_RECIEVER 7
#define IR_BUTTON_0_SPRAY 22  //steppa motor
#define IR_BUTTON_1_State_One   12 // now it cycles through Leds   // motor   check didnt have time for these motors unfourtantely 
#define IR_BUTTON_2_State_Two  24  // now it cycles through Leds  // motor    check didnt have time for these motors unfourtantely 
#define IR_BUTTON_3_STATE_THREE  94
#define IR_PAUSEPLAY_STOPSPRAY 64
Adafruit_NeoPixel strip(19, 9);
Adafruit_NeoPixel strip2(16, 10);
Servo sprayer;
Servo sprayer1;

int command = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 
  IrReceiver.begin(IR_RECIEVER);
strip2.begin();
strip2.clear();
strip2.show();
strip.begin();
strip.clear();
strip.show();
sprayer.attach(3);
sprayer1.attach(4);

 }

void loop() {
  // put your main code here, to run repeatedly:
  
//sprayer.write(180);



if(IrReceiver.decode()){
  IrReceiver.resume();


  command = IrReceiver.decodedIRData.command;
  Serial.println(command);

}


  switch (command){
    case  IR_BUTTON_0_SPRAY: {

sprayer.write(0);
sprayer1.write(180);


 }
break;
    case IR_BUTTON_1_State_One: {
//StateOne = ()
timerLightTravel(strip.Color(255, 50, 50), 100);
timerLightTravelInside(strip.Color(255, 50, 50), 100);
break;
    }
    case IR_BUTTON_2_State_Two: {

      
timerLightTravelTwo(strip.Color(255, 0, 0), strip.Color(255, 190, 0), 1000);
timerLightTravelTwoInterior(strip.Color(255, 0, 0), strip.Color(255, 190, 0), 1000 );


      }


break;

    case IR_BUTTON_3_STATE_THREE: {

timerColorSweep(strip.Color(random(), random(), random()),strip.Color(random(), random(), random()), strip.Color(random(), random(), random()), 50 );
timerColorSweep1(strip.Color(random(), random(), random()),strip.Color(random(), random(), random()), strip.Color(random(), random(), random()), 50 );
    }
break ;
 

 case IR_PAUSEPLAY_STOPSPRAY:{

  sprayer.write(180);
  sprayer1.write(0);
 }
break;


  }


}
// first sequence sign
void timerLightTravel(uint32_t aColor, unsigned long aTime){
static int i = 0;
static unsigned long startTime = millis();
unsigned long currentTime = millis();



for (int i = 0; i<= strip.numPixels(); i++){

strip.setPixelColor(i,   strip.Color(255, 165, 0));




}
if (currentTime - startTime > aTime){
  startTime = millis();
  strip.setPixelColor(i, aColor);
  strip.setPixelColor(i + 1, aColor);

  strip.show();
  i++;


  if(i >= strip.numPixels()){
    i = 0;
  }
  

}
}

// first sequence interior

void timerLightTravelInside(uint32_t aColor, unsigned long aTime){
static int i = 0;
static unsigned long startTime = millis();
unsigned long currentTime = millis();



for (int i = 8; i<= strip2.numPixels(); i++){

strip2.setPixelColor(i,   strip2.Color(255, 165, 0));




}
if (currentTime - startTime > aTime){
  startTime = millis();
  strip2.setPixelColor(i, aColor);
  strip2.setPixelColor(i + 1, aColor);

  strip2.show();
  i++;


  if(i >= 16){
    i = 8;
  }
  

}





}
  // second sequence for sign
void timerLightTravelTwo(uint32_t aColor, uint32_t aColor2,unsigned long aTime){
static int i = 0;
static int j = 19;
static unsigned long startTime = millis();
unsigned long currentTime = millis();

for (int i = 0; i<= strip.numPixels(); i++){

strip.setPixelColor(i,   strip.Color(255, 100, 0));




}


if (currentTime - startTime > aTime){
  startTime = millis();
 
  strip.setPixelColor(i, aColor);
  strip.setPixelColor(i-1, aColor2);
  strip.show();
  i++;


  if(i >= strip.numPixels()){
     strip.setPixelColor(j, aColor);
      strip.setPixelColor(j - 1, aColor2);
  strip.show();
     j--;

     if(j == 0){
      i= 0;
     }
     if(i == 0){
      j = 60;
     }
   
  }
  }

}
// second sequence for interior


void timerLightTravelTwoInterior(uint32_t aColor, uint32_t aColor2,unsigned long aTime){
static int i = 0;
static int j = 8;
static unsigned long startTime = millis();
unsigned long currentTime = millis();

for (int i = 0; i<= strip2.numPixels(); i++){

strip2.setPixelColor(i,   strip2.Color(255, 100, 0));




}


if (currentTime - startTime > aTime){
  startTime = millis();
 
  strip2.setPixelColor(i, aColor);
  strip2.setPixelColor(i-1, aColor2);
  strip2.show();
  i++;


  if(i >= strip2.numPixels()){
     strip2.setPixelColor(j, aColor);
      strip2.setPixelColor(j - 1, aColor2);
  strip2.show();
     j--;

     if(j == 0){
      i= 0;
     }
     if(i == 0){
      j = 8;
     }
   
  }
  }

}

















// interoir and sign ----- timerColorSweep(strip.Color(random(), random(), random()),strip.Color(random(), random(), random()), strip.Color(random(), random(), random()), 50 );
// timerColorSweep1(strip.Color(random(), random(), random()),strip.Color(random(), random(), random()), strip.Color(random(), random(), random()), 50 );

void timerColorSweep(uint32_t aColor1, uint32_t aColor2, uint32_t aColor3, unsigned long aTime){
static int i = 0;
static unsigned long startTime = millis();
unsigned long currentTime = millis();
int state = i % 3;


if (currentTime - startTime > aTime){
  startTime = millis();
  strip.clear();


if (state == 0){
  
  for( int i = 0 ; i<  strip.numPixels(); i= i + 3 ){
  strip.setPixelColor(i, aColor1);

  strip.setPixelColor(i +1 , aColor2);
  strip.setPixelColor(i+ 2, aColor3);
   strip.show();
}}

if (state == 1){
   for( int i = 0 ; i<  strip.numPixels(); i= i + 3 ){
  strip.setPixelColor(i, aColor2);
  strip.setPixelColor(i +1 , aColor3);
  strip.setPixelColor(i+ 2, aColor1);
   strip.show();
}}

if (state == 2){
   for( int i = 0 ; i<  strip.numPixels(); i= i + 3 ){
  strip.setPixelColor(i, aColor3);
  strip.setPixelColor(i +1 , aColor1);
  strip.setPixelColor(i+ 2, aColor2);
   strip.show();
}}

  strip.show();
  i++;


  if(i >= strip.numPixels()){
    i = 0;
  }
  

}

}


void timerColorSweep1(uint32_t aColor1, uint32_t aColor2, uint32_t aColor3, unsigned long aTime){
static int i = 0;
static unsigned long startTime = millis();
unsigned long currentTime = millis();
int state = i % 3;


if (currentTime - startTime > aTime){
  startTime = millis();
  strip2.clear();


if (state == 0){
  
  for( int i = 0 ; i<  strip2.numPixels(); i= i + 3 ){
  strip2.setPixelColor(i, aColor1);

  strip2.setPixelColor(i +1 , aColor2);
  strip2.setPixelColor(i+ 2, aColor3);
   strip2.show();
}}

if (state == 1){
   for( int i = 0 ; i<  strip2.numPixels(); i= i + 3 ){
  strip2.setPixelColor(i, aColor2);
  strip2.setPixelColor(i +1 , aColor3);
  strip2.setPixelColor(i+ 2, aColor1);
   strip2.show();
}}

if (state == 2){
   for( int i = 0 ; i<  strip2.numPixels(); i= i + 3 ){
  strip2.setPixelColor(i, aColor3);
  strip2.setPixelColor(i +1 , aColor1);
  strip2.setPixelColor(i+ 2, aColor2);
   strip2.show();
}}

  strip2.show();
  i++;


  if(i >= strip2.numPixels()){
    i = 0;
  }
  

}

}


