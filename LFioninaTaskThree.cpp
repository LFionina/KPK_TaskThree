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

    void Draw ();
    void Control ();
    };

//-------------------   Ф У Н К Ц И И    К Л А С С О В    ---------------------

/*
//- - - - - - - - - - - - рисование героя  - - - - - - - - - - - - - - - - - -
void Person::Draw ()
    {
    HDC ghost = txLoadImage ("personFront1.bmp");
    txTransparentBlt  ( txDC(), x + 42, y + 50, 0, 0, ghost, 0, 0, RGB(0,255,0));
    txDeleteDC (ghost);

    }
 */

//- - - - - - - - - - - - рисование героя  - - - - - - - - - - - - - - - - - -
void Person::Draw ()
    {
    txSetColor     (RGB (84, 0, 0));
    txSetFillColor (RGB (255, 213, 213));
    txCircle (x, y, 30);
    txSetFillColor (RGB (84, 0, 0));
    txCircle (x, y, 4);
    }

//- - - - - - - - - - - - управление тележкой - - - - - - - - - - - - - - - - -
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT)  ) (*this).x += 5;
    if (txGetAsyncKeyState (VK_LEFT )  ) (*this).x -= 5;
    if (txGetAsyncKeyState (VK_UP   )  ) (*this).y -= 5;
    if (txGetAsyncKeyState (VK_DOWN )  ) (*this).y += 5;
    }


//--------------------  ПРОТОТИПЫ ФУНКЦИЙ  ---------------------------------------
void MovePerson ();

//======================== ОСНОВНАЯ ФУНКЦИЯ  ====================================
int main ()
    {
    txCreateWindow (1300, 800);



    MovePerson ();


    return 0;
    }


//-----------------------------------------------------------------------------
void MovePerson ()
    {
    HDC  background = txLoadImage ("map.bmp");
    HDC  mapBG      = txLoadImage ("map.bmp");
    //HDC  manya = txLoadImage ("personFront1.bmp");

    Person ghost = {1090, 230};
    Person ghostOld = ghost;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (0, 100, background);
        ghost.Draw ();

        ghostOld = ghost;

        ghost.Control ();

        //printf("old: x= %.1f y= %.1f real: x= %.1f y= %.1f\n",ghostOld.x, ghostOld.y, ghost.x, ghost.y);

        COLORREF colorControl = txGetPixel(ghost.x, ghost.y, mapBG);

        if ( colorControl != RGB (0, 0, 0) )
        {

        ghost = ghostOld;
        }



        txSleep(20);
        }

    txDeleteDC (background);
    txDeleteDC (mapBG);
    }
