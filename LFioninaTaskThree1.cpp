//{===========================================================================
//! @file       LFioninaTaskThree.cpp
//!
//! @brief      ИГРА "БРОДИЛКА"
//!
//!               $Date: 2021-06-23 $
//          (C) Фионина Людмила Евгеньевна, г. Самара, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>


const HDC SPRITE_PERSON  = txLoadImage ("Images\\person.bmp");
const int X_PERSON = txGetExtentX (SPRITE_PERSON)/4,
          Y_PERSON = txGetExtentY (SPRITE_PERSON)/4;

const HDC SPRITE_PRESENT  = txLoadImage ("Images\\presents1.bmp");
const int X_PRESENT = txGetExtentX (SPRITE_PRESENT)/6,
          Y_PRESENT = txGetExtentY (SPRITE_PRESENT);

const HDC SPRITE_REBUS  = txLoadImage ("Images\\rebus.bmp");
const int X_REBUS = txGetExtentX (SPRITE_PRESENT),
          Y_REBUS = txGetExtentY (SPRITE_PRESENT)/6;

//---------------------СТРУКТУРЫ-------------------------------------------------
struct Person
    {
    double x, y;

    int course;

    int live;
    int money;

    void Draw (int view);
    void Control ();
    };

struct Present
    {
    int x, y;

    void Draw (int num);
    };

struct Task
    {
    void Draw(char taskText[], int num);
    };

//-------------------   Ф У Н К Ц И И    К Л А С С О В    ---------------------

//- - - - - - - - - - - - рисование героя  - - - - - - - - - - - - - - - - - -
void Person::Draw (int view)
    {
    if (course == 1)  //--- вправо
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 1*Y_PERSON, RGB(0,255,0));
        }
    if (course == 2)  //--- влево
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 2*Y_PERSON, RGB(0,255,0));
        }
    if (course == 0)  //---вверх
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 0*Y_PERSON, RGB(0,255,0));
        }
    if (course == 3)  //--- вниз
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 3*Y_PERSON, RGB(0,255,0));
        }
    }

//- - - - - - - - - - - - управление героем - - - - - - - - - - - - - - - - -
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT) )
        {
        (*this).x += 10;
        (*this).course = 1;
        }
    if (txGetAsyncKeyState (VK_LEFT ) )
        {
        (*this).x -= 10;
        (*this).course = 2;
        }
    if (txGetAsyncKeyState (VK_UP   ) )
        {
        (*this).y -= 10;
        (*this).course = 3;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        (*this).y += 10;
        (*this).course = 0;
        }
    }

//- - - - - - - - - - - - рисование подарка  - - - - - - - - - - - - - - - - - -
void Present::Draw (int num)
    {
    txTransparentBlt (txDC(), x, y, X_PRESENT, Y_PRESENT, SPRITE_PRESENT, num*X_PRESENT, 0*Y_PRESENT, RGB(0,255,0));
    }

//- - - - - - - - - - - - рисование задания  - - - - - - - - - - - - - - - - - -
void Task::Draw (char taskText[], int num)
    {
    txSetColor (RGB(23, 112, 17), 3);
    txSetFillColor (RGB(170, 222, 135));
    txRectangle(350, 250, 950, 550);

    txDrawText (400, 270, 830, 330, taskText,  DT_CENTER);
    txBitBlt (txDC(), 400, 350, X_REBUS, Y_REBUS, SPRITE_REBUS, 0*X_REBUS, num*Y_REBUS);
    }

//--------------------  ПРОТОТИПЫ ФУНКЦИЙ  ---------------------------------------
void GameOver  (Person  hero);
void LiveDraw  (Person* hero);
void MoneyDraw (Person* hero);

void PresentCheck (Person* hero, int v);

