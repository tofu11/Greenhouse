const int SENSOR = A0;
const int PUMP = 9;
int BASE_LVL = 0;
int MOISTURE_LVL = 600;

void setup(){
  pinMode(SENSOR,INPUT);
  pinMode(PUMP,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  MOISTURE_LVL = analogRead(SENSOR);
  Serial.print(MOISTURE_LVL);
  Serial.print("\n");
  if (MOISTURE_LVL > BASE_LVL){
    Serial.print("Pump should run here\n");
    digitalWrite(PUMP, HIGH);
    delay(2000);
  }
  else{
    digitalWrite(PUMP, LOW);
  }
}
