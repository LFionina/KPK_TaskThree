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


//---------------------СТРУКТУРЫ-------------------------------------------------

struct Person
    {
    double x, y;

    int numView;

    void SetView (int view);
    void Draw ();
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

//- - - - - - - - - - - - номер героя  - - - - - - - - - - - - - - - - - -
void Person::SetView (int view)
    {
    this -> numView = view;
    }
//- - - - - - - - - - - - рисование героя  - - - - - - - - - - - - - - - - - -
void Person::Draw ()
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

//- - - - - - - - - - - - управление тележкой - - - - - - - - - - - - - - - - -
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT)  ) (*this).x += 5;
    if (txGetAsyncKeyState (VK_LEFT )  ) (*this).x -= 5;
    if (txGetAsyncKeyState (VK_UP   )  ) (*this).y -= 5;
    if (txGetAsyncKeyState (VK_DOWN )  ) (*this).y += 5;
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
void MovePerson ();

void Menu ();
void MenuDraw ();

void SubMenuDraw (double x, double y, char etemMenu1[14], char etemMenu2[14], char etemMenu3[14]);
int  SubMenuSelect (SubMenu view);
void SelectDraw (SubMenu view, int pos);


//======================== ОСНОВНАЯ ФУНКЦИЯ  ====================================
int main ()
    {
    txCreateWindow (1300, 800);


    //Menu();

    MovePerson ();
    return 0;
    }


//-----------------------------------------------------------------------------
void Menu ()
    {
    MenuDraw ();

    while (true)
        {
        if (txGetAsyncKeyState (VK_F1) )
            {
            MenuDraw();
            SubMenu subMenuF1 = {10, 100, "круг","квадрат","картинка"};
            subMenuF1.Draw();

            int d1 = SubMenuSelect (subMenuF1);
            printf("выбор f1: %d", d1);
            //break;
            }
        if (txGetAsyncKeyState (VK_F2) )
            {
            MenuDraw();
            SubMenu subMenuF2 = {200, 100, "уровень 1","уровень 2","уровень 3"};
            subMenuF2.Draw();

            int d2 = SubMenuSelect (subMenuF2);
            printf("выбор f2: %d", d2);
            //break;
            }

        }
    }

//-----------------------------------------------------------------------------
void MenuDraw ()
    {
    txSetFillColor (TX_BLACK);
    txClear();

    txSetColor (RGB(23, 112, 17));
    txSetFillColor (RGB(23, 112, 17));
    txRectangle(0, 0, 1300, 100);

    Button buttonF1 = { 20, 50, "F1 - герой"};
    Button buttonF2 = {210, 50, "F2 - уровень"};

    buttonF1.Draw();
    buttonF2.Draw();
    }

//-----------------------------------------------------------------------------
void SubMenuDraw (double x, double y, char etemMenu1[14], char etemMenu2[14], char etemMenu3[14])
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
//-----------------------------------------------------------------------------
int SubMenuSelect (SubMenu view)
    {
    int pos = 1;
    txSetColor(TX_YELLOW);
    txSelectFont ("Arial Black", 25);
    txDrawText (view.x + 10, view.y + 10, view.x + 160, view.y +  40, view.etemMenu1, DT_LEFT);

    txSetColor(RGB(170, 222, 135));
    txDrawText (view.x + 10, view.y + 50, view.x + 160, view.y +  80, view.etemMenu2, DT_LEFT);
    txDrawText (view.x + 10, view.y + 90, view.x + 160, view.y + 120, view.etemMenu3, DT_LEFT);

    while (true)
        {
        if (GetAsyncKeyState(VK_UP) != 0)
            {
            pos -= 1;
            if (pos == 0) pos = 3;
            SelectDraw (view, pos);
            txSleep(25);
            }
        else if (GetAsyncKeyState(VK_DOWN) != 0)
            {
            pos += 1;
            if (pos == 4) pos = 1 ;
            SelectDraw (view, pos);
            txSleep(25);
            }
        else if (GetAsyncKeyState(VK_RETURN) != 0)
            {
            MenuDraw ();
            return pos;

            }
        }
    }
//-----------------------------------------------------------------------------
void SelectDraw (SubMenu view, int pos)
    {
    switch (pos)
        {
        case 1:
            {
            MenuDraw ();
            view.Draw();
            txSetColor(TX_YELLOW);
            txSelectFont ("Arial Black", 25);
            txDrawText (view.x + 10, view.y + 10, view.x + 160, view.y +  40, view.etemMenu1, DT_LEFT);

            txSetColor(RGB(170, 222, 135));
            txDrawText (view.x + 10, view.y + 50, view.x + 160, view.y +  80, view.etemMenu2, DT_LEFT);
            txDrawText (view.x + 10, view.y + 90, view.x + 160, view.y + 120, view.etemMenu3, DT_LEFT);
            }
            break;
        case 2:
            {
            MenuDraw ();
            view.Draw();
            txSetColor(TX_YELLOW);
            txSelectFont ("Arial Black", 25);
            txDrawText (view.x + 10, view.y + 50, view.x + 160, view.y +  80, view.etemMenu2, DT_LEFT);

            txSetColor(RGB(170, 222, 135));
            txDrawText (view.x + 10, view.y + 10, view.x + 160, view.y +  40, view.etemMenu1, DT_LEFT);
            txDrawText (view.x + 10, view.y + 90, view.x + 160, view.y + 120, view.etemMenu3, DT_LEFT);
            }
            break;
        case 3:
            {
            MenuDraw ();
            view.Draw();
            txSetColor(TX_YELLOW);
            txSelectFont ("Arial Black", 25);
            txDrawText (view.x + 10, view.y + 90, view.x + 160, view.y + 120, view.etemMenu3, DT_LEFT);

            txSetColor(RGB(170, 222, 135));
            txDrawText (view.x + 10, view.y + 50, view.x + 160, view.y +  80, view.etemMenu2, DT_LEFT);
            txDrawText (view.x + 10, view.y + 10, view.x + 160, view.y +  40, view.etemMenu1, DT_LEFT);
            }
            break;
        }
    }
//-----------------------------------------------------------------------------
void MovePerson ()
    {
    HDC  background = txLoadImage ("bgfon.bmp");
    HDC  mapBG      = txLoadImage ("map.bmp");
    //HDC  manya = txLoadImage ("personFront1.bmp");

    Person ghost = {1090, 231, 2};
    Person ghostOld = ghost;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (0, 101, background);

        if (txGetAsyncKeyState (VK_F1)) txBitBlt (0, 101, mapBG);

        ghost.Draw ();
        ghostOld = ghost;
        ghost.Control ();

        COLORREF colorControl = txGetPixel(ghost.x, ghost.y, mapBG);
        if ( colorControl != RGB (0, 0, 0) )
            {
            //printf("%06X - color \n",colorControl);
            ghost = ghostOld;
            }

        txSleep(200);
        }

    txDeleteDC (background);
    txDeleteDC (mapBG);
    }
