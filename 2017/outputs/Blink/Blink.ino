/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 

// led Pin number:
 int led = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
//  pinMode(LED_BUILTIN, OUTPUT);   
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);               // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);               // wait for a second

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(200);               // wait for a second
}
