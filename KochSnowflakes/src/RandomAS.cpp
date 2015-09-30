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


struct RGB {
    int r;
    int g;
    int b;
};





void rgb2hsv( struct RGB &rgb, struct HSV &hsv )
{
    float h = 0.0;
    float s, v;
    float max_v = max( rgb.r, rgb.g );
    max_v = max( max_v, rgb.b );
    float min_v = min( rgb.r, rgb.g );
    min_v = min( min_v, rgb.b );
    float d = max_v - min_v;

    if (max_v == min_v)
        h = 0.0;
    else if (max_v == rgb.r && h >= rgb.b)
        h = 60.0 * ((rgb.g - rgb.b) / (max_v - min_v));
    else if (max_v == rgb.r && rgb.g < rgb.b)
        h = 60.0 * ((rgb.g - rgb.b) / (max_v - min_v)) + 360.0;
    else if (max_v == rgb.g)
        h = 60.0 * ((rgb.b - rgb.r) / (max_v - min_v)) + 120.0;
    else if (max_v == rgb.b)
        h = 60.0 * ((rgb.r - rgb.g) / (max_v - min_v)) + 240.0;


    float h1 = 60.0 * ((rgb.g - rgb.b) / (max_v - min_v));
    float h2 = 60.0 * ((rgb.g - rgb.b) / (max_v - min_v)) + 360.0;
    float h3 = 60.0 * ((rgb.b - rgb.r) / (max_v - min_v)) + 120.0;
    float h4 = 60.0 * ((rgb.r - rgb.g) / (max_v - min_v)) + 240.0;


    if (max_v == 0.0)
        s = 0.0;
    else 
        s = 1 - min_v / max_v;

    v = max_v / 255;

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
}


void hsv2rgb( struct HSV &hsv, struct RGB &rgb )
{
    double hh, p, q, t, ff;
    long i;
    RGB out;   

    if (hsv.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = hsv.v;
        out.g = hsv.v;
        out.b = hsv.v;
        rgb = out;
    }
    hh = hsv.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = 255 * hsv.v * (1.0 - hsv.s / 100) / 100;
    q = 255 * hsv.v * (1.0 - (hsv.s / 100 * ff)) / 100;
    t = 255 * hsv.v * (1.0 - (hsv.s / 100 * (1.0 - ff))) / 100;

    switch (i) {
        case 0:
            out.r = 255 * hsv.v / 100;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = 255 * hsv.v / 100;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = 255 * hsv.v / 100;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = 255 * hsv.v / 100;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = 255 * hsv.v / 100;
            break;
        case 5:
        default:
            out.r = 255 * hsv.v / 100;
            out.g = p;
            out.b = q;
            break;
    }
    rgb = out;
}

HSV RandomAS::GetColorStep() const
{
    HSV hsv;
    hsv.h = GetRandomNumber( 50 ) + 30;
    hsv.s = GetRandomNumber( 40 ) + 10;
    hsv.v = GetRandomNumber( 40 ) + 10;
    return hsv;
}

Color RandomAS::GetRandomColor( const Color& color_)
{
    RGB rgb = { color_.GetR(), color_.GetG(), color_.GetB() };

    HSV hsv = { 0, 0, 0 };
    rgb2hsv( rgb, hsv );

    HSV delta_hsv = GetColorStep();
    hsv.h += delta_hsv.h;
    hsv.v += delta_hsv.v;
    hsv.s += delta_hsv.s;

    hsv2rgb( hsv, rgb );

    return Color( rgb.r, rgb.g, rgb.b );
};
   


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
