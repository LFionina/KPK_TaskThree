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
          Y_PERSON = txGetExtentY (SPRITE_PERSON)/3;

//---------------------СТРУКТУРЫ-------------------------------------------------

struct Person
    {
    double x, y;

    int numView;
    int course;

    int live;
    int money;

    void Draw (int view);
    void Control ();
    };

struct Button
    {
    double x, y;
    char text[15];

    void Draw ();
    };

struct SubMenu
    {
    double x, y;
    char etemMenu1[14];
    char etemMenu2[14];
    char etemMenu3[14];

    void Draw ();
    };

//-------------------   Ф У Н К Ц И И    К Л А С С О В    ---------------------


//- - - - - - - - - - - - рисование героя  - - - - - - - - - - - - - - - - - -
/*void Person::Draw (int view)
    {
    switch (numView)
        {
        case 1:
            {
            txSetColor     (RGB (84, 0, 0));
            txSetFillColor (RGB (255, 213, 213));
            txCircle (x, y, 30);
            txSetFillColor (RGB (84, 0, 0));
            txCircle (x, y,  4);
            }
            break;
        case 2:
            {
            txSetColor     (RGB (84, 0, 0));
            txSetFillColor (RGB (255, 213, 213));
            txRectangle (x - 30, y - 30, x + 30, y + 30);
            txSetFillColor (RGB (84, 0, 0));
            txRectangle (x -  4, y -  4, x +  4, y +  4);
            }
            break;
        case 3:
            {
            HDC ghost = txLoadImage ("personFront1.bmp");
            txTransparentBlt  ( txDC(), x + 42, y + 50, 0, 0, ghost, 0, 0, RGB(0,255,0));
            txDeleteDC (ghost);
            }
            break;
        }

    }
    */
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
    if (course == 0)  //---вверх или вниз
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 0*Y_PERSON, RGB(0,255,0));
        }
    }

//- - - - - - - - - - - - управление тележкой - - - - - - - - - - - - - - - - -
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT) )
        {
        (*this).x += 5;
        (*this).course = 1;
        }
    if (txGetAsyncKeyState (VK_LEFT ) )
        {
        (*this).x -= 5;
        (*this).course = 2;
        }
    if (txGetAsyncKeyState (VK_UP   ) )
        {
        (*this).y -= 5;
        (*this).course = 0;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        (*this).y += 5;
        (*this).course = 0;
        }
    }

//- - - - - - - - - - - - рисование кнопки  - - - - - - - - - - - - - - - - - -
void Button::Draw ()
    {
    txSetColor (RGB(23, 112, 17));
    txSetFillColor (RGB(23, 40, 11));
    txRectangle(x, y, x + 150, y + 40);

    txSetColor (RGB(23, 112, 17));
    txSetFillColor (RGB(170, 222, 135));
    txRectangle(x - 3, y - 3, x + 147, y + 37);

    txSetColor(RGB(23, 112, 17));
    txSelectFont ("Arial Black", 25);
    txDrawText (x, y+3, x + 150, y + 40, text, DT_CENTER);
    }

//- - - - - - - - - - - - рисование подменю  - - - - - - - - - - - - - - - - - -
void SubMenu::Draw ()
    {
    txSetColor (RGB(23, 112, 17));
    txSetFillColor (RGB(23, 112, 17));
    txRectangle(x, y, x + 170, y + 200);

    txSetColor(RGB(170, 222, 135));
    txSelectFont ("Arial Black", 25);
    txDrawText (x + 10, y + 10, x + 160, y +  40, etemMenu1, DT_LEFT);
    txDrawText (x + 10, y + 50, x + 160, y +  80, etemMenu2, DT_LEFT);
    txDrawText (x + 10, y + 90, x + 160, y + 120, etemMenu3, DT_LEFT);

    }




//--------------------  ПРОТОТИПЫ ФУНКЦИЙ  ---------------------------------------
void GameOver (Person hero);


//======================== ОСНОВНАЯ ФУНКЦИЯ  ====================================
int main ()
    {
    txCreateWindow (1300, 800);

    Person hero = {1090, 231, 1, 1, 100, 100};

    HDC background = txLoadImage ("Images\\bgfon2.bmp");
    HDC mapBG      = txLoadImage ("Images\\map1.bmp");

    int view  = 0;
    int d1 = 1;

    // ________ пока не конец игры (не нажата кнопка ESC) _______
    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBegin();
        //____ рисуем фон и героя
        txBitBlt (0, 0, background);

        view ++;

        hero.Draw(view);
        hero.Control();

        //____ в противном случае персонаж бродит по полю
        //     границы отнимают здоровье

        //     У персонажа 2 характеристики: жизни и монеты

        //____     на старте 100% здоровья и 100 монет
        //____ ___ если натыкается на подарок смотрим какой он по номеру
        //         1 случайно добавляются/удаляются здоровье или деньги
        //         2 требует заплатить за вход, если денег не хватает их
        //           можно заработать в школе, пройдя тест
        //         3 случайно добавляются/удаляются здоровье или деньги
        //         4 требует заплатить за вход, если денег не хватает их
        //           можно заработать в школе, пройдя тест

        //____     на стадионе можно заработать монеты набирая очки в арканоиде

        //____     фудкорт добавляет единицы здоровья

        //____     озеро отнимает 50% здоровья

        //____ финиш - когда у тебя более 80% здоровья и N монет

        txEnd();
        txSleep(150);
        }

    txDeleteDC (background);
    txDeleteDC (mapBG);
    txDeleteDC (SPRITE_PERSON);

    GameOver(hero);

    return 0;
    }


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
    sprintf (strLive,  "монет    : %4d", hero.live);

    char strMoney [20] = "";
    sprintf (strMoney, "здоровье : %4d", hero.money);

    txDrawText (400, 400, 830, 460, strLive,  DT_LEFT);
    txDrawText (400, 480, 830, 540, strMoney, DT_LEFT);
    }


