#include "stdafx.h"
#include "RandomAS.h"

#include <cmath>
#include <ctime>
#include <cstdlib>



RandomAS::RandomAS()
    : min_val( 100.0 )
    , max_val( 0.0 )
    , num_iter( 0 )
{
  
}


int RandomAS::GetRandomNumber( int base ) const
{
    Sleep( 2 );
    srand( time( NULL ) );

    int v = rand() % base;
    return v;
}


bool RandomAS::IsDivideRandom( int current, int size, double w )
{
    int ver[3] = { 0, 0, 0 };

    if (min_val < w)
    {
        if ((max_val + min_val) / 2.0 < w)
            ver[0] = 1;
    }

    if (max_val < w)
    {
        max_val = w;

    }
    else
        ver[1] = 1;

    int t = GetRandomNumber( 100 );

    if (t % 2 == 0)
        ver[2] = 1;

    int ver_sum = ver[0] + ver[1] + ver[2];

    if (ver_sum < 2)
        return false;

    return true;
}


Color RandomAS::GetRandomColor()
{
    int col = GetRandomNumber( 5 );

    switch (col)
    {
        case 0:
            return Color::Yellow;
            break;
        case 1:
            return Color::Blue;
            break;
        case 2:
            return Color::Red;
            break;    
        case 3:
            return Color::Green;
            break;
        case 4:
            return Color::Purple;
            break;
        default:
            return Color::White;
            break;
    }
}


#include <Windows.h>
#include <iostream>
#include <sstream>
int* RandomAS::GetRandomNumbers( int randoms, int w )
{
    num_iter++;


    int s = 2;
    if (randoms > s)
        s = randoms;

    int first = GetRandomNumber( s );
    int second = GetRandomNumber( s );

    
    while (second == first)
        second = GetRandomNumber( s );

    int ver[2] = { first, second };
    OutputDebugStringW( L"New Iteration  " );

    std::wostringstream os_;    
    os_ << num_iter << "  ( " << randoms << " )  elements" << std::endl << "first: " << first << "    second: " << second << std::endl;
    OutputDebugStringW( os_.str().c_str() );


    return ver;
}
