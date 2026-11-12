
#define PIR_PIN 27
#define GAS_PIN 34

#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 21
#define BUZZER 23

const int GAS_THRESHOLD = 1800;
const unsigned long LIGHT_HOLD_TIME = 5000;

volatile bool motionEvent = false;
unsigned long lastMotionTime = 0;
unsigned long previousMillis = 0;
unsigned long previousPrintMillis = 0;

bool redLedState = false;

void IRAM_ATTR motionISR() {
  motionEvent = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionISR, RISING);

  Serial.println("Smart Home Safety System Started");
}

void loop() {
  int gasValue = analogRead(GAS_PIN);
  int pirValue = digitalRead(PIR_PIN);

  if (motionEvent) {
    motionEvent = false;
    lastMotionTime = millis();
  }

  if (pirValue == HIGH) {
    lastMotionTime = millis();
  }

  if (millis() - previousPrintMillis >= 500) {
    previousPrintMillis = millis();
    Serial.print("Gas ADC Value: ");
    Serial.println(gasValue);
    Serial.print("PIR Value: ");
    Serial.println(pirValue);
  }

  // GAS SAFETY OVERRIDE
  if (gasValue > GAS_THRESHOLD) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BUZZER, HIGH);

    if (millis() - previousMillis >= 300) {
      previousMillis = millis();
      redLedState = !redLedState;
      digitalWrite(RED_LED, redLedState);
    }

    Serial.println("GAS ALERT! SAFETY MODE");
  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    redLedState = false;

    if (lastMotionTime != 0 &&
        millis() - lastMotionTime < LIGHT_HOLD_TIME) {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      Serial.println("Motion Detected - LIGHTS ON");
    }
    else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      Serial.println("No Motion - LIGHTS OFF");
    }
  }

  delay(50);
}
