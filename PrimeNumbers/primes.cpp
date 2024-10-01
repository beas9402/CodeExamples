#include <vector>
#include <iostream>
#include <array>

using namespace std;


class Primes
{
public:
    std::vector<int> _known;
    Primes()
    {
        _known.push_back(2);
        findupto(100);

    }
    void findupto(int upto)
    {
        for (int candidate = _known.front() + 1; candidate < upto; candidate++)
        {
            bool isPrime = true;
            for (auto itr = _known.begin(); itr != _known.end(); itr++)
            {
                int prime = *itr;
                int fraction = candidate / prime;
                if (fraction * prime == candidate)
                {
                    isPrime = false;
                }
            }
            if (isPrime)
            {
                _known.push_back(candidate);
            }
        }
    }

    bool isPrime(int x)
    {
        if (x > _known.back())
        {
            findupto(x);
        }
        
        return std::find(_known.begin(), _known.end(), x) != _known.end();
    }
    int& getElement(int index)
    {
        return _known.at(index);
    };
};