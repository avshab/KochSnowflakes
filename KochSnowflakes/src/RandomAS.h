 #pragma once


class RandomAS 
{
public:

    RandomAS();

    bool IsDivideRandom( int current, int num, double w );

    int GetRandomNumber( int base ) const;

    int* GetRandomNumbers( int num, int w );

    Color GetRandomColor();

private:

    double min_val;

    double max_val;

    int num_iter;

};