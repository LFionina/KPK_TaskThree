//{===========================================================================
//! @file       LFioninaTaskThree.cpp
//!
//! @brief      ???? "????????"
//!
//!               $Date: 2021-06-23 $
//          (C) ??????? ??????? ??????????, ?. ??????, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>

const HDC SPRITE_PERSON  = txLoadImage ("GameSDK\\Images\\person.bmp");
const int X_PERSON = txGetExtentX (SPRITE_PERSON)/4,
          Y_PERSON = txGetExtentY (SPRITE_PERSON)/4;

const HDC SPRITE_PRESENT  = txLoadImage ("GameSDK\\Images\\presents1.bmp");
const int X_PRESENT = txGetExtentX (SPRITE_PRESENT)/6,
          Y_PRESENT = txGetExtentY (SPRITE_PRESENT);

const HDC SPRITE_REBUS  = txLoadImage ("GameSDK\\Images\\rebus.bmp");
const int X_REBUS = txGetExtentX (SPRITE_REBUS),
          Y_REBUS = txGetExtentY (SPRITE_REBUS)/6;

const int PERSON_LEFT = 2,
          PERSON_RIGHT = 1,
          PERSON_UP = 3,
          PERSON_DOWN = 0;

const int STEP = 10;

# include "GameSDK\Person.h"
# include "GameSDK\Present.h"

const COLORREF COLOR_TUNNEL  = RGB (0,     0,   0),
               COLOR_FINISH  = RGB (255, 255,   0),
               COLOR_PRESENT = RGB (255, 255, 255),
               COLOR_TASK    = RGB (255,   0, 255);

//----------------------------------------------------------------------
struct Sprite
    {
    HDC img;
    int xSize;
    int ySize;

    void Load (const char namefile []);
    void Delete ();
    };


struct Resourses
    {
    Sprite person;
    Sprite present;
    Sprite rebus;

    void Load ();
    void Delete ();
    };

struct Task
    {

    void Draw(char taskText[], char answer[], int num);

    };

//-------------------   ? ? ? ? ? ? ?    ? ? ? ? ? ? ?    ---------------------



//- - - - - - - - - - - - ????????? ???????  - - - - - - - - - - - - - - - - - -
void Task::Draw (char taskText[], char answer[], int num)
    {
    txSetColor (RGB(23, 112, 17), 3);
    txSetFillColor (RGB(170, 222, 135));
    txRectangle(350, 250, 950, 550);
    txSelectFont ("Arial Black", 40);

    txDrawText (400, 270, 900, 320, taskText,  DT_CENTER);
    txBitBlt (txDC(), 480, 320, X_REBUS, Y_REBUS, SPRITE_REBUS, 0*X_REBUS, num*Y_REBUS);
    txSetColor (TX_BLUE);
    txSelectFont ("Arial", 30);
    txDrawText (400, 450, 900, 510, answer,  DT_CENTER);

    txSetColor (RGB(23, 112, 17), 3);
    txSelectFont ("Arial Black", 40);
    txDrawText (400, 490, 900, 525, "1 - ?????      0 - ?? ?????",  DT_CENTER);
    }


//--------------------  ????????? ???????  ---------------------------------------
void GameOver  (Person  hero);
void LiveDraw  (Person* hero);
void MoneyDraw (Person* hero);

void PresentCheck (Person* hero, int v);
void VisitSchool(Task task, Person* hero, int* visitSchool);