//======================== ОСНОВНАЯ ФУНКЦИЯ  ====================================
int main ()
    {
    txCreateWindow (1300, 800);

    // ___________ у персонажа 2 характеристики: здоровье и монеты: на старте 100% здоровья и 100 монет
    Person hero = {1050, 215, 1, 100, 100};
    Person heroOld = hero;

    HDC background = txLoadImage ("Images\\bgfon2.bmp");
    HDC mapBG      = txLoadImage ("Images\\map1.bmp");

    txSetColor (RGB(170, 222, 135), 1);
    txRectangle(779, 44, 981, 81);

    int view  = 0;
    int widthHero  = X_PERSON / 2;
    int heightHero = Y_PERSON / 2;

    // ___________ массив координат для вывода подарков на экран
    int coorX [4] = { 96, 415, 580, 1030};
    int coorY [4] = {266, 555, 400,  450};

    Present pres1 = {coorX[0], coorY[0]};
    Present pres2 = {coorX[1], coorY[1]};
    Present pres3 = {coorX[2], coorY[2]};
    Present pres4 = {coorX[3], coorY[3]};

    int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
    int v1 = rand()%5, v2 = rand()%5, v3 = rand()%5, v4 = rand()%5;

    // ________ пока не конец игры (не нажата кнопка ESC) _______
    while (! txGetAsyncKeyState (VK_ESCAPE) and hero.live > 0 and hero.money > 0)
        {
        txBegin();
        //____ рисуем фон
        txBitBlt (0, 0, background);

        //_____рисуем на фоне подарки
        pres1.Draw (v1);
        pres2.Draw (v2);
        pres3.Draw (v3);
        pres4.Draw (v4);

        //_____рисуем героя с спрайтовой анимацией
        view ++;
        hero.Draw(view);

        heroOld = hero;
        hero.Control();

        LiveDraw  (&hero);
        MoneyDraw (&hero);

        //____ персонаж бродит по полю - границы отнимают здоровье
        if (txGetAsyncKeyState (VK_F1)) txBitBlt (0, 0, mapBG);

        //  границы L - левая, R -  правая, T - верхняя, B - нижняя
        COLORREF colorControlL = txGetPixel(hero.x + widthHero - 15, hero.y + heightHero, mapBG);
        COLORREF colorControlR = txGetPixel(hero.x + widthHero + 15, hero.y + heightHero, mapBG);

        COLORREF colorControlT = txGetPixel(hero.x + widthHero, hero.y + heightHero - 5, mapBG);
        COLORREF colorControlB = txGetPixel(hero.x + widthHero, hero.y + heightHero + 22, mapBG);

        if ( colorControlL != RGB (0, 0, 0) and colorControlL != RGB (255, 255, 255) and colorControlL != RGB (255, 255, 0))
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlR != RGB (0, 0, 0) and colorControlR != RGB (255, 255, 255) and colorControlL != RGB (255, 255, 0))
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlT != RGB (0, 0, 0) and colorControlT != RGB (255, 255, 255) and colorControlL != RGB (255, 255, 0))
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlB != RGB (0, 0, 0) and colorControlB != RGB (255, 255, 255) and colorControlL != RGB (255, 255, 0))
            {
            hero = heroOld;
            hero.live -= 1;
            }

        if ( colorControlL == RGB (255, 255, 255) or colorControlR == RGB (255, 255, 255) or
             colorControlT == RGB (255, 255, 255) or colorControlB == RGB (255, 255, 255) )
            {
            if (hero.x > 1033 and hero.x < 1117 and hero.y > 460 and hero.y < 550 and flag4 == 0)
                {
                flag4 = 1;
                PresentCheck (&hero, v4);
                txSleep(5);
                v4 = 5;
                }
            if (hero.x > 583 and hero.x < 667 and hero.y > 405 and hero.y < 495 and flag3 == 0)
                {
                flag3 = 1;
                PresentCheck (&hero, v3);
                txSleep(5);
                v3 = 5;
                }
            if (hero.x > 416 and hero.x < 500 and hero.y > 560 and hero.y < 650 and flag2 == 0)
                {
                flag2 = 1;
                PresentCheck (&hero, v2);
                txSleep(5);
                v2 = 5;
                }
            if (hero.x > 98 and hero.x < 182 and hero.y > 270 and hero.y < 360 and flag1 == 0)
                {
                flag1 = 1;
                PresentCheck (&hero, v1);
                txSleep(5);
                v1 = 5;
                }
            }
        if ( colorControlL == RGB (255, 255, 0) or colorControlR == RGB (255, 255, 0) or
             colorControlT == RGB (255, 255, 0) or colorControlB == RGB (255, 255, 0) )
            {
            break;
            }

        txEnd();
        txSleep(150);
        }

    txDeleteDC (background);
    txDeleteDC (mapBG);
    txDeleteDC (SPRITE_PERSON);
    txDeleteDC (SPRITE_REBUS);

    GameOver(hero);

    return 0;
    }


//-----------------------------------------------------------------------------
void PresentCheck (Person* hero, int v)
    {
    if (v == 0)
        {
        (*hero).money += 10;  // желтый
        txMessageBox ("ВНИМАНИЕ! ПРИЗ!!! \n  10 монет");
        }
    if (v == 1)
        {
        (*hero).money -= 10;  // синий
        txMessageBox ("ОЙ! НАЛОГ !!! \n  10 монет");
        }
    if (v == 2)
        {
        (*hero).live  -= 10;  // красный
        txMessageBox ("ОЙ! У ВАС ПОТЕРИ :( \n  10% здоровья");
        }
    if (v == 3)
        {
        (*hero).live  = 100;  // белый
        txMessageBox ("ВНИМАНИЕ! ПРИЗ!!! \n  Вы полностью здоровы");
        }
    if (v == 4)
        {
        (*hero).money += 10;  // горох
        (*hero).live  += 10;
        txMessageBox ("ВНИМАНИЕ! ПРИЗ!!! \n  10 монет И 10% здоровья");
        }
    }
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void GameOver (Person hero)
    {
    txSetColor (RGB(23, 112, 17), 3);
    txSetFillColor (RGB(170, 222, 135));
    txRectangle(350, 250, 950, 550);
    txSelectFont ("Arial Black", 70);
    txDrawText (370, 270, 930, 370, "GAME OVER", DT_CENTER);
    txSelectFont ("Arial Black", 40);

    char strLive [20] = "";
    sprintf (strLive,  "монет    : %4d", hero.money);

    char strMoney [20] = "";
    sprintf (strMoney, "здоровье : %4d", hero.live);

    txDrawText (400, 400, 830, 460, strLive,  DT_LEFT);
    txDrawText (400, 480, 830, 540, strMoney, DT_LEFT);
    }

//-----------------------------------------------------------------------------
void LiveDraw (Person* hero)
    {
    int procent = (*hero).live;
    if (procent > 0)
        {
        txSetColor (RGB(170, 222, 135), 1);

        txSetFillColor (RGB(255, 255 - (255 - procent*2.55), 128 - (128 - procent*1.28)));
        txRectangle(780, 45, 780 + procent*2, 80);

        txSetFillColor (RGB(23, 112, 17));
        txRectangle(980 - (200 - procent*2), 45, 980, 80);
        }
    }

//-----------------------------------------------------------------------------
void MoneyDraw (Person* hero)
    {
    txSetColor (RGB(170, 222, 135));

    txSelectFont ("Arial Black", 40);

    char strMoney [7] = "";
    sprintf (strMoney, "%4d",(*hero).money);

    txDrawText (500, 45, 600, 80, strMoney,  DT_LEFT);
    }
