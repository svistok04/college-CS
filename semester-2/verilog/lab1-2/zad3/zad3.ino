  int pm = 0;
  int cm;
  int stan = HIGH;

void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 11; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
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
  if (cm - pm >= 500)
  {
    pm = cm;
    
  }
}


/*
 void loop() {
  // put your main code here, to run repeatedly:
  cm = millis();

    if(cm - pm >= 500)
    {
      for(int i = 11; i < 14; i++)
      {
       pm = cm;
       digitalWrite(i, stan);
       stan = !stan;
      }
  }
}
*/

/*
void loop() {
  // put your main code here, to run repeatedly:
  cm = millis();

    for(int i = 11; i < 14; i++)
    {
    if(cm - pm >= 500)
    {
      pm = cm;
      stan = !stan;
      digitalWrite(i, stan);
      break;
    }
  }
}
*/
