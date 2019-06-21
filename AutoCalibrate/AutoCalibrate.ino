/*
   * Autocalibrate OSSCAL
   * 
   * Connect an ATMEL chip to the corresponding remote_dec/inc pins,
   * Connect its pwm out return to A0
   * Connect the arduino feedback to A1
   * 
   * and this software will automatically (eventually) determine the
   * correct RC osscilator value for the attached chip.
   * 
   * Only run on a device with an external clock!
   */


byte osccal_val = 0; //The OSSCAL register is a single byte in size

int arduinoBaseFrequency = 16000000;
int atTinyBaseFrequency = 8000000;
int multiplier = arduinoBaseFrequency/atTinyBaseFrequency; //used to fix the PWM

//Match these names for connection to the slave chip
int remote_dec = 6;
int remote_inc = 7;


int baseHighTime;
int baseLowTime;
float arduinoFreq;

int chipHighTime;
int chipLowTime;
float chipFreq;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(remote_inc, OUTPUT); //remote plus
  pinMode(remote_dec, OUTPUT); //remove less

  pinMode(pwm_pin, OUTPUT);
}

void loop() 
{
  
  analogWrite(pwm_pin, 100); //Arduino feedback for comparison checking

  //First calculate frequencies of the feedback, and the slave chip
  baseHighTime = pulseIn(A1, HIGH);
  baseLowTime = pulseIn(A1, LOW);

  chipHighTime = pulseIn(A0, HIGH);
  chipLowTime = pulseIn(A0, LOW);
  arduinoFreq = 1000000/(baseHighTime+baseLowTime);
  chipFreq = 1000000/(chipHighTime+chipLowTime);
  Serial.print("BaseFrequency: ");
  Serial.println(arduinoFreq);
  Serial.print("ChipFrequency: ");
  Serial.println(chipFreq);

  //Now calibrate the OSSCAL as required
  if(arduioFreq > (chipFreq * multiplier))
  {
    digitalWrite(remote_inc, HIGH);
    delay(500);
    digitalWrite(remote_inc, LOW);
    osccal_val = osccal_val + 1;
  } else
  {
    digitalWrite(remote_dec, HIGH);
    delay(500);
    digitalWrite(remote_dec, LOW);
    osccal_val = osccal_val - 1;
  }
  
  //Print out new OSSCAL value
  Serial.print("Osscal: ");
  Serial.println(osccal_val);
  delay(500);
 
}
