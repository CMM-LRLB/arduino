#define THRESHHOLD 1.00
#define ANALOGINPUT A3
#define CALIBRATE_SAMPLE_COUNT 100

float analog = 0;
float rawTh = ( 1024 / 5 ) * THRESHHOLD;
int count = 0;
int ERROR = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("calibrating...");

  //float sample[CALIBRATE_SAMPLE_COUNT];
  float avg = 0, max = 0, sum = 0;

  for (int i = 0; i < CALIBRATE_SAMPLE_COUNT; i++) {
    analog = analogRead(ANALOGINPUT);
    //sample[i] = analog;
    sum += analog;
    if (analog > max) max = analog;
    delay(100);
  }

  avg = sum / CALIBRATE_SAMPLE_COUNT;

  //determine if max is reasonable
  Serial.print("MAX:"); Serial.println(max);
  Serial.print("AVG:"); Serial.println(avg);
  
  if ( (max - avg) > avg) {
    ERROR = 1;
    Serial.println("calibration error");
    return;
  }

  rawTh = max;
  Serial.print("Threshold: "); Serial.print( (rawTh / 1024) * 5 ); Serial.println("V");

}

void loop() {
  if (ERROR == 1) return;
  analog = analogRead(ANALOGINPUT);  // read the input pin

  if (analog > rawTh) count++;
  while ( analog > rawTh ) analog = analogRead(ANALOGINPUT);

  Serial.println(count);
}
