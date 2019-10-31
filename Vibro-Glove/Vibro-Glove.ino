const int VM0 = 0;
const int VM1 = 1;
const int VM2 = 2;
const int VM3 = 3;

void setup() {
  Serial.begin(9600);
  pinMode(VM0, OUTPUT);
  pinMode(VM1, OUTPUT);
  pinMode(VM2, OUTPUT);
  pinMode(VM3, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
  digitalWrite(VM0, HIGH);
  digitalWrite(VM1, HIGH);
  digitalWrite(VM2, HIGH);
  digitalWrite(VM3, HIGH);
  delay(1000);
  digitalWrite(VM0, LOW);
  digitalWrite(VM1, LOW);
  digitalWrite(VM2, LOW);
  digitalWrite(VM3, LOW);
  delay(1000);
  }
}
