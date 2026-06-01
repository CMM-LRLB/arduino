#define THRESHOLD 0.1
#define ANALOGINPUT A3
#define CALIBRATE_SAMPLE_COUNT 50
#define DATAPOINT_COUNT 1024

const int doFindTh = 0;
float rawTh = ( 1024 / 5 ) * THRESHOLD;
int ERROR = 0;

void stop() {
  while(1);
}

int findThreshold(int *rawTh) {
  
  Serial.println("calibrating...");
  float sum = 0, read = 0, max = 0, avg = 0;

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
  *rawTh = max;
  if ( avg * 2 < max) {
    Serial.println("calibration error, max sample deviates too much from average to function as accurate threshold");
    return 1;
  } else return 0;
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  //determine threshold 
  if (doFindTh == 1) ERROR = findThreshold;

  Serial.print("Threshold: "); Serial.print( (rawTh / 1024) * 5 ); Serial.println("V");
}




int flag = 0, n = 0;
float analog = 0;

void loop() {
  if (ERROR) stop;

  analog = analogRead(ANALOGINPUT);  // read the input pin
  if (flag == 0 && analog > rawTh) { 
    flag = 1;
    Serial.print("1, "); 
  } else Serial.print("0, ");
  Serial.println(analog);

  if (analog < rawTh) flag = 0;

  n++;
  if (n > DATAPOINT_COUNT) stop;
}
