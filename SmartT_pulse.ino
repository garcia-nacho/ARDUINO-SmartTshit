
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

#include <Adafruit_NeoPixel.h>

//Digital Pin connected to Arduino
#define PIN  6 
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int pulseStop;
//Color codes RGB
int R;
int G;
int B;


// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   


  pixels.begin(); 
  pixels.setBrightness(255);
  pixels.show();

//Here goes the start sequence
  
  for (int i=0; i<10; i++){
  pixels.setPixelColor(0, pixels.Color(0,0,255));
  pixels.setPixelColor(1, pixels.Color(0,0,255));
  
  pixels.setPixelColor(4, pixels.Color(0,0,255));
  pixels.setPixelColor(5, pixels.Color(0,0,255));
  
  pixels.setPixelColor(8, pixels.Color(0,0,255));
  pixels.setPixelColor(9, pixels.Color(0,0,255));
  
  pixels.setPixelColor(12, pixels.Color(0,0,255));
  pixels.setPixelColor(13, pixels.Color(0,0,255));
  
    pixels.setPixelColor(2, pixels.Color(0,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,0));
  
  pixels.setPixelColor(6, pixels.Color(0,0,0));
  pixels.setPixelColor(7, pixels.Color(0,0,0));
  
  pixels.setPixelColor(10, pixels.Color(0,0,0));
  pixels.setPixelColor(11, pixels.Color(0,0,0));
  
  pixels.setPixelColor(14, pixels.Color(0,0,0));
  pixels.setPixelColor(15, pixels.Color(0,0,0));
  
    pixels.show();
delay(200);

  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  
  pixels.setPixelColor(4, pixels.Color(0,0,0));
  pixels.setPixelColor(5, pixels.Color(0,0,0));
  
  pixels.setPixelColor(8, pixels.Color(0,0,0));
  pixels.setPixelColor(9, pixels.Color(0,0,0));
  
  pixels.setPixelColor(12, pixels.Color(0,0,0));
  pixels.setPixelColor(13, pixels.Color(0,0,0));
  
  pixels.setPixelColor(2, pixels.Color(0,0,255));
  pixels.setPixelColor(3, pixels.Color(0,0,255));
  
  pixels.setPixelColor(6, pixels.Color(0,0,255));
  pixels.setPixelColor(7, pixels.Color(0,0,255));
  
  pixels.setPixelColor(10, pixels.Color(0,0,255));
  pixels.setPixelColor(11, pixels.Color(0,0,255));
  
  pixels.setPixelColor(14, pixels.Color(0,0,255));
  pixels.setPixelColor(15, pixels.Color(0,0,255));
  pixels.show();
delay(200);
  }

for(int i=0;i<NUMPIXELS;i++){
   pixels.setPixelColor(i, pixels.Color(0,0,0)); 
   pixels.show();
   delay(50);
}

for(int i=0;i<NUMPIXELS;i++){
   pixels.setPixelColor(i, pixels.Color(0,0,255)); 
   pixels.show();
   delay(50);
}

for(int i=0;i<NUMPIXELS;i++){
   pixels.setPixelColor(i, pixels.Color(0,0,0)); 
   pixels.show();
   delay(50);
}


}


//  Where the Magic Happens
void loop(){


if (BPM<70){
   BPM = 70;
}

pulseStop = abs(1000*3.75/BPM);


if (BPM>181){
   BPM = 181;
}

if (BPM <= 125)
{
   R= abs((BPM-70)*4.63);
   G=255;
   B=0;
}

else
{
   R=255;
   G= abs(255-((BPM-126)*4.63));
   B=0;
}


  pixels.setPixelColor(15, pixels.Color(0,0,0));
  pixels.setPixelColor(14, pixels.Color(0,0,0));
    pixels.show();

for(int i=0;i<NUMPIXELS;i++){

  
  pixels.setPixelColor(i, pixels.Color(R,G,B)); 
  pixels.setPixelColor(i+1, pixels.Color(R,G,B));
  pixels.setPixelColor(i-1, pixels.Color(0,0,0));
    pixels.show();

if (i==NUMPIXELS-1){
  pixels.setPixelColor(i, pixels.Color(R,G,B));
  pixels.setPixelColor(0, pixels.Color(R,G,B));
  pixels.show();
}
    

    delay(pulseStop);

  }







 
}




