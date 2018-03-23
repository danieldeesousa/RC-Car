#define left_led 13
#define right_led 7

int left_m = 14; // Digital pins controlling motor 1 - 0b00001110
int right_m = 104; // Digital pins controlling motor 2 - 0b01101000
int motorSpeed = 255;

char input; // string which stores incoming message from app

void setup()
{
  Serial.begin(9600); //set baud rate
  DDRB |= left_m; // setup pins attatched to motor 1 as OUTPUT - LEFT
  DDRD |= right_m; // setup pins attatched to motor 2 as OUTPUT - RIGHT
  pinMode(left_led, OUTPUT); pinMode(right_led, OUTPUT); // enable leds as OUTPUT
}

void loop()
{
   // interrupt processor to check if data is available from Bluetooth module
   if(Serial.available() > 0){
    input = Serial.read(); // interrupt processor to read available data
    switch (input){
      case 'F':
        motorStop(); // reset direction
        forward();
        break;
      case 'R':
        motorStop(); // reset direction
        right();
        break;
      case 'L':
        motorStop(); // reset direction
        left();
        break;
      case 'B':
        motorStop(); // reset direction
        backwards();
        break;
      case 'S':
        motorStop();
        break;
      case 'H':
        honk();
        break;
    }
  }
}

void forward()
{
  Serial.println("F");  

  leftMotor(HIGH, LOW, motorSpeed);

  rightMotor(HIGH, LOW, motorSpeed);

  ledWrite(HIGH, HIGH);
}

void right()
{
  Serial.println("R");  

  leftMotor(HIGH, LOW, motorSpeed);

  rightMotor(LOW, LOW, 0);

  ledWrite(HIGH, LOW);
}

void left()
{
  Serial.println("L");  

  leftMotor(LOW, LOW, 0);
  
  rightMotor(HIGH, LOW, motorSpeed);

  ledWrite(LOW, HIGH);
}

void backwards()
{
  Serial.println("B");  

  leftMotor(LOW, HIGH, motorSpeed);

  rightMotor(LOW, HIGH, motorSpeed);

  ledWrite(LOW, LOW);
}

void motorStop()
{
  Serial.println("S");  
  // turn off outputs
  PORTB &= ~left_m; 
  PORTD &= ~right_m; 

  //ledWrite(LOW, LOW);
}

void honk()
{
   tone(8, 460, 100);
}

void leftMotor(int positive, int negative, int motorspeed)
{
  digitalWrite(11, positive);
  digitalWrite(10, negative);
  analogWrite(9, motorspeed-5);
}

void rightMotor(int positive, int negative, int motorspeed)
{
  digitalWrite(6, positive);
  digitalWrite(5, negative);
  analogWrite(3, motorspeed);
}

void ledWrite(int left, int right)
{
 digitalWrite(left_led, left); 
 digitalWrite(right_led, right); 
}
