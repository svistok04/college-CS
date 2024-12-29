void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 5; i++)
  {
    pinMode(i, OUTPUT);
  }
  for(int i = 11; i < 14; i++)
  {
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }
}

void loop() {
  for(int i = 2; i < 5; i++)
  {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);  
  }
}
