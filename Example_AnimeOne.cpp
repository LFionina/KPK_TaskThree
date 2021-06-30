//{===========================================================================
//! @file       Example_AnimeOne.cpp
//!
//! @brief      СПРАЙТОВАЯ АНИМАЦИЯ
//!
//!               $Date: 2021-06-30 $
//          (C) Фионина Людмила Евгеньевна, г. Самара, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>

int main()
    {
    txCreateWindow (500, 500);

    HDC person  = txLoadImage ("Images\\person.bmp");

    int sizeX = txGetExtentX (person)/4,
        sizeY = txGetExtentY (person)/3;

    int t = 1;
    int nanim = 0;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);
        txClear();

        txTransparentBlt (txDC(), 250, 250, sizeX, sizeY, person, (t%4)*sizeX, nanim*sizeY, RGB(0,255,0));


        if (txGetAsyncKeyState (VK_F1))  nanim = 0;
        if (txGetAsyncKeyState (VK_F2))  nanim = 1;
        if (txGetAsyncKeyState (VK_F3))  nanim = 2;

        t++;

        txSleep(100);
        }

    txDeleteDC (person);

    return 0;
    }
