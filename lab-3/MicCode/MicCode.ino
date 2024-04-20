// www.elegoo.com
// 2018.10.24
/*
  LED1 should be lit, showing power. LED2 indicates sound input, and the sensitivity is adjusted by potentiometer.
  There is a tiny screw on the blue potentiometer block that you can use for adjustment. Turning that
  clockwise lowers the potentiometer value, while counter-clockwise raises the potentiometer value.
  Use the potentiometer to adjust the Sound Sensor sensitivity. Turn the potentiometer
  several rotations until you see the LED2 extinguish (or just faintly blink). This might be slightly greater than
  500, if you are also watching Serial Monitor (inital adjustment), or, Serial Plotter (the latter is prefererd for observation).
  Special thanks to user CRomer, for his input and hard work!
*/
#include "arduinoFFT.h"
int  sensorAnalogPin = A0;    // Select the Arduino input pin to accept the Sound Sensor's analog output 
int  sensorDigitalPin = 2;    // Select the Arduino input pin to accept the Sound Sensor's digital output
int  analogValue = 0;         // Define variable to store the analog value coming from the Sound Sensor
int  digitalValue;            // Define variable to store the digital value coming from the Sound Sensor
int  Led13 = 13;              // Define LED port; this is the LED built in to the Arduino (labled L)
                              // When D0 from the Sound Sensor (connnected to pin 7 on the
                              // Arduino) sends High (voltage present), L will light up. In practice, you
                              // should see LED13 on the Arduino blink when LED2 on the Sensor is 100% lit.

//Arduino FFT Library Constants and Declarations
double main_freq = 0;
int frequencies{};
int numSamples = 0;
unsigned long ms = 0;
const uint16_t samples = 128;
double vReal[samples];
double vImag[samples];
const double samplingFreq = 1600;
unsigned int time_const = round(1000000/samplingFreq);
arduinoFFT FFT = arduinoFFT();
double a4 = 440;
double c4 = 262;
double precision = 0.02;


void setup(){
  pinMode(sensorDigitalPin,INPUT);
  Serial.begin(115200);               // The IDE settings for Serial Monitor/Plotter (preferred) must match this speed
  pinMode(sensorDigitalPin,INPUT);  // Define pin 3 as an input port, to accept digital input
}

void loop(){
  ms = micros();
  for(int i = 0; i < samples; i++){
    vReal[i] = (double)analogRead(sensorAnalogPin);
    vImag[i] = 0;
    while(micros() < ms + time_const){

    }
    ms += time_const;
  }

  FFT.Windowing(vReal, samples, FFTWindow::Hamming, FFTDirection::Forward);
  FFT.Compute(vReal, vImag, samples, FFTDirection::Forward);
  FFT.ComplexToMagnitude(vReal, vImag, samples);
  Serial.print("Main frequency: ");
  main_freq = FFT.MajorPeak(vReal, samples, samplingFreq);
  Serial.println(main_freq);
  
  delay(50);                  // Slight pause so that we don't overwhelm the serial interface
}
