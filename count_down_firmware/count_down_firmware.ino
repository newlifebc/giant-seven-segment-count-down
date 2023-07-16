/*
  count down firmware for giant 7 segment display
  Created by Matthew Swarts, July 2023
  designed for use on an Arduino Uno R3 or M0
  uses the Adafruit Neopixel library
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BUTTON_PIN  13
#define DATA_PIN    3
#define NUM_PIXELS  50
Adafruit_NeoPixel pixels(NUM_PIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);

uint32_t last_button_state_update = 0;
bool last_button_state = HIGH; //should be high


/*
 * enums for the 7 segments
 */
enum segment_t:uint8_t{
  UpperRightSegment,
  UpperSegment,
  UpperLeftSegment,
  CenterSegment,
  LowerRightSegment,
  LowerSegment,
  LowerLeftSegment
};



/*
 * takes in a segment enum type
 * sets the pixel offset since they're all 7 pixels wide
 *  and they're in a linear sequence
 * sets those 7 pixels to white
 * assumes you have already cleared all leds to black before adding these segments
 */
void setSegment(segment_t segment){
  int pixel_offset;
  
  switch(segment){
    case UpperRightSegment:
      pixel_offset = 1;
      break;
    case UpperSegment:
      pixel_offset = 8;
      break;
    case UpperLeftSegment:
      pixel_offset = 15;
      break;
    case CenterSegment:
      pixel_offset = 22;
      break;
    case LowerRightSegment:
      pixel_offset = 29;
      break;
    case LowerSegment:
      pixel_offset = 36;
      break;
    case LowerLeftSegment:
      pixel_offset = 43;
      break;
    
    default:
    return; //exit the function since this isn't a valid segment id
    break;
  }
  for(int i=0; i<7; i++) { // For each pixel...
     pixels.setPixelColor(i+pixel_offset, pixels.Color(255, 255, 255)); //set pixels to white
  }
}



/*
 * should only be 0-9
 * assumes you have already cleared all leds to zero/black before this
 */
void setNumber(int num){
  switch(num){
    case 0:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      //setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      setSegment(LowerLeftSegment);
      break;
    case 1:
      setSegment(UpperRightSegment);
      //setSegment(UpperSegment);
      //setSegment(UpperLeftSegment);
      //setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      //setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    case 2:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      //setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      //setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      setSegment(LowerLeftSegment);
      break;
    case 3:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      //setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    case 4:
      setSegment(UpperRightSegment);
      //setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      //setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    case 5:
      //setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    case 6:
      //setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      setSegment(LowerLeftSegment);
      break;
    case 7:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      //setSegment(UpperLeftSegment);
      //setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      //setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    case 8:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      setSegment(LowerLeftSegment);
      break;
    case 9:
      setSegment(UpperRightSegment);
      setSegment(UpperSegment);
      setSegment(UpperLeftSegment);
      setSegment(CenterSegment);
      setSegment(LowerRightSegment);
      setSegment(LowerSegment);
      //setSegment(LowerLeftSegment);
      break;
    default:
      //do nothing
      break;
  }
}


/*
 * this should flicker with an orange flame
 * this does NOT clear the pixels to zero/black when it is done
 */
void flicker(uint32_t duration_millis=5000){

  uint32_t start_millis = millis();

  while(millis()-start_millis<duration_millis){
    
    //  Uncomment one of these RGB (Red, Green, Blue) values to
    //  set the base color of the flame.  The color will flickr
    //  based on the initial base color
    
    //  Regular (orange) flame:
      int r = 226, g = 121, b = 35;
  
    //  Purple flame:
    //  int r = 158, g = 8, b = 148;
  
    //  Green flame:
    //int r = 74, g = 150, b = 12;
  
    //  Flicker, based on our initial RGB values
    for(int i=0; i<pixels.numPixels(); i++) {
      int flicker = random(0,55);
      int r1 = r-flicker;
      int g1 = g-flicker;
      int b1 = b-flicker;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      pixels.setPixelColor(i,r1,g1, b1);
    }
    pixels.show();
  
    //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
    //  color switch delay to give a sense of realism
    delay(random(10,113));
  }
}


/*
 * counts down from 9 to 0; can't do 10 unfortunately
 * this is blocking code
 * does a flicker of flames at the end
 * abruptly stops after the flames; could be coded to fade out
 */
void countDown(){
  for(int i=9;i>=0;i--){
    pixels.clear(); // Set all pixel colors to 'off'
    setNumber(i);   //set the white pixels
    pixels.show();  //actually load the pixel value data
    delay(1000);    //wait 1 second
  }
  flicker(5000); //flicker for 5 seconds
  pixels.clear(); // Set all pixel colors to 'off'
}


/*
 * checks the button state with hysteresis
 */
void checkButtonState(){
  bool curr_button_state = digitalRead(BUTTON_PIN); //get current button state
  if(last_button_state != curr_button_state){ //there is a change in state
    last_button_state = curr_button_state;
    if(curr_button_state == LOW){ //we have a press
      countDown();
    }else{ //we have a release
      //do nothing
    }
  }
}



void setup() {
  delay(3000); // 3 second delay for recovery
  pinMode(BUTTON_PIN,INPUT_PULLUP); //pull pin 13 high with internal pullup
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
}

void loop()
{
  if(millis()-last_button_state_update>5){ //scan at ~200Hz
    checkButtonState();
  }
}
