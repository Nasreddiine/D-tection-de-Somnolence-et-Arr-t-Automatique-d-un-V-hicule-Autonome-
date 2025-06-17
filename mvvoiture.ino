const int ENA = 5;   // PWM moteur A
const int ENB = 6;   // PWM moteur B
const int IN1 = 8;   // Contrôle moteur A
const int IN2 = 9;
const int IN3 = 10;  // Contrôle moteur B
const int IN4 = 11;
const int buzzerPin = 7;
const int emergencyButton = 4;  // Bouton d'arrêt (pull-up)
const int ledPin = 3; 

void setup() {
  // Configuration des broches
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(emergencyButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Initialisation série
  Serial.begin(9600);
  while (!Serial);  // Pour cartes avec USB natif uniquement

  stopMotors();
  Serial.println("🚗 Système prêt - démarrage automatique");

  // Lancement automatique
  moveForward();
}

void loop() {
  // Arrêt d'urgence manuel
  if (digitalRead(emergencyButton) == LOW) {
    triggerEmergencyStop();
  }
   // Lecture des commandes série du Raspberry Pi
    if (Serial.available() > 0) {
        char command = Serial.read();
        if (command == 'S') {
            triggerEmergencyStop();  // Arrêt immédiat
        }
    }

  // Autres tâches possibles ici (capteurs, évitement, etc.)
}

// Fonctions de contrôle
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);  // Vitesse modérée
  analogWrite(ENB, 200);
}

void stopMotors() {
  int currentSpeedA = 200;
  int currentSpeedB = 200;

  // Décélération progressive
  for (int speed = currentSpeedA; speed >= 0; speed -= 10) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(50);  // Délai entre chaque palier
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void triggerEmergencyStop() {
  stopMotors();
  Serial.println("🚨 Arrêt d'urgence activé !");
  digitalWrite(ledPin, HIGH);  // 🔴 LED allumée

  // Alarme sonore
  unsigned long startTime = millis();
  while (millis() - startTime < 10000) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);

    if (digitalRead(emergencyButton) == LOW) {
      break;
    }
  }
}