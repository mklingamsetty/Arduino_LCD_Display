
#define LED_Line  13

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

class MyClock
{
  private:
  unsigned int seconds, minutes, hours, days, years;

  public:
  MyClock(unsigned int s, unsigned int m, unsigned int h, unsigned int d, unsigned int y)
  {
    seconds = s;
    minutes = m;
    hours = h;
    days = d;
    years = y;
  }

  void increment_seconds(void)
  {
    //increment seconds
    seconds++;

    //if seconds is greater than a minute
    if(seconds >= 60)
    {
      //make seconds = 0            
      seconds = 0;
      minutes++;
      if(minutes >= 60)
      {
        minutes = 0;
        hours++;
        if(hours >= 24)
        {
          hours = 0;
          days++;
          if(days >= 365)
          {
            days = 0;
            years++;
          }
        }
      }
    } 
  }

  unsigned long getTime(void)
  {
    unsigned long temp = 0;
    temp = days;
    temp = temp << 8;
    temp |= hours;
    temp = temp << 8;
    temp |= minutes;
    temp = temp << 8;
    temp |= seconds;

    return temp;
  }
};//End of clock class

unsigned long time1 = 0;
unsigned long time2 = 0;

MyClock myClock(0, 0, 0, 0, 0);


void setup() {
  // put your setup code here, to run once:++
  Serial.begin(9600); 
  
  lcd.begin(16, 2);
  lcd.print("HI");


  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);  
   
}

void loop() 
{
  String message = " ";
  unsigned long currentTime = 0;

  //Get current timestamp
  time2 = micros();

  // if time difference is greater than 1s( 1s = 1000000 * 1 ms)
  if((time2 - time1) >= 1000000)
  {
    //save timestamp        
    time1 = time2; 

    //increment seconds
    myClock.increment_seconds();

    //get current time
    currentTime = myClock.getTime();

    //compose a time message
    message = "TIME: ";
    message += currentTime >> 24;
    message += ":";
    message += ((currentTime >> 16) & 0xFF);    
    message += ":";
    message += ((currentTime >> 8) & 0xFF);
    message += ":";
    message += ((currentTime >> 0) & 0xFF);

    //Display on serial port
    Serial.print(01);

    if(currentTime%2 == 0)
    {
     //lcd.print("First line");
       lcd.setCursor(0,1);
  lcd.print("1");
     digitalWrite(13, HIGH);
    }
    else
    {
     //lcd.print("Second line");
       lcd.setCursor(0,1);
  lcd.print("2");
     digitalWrite(13, LOW);
    }
   
  }
  
}
