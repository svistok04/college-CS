int pm = 0;
int cm;
int stan = HIGH;
  
void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 6; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for(int i = 11; i < 14; i++)
  {
     pinMode(i, OUTPUT);
     digitalWrite(i, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  cm = millis();
  if(cm - pm >= 1)
  {
    pm = cm;
  digitalWrite(2, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(2, LOW);
  digitalWrite(11, HIGH);
  
  digitalWrite(3, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(3, LOW);
  digitalWrite(12, HIGH);
  
  digitalWrite(4, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(4, LOW);
  digitalWrite(13, HIGH);
  }

}


/*
  digitalWrite(2, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(2, LOW);
  digitalWrite(11, HIGH);
  
  digitalWrite(3, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(3, LOW);
  digitalWrite(12, HIGH);
  
  digitalWrite(4, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(4, LOW);
  digitalWrite(13, HIGH);
*/
