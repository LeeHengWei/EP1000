const int RED = 8, GREEN = 7, BLUE = 6, MS = 250, SW = 4;
int count = 0;

void setup(){
  pinMode(RED, OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  int status = digitalRead(SW);
  if (status == LOW)
  {
    count++;
    delay(1000);
    status = digitalRead(SW);
    if (status == LOW)
      reset();
    if(count>6)
      count=0;
  }
  switch(count)
  {
    case 1:
    light(1,0,0);
    break;
      
    case 2:
    light(0,1,0);
    break;
      
    case 3:
    light(0,0,1);
    break;
      
    case 4:
    light(1,1,1);
    break;
      
    case 5:
    light(0,0,0);
    break;
      
    case 6:
    light6();
    break;
      
    default:
    digitalWrite(RED,LOW); 
    digitalWrite(GREEN,LOW);
  	digitalWrite(BLUE,LOW);
    break;
  }  
}

void light(int red, int green, int blue)
{
  digitalWrite(RED,red);
  digitalWrite(GREEN,green);
  digitalWrite(BLUE,blue);
}

void light6(){
  digitalWrite(RED,HIGH);
  delay(200);
  digitalWrite(GREEN,HIGH);
  delay(200);
  digitalWrite(BLUE,HIGH);
  delay(200);
  digitalWrite(RED,LOW);
  delay(200);
  digitalWrite(GREEN,LOW);
  delay(200);
  digitalWrite(BLUE,LOW);
  delay(200);
  delay(MS);
  digitalWrite(BLUE,HIGH);
  delay(200);
  digitalWrite(GREEN,HIGH);
  delay(200);
  digitalWrite(RED,HIGH);
  delay(200);
  digitalWrite(BLUE,LOW);
  delay(200);
  digitalWrite(GREEN,LOW);
  delay(200);
  digitalWrite(RED,LOW);
  delay(200);
  delay(MS);
}

void reset(){
  delay(2000);
  light(0,0,0);
  count = 0;
  delay(1500);
}
