/*
  BlinkPattern
  short short long...

  This example code is in the public domain.
*/


// give it a name:
int out = 3;



// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(out, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {

  if(random(100) > 70){
    digitalWrite(out, HIGH);
    delay(10);
    digitalWrite(out, LOW);
    delay(140);
  }
  else{
    delay(150);
  }
  

}


