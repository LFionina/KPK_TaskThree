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


const HDC SPRITE_PERSON  = txLoadImage ("Images\\person.bmp");
const int X_PERSON = txGetExtentX (SPRITE_PERSON)/4,
          Y_PERSON = txGetExtentY (SPRITE_PERSON)/4;

const HDC SPRITE_PRESENT  = txLoadImage ("Images\\presents1.bmp");
const int X_PRESENT = txGetExtentX (SPRITE_PRESENT)/5,
          Y_PRESENT = txGetExtentY (SPRITE_PRESENT);

//---------------------���������-------------------------------------------------

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
    double x, y;

    void Draw (int num);
    };

//-------------------   � � � � � � �    � � � � � � �    ---------------------


//- - - - - - - - - - - - ��������� �����  - - - - - - - - - - - - - - - - - -
void Person::Draw (int view)
    {
    if (course == 1)  //--- ������
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 1*Y_PERSON, RGB(0,255,0));
        }
    if (course == 2)  //--- �����
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 2*Y_PERSON, RGB(0,255,0));
        }
    if (course == 0)  //---�����
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 0*Y_PERSON, RGB(0,255,0));
        }
    if (course == 3)  //--- ����
        {
        txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (view % 4)*X_PERSON, 3*Y_PERSON, RGB(0,255,0));
        }
    }

//- - - - - - - - - - - - ���������� ������ - - - - - - - - - - - - - - - - -
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
        (*this).course = 3;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        (*this).y += 5;
        (*this).course = 0;
        }
    }

//- - - - - - - - - - - - ��������� �����  - - - - - - - - - - - - - - - - - -
void Present::Draw (int num)
    {
    txTransparentBlt (txDC(), x, y, X_PRESENT, Y_PRESENT, SPRITE_PRESENT, num*X_PRESENT, 0*Y_PRESENT, RGB(0,255,0));
    }

//--------------------  ��������� �������  ---------------------------------------
void GameOver  (Person  hero);
void LiveDraw  (Person* hero);
void MoneyDraw (Person* hero);

//======================== �������� �������  ====================================
int main ()
    {
    txCreateWindow (1300, 800);

    Present pres1 = {1030, 450};

    //� ��������� 2 ��������������: ����� � ������
    // ____     �� ������ 100% �������� � 100 �����
    Person hero = {1050, 215, 1, 100, 100};
    Person heroOld = hero;

    HDC background = txLoadImage ("Images\\bgfon2.bmp");
    HDC mapBG      = txLoadImage ("Images\\map1.bmp");

    txSetColor (RGB(170, 222, 135), 1);
    txRectangle(779, 44, 981, 81);

    int view  = 0;
    int widthHero  = X_PERSON / 2;
    int heightHero = Y_PERSON / 2;

    printf("x pres = %04d   y pres %04d", X_PRESENT,Y_PRESENT);

    // ________ ���� �� ����� ���� (�� ������ ������ ESC) _______
    while (! txGetAsyncKeyState (VK_ESCAPE) and hero.live > 0 and hero.money > 0)
        {
        txBegin();
        //____ ������ ��� � �����
        txBitBlt (0, 0, background);

        view ++;
        hero.Draw(view);

        heroOld = hero;
        hero.Control();
        LiveDraw  (&hero);
        MoneyDraw (&hero);

        pres1.Draw (1);

        //____ �������� ������ �� ���� - ������� �������� ��������
        if (txGetAsyncKeyState (VK_F1)) txBitBlt (0, 0, mapBG);

        //  ������� L - �����, R -  ������, T - �������, B - ������
        COLORREF colorControlL = txGetPixel(hero.x + widthHero - 15, hero.y + heightHero, mapBG);
        COLORREF colorControlR = txGetPixel(hero.x + widthHero + 15, hero.y + heightHero, mapBG);

        COLORREF colorControlT = txGetPixel(hero.x + widthHero, hero.y + heightHero - 5, mapBG);
        COLORREF colorControlB = txGetPixel(hero.x + widthHero, hero.y + heightHero + 22, mapBG);

        if ( colorControlL != RGB (0, 0, 0) )
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlR != RGB (0, 0, 0) )
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlT != RGB (0, 0, 0) )
            {
            hero = heroOld;
            hero.live -= 1;
            }
        if ( colorControlB != RGB (0, 0, 0) )
            {
            hero = heroOld;
            hero.live -= 1;
            }

        //____ ___ ���� ���������� �� ������� ������� ����� �� �� ������
        //         1 �������� �����������/��������� �������� ��� ������
        //         2 ������� ��������� �� ����, ���� ����� �� ������� ��
        //           ����� ���������� � �����, ������ ����
        //         3 �������� �����������/��������� �������� ��� ������
        //         4 ������� ��������� �� ����, ���� ����� �� ������� ��
        //           ����� ���������� � �����, ������ ����

        //____     �� �������� ����� ���������� ������ ������� ���� � ���������

        //____     ������� ��������� ������� ��������

        //____     ����� �������� 50% ��������

        //____ ����� - ����� � ���� ����� 80% �������� � N �����

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
    sprintf (strLive,  "�����    : %4d", hero.money);

    char strMoney [20] = "";
    sprintf (strMoney, "�������� : %4d", hero.live);

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
