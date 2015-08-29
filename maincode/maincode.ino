#include <Password.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(6,7,8,9,10,11,12);
Password password = Password( "4321" );

const byte ROWS = 4; 
const byte COLS = 4;
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0',' ','D'}
};
// Connect keypad ROW0S to these Arduino pins.
byte rowPins[ROWS] = {22,24,26,28};
byte colPins[COLS] = {30, 32, 34,36}; 

const int buttonPin = 5;
int motor_forward = 4;
int motor_reverse = 3;
int pin = 2;


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(motor_forward, OUTPUT);
  pinMode(motor_reverse, OUTPUT);
  pinMode(pin,OUTPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);
  
    lcd.print("Password Based");
    lcd.setCursor(0,1);
    lcd.print(" Door Locking");
    delay(2500);
    lcd.clear();
    lcd.print("Enter Pasword...");
    delay(200);
    lcd.clear();
    
  keypad.addEventListener(keypadEvent); 
  keypad.setDebounceTime(200);
}

void loop()
{
  keypad.getKey();
}


void keypadEvent(KeypadEvent eKey)
{
    switch (keypad.getState())
    {
      case PRESSED:
      lcd.print(eKey);
      switch (eKey)
      {
        case ' ': 
                guessPassword();
                break;
        default:
                 password.append(eKey);
      }
    }
 
}
void guessPassword()
{
  if (password.evaluate())
  {
    
    lcd.setCursor(0,1);
    lcd.print(" VALID PASSWORD "); 
    
    password.reset(); 
    delay(1500);
    
    lcd.clear();
    lcd.print(" Thank You ^_^ ");
    lcd.setCursor(0,1);
    lcd.print("  Door Open!!");
    delay(5000);
    
    motor_rotate();
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("INVALID PASSWORD ");
    
     buzzer();
   
    password.reset(); 
  
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Try Again  ");
    lcd.setCursor(0,1);
    lcd.print("Enter Password");
    delay(2000);
    lcd.clear();
  }
}

int motor_rotate()
{
  digitalWrite(motor_forward,1); 
  digitalWrite(motor_reverse,0); 
  delay(7000);     

  digitalWrite(motor_forward,0); 
  digitalWrite(motor_reverse,1); 
  delay(7000); 
  
  digitalWrite(motor_forward,1); 
  digitalWrite(motor_reverse,0);
  delay(3000);
  
  digitalWrite(motor_forward,0); 
  digitalWrite(motor_reverse,0);
}

void buzzer()
{
   digitalWrite(pin, HIGH);   
  delay(3000);              
  digitalWrite(pin, LOW);    
  delay(1000);   
  
  digitalWrite(pin, HIGH);   
  delay(3000);               
  digitalWrite(pin, LOW);    
  delay(1000); 
}
