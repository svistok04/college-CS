void setup() {
  // put your setup code here, to run once:
  for(int i = 1; i < 14; i++)
  {
     pinMode(i, OUTPUT);
  }
  for(int i = 11; i < 14; i++)
  {
     digitalWrite(i, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 11; i < 14; i++)
  {
     digitalWrite(i, LOW);
     for(int i = 2; i < 11; i++)
     {
       digitalWrite(i, HIGH);
       delay(500);
       digitalWrite(i, LOW);
     }
     delay(500);
     digitalWrite(i, HIGH);
  }
}
