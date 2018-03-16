int left_m = 14; // Digital pins controlling motor 1 - 0b00001110
int right_m = 104; // Digital pins controlling motor 2 - 0b01101000
int motorSpeed = 255;

char input; // string which stores incoming message from app

void setup()
{
  Serial.begin(9600); //set baud rate
  DDRB |= left_m; // setup pins attatched to motor 1 as OUTPUT - LEFT
  DDRD |= right_m; // setup pins attatched to motor 2 as OUTPUT
  pinMode(6, OUTPUT);pinMode(5, OUTPUT);pinMode(3, OUTPUT);
}

void loop()
{
   if(Serial.available() > 0){
    input = Serial.read();
    motorStop(); // reset direction
    switch (input){
      case 'F':
        forward();
        break;
      case 'R':
        right();
        break;
      case 'L':
        left();
        break;
      case 'B':
        backwards();
        break;
      case 'S':
        motorStop();
        break;
    }
  }
}

void forward()
{
  Serial.println("F");  

  leftMotor(HIGH, LOW, motorSpeed);

  rightMotor(HIGH, LOW, motorSpeed);
}

void right()
{
  Serial.println("R");  

  leftMotor(HIGH, LOW, motorSpeed);

  rightMotor(LOW, LOW, 0);
}

void left()
{
  Serial.println("L");  

  leftMotor(LOW, LOW, 0);
  
  rightMotor(HIGH, LOW, motorSpeed);
}

void backwards()
{
  Serial.println("B");  

  leftMotor(LOW, HIGH, motorSpeed);

  rightMotor(LOW, HIGH, motorSpeed);
}

void motorStop()
{
  Serial.println("S");  
  // turn off outputs
  PORTB &= ~left_m; 
  PORTD &= ~right_m; 
}

void leftMotor(int positive, int negative, int motorspeed)
{
  digitalWrite(11, positive);
  digitalWrite(10, negative);
  analogWrite(9, motorspeed);
}

void rightMotor(int positive, int negative, int motorspeed)
{
  digitalWrite(6, positive);
  digitalWrite(5, negative);
  analogWrite(3, motorspeed);
}

