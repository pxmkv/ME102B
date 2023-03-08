#include <ESP32Encoder.h>
#define BIN_1 26
#define BIN_2 25

ESP32Encoder encoder;

/* encoder */
float p = 0;
float v = 0;
float p_last = 0;
const long dt = 20;

/* setting PWM properties */
const int freq = 5000;
const int ledChannel_1 = 1;
const int ledChannel_2 = 2;
const int resolution = 8;
int MAX_PWM_VOLTAGE = 255;

unsigned long time_now = 0;
long t = 0;
float dp=0;

void setup() {
  Serial.begin(115200);
  ESP32Encoder::useInternalWeakPullResistors = UP; // Enable the weak pull up resistors
  encoder.attachHalfQuad(27, 33); // Attache pins for use as encoder pins
  encoder.setCount(0);  // set starting count value after attaching

  /* configure LED PWM functionalitites */
  ledcSetup(ledChannel_1, freq, resolution);
  ledcSetup(ledChannel_2, freq, resolution);

  /* attach the channel to the GPIO to be controlled */
  ledcAttachPin(BIN_1, ledChannel_1);
  ledcAttachPin(BIN_2, ledChannel_2);
}

void loop() {
  /* encoder section */
  time_now = millis();
  
  p = encoder.getCount() / (75.81 * 6) * 2 * M_PI;
  
  /* motor sine wave section */
  t++;
  float angle = t * 0.1;
  float output = sin(angle) *MAX_PWM_VOLTAGE;
  if (output > 0) {
    ledcWrite(ledChannel_1, LOW);
    ledcWrite(ledChannel_2, output);
  }
  else {
    ledcWrite(ledChannel_2, LOW);
    ledcWrite(ledChannel_1, -output);
  }
  

  
  
  while (millis() < (time_now + dt)) {

    
  }
  
  dp = ((encoder.getCount() / (75.81 * 6) * 2 * M_PI) -p);
  Serial.print(" ");
  Serial.println(dt*dp);
  Serial.println(output);
  
}
