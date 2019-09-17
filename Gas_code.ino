
/*If you like my video please
Like.Comment.Share

Subscribe my channel for more updates & click on the bell icon for notification
https://www.youtube.com/c/Technolabcreation  */
int smokeA0 = A5;
int buzzer = 8;

void setup() {
  
  pinMode(smokeA0, INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

 if(analogSensor>400)
 {
  digitalWrite(buzzer,HIGH);
  
}

else
{
  digitalWrite(buzzer,LOW);
}
}
