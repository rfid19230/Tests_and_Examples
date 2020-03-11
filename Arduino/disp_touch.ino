// Подключение библиотек
#include <UTFT.h>
#include <URTouch.h>

// Определение различных констант
#define X_MIN 0
#define X_MAX 319

#define Y_MIN 0
#define Y_MAX 239

#define TPX_MIN 0
#define TPX_MAX 4000
#define TPXD_T 4000
#define TPXD_B 4500

#define TPY_MIN 0
#define TPY_MAX 4000
#define TPYD_L 3800
#define TPYD_R 4000

#define BC_R 0
#define BC_G 0
#define BC_B 0

#define FC_R 255
#define FC_G 255
#define FC_B 0

// Создание объектов библиотечного класса
UTFT disp(TFT01_24SP,  9, 8, 12, 11, 10);
URTouch ts( 6, 5, 4, 3, 2);

int x, y;
int16_t tpx, tpy;

extern uint8_t BigFont[];  

// Инициализация дисплея, отображение тестируемого экрана
void setup()
{
  Serial.begin(9600);
  
  disp.InitLCD(LANDSCAPE);
  disp.setFont(BigFont);
  disp.setBackColor(BC_R, BC_G, BC_B);
  disp.setColor(BC_R, BC_G, BC_B);
  disp.fillRect(X_MIN, Y_MIN, X_MAX, Y_MAX);
  
  ts.InitTouch(LANDSCAPE);
  ts.setPrecision(PREC_HI); 

  printTRQ(FC_R, FC_G, FC_B);
  //printCBQ(FC_R, FC_G, FC_B, 0);
  //printISM(FC_R, FC_G, FC_B);
  //printNCE(FC_R, FC_G, FC_B);
  //printSCE(FC_R, FC_G, FC_B);
  //printSSM(FC_R, FC_G, FC_B);
}

// Тестирование определенного экрана
void loop()
{
  if (ts.dataAvailable())
  {
    ts.read();
    tpx = ts.TP_X;
    tpy = ts.TP_Y;
      
    x = tpyToX(tpy);
    y = tpxToY(tpx);

    int b = touchTRQ(x, y);
    // int b = touchCBQ(x, y);
    // int b = touchISM(x, y);
    // int b = touchNCE(x, y);
    // int b = touchSCE(x, y);
    // int b = touchSSM(x, y);
    
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(b);

    delay(500);
  }
}

// Функции нахождения координат касания
int tpyToX(int16_t tpy)
{
  if (tpy < TPY_MIN)
    tpy = TPY_MIN;

  if (tpy > TPY_MAX)
    tpy = TPY_MAX;

  int tpyd;
  if (int(tpy) <= int(TPY_MAX / 2))
    tpyd = TPYD_R;
  else
    tpyd = TPYD_L;
  
  return int( double(X_MAX) * ( 1.0 - double(tpy) / double(tpyd) ) );
}

int tpxToY(int16_t tpx)
{
  if (tpx < TPX_MIN)
    tpx = TPX_MIN;

  if (tpx > TPX_MAX)
    tpx = TPX_MAX;

  int tpxd;
  if (int(tpx) <= int(TPX_MAX / 2))
    tpxd = TPXD_B;
  else
    tpxd = TPXD_T;
  
  return int( double(Y_MAX) * ( 1.0 - double(tpx) / double(tpxd) ) );
}

// Функции отображения экранов и считывания касаний
void printWFR(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("WAITING", 103, 24);
  disp.print("FOR", 135, 84);
  disp.print("RFID", 127, 144);
}

void printAG(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("ACCESS GRANTED", 47, 204);
}

void printAD(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("ACCESS DENIED", 55, 204);
}

void printTRQ(int r, int g, int b)
{
  disp.setColor(r, g, b);
  
  disp.print("CHOOSE ACTION", 55, 7);
  
  disp.drawRoundRect(50, 40, 270, 90);
  disp.print("TAKE", 127, 57);

  disp.drawRoundRect(50, 110, 270, 160);
  disp.print("RETURN", 111, 127);

  disp.drawRoundRect(50, 180, 270, 230);
  disp.print("QUIT", 127, 197);
}

int touchTRQ(int x, int y)
{
  int res = 0;

  if (x >= 50 && x <= 270 && y >= 40 && y <= 90)
    res = 1; // TAKE

  if (x >= 50 && x <= 270 && y >= 110 && y <= 160)
    res = 2; // RETURN

  if (x >= 50 && x <= 270 && y >= 180 && y <= 230)
    res = 3; // QUIT

  return res;
}

