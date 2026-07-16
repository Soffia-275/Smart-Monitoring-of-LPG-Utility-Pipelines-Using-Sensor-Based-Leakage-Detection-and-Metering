#define ENA D5
#define IN1 D8
#define IN2 D7
#define IN3 D4
#define IN4 D3
#define ENB D6

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  Serial.println("Forward");
  forward();
  delay(3000);
  stopCar();
  delay(2000);

  Serial.println("Backward");
  backward();
  delay(3000);
  stopCar();
  delay(2000);

  Serial.println("Left");
  left();
  delay(3000);
  stopCar();
  delay(2000);

  Serial.println("Right");
  right();
  delay(3000);
  stopCar();
  delay(5000);
}

// ===== Movement Functions =====

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 800);
  analogWrite(ENB, 800);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 800);
  analogWrite(ENB, 800);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 800);
  analogWrite(ENB, 800);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 800);
  analogWrite(ENB, 800);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
