#include <FastLED.h>
#include "IRremote.h"

#define LED_PIN  5
#define NUM_LEDS 60

//#define FASTLED_ALLOW_INTERRUPTS 0

#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

int hue = 255;
int sat = 255;
int bri = 128;

int receiver = 11;
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

#define UPDATES_PER_SECOND 10

/*-----( Function )-----*/
String translateIR() {// takes action based on IR code received

// describing Remote IR codes 


  String ans = "";
  switch(results.value)

  {
  case 0xFFA25D: ans = "POWER"; break;
  case 0xFFE21D: ans =("FUNC/STOP"); break;
  case 0xFF629D: ans =("VOL+"); break;
  case 0xFF22DD: ans =("FAST BACK");    break;
  case 0xFF02FD: ans =("PAUSE");    break;
  case 0xFFC23D: ans =("FAST FORWARD");   break;
  case 0xFFE01F: ans =("DOWN");    break;
  case 0xFFA857: ans =("VOL-");    break;
  case 0xFF906F: ans =("UP");    break;
  case 0xFF9867: ans =("EQ");    break;
  case 0xFFB04F: ans =("ST/REPT");    break;
  case 0xFF6897: ans =("0");    break;
  case 0xFF30CF: ans =("1");    break;
  case 0xFF18E7: ans =("2");    break;
  case 0xFF7A85: ans =("3");    break;
  case 0xFF10EF: ans =("4");    break;
  case 0xFF38C7: ans =("5");    break;
  case 0xFF5AA5: ans =("6");    break;
  case 0xFF42BD: ans =("7");    break;
  case 0xFF4AB5: ans =("8");    break;
  case 0xFF52AD: ans =("9");    break;
  case 0xFFFFFFFF: ans =(" REPEAT");break;  

  default: 
    ans =(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat
  return ans;

} //END translateIR

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
  for(int i = 0; i < 100; i++){
    FastLED.clear();
    FastLED.setBrightness(bri);
  }
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:

    if(irrecv.decode(&results)){
      String val = translateIR();


      if(val.equals("POWER")){
        FastLED.clear();
        FastLED.show();
        Serial.println(val);
      }

      /*if(val.equals("VOL+")){
        int equation = bri + 64;
        if(equation > 255){
          equation = 255;
        }
        FastLED.setBrightness(equation);
        bri = equation;
        Serial.println(bri);
        
        FastLED.show();
        Serial.println(val);
      }*/

      if(val.equals("VOL-")){
        int adj = bri / 2;
        for(int i = 0; i < NUM_LEDS; i++){
          leds[i].fadeLightBy(128);
          //leds[i].setHSV(hue, sat, bri - adj);
        }
        bri -= adj;
        FastLED.show();
        Serial.println(val);
        Serial.println(bri);
      }
      if(val.equals("6")){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS; i++){
          //leds[i].setHSV(171, 255, 225); //PURE BLUE
          leds[i] = CRGB::Blue;
          
        }
       
        FastLED.show();
        Serial.println(val);
      }

      if(val.equals("0")){
        FastLED.clear();
        darkSynth();
        bri = 255;
        FastLED.show();
        Serial.println(val);
      }

      if(val.equals("2")){
        FastLED.clear();
        party1();
        bri = 255;
        FastLED.show();
        Serial.println(val);
      }

      if(val.equals("4")){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS; i++){
          //leds[i].setHSV(100, 255, 255); //PURE RED
          leds[i] = CRGB::Green;
        }
        bri = 255;
        FastLED.show();
        Serial.println(val);
      }

      if(val.equals("5")){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS; i++){
          //leds[i].setHSV(0, 255, 255); //PURE GREEN
          leds[i] = CRGB::Red;
        }
        bri = 255;
        FastLED.show();
        Serial.println(val);
      }

      if(val.equals("3")){
        FastLED.clear();
        halloween();
        FastLED.show();
        Serial.println(val);
      }

     /* if(val.equals("1")){
        FastLED.clear();
        FastLED.setTemperature(DirectSunlight);
        for(int i = 0; i < NUM_LEDS; i++){
          //leds[i].setHSV(255, 255, 255);
          leds[i] = CRGB::White;
          leds[i] = DirectSunlight;
        }
        hue = 255;
        sat = 255;
        bri = 255;
        FastLED.setBrightness(127);
        FastLED.show();
        Serial.println(val);
      }*/



      irrecv.resume();
    }
 
    delay(1000);

    

    
    
}

void darkSynth(){

      for(int i = 0; i < NUM_LEDS; i++){
     
      if(i % 2 == 0){
        leds[i].setHSV(100, 255, 255);
      }
      else{
        leds[i].setHSV(150, 225, 225);
        //leds[i].setRGB(26,85, 139);
      }
    }
  
}

void party1(){
  //make the colors change in and out like the other soutwest dorms -- Ben Cannoli
  for(int i = 0; i < NUM_LEDS; i++){

    if(i % 2 == 0){
      leds[i].setRGB(20, 219, 60);
    }
    else{
      leds[i].setRGB(0, 0, 166);
    }
  }
  FastLED.show();

}

void halloween(){
  for(int i = 0; i < NUM_LEDS; i++){

    if(i % 3 == 0 || i % 3 == 2){
    leds[i].setRGB(131, 244, 27);
    }
    else{
      leds[i].setHSV(150, 207, 225);
      
    }
  }
}
