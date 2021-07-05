//{===========================================================================
//! @file       Person.h
//!
//!             ����� �������
//!
//!@author  (C) ������� ������� ����������, �. ������,
//!@date          2021
//!
//!@mainpage
//!         ����� ���������� ����
//!
//!
//!@par   ����������
//!
//!       ����� ������� - ����� ��� �������� ���������� ���� "��������".
//!     ������� �� 5 ���������: ���������� ��������� �� ���� ����, ��� �������� ���������,
//!     ������� �������� � ���������� �����.
//!
//!     �������� ��� ������� ������: ��������� ��������� � ���������� ����������.
//!
//!       Class Person - a class for creating characters for the game "Adventurer".
//!     Consists of 5 components: coordinates of the character on the field of play,
//!     type of character animation, health level and number of coins.
//!
//!     Includes two class functions: character drawing and character control.
//!
//}===========================================================================


//{-----------------------------------------------------------------------------
//! ��������� ���������
//!
//! @param  x       ���������� �� �
//!         y       ���������� �� Y
//!         anim    ��� �������� (��� �������, �����, ������, �����)
//!
//!         live    ������� �������� (�� 0 �� 100%)
//!         money   ���������� ������������ �����
//!
//}-----------------------------------------------------------------------------
struct Person
    {
    double x, y;

    int anim;

    int live;
    int money;

    void Draw (int frame);
    void Control ();
    };

//{-----------------------------------------------------------------------------
//! ������� ��������� ��������� ����� ��������� ��� ������ ���������� ��������
//!
//! @param frame  ���� �������� ��������� ��� ��������
//!
//}-----------------------------------------------------------------------------
void Person::Draw (int frame)
    {
    txTransparentBlt (txDC(), x, y, X_PERSON, Y_PERSON, SPRITE_PERSON, (frame % 4)*X_PERSON, anim*Y_PERSON, RGB(0,255,0));
    }

//{-----------------------------------------------------------------------------
//! ������� ���������� ��������� ���������
//!
//! @param frame  ���� �������� ��������� ��� ��������
//!
//}-----------------------------------------------------------------------------
void Person::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT) )
        {
        (*this).x += STEP;
        (*this).anim = PERSON_RIGHT;
        }
    if (txGetAsyncKeyState (VK_LEFT ) )
        {
        (*this).x -= STEP;
        (*this).anim = PERSON_LEFT;
        }
    if (txGetAsyncKeyState (VK_UP   ) )
        {
        (*this).y -= STEP;
        (*this).anim = PERSON_UP;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        (*this).y += STEP;
        (*this).anim = PERSON_DOWN;
        }
    }