//======================== ???????? ???????  ====================================
int main ()
    {
    txCreateWindow (1300, 800);

    // ___________ ? ????????? 2 ??????????????: ???????? ? ??????: ?? ?????? 100% ???????? ? 100 ?????
    //Person hero = {1050, 215, 1, 100, 100};
    Person hero = {700, 280, 1, 100, 100};
    Person heroOld = hero;

    HDC background = txLoadImage ("GameSDK\\Images\\bgfon2.bmp");
    HDC mapBG      = txLoadImage ("GameSDK\\Images\\map1.bmp");

    txSetColor (RGB(170, 222, 135), 1);
    txRectangle(779, 44, 981, 81);

    int view  = 0;
    int widthHero  = X_PERSON / 2;
    int heightHero = Y_PERSON / 2;


    int presentX [4] = { 96, 415, 580, 1030};
    int presentY [4] = {266, 555, 400,  450};

    Present pres1 = {presentX[0], presentY[0]};
    Present pres2 = {presentX[1], presentY[1]};
    Present pres3 = {presentX[2], presentY[2]};
    Present pres4 = {presentX[3], presentY[3]};

    Task task4 = {};


    // _________ ????? - ??????? ???????, v - ??? ??????? ?? ????? ?? ????????
    int gotPresent1 = 0, gotPresent2 = 0, gotPresent3 = 0, gotPresent4 = 0, visitSchool = 0;
    int v1 = rand()%5, v2 = rand()%5, v3 = rand()%5, v4 = rand()%5;

    // ________ ???? ?? ????? ???? (?? ?????? ?????? ESC) _______
    while (! txGetAsyncKeyState (VK_ESCAPE) and hero.live > 0 and hero.money > 0)
        {
        txBegin();
        //____ ?????? ???
        txBitBlt (0, 0, background);

        //_____?????? ?? ???? ???????
        pres1.Draw (v1);
        pres2.Draw (v2);
        pres3.Draw (v3);
        pres4.Draw (v4);

        //_____?????? ????? ? ?????????? ?????????
        view ++;
        hero.Draw(view);

        heroOld = hero;
        hero.Control();

        LiveDraw  (&hero);
        MoneyDraw (&hero);

        //____ ???????? ?????? ?? ???? - ??????? ???????? ????????
        if (txGetAsyncKeyState (VK_F1)) txBitBlt (0, 0, mapBG);

        //  ??????? L - ?????, R -  ??????, T - ???????, B - ??????
        COLORREF colorControlL = txGetPixel(hero.x + widthHero - 15, hero.y + heightHero, mapBG);
        COLORREF colorControlR = txGetPixel(hero.x + widthHero + 15, hero.y + heightHero, mapBG);

        COLORREF colorControlT = txGetPixel(hero.x + widthHero, hero.y + heightHero - 5, mapBG);
        COLORREF colorControlB = txGetPixel(hero.x + widthHero, hero.y + heightHero + 22, mapBG);

        if ( colorControlL != COLOR_TUNNEL and colorControlL != COLOR_PRESENT and
             colorControlL != COLOR_FINISH and colorControlL != COLOR_TASK)
            {
            hero = heroOld;
            hero.live -= 1;
            visitSchool = false;
            }

        if ( colorControlR != COLOR_TUNNEL and colorControlR != COLOR_PRESENT and
             colorControlR != COLOR_FINISH and colorControlR != COLOR_TASK)
            {
            hero = heroOld;
            hero.live -= 1;
            visitSchool = false;
            }

        if ( colorControlT != COLOR_TUNNEL and colorControlT != COLOR_PRESENT and
             colorControlT != COLOR_FINISH and colorControlT != COLOR_TASK)
            {
            hero = heroOld;
            hero.live -= 1;
            visitSchool = false;
            }
        if ( colorControlB != COLOR_TUNNEL and colorControlB != COLOR_PRESENT and
             colorControlB != COLOR_FINISH and colorControlB != COLOR_TASK)
            {
            hero = heroOld;
            hero.live -= 1;
            visitSchool = false;
            }

        if ( colorControlL == COLOR_PRESENT or colorControlR == COLOR_PRESENT or
             colorControlT == COLOR_PRESENT or colorControlB == COLOR_PRESENT )
            {
            if (hero.x > 1033 and hero.x < 1117 and hero.y > 460 and hero.y < 550 and gotPresent4 == 0)
                {
                gotPresent4 = 1;
                PresentCheck (&hero, v4);
                txSleep(5);
                v4 = 5;
                }
            if (hero.x > 583 and hero.x < 667 and hero.y > 405 and hero.y < 495 and gotPresent3 == 0)
                {
                gotPresent3 = 1;
                PresentCheck (&hero, v3);
                txSleep(5);
                v3 = 5;
                }
            if (hero.x > 416 and hero.x < 500 and hero.y > 560 and hero.y < 650 and gotPresent2 == 0)
                {
                gotPresent2 = 1;
                PresentCheck (&hero, v2);
                txSleep(5);
                v2 = 5;
                }
            if (hero.x > 98 and hero.x < 182 and hero.y > 270 and hero.y < 360 and gotPresent1 == 0)
                {
                gotPresent1 = 1;
                PresentCheck (&hero, v1);
                txSleep(5);
                v1 = 5;
                }
            }
        if ( colorControlL == COLOR_FINISH or colorControlR == COLOR_FINISH or
             colorControlT == COLOR_FINISH or colorControlB == COLOR_FINISH )
            {
            break;
            }
        if ( colorControlL == COLOR_TASK or colorControlR == COLOR_TASK or
             colorControlT == COLOR_TASK or colorControlB == COLOR_TASK )
            {
            if (hero.x > 661 and hero.x < 756 and hero.y < 708 and visitSchool == 0)
                {
                VisitSchool(task4, &hero, &visitSchool);
                }
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
 void VisitSchool(Task task4, Person* hero, int* visitSchool)
    {
    int Answer = rand() % 6, numRebus = rand() % 6;

    if (Answer == 0) task4.Draw ("????? ?? ??????? ?????", "??????",      numRebus);
    if (Answer == 1) task4.Draw ("????? ?? ??????? ?????", "????????",    numRebus);
    if (Answer == 2) task4.Draw ("????? ?? ??????? ?????", "??????",      numRebus);
    if (Answer == 3) task4.Draw ("????? ?? ??????? ?????", "???????",     numRebus);
    if (Answer == 4) task4.Draw ("????? ?? ??????? ?????", "???????",     numRebus);
    if (Answer == 5) task4.Draw ("????? ?? ??????? ?????", "???????????", numRebus);

    txSleep(200);

    while (true)
        {
        if ((txGetAsyncKeyState ('1') and Answer == numRebus) or (txGetAsyncKeyState ('0') and Answer != numRebus))
            {
            hero -> money += 30;
            txMessageBox ("?????!!! \n ????: 30 ?????");
            break;
            }

        else if ((txGetAsyncKeyState ('1') and Answer != numRebus) or (txGetAsyncKeyState ('0') and Answer == numRebus))
            {
            hero -> money -= 10;
            txMessageBox ("???!!! \n ????????: -10 ?????");
            break;
            }

        Sleep (10);
        }

    *visitSchool = 1;

     }
//-----------------------------------------------------------------------------
void PresentCheck (Person* hero, int v)
    {
    if (v == 0)
        {
        (*hero).money += 10;  // ??????
        txMessageBox ("????????! ????!!! \n  10 ?????");
        }
    if (v == 1)
        {
        (*hero).money -= 10;  // ?????
        txMessageBox ("??! ????? !!! \n  10 ?????");
        }
    if (v == 2)
        {
        (*hero).live  -= 10;  // ???????
        txMessageBox ("??! ? ??? ?????? :( \n  10% ????????");
        }
    if (v == 3)
        {
        (*hero).live  = 100;  // ?????
        txMessageBox ("????????! ????!!! \n  ?? ????????? ???????");
        }
    if (v == 4)
        {
        (*hero).money += 10;  // ?????
        (*hero).live  += 10;
        txMessageBox ("????????! ????!!! \n  10 ????? ? 10% ????????");
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
    sprintf (strLive,  "?????    : %4d", hero.money);

    char strMoney [20] = "";
    sprintf (strMoney, "???????? : %4d", hero.live);

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
