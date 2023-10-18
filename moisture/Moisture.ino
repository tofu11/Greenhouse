const int relayPin = 8;
const int sensorPin = A0;
float sensorValue = 0;

void setup() {
Serial.begin(9600);
pinMode(relayPin, OUTPUT)
pinMode(sensorPin, INPUT);
digitalWrite(relayPin, HIGH);
delay(2000);
}

void loop() {
Serial.print("MOISTURE LEVEL: ");
sensorValue = analogRead(sensorPin);
//sets "sensorValue" to input value from A0
Serial.print(sensorValue);
//prints moisture level
if(sensorValue>750)
{
digitalWrite(relayPin, HIGH);
//if moisture level is above 750, turns off pump
}
else
{
digitalWrite(relayPin, LOW);
//if moisture level is not above 750, turns on pump
}
Serial.println();
delay(1000);
}
Ziang Chen — Yesterday at 4:15 PM
Image
const int button= 2;
const int led= 8;
int buttonstate;
void setup(){
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
}
void loop(){
  buttonstate=digitalRead(button);
  if (button==HIGH){
    digitalWrite(led,LOW);
  }
  else{
    digitalWrite(led,HIGH);
  }
}