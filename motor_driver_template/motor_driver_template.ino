#define BIN_1 26
#define BIN_2 25

/* setting PWM properties */
const int freq = 5000;
const int ledChannel_1 = 1;
const int ledChannel_2 = 2;
const int resolution = 8;
int MAX_PWM_VOLTAGE = 255;

long t = 0;

void setup() {
  /* configure LED PWM functionalitites */
  ledcSetup(ledChannel_1, freq, resolution);
  ledcSetup(ledChannel_2, freq, resolution);

  /* attach the channel to the GPIO to be controlled */
  ledcAttachPin(BIN_1, ledChannel_1);
  ledcAttachPin(BIN_2, ledChannel_2);
}

void loop() {
  t++;
  float angle = t * 0.1;
  float output = sin(angle) * MAX_PWM_VOLTAGE;
  if (output > 0) {
    ledcWrite(ledChannel_1, LOW);
    ledcWrite(ledChannel_2, output);
  }
  else {
    ledcWrite(ledChannel_2, LOW);
    ledcWrite(ledChannel_1, -output);
  }
  delay(50);
}
