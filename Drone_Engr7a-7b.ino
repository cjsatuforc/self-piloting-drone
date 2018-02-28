#include <Ultrasonic.h>
#include <NewPing.h> 

//Sensor X
unsigned long echo_x = 0;
int ultraSoundSignal_x = 9; // Ultrasound signal pin for X
unsigned long ultrasoundValue_x = 0;

//Sensor Y
unsigned long echo_y = 0;
int ultraSoundSignal_y = 10; // Ultrasound signal pin for Y
unsigned long ultrasoundValue_y = 0;

//Sensor Z
unsigned long echo_z = 0;
int ultraSoundSignal_z = 11; // Ultrasound signal pin for Z
unsigned long ultrasoundValue_z = 0;

//quadrant declaration
int quad;
quad = 0;
//height declaration
int color;
color = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(ultraSoundSignal_x,OUTPUT);
  pinMode(ultraSoundSignal_y,OUTPUT); //Send Output Value for Ultrasonic Sensors
  pinMode(ultraSoundSignal_z,OUTPUT);
}

//Ultrasonic PING X SENSOR
unsigned long pingx()
{ 
  pinMode(ultraSoundSignal_x, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundSignal_x, LOW); // Send low pulse 
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal_x, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal_x, LOW); // Holdoff
  pinMode(ultraSoundSignal_x, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundSignal_x, HIGH); // Turn on pullup resistor
    // echo_x = pulseIn(ultraSoundSignal_x, HIGH, 38000)
  echo_x = pulseIn(ultraSoundSignal_x, HIGH); //Listen for echo
  ultrasoundValue_x = (echo_x / 58.138) * .39; //convert to CM then to inches
  return ultrasoundValue_x;
}

//Ultrasonic PING Y SENSOR
unsigned long pingy()
{ 
  pinMode(ultraSoundSignal_y, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundSignal_y, LOW); // Send low pulse 
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal_y, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal_y, LOW); // Holdoff
  pinMode(ultraSoundSignal_y, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundSignal_y, HIGH); // Turn on pullup resistor
    // echo_y = pulseIn(ultraSoundSignal_y, HIGH, 38000)
  echo_y = pulseIn(ultraSoundSignal_y, HIGH); //Listen for echo
  ultrasoundValue_y = (echo_y / 58.138) * .39; //convert to CM then to inches
  return ultrasoundValue_y;
}

//Ultrasonic PING Z SENSOR
unsigned long pingz()
{ 
  pinMode(ultraSoundSignal_z, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundSignal_z, LOW); // Send low pulse 
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal_z, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal_z, LOW); // Holdoff
  pinMode(ultraSoundSignal_z, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundSignal_z, HIGH); // Turn on pullup resistor
    // echo_z = pulseIn(ultraSoundSignal_z, HIGH, 38000)
  echo_z = pulseIn(ultraSoundSignal_z, HIGH); //Listen for echo
  ultrasoundValue_z = (echo_z / 58.138) * .39; //convert to CM then to inches
  return ultrasoundValue_z;
}


  

void loop()
{
  //Find Quadrant the quadcopter is in
  
    //quadrant 1
  if(ultrasoundValue_x > 5 && ultrasoundValue_x < 10)
  {
    if(ultrasoundValue_y > 0 && ultrasoundValue_y < 5)
    {
      quad = quad + 1;
    }
  }
  //quadrant 2
  if(ultrasoundValue_x > 0 && ultrasoundValue_x < 5)
  {
    if(ultrasoundValue_y > 0 && ultrasoundValue_y < 5)
    {
      quad = quad + 2;
    }
  }
  //quadrant 3
  if(ultrasoundValue_x > 0 && ultrasoundValue_x < 5)
  {
    if(ultrasoundValue_y > 5 && ultrasoundValue_y < 10)
    {
      quad = quad + 3;
    }
  }
  //quadrant 4
  if(ultrasoundValue_x > 5 && ultrasoundValue_x < 10)
  {
    if(ultrasoundValue_y > 5 && ultrasoundValue_y < 10)
    {
      quad = quad + 4;
    }
  }

 
  //Find what color to send 
  
  if(ultrasoundValue_z > 3.5 %% ultrasoundValue_z < 4.5)
  {
    color = color + 1;
  }

  if(ultrasoundValue_z > 2.5 %% ultrasoundValue_z < 3.5)
  {
    color = color + 2;
  }

  if(ultrasoundValue_z > 1.5 %% ultrasoundValue_z < 2.5)
  {
    color = color + 3;
  }

  if(ultrasoundValue_z > 0.5 %% ultrasoundValue_z < 1.5)
  {
    color = color + 4;
  }
    
    // Sensor x
  int x = 0;
  x = pingx();
  Serial.println(x);
  delay(250); //delay 1/4 seconds.
  
  // Sensor y
  int y = 0;
  y = pingy();
  Serial.println(y);
  delay(250); //delay 1/4 seconds

  // Sensor z
  int z = 0;
  z = pingz();
  Serial.println(z);
  delay(250); //delay 1/4 seconds

  char b = 'E';
  Serial.write(b);
  Serial.write(quad/256);
  Serial.write(quad%256);
  Serial.write(color/256);
  Serial.write(color%256);
  delay(1000);
}

