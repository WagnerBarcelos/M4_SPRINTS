void setup () {
  Serial.begin(9600);
  Serial.setTimeout(10);

  Serial.println("What is your name?");
}

void loop() {
  if (Serial.available()> 0) {
    String userName = Serial.readString();
    Serial.print("Your name is ");
    Serial.println(userName);
    Serial.println("What is your name?");
  }

}
