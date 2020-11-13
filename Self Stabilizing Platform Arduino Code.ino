#include <SoftwareSerial.h>

#include <Servo.h>


#define START_CMD_CHAR '>'
#define END_CMD_CHAR '\n'
#define DIV_CMD_CHAR ','

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data

// Create servo objects
Servo XServo;
Servo YServo;

// Center servos
int YVal = 90; 
int XVal =90; 

// sensoduino stuff
//String inText;
float value0, value1, value2;

void setup() {

  // Attach servo objects to Arduino pins
  XServo.attach(11); 
  YServo.attach(10);

  Serial.begin(9600); // The default speed of the HC-05  Bluetooth serial modules
 
  Serial.flush();
}

void loop()
{
  Serial.flush();
  int inCommand = 0;
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag
  getChar = Serial.read();
  if (getChar != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming pin# and value 
  sensorType = Serial.parseInt(); // read sensor typr
  logCount = Serial.parseInt();  // read total logged sensor readings
  value0 = Serial.parseFloat();  // 1st sensor value
  value1 = Serial.parseFloat();  // 2rd sensor value if exists
  value2 = Serial.parseFloat();  // 3rd sensor value if exists
  
  XServo.write(90+value1);
  YServo.write(90-value2);

  // send sensoduino readings to serial monitor/terminal
  if (DEBUG) {
    Serial.print("Sensor type: ");
    Serial.println(sensorType);
    Serial.print("Sensor log#: ");
    Serial.println(logCount);
    Serial.print("Val[0]: ");
    Serial.println(value0);
    Serial.print("Val[1]: ");
    Serial.println(value1);
    Serial.print("Val[2]: ");
    Serial.println(value2);
    Serial.println("-----------------------");
    delay(10);
  }
}
