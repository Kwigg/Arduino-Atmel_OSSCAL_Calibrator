/*
*	OSSCAL calibrator. To be used with an arduino running the AutoCalibrate sketch.
*	Generates feedback PWMS so the arduino can calibrate the device's RC osscilator calibration value.
*
*/

byte osccal_val = 0; //OSCCAL inicial start
byte remote_dec = 3; //remote arduino tells to decrement
byte remote_inc = 4; //remote arduino tells to increment
int outPin = 6;
void setup()  
{
  pinMode(outPin, OUTPUT);
  pinMode(remote_inc, INPUT);
  pinMode(remote_dec, INPUT);
} 

void loop()  
{
  OSCCAL = osccal_val;
  analogWrite(outPin, 100); //Send PWM out signal for frequency checking
  
  //Wait until we get an input
  while(digitalRead(remote_inc) == LOW && digitalRead(remote_dec) == LOW);
  
  if(digitalRead(remote_inc) == HIGH)
  {
    osccal_val = osccal_val + 1;
    //Wait until signal drops LOW again
    while(digitalRead(remote_inc) == HIGH);
  }
  
  if(digitalRead(remote_dec) == HIGH)
  {
    osccal_val = osccal_val -1;
    //Wait until signal drops LOW again
    while(digitalRead(remote_dec) == HIGH);
  }
}
