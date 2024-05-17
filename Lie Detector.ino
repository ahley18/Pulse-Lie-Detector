#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int PulseWire = 0;
const int redLED = 9;
const int greenLED = 10;
const int button = 8;
const int buzzer = 11;
int Threshold = 550;


PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);


void setup() {   

  Serial.begin(9600);          // For Serial Monitor
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

 
  
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);  
  pulseSensor.setThreshold(Threshold);   

  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  
}



void loop() {
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("    LIE \n DETECTOR");
    display.setCursor(0,0);
    display.display();  
start:
 char button_status = digitalRead(button);

if (button_status == LOW) {            
int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
  delay(100);
  if(myBPM >= 100){
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("   Stop  \n lying!!!");
    display.setCursor(0,0);
    display.display(); // actually display all of the above

    for(int x = 0; x <= 5;x++){
      tone(buzzer,440);
      delay(200);
      noTone(buzzer);
      delay(200);
    }
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.setCursor(0,0);
  }
  else{
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Wow ang \nhonest!!!");
    display.setCursor(0,0);
    display.display(); // actually display all of the above
    
    delay(2000);
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.setCursor(0,0);
  }

}

else{
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,LOW);
  goto start;  
}


}

  
