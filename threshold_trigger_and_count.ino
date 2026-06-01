#define THRESHHOLD 0.1
#define ANALOGINPUT A3
#define CALIBRATE_SAMPLE_COUNT 50

float analog = 0;
float rawTh = ( 1024 / 5 ) * THRESHHOLD;
int count = 0;
int ERROR = 0;

void setup() {
  Serial.begin(9600);

  /*
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

//multiply by 2 for best result
  rawTh = max * 2;*/
  Serial.print("Threshold: "); Serial.print( (rawTh / 1024) * 5 ); Serial.println("V");
  
}

void loop() {
  if (ERROR == 1) return;

  int n = 0;
  analog = analogRead(ANALOGINPUT);  // read the input pin
  Serial.print(count); Serial.print(", "); Serial.println(analog); n++;
  if (n > 1024) return;

  if (analog > rawTh) { 
    count++;
    //Serial.println(count);
  }
  //delay(10);
  while ( analog > rawTh ) {
    analog = analogRead(ANALOGINPUT);
    Serial.print(count); Serial.print(", "); Serial.println(analog); n++;
    if (n > 1024) return;
  }
  //Serial.println(count);
  return;
}
