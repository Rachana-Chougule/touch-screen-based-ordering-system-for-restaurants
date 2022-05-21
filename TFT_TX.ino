#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <RH_ASK.h>
#include <SPI.h> 
RH_ASK driver;
RH_ASK radio(2000, 11, 12);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define YP A1
#define XM A2
#define YM 7
#define XP 6

#define TS_MINX 940
#define TS_MINY 160
#define TS_MAXX 160
#define TS_MAXY 970

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 40
#define PENRADIUS 3

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define NUM_STRINGS 10
int i, j, a, b = 0;
char *arr[NUM_STRINGS];

bool change = 0;
bool touch = 0;
void setup() 
{
  Serial.begin(9600);   
  if (!radio.init())
  {
    Serial.println("Radio module failed to initialize");
  }
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
  tft.reset();
  tft.begin(0x9325);
  tft.setRotation(3);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.fillScreen(WHITE);
  //tft.fillRect(170, 80, 150, 70, GREEN); // Burger
  tft.setCursor(40,90);
  tft.println("Welcome to  Buddies Resto");
  delay(2100);  
  tft.fillScreen(WHITE);

  tft.setCursor(70, 10);
  tft.println("Welcome!!");
  tft.setTextSize(2);
  tft.setCursor(12,60);
  tft.println("Select your table number: ");
  digitalWrite(A5, LOW);
  tft.fillRect(10, 80, 150, 70, CYAN);  // Table 1
  tft.setCursor(12, 110);
  tft.println("Table 1");
  tft.fillRect(170, 80, 150, 70, CYAN); // Table 2
  tft.setCursor(180,110);
  tft.println("Table 2");
  tft.fillRect(10, 160, 150, 70, CYAN);// Table 3
  tft.setCursor(12,185);
  tft.println("Table 3");
  tft.fillRect(170, 160, 150, 70, CYAN); // Table 4
  tft.setCursor(180,185);
  tft.println("Table 4");
}

//TSPoint p = ts.getPoint();


void loop() {

// Loops for displaying table number
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    const char *msg;
    while ((p.x > 0 && p.x < 170) && (p.y > 80 && p.y < 170)) {   // Table 1
    change = 0;
    touch = !touch;
    msg = "Table 1 has ordered             "; 
    touch = 1;
    tft.fillRect(10, 80, 150, 70, GREEN);
    tft.setCursor(12, 110);
    tft.println("Ordered");
    change = 1;
    radio.send((uint8_t*)msg, strlen(msg));    // Wait until the data has been sent
    radio.waitPacketSent();                    // Delay since we dont want to send a trillion packets 
    delay(1000);                               // Also inform the serial port that we are done!
    Serial.println("Data Sent");
    delay(200);
      break;
    }  
    while ((p.x > 170 && p.x < 310) && (p.y > 80 && p.y < 200))   // Table 2
    {
      change = 0;
      touch = !touch;
      msg = "Table 2 has ordered             ";
      touch = 1;
      tft.fillRect(170, 80, 150, 70, GREEN); // Burger
      tft.setCursor(180,110);
      tft.println("Ordered");
      change = 1;
      radio.send((uint8_t*)msg, strlen(msg));       // Wait until the data has been sent
      radio.waitPacketSent();                       // Delay since we dont want to send a trillion packets 
      delay(1000);                                 // Also inform the serial port that we are done!
      Serial.println("Data Sent");
      delay(200);
      break;
    } 
    while ((p.x > 0 && p.x < 170) && (p.y > 200 && p.y < 239))   // Table 3
    {
      change = 0;
      touch = !touch;
      msg = "Table 3 has ordered             ";
      touch = 1;
      tft.fillRect(10, 160, 150, 70, GREEN);// Biryani
      tft.setCursor(12,185);
      tft.println("Ordered");
      change = 1;
      radio.send((uint8_t*)msg, strlen(msg));       // Wait until the data has been sent
      radio.waitPacketSent();                       // Delay since we dont want to send a trillion packets 
      delay(1000);                                  // Also inform the serial port that we are done!
      Serial.println("Data Sent");
      delay(200);
      break;
    }
    while ((p.x > 170 && p.x < 310) && (p.y > 200 && p.y < 239))   // Table 4
    {
      change = 0;
      touch = !touch;
      msg = "Table 4 has ordered             ";
      touch = 1;
      tft.fillRect(170, 160, 150, 70, GREEN); // Momos
      tft.setCursor(180,185);
      tft.println("Ordered");
      change = 1;
      radio.send((uint8_t*)msg, strlen(msg));       // Wait until the data has been sent
      radio.waitPacketSent();                       // Delay since we dont want to send a trillion packets 
      delay(1000);                                  // Also inform the serial port that we are done!
      Serial.println("Data Sent");
      delay(200);
      break;
    }
    if (touch = 1)
    {
      setup2();
    }
    setup();
  }
}