void printCBQ(int r, int g, int b, int superuser)
{
  disp.setColor(r, g, b);

  disp.print("CHOOSE CELL", 71, 7);

  disp.drawRoundRect(10, 40, 70, 100);
  disp.print("1", 32, 62);

  disp.drawRoundRect(90, 40, 150, 100);
  disp.print("2", 112, 62);

  disp.drawRoundRect(170, 40, 230, 100);
  disp.print("3", 192, 62);

  disp.drawRoundRect(250, 40, 310, 100);
  disp.print("4", 272, 62);

  disp.drawRoundRect(10, 120, 70, 180);
  disp.print("5", 32, 142);

  disp.drawRoundRect(90, 120, 150, 180);
  disp.print("6", 112, 142);

  disp.drawRoundRect(170, 120, 230, 180);
  disp.print("7", 192, 142);

  if (superuser >= 0)
  {
    disp.drawRoundRect(250, 120, 310, 180);
    disp.print("8", 272, 142);
  }

  disp.drawRoundRect(40, 200, 120, 230);
  disp.print("BACK", 48, 207);
  
  disp.drawRoundRect(200, 200, 280, 230);
  disp.print("QUIT", 208, 207);
}

int touchCBQ(int x, int y)
{
  int res = 0;

  if (x >= 10 && x <= 70 && y >= 40 && y <= 100)
    res = 1; // cell 1

  if (x >= 90 && x <= 150 && y >= 40 && y <= 100)
    res = 2; // cell 2

  if (x >= 170 && x <= 230 && y >= 40 && y <= 100)
    res = 3; // cell 3

  if (x >= 250 && x <= 310 && y >= 40 && y <= 100)
    res = 4; // cell 4

  if (x >= 10 && x <= 70 && y >= 120 && y <= 180)
    res = 5; // cell 5

  if (x >= 90 && x <= 150 && y >= 120 && y <= 180)
    res = 6; // cell 6

  if (x >= 170 && x <= 230 && y >= 120 && y <= 180)
    res = 7; // cell 7

  if (x >= 250 && x <= 310 && y >= 120 && y <= 180)
    res = 8; // cell 8

  if (x >= 40 && x <= 120 && y >= 200 && y <= 230)
    res = 9; // BACK

  if (x >= 200 && x <= 280 && y >= 200 && y <= 230)
    res = 10; // QUIT

  return res;
} 

void printIC(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("INITIALIZING", 63, 52);
  disp.print("COMPONENTS", 79, 172);
}

void printISM(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("IN", 143, 22);
  disp.print("SUPERUSER", 87, 82);
  disp.print("MODE", 127, 142);

  disp.drawRoundRect(100, 190, 220, 230);
  disp.print("QUIT", 127, 202);
}

int touchISM(int x, int y)
{
  int res = 0;

  if (x >= 100 && x <= 220 && y >= 190 && y <= 230)
    res = 1; // QUIT

  return res;
}

void printNCE(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("NET", 135, 22);
  disp.print("CONNECTION", 79, 82);
  disp.print("ERROR", 119, 142);

  disp.drawRoundRect(10, 190, 310, 230);
  disp.print("LOGIN AS SUPERUSER", 15, 202);
}

int touchNCE(int x, int y)
{
  int res = 0;

  if (x >= 10 && x <= 310 && y >= 190 && y <= 230)
    res = 1; // LOGIN AS SUPERUSER

  return res;
}

void printSCE(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("SERVER", 111, 22);
  disp.print("CONNECTION", 79, 82);
  disp.print("ERROR", 119, 142);

  disp.drawRoundRect(10, 190, 310, 230);
  disp.print("LOGIN AS SUPERUSER", 15, 202);
}

int touchSCE(int x, int y)
{
  int res = 0;

  if (x >= 10 && x <= 310 && y >= 190 && y <= 230)
    res = 1; // LOGIN AS SUPERUSER

  return res;
}

void printSSM(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("SWITCH TO", 87, 22);
  disp.print("SUPERUSER", 87, 82);
  disp.print("MODE?", 119, 142);

  disp.drawRoundRect(50, 190, 150, 230);
  disp.print("YES", 76, 202);

  disp.drawRoundRect(170, 190, 270, 230);
  disp.print("NO", 204, 202);
}

int touchSSM(int x, int y)
{
  int res = 0;

  if (x >= 50 && x <= 150 && y >= 190 && y <= 230)
    res = 1; // YES

  if (x >= 170 && x <= 270 && y >= 190 && y <= 230)
    res = 2; // NO

  return res;
}

void printTRC(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("OPEN SELECTED CELL", 7, 15);
  disp.print("TAKE OR RETURN VALUE", 0, 60);
  disp.print("CLOSE CELL", 79, 105);
  disp.print("AND COMFIRM ACTION", 15, 150);

  disp.drawRoundRect(10, 190, 130, 230);
  disp.print("CONFIRM", 14, 202);

  disp.drawRoundRect(150, 190, 220, 230);
  disp.print("BACK", 153, 202);

  disp.drawRoundRect(240, 190, 310, 230);
  disp.print("QUIT", 243, 202);
}

int touchTRC(int x, int y)
{
  int res = 0;

  if (x >= 10 && x <= 130 && y >= 190 && y <= 230)
    res = 1; // CONFIRM

  if (x >= 150 && x <= 220 && y >= 190 && y <= 230)
    res = 2; // BACK

  if (x >= 240 && x <= 310 && y >= 190 && y <= 230)
    res = 3; // QUIT

  return res;
}
