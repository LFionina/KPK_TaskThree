//{===========================================================================
//! @file       LFioninaTaskThree.cpp
//!
//! @brief      ���� "��������"
//!
//!               $Date: 2021-06-23 $
//          (C) ������� ������� ����������, �. ������, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>


//---------------------���������-------------------------------------------------

struct Person
    {
    double x, y;

    void Draw ();
    void Control ();
    };

struct Button
    {
    double x, y;
    char text[15];

    void Draw ();
    };

//-------------------   � � � � � � �    � � � � � � �    ---------------------

/*
//- - - - - - - - - - - - ��������� �����  - - - - - - - - - - - - - - - - - -
void Person::Draw ()
    {
    HDC ghost = txLoadImage ("personFront1.bmp");
    txTransparentBlt  ( txDC(), x + 42, y + 50, 0, 0, ghost, 0, 0, RGB(0,255,0));
    txDeleteDC (ghost);

    }
 */

//- - - - - - - - - - - - ��������� �����  - - - - - - - - - - - - - - - - - -
void Person::Draw ()
    {
    txSetColor     (RGB (84, 0, 0));
    txSetFillColor (RGB (255, 213, 213));
    txCircle (x, y, 30);
    txSetFillColor (RGB (84, 0, 0));
    txCircle (x, y, 4);
    }

//- - - - - - - - - - - - ���������� �������� - - - - - - - - - - - - - - - - -
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT)  ) (*this).x += 5;
    if (txGetAsyncKeyState (VK_LEFT )  ) (*this).x -= 5;
    if (txGetAsyncKeyState (VK_UP   )  ) (*this).y -= 5;
    if (txGetAsyncKeyState (VK_DOWN )  ) (*this).y += 5;
    }

//- - - - - - - - - - - - ��������� ������  - - - - - - - - - - - - - - - - - -
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

//--------------------  ��������� �������  ---------------------------------------
void MovePerson ();
void Menu ();


//======================== �������� �������  ====================================
int main ()
    {
    txCreateWindow (1300, 800);

    //MovePerson ();
    Menu();
    return 0;
    }


//-----------------------------------------------------------------------------
void Menu ()
    {
    txSetColor (RGB(23, 112, 17));
    txSetFillColor (RGB(23, 112, 17));
    txRectangle(0, 0, 1300, 100);

    Button buttonF1 = { 20, 50, "F1 - �����"};
    Button buttonF2 = {190, 50, "F2 - �������"};

    buttonF1.Draw();
    buttonF2.Draw();

    }

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void MovePerson ()
    {
    HDC  background = txLoadImage ("bgfon.bmp");
    HDC  mapBG      = txLoadImage ("map.bmp");
    //HDC  manya = txLoadImage ("personFront1.bmp");

    Person ghost = {1090, 130};
    Person ghostOld = ghost;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (0, 0, background);

        if (txGetAsyncKeyState (VK_F1)) txBitBlt (0, 0, mapBG);

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