void setup2() 
{
  tft.fillScreen(WHITE);
  tft.fillRect(0, 0, 310, 60, RED); // Confirm
  tft.setCursor(70, 10);
  tft.println("Confirm");
  tft.setTextSize(2);
  tft.setCursor(12,60);
  tft.println("Menu: ");
  digitalWrite(A5, LOW);
  tft.fillRect(10, 80, 150, 70, CYAN);  // Chinese
  tft.setCursor(12, 110);
  tft.println("Chinese: 250");
  tft.fillRect(170, 80, 150, 70, CYAN); // Burger
  tft.setCursor(180,110);
  tft.println("Burger: 70");
  tft.fillRect(10, 160, 150, 70, CYAN);// Biryani
  tft.setCursor(12,185);
  tft.println("Biryani: 200");
  tft.fillRect(170, 160, 150, 70, CYAN); // Momos
  tft.setCursor(180,185);
  tft.println("Momos: 50"); 
  delay(200);
  item();
}

void item () {
  
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  delay(200);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    while ((p.x > 0 && p.x < 170) && (p.y > 130 && p.y < 200))  //Chinese loop
    {
      change = 0;
      touch = !touch;
      char item = "Chinese";
      tft.fillRect(10, 80, 150, 70, GREEN);
      tft.setCursor(12, 110);
      tft.println("Ordered");
      change = 1;
      arr[i] = "Chinese Ordered                 ";   
      i++;
      break;     
    }
    
    while ((p.x > 170 && p.x < 310) && (p.y > 80 && p.y < 200))   //Burger loop
    {
      change = 0;
      touch = !touch;
      tft.fillRect(170, 80, 150, 70, GREEN); // Burger
      tft.setCursor(180,110);
      tft.println("Ordered");
      change = 1;
      arr[i] = "Burger Ordered                  ";   
      i++; 
      break;     
    }
    
    while ((p.x > 0 && p.x < 170) && (p.y > 200 && p.y < 239))   //Biryani loop
    { 
      change = 0;
      touch = !touch;
      tft.fillRect(10, 160, 150, 70, GREEN);// Biryani
      tft.setCursor(12,185);
      tft.println("Ordered");
      change = 1;
      arr[i] = "Biryani Ordered                 ";   
      i++;
      break;      
    }
    
    while ((p.x > 250 && p.x < 310) && (p.y > 200 && p.y < 239))   //Momos loop
    {
      change = 0;
      touch = !touch;
      tft.fillRect(170, 160, 150, 70, GREEN); // Momos
      tft.setCursor(180,185);
      tft.println("Ordered");
      change = 1;
      arr[i] = "Momos Ordered                   ";   
      i++;
      break;       
    } 
    
    while ((p.x > 0 && p.x < 360) && (p.y > 0 && p.y < 130))  //Confirm loop
    {
      change = 0;
      touch = !touch;
      tft.setCursor(70, 10);
      tft.println("Confirmed");
      change = 1;
      
      for(j=0; j<i; j++)
      {
        radio.send((uint8_t*)arr[j], strlen(arr[j]));    // Wait until the data has been sent
        radio.waitPacketSent();                          // Delay since we dont want to send a trillion packets 
        delay(1000);                                     // Also inform the serial port that we are done!
        Serial.println("Data Sent");
        delay(200);  
      }
      tft.fillScreen(WHITE);
      a = 12, b = 90;
      tft.setTextSize(2);
      tft.setCursor(12,40);
      tft.println("Your Order is: ");
      for(j=0; j<i; j++) {
        tft.setCursor(a, b);
        tft.println(arr[j]);
        b+=20;
      }
      delay(9000);
      return 0; 
    }
  }
    item();
  return 0;
}
