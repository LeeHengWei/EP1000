const int RED=8;
const int GREEN=7;
const int WHITE=6;
const int SW= 5;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WHITE, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(RED, HIGH);
  delay(150); 
  digitalWrite(GREEN, HIGH);
  delay(150); 
  digitalWrite(WHITE, HIGH);
  delay(150); 
  digitalWrite(RED, LOW);
  delay(150);  
  digitalWrite(GREEN, LOW);
  delay(150); 
  digitalWrite(WHITE, LOW);
  delay(150); 
}