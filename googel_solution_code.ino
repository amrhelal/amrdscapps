#include <LiquidCrystal.h>
//==//
#define rs 10
#define en 9
#define d4 2
#define d5 3
#define d6 4
#define d7 5
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
#define laser 7
#define ldr A0
int value;
int standard = 400;
int s;
int counter;
bool writeOnce = false;
bool exitFlag = false;
//======================================================//
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();  
  pinMode (laser, OUTPUT);
  pinMode (ldr, INPUT);
  digitalWrite (laser, HIGH);
}

void loop()
{
  value = analogRead (ldr);
  if (value >= standard)
  {
    if (writeOnce == false)
    {
      writeOnce = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" !! Stay Home !! ");
    }
  }
  else
  {
    writeOnce = false;
    lcd_countdown(20);
  }







  
  
}

int lcd_countdown(int s)
{
  exitFlag = false;
  for (int i = s; i >= 0; i--)
  {
    if (exitFlag == true)
    {
      break;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(i);
    delay(1000);
    value = analogRead (ldr);
    Serial.print(value);
    if (value >= standard)
    {
      for (int i = 5; i >= 0; i--)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(i);
        delay(1000);
        value = analogRead (ldr);
        if (value < standard)
        {
          break;
        }
        if (i == 0)
        {
          exitFlag = true;
        }
      }
    }
  }//*****//
}
