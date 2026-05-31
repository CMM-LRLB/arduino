#define THRESHHOLD 1.00
#define ANALOGINPUT A3

int analog = 0;
float rawTh = ( 1024 / 5 ) * THRESHHOLD;
int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  analog = analogRead(ANALOGINPUT);  // read the input pin

  if (analog > rawTh) count++;
  while ( analog > rawTh ) analog = analogRead(ANALOGINPUT);

  Serial.println(count);
}