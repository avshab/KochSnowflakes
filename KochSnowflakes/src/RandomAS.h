#pragma once


class RandomAS 
{
public:

    RandomAS();

    bool GetRandomAS( int current, int num, double w );

    int GetRandomNumber() const;

private:

    double min_val;

    double max_val;

};