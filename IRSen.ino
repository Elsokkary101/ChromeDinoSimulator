void setup() {
  Serial.begin(9600);
  pinMode(13 , INPUT);
  pinMode(8 , OUTPUT);
  pinMode(7 , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int statusSensor = digitalRead (13);
  
  if (statusSensor == 1){
    digitalWrite(8, LOW); 
    //Serial.println("The value of IR sensor is : " + statusSensor); 
  }else{
    digitalWrite(8, HIGH);  
  }

  int input_val = analogRead(A0);
  Serial.print("LDR Value is: ");
  Serial.println(input_val);
  if (input_val > 760){
    digitalWrite(7, LOW); 
  }else {
    digitalWrite(7, HIGH);
    }
  
}
