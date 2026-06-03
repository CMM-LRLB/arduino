#define THRESHOLD 0.12
#define ANALOGINPUT A3
#define CALIBRATE_SAMPLE_COUNT 20
#define DATAPOINT_COUNT 1024

const int doFindTh = 1;
float rawTh = ( THRESHOLD / 5 ) * 1024;
int ERROR = 0;

int findThreshold(float *rawTh) {
  
  Serial.println("calibrating...");

  int sum = 0;
  float read = 0, max = 0, avg = 0;

  //determine average, maximum
  for (int i = 0; i < CALIBRATE_SAMPLE_COUNT; i++) {
    read = analogRead(ANALOGINPUT);
    sum += read;
    if (read > max) max = read;
    delay(100);
  }
  avg = sum / CALIBRATE_SAMPLE_COUNT;

  Serial.print("MAX:"); Serial.println(max);
  Serial.print("AVG:"); Serial.println(avg);
  
  //somewhat arbitrary way to determine threshold accuracy
  *rawTh = max * 1.5;
  if ( avg * 1.5 < max) {
    Serial.println("calibration error, max sample deviates too much from average to function as accurate threshold");
    return 1;
  } else return 0;
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  //determine threshold 
  if (doFindTh == 1) ERROR = findThreshold(&rawTh);

  Serial.print("Threshold: "); Serial.println( rawTh ); //Serial.println("V");
}




int n = 0;
float analog = 0;
//unsigned long startTime = micros(), endTime;
void loop() {
  if (ERROR) while(1);

  do {
    analog = analogRead(ANALOGINPUT);
    Serial.println(); Serial.print(micros()); Serial.print(","); Serial.print(analog); Serial.print(",");
    n++; if (n > DATAPOINT_COUNT) while(1);
  } while (analog < rawTh);
  Serial.print("1");
  do {
    analog = analogRead(ANALOGINPUT);
    Serial.println(); Serial.print(micros()); Serial.print(","); Serial.print(analog); Serial.print(",");
    n++; if (n > DATAPOINT_COUNT) while(1);
  } while (analog > rawTh);

/*
  if (ERROR || n > DATAPOINT_COUNT) {
    Serial.println("stopping...");
    while(1);
  }*/
}