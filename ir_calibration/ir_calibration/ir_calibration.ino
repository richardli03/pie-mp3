int sensorPin = A0;    // select the input pin for the IR
int voltages[5];
int curr_voltage; 
bool isLine; 
int threshold_voltage = 700; 

void setup() {
  // declare the sensorPin as an INPUT:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  for (int n = 0; n < 5; n++) {
      voltages[n] = analogRead(sensorPin);
  }
  curr_voltage = average(voltages,5);
  if (curr_voltage > threshold_voltage) {
    isLine = true;
  }
  else {
    isLine = false;
  }
  Serial.println(isLine);
  Serial.println(curr_voltage);
  delay(500);
}

float average (int * array, int len)  // assuming array is int.
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ;  // average will be fractional, so float may be appropriate.
}
