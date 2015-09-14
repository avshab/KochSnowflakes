#include "stdafx.h"
#include "RandomAS.h"

#include <cmath>
#include <ctime>
#include <cstdlib>

RandomAS::RandomAS()
    : min_w( 0.0 )
{
  
}


bool RandomAS::GetRandomAS( int current, int num, double w )
{
    srand( time( NULL ) );
    int x = rand() % 100 + 1;



    if (min_w == 0.0)
    {   
        min_w = w;
        if (x > 49)
            return true;
    }   

    if (min_w > w)
        min_w = w;
    
    if ( w > min_w)
        return true;
   
    if (x < 80  && x >20)
        return false;


    return true;
}