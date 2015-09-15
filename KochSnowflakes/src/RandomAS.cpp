#include "stdafx.h"
#include "RandomAS.h"

#include <cmath>
#include <ctime>
#include <cstdlib>



RandomAS::RandomAS()
    : min_val( 100.0 )
    , max_val( 0.0 )
{
  
}


int RandomAS::GetRandomNumber() const
{
    Sleep( 10 );
    srand( time( NULL ) );
    int v = rand() % 100 + 1;
    return v;
}


bool RandomAS::GetRandomAS( int current, int size, double w )
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

    int t = GetRandomNumber();

    if (t % 2 == 0)
        ver[2] = 1;

    int ver_sum = ver[0] + ver[1] + ver[2];

    if (ver_sum < 2)
        return false;

    return true;
}