//{===========================================================================
//! @file       Example_AnimeOne.cpp
//!
//! @brief      —œ–¿…“Œ¬¿ﬂ ¿Õ»Ã¿÷»ﬂ
//!
//!               $Date: 2021-06-30 $
//          (C) ‘ËÓÌËÌ‡ À˛‰ÏËÎ‡ ≈‚„ÂÌ¸Â‚Ì‡, „. —‡Ï‡‡, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>

int MovePerson (int* dx, int*dy);

//-----------------------------------------------------------------------------

int main()
    {
    txCreateWindow (500, 500);

    HDC person  = txLoadImage ("Images\\person.bmp");

    int sizeX = txGetExtentX (person)/4,
        sizeY = txGetExtentY (person)/3;

    int t=0;
    int nanim = 0, dx = 100, dy = 100;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);
        txClear();

        txTransparentBlt (txDC(), dx, dy, sizeX, sizeY, person, (t%4)*sizeX, nanim*sizeY, RGB(0,255,0));

        nanim = MovePerson (&dx, &dy);
        //if (txGetAsyncKeyState (VK_F1))  nanim = 0;
        //if (txGetAsyncKeyState (VK_F2))  nanim = 1;
       //if (txGetAsyncKeyState (VK_F3))  nanim = 2;

        t++;

        txSleep(150);
        }

    txDeleteDC (person);

    return 0;
    }


//-----------------------------------------------------------------------------
int MovePerson (int* dx, int*dy)
    {
    if (txGetAsyncKeyState (VK_RIGHT) )
        {
        *dx += 5;
        return 1;
        }
    if (txGetAsyncKeyState (VK_LEFT ) )
        {
        *dx -= 5;
        return 2;
        }
    if (txGetAsyncKeyState (VK_UP   ) )
        {
        *dy -= 5;
        return 0;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        *dy += 5;
        return 0;
        }
    }
