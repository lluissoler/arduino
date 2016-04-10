void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  
  String content = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
      //delay(1);
  }

  if (content != ""){
      Serial.print(content);
      if (content == "a") {
          //Serial.println("Pin 12 is ON");
          digitalWrite(12, HIGH);
      } else if (content == "b") {
          //Serial.println("Pin 12 is OFF");
          digitalWrite(12, LOW);
      } else if (content == "c") {
          //Serial.println("Pin 12 is ON");
          digitalWrite(13, HIGH);
      } else if (content == "d") {
          //Serial.println("Pin 12 is OFF");
          digitalWrite(13, LOW);
      }
  }

}
