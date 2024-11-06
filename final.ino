//create project where there is to animations on fire one and one rainbow
//make sure it can ditect sound and play a song when it detects sound



#include <Adafruit_CircuitPlayground.h>
const int soundThreshold = 25;//sets the sound it can detect
const int melody[] = {440, 440, 415, 330, 370, 415, 440};// notes for the song
const int noteDurations[] = {4, 3, 4, 3, 5, 5, 2};// duration of notes 
float tiltThreshold = 2.0;// detction of the tilt
bool  isPlaying = false; // for the song to stop playing

void setup() {
  CircuitPlayground.begin();          
  CircuitPlayground.clearPixels();     
}

void loop() {
  if (CircuitPlayground.leftButton()) {    
    rainbowAnimation();                    // Show rainbow animation if pressed
  } else {
    fireAnimation();                       // show fire aniamtion if not pressed 
  }

int soundLevel = CircuitPlayground.soundSensor();//activates the sound sensor
if (soundLevel> soundThreshold && !isPlaying){
  isPlaying = true;//if its playing play
  Sound(); 
  isPlaying = false;//if there is no detected sound it stops playing
} 
  if(detectTilt()){
    pulseHeart();// if the expressis tilted it plays heart animation
  }else {
    CircuitPlayground.clearPixels(); // Turn off LEDs of heartanimation
  }
}

void Sound(){
for (int i = 0; i < 15; i++) {
    int noteDuration = 1000 / noteDurations[i];// plays the notes and the durations
    CircuitPlayground.playTone(melody[i], noteDuration);
    delay(noteDuration * 1.1); // Slight pause between notes
  }
}

// Function for fire animation
void fireAnimation() {

  for (int i = 0; i < 10; i++) {  // Loop the colors
    int red = random(230, 255);    // Intense red tones
    int green = random(30, 120);   // Lower green for warmth
    int brightness = random(50, 235);  // Random brightness to simulate flickering

    CircuitPlayground.setPixelColor(i, red, green, 0); // Set each LED colors
    CircuitPlayground.setBrightness( 50);  // Set the pixel brightness 
  }
  delay(random(30, 100));  // delay for flickering effect
}

// Function for rainbow animation
void rainbowAnimation() {
  
  uint8_t hue = 0;    // Start hue at 0
  for (int j = 0; j < 256; j++) {    // Loop through hues for full rainbow
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel((hue + (i * 256 / 10)) & 255));//set the LED hue for each one
    }
    hue++;                           // Increment hue for shifting rainbow
    delay(10);                       //delay for smooth rainbow effect
  }
  
}
bool detectTilt() {
  // Read X-axis value from the accelerometer for the tilt
  float x = CircuitPlayground.motionX();

  // Check if X-axis exceeds the tilt threshold positive or negative
  if (abs(x) > tiltThreshold) {
    return true; // Tilt detected
  }
  return false; // No tilt detected
}

void pulseHeart() {
  // Brighten and dim the heart animation
  for (int brightness = 50; brightness <= 255; brightness += 5) {
    setHeartColor(brightness, 0, 0); // Set color to red with increasing brightness
    delay(20); // Delay for smooth pulsing
  }
  for (int brightness = 255; brightness >= 50; brightness -= 5) {
    setHeartColor(brightness, 0, 0); // Dim the heart
    delay(20);
  }
}

// Function to set LEDs in a heart pattern with a given color
void setHeartColor(int red, int green, int blue) {
  //  LEDs in a heart pattern
  int heartPattern[] = {0, 1, 3, 4, 5, 6, 8, 9}; // LEDs that form a heart shape
  
  CircuitPlayground.clearPixels(); // Clear all LEDs first
  
  // Set each LED in the heart pattern to the specified color
  for (int i = 0; i < 8; i++) {
    CircuitPlayground.setPixelColor(heartPattern[i], red, green, blue);
  }
}
