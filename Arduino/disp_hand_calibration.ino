// Подключение библиотек
#include <UTFT.h>
#include <URTouch.h>

// Максимальные и минимальные координаты дисплея по осям
#define X_MIN 0
#define X_MAX 319
#define Y_MIN 0
#define Y_MAX 239

// Максимальные и минимальные значения АЦП по осям
#define TPX_MIN 0
#define TPX_MAX 4000
#define TPY_MIN 0
#define TPY_MAX 4000

// Корректировочные калибровочные константы
#define TPXD_T 4000
#define TPXD_B 4500
#define TPYD_L 3800
#define TPYD_R 4000

// Инициализация объектов библиотечных классов
UTFT myGLCD(TFT01_24SP,  9, 8, 12, 11, 10);
URTouch  myTouch( 6, 5, 4, 3, 2);

// Переменные для хранения координат и уровней АЦП
int x, y;
int16_t tpx, tpy;

// Инициализация и настойка дисплея
void setup()
{
  Serial.begin(9600);
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.fillScr(255,255,0);
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI); 
  myGLCD.setColor(0,0,255);

  myGLCD.drawRect(159,0,160,239);
  myGLCD.drawRect(0,119,319,120);

  myGLCD.setColor(255,0,0);
}

void loop()
{
    // При касании
    if (myTouch.dataAvailable())
    {
      // Получение информации о касании
      myTouch.read();

      // Получение уровней АЦП
      tpx = myTouch.TP_X;
      tpy = myTouch.TP_Y;

      // Вывод уровней АЦП
      Serial.print("TPX = ");
      Serial.print(tpx);
      Serial.print(" TPY = ");
      Serial.println(tpy);

      // Преобразование уровней АЦП в координаты
      x = tpy_to_x(tpy);
      y = tpx_to_y(tpx);

      // Вывод координат
      Serial.print("X = ");
      Serial.print(x);
      Serial.print(", Y = ");
      Serial.println(y);

      // Отображение точки касания (использовалось для наглядности)
      myGLCD.fillCircle(x, y, 5);

      // Задержка между считыванием касаний
      delay(100);
    }
}

/*
 * Нужно отметить, что оси АЦП расположены всегда под вертикальную ориентацию дисплея.
 * В проекте же применяется горизонтальная.
 * По этой причине уровень АЦП по оси X преобразуется в координату Y,
 * а уровень АЦП по оси Y преобразуется в координату X.
 */

// Функция преобразования уровня АЦП по оси Y в координату по оси X
int tpy_to_x(int16_t tpy)
{
  if (tpy < TPY_MIN)
  {
    tpy = TPY_MIN;
  }

  if (tpy > TPY_MAX)
  {
    tpy = TPY_MAX;
  }

  int tpyd;
  if (int(tpy) <= int(TPY_MAX / 2))
  {
    tpyd = TPYD_R;
  }
  else
  {
    tpyd = TPYD_L;
  }
  
  return int( double(X_MAX) * ( 1.0 - double(tpy) / double(tpyd) ) );
}

// Функция преобразования уровня АЦП по оси X в координату по оси Y
int tpx_to_y(int16_t tpx)
{
  if (tpx < TPX_MIN)
  {
    tpx = TPX_MIN;
  }

   if (tpx > TPX_MAX)
  {
    tpx = TPX_MAX;
  }

  int tpxd;
  if (int(tpx) <= int(TPX_MAX / 2))
  {
    tpxd = TPXD_B;
  }
  else
  {
    tpxd = TPXD_T;
  }
  
  return int( double(Y_MAX) * ( 1.0 - double(tpx) / double(tpxd) ) );
}
