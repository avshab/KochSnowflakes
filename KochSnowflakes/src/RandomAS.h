 #pragma once

struct HSV {
    float h;
    float s;
    float v;
};


class RandomAS 
{
public:

    RandomAS();

    bool IsDivideRandom( int current, int num, double w );

    int GetRandomNumber( int base ) const;

    int* GetRandomNumbers( int num, int w );

    Color GetRandomColor( const Color& color_, int iter_num, int elem_num );

    Color GetBaseColor() const;

private:

    HSV GetColorStep( int iter_num, int elem_num ) const;

private:

    double min_val;

    double max_val;

    int num_iter;

};