
#include <ESP8266WiFi.h>
#include <Servo.h>

String apiWritekey = "GE6QRHO8SOQGEQRR"; // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "pulchokians_wlink"; // your wifi SSID name
const char* password = "rautahat11" ;// wifi pasword
 
const char* server = "api.thingspeak.com";
//float resolution=3.3/1023;// 3.3 is the supply volt  & 1023 is max analog read value
WiFiClient client;

#define MUX_A D0
#define MUX_B D1
#define MUX_C D2
#define buzzer D3
#define button D5
#define servo D4


#define ANALOG_INPUT A0
Servo myservo;


void setup() {
  //Deifne output pins for Mux
 Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
  pinMode(MUX_C, OUTPUT);  
  myservo.attach(servo);
  myservo.write( 70 );
  delay(7500);
  myservo.write( 0 );
  
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(button,LOW); 
  digitalWrite(buzzer,LOW);
    
}

void changeMux(int c, int b, int a) {
  digitalWrite(MUX_A, a);
  digitalWrite(MUX_B, b);
  digitalWrite(MUX_C, c);
}

void loop() {
  float value;
  float v1;
  float v2;
 
  
  changeMux(LOW, LOW, LOW);
  value = analogRead(ANALOG_INPUT); //Value of the  alcohol sensor connected Option 0 pin of Mux
  Serial.print("data from alcohol sensor  ");
  Serial.println(value);
  
  changeMux(LOW, LOW, HIGH);
  v1 = analogRead(ANALOG_INPUT); //Value of the  gas sensor connected Option 1 pin of Mux
  Serial.print(" data from gas sensor");
  Serial.println(v1);

   changeMux(LOW, HIGH, LOW);
  v2 = analogRead(ANALOG_INPUT); //Value of the  fire sensor connected Option 2 pin of Mux
  Serial.print("data from fire sensor ");
  Serial.println(v2);

  

    if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(v1);
           tsData +="&field2=";
           tsData += String(v2);
           tsData += "\r\n\r\n";
           
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     /*Serial.print("Voltage: ");
     Serial.print(v1);*/
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();

   int b=digitalRead(button);
   Serial.println(b);
  if(b == HIGH)
   {

     if (value <= 580) //check alcohol level
  {
    Serial.println("Authorized access");
    Serial.println();
   myservo.write( 70 );
 delay(7500);
  myservo.write( 0 );

 
   }
 
 else   
 {
    Serial.println(" drunkar person");
    

    delay(100);

 
  }
}

   if(v2<=400)
   {
     digitalWrite(buzzer,HIGH);
   }
   else
   {
     digitalWrite(buzzer,LOW);
   }

  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1500);
 
  
  // thingspeak needs minimum 15 sec delay between updates
 // delay(2000);
  
}
