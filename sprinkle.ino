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