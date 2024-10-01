#include <iostream>
#include "primes.cpp"
using namespace std;

int main()
{
    Primes x;

    cout << 17 << " isPrime " << x.isPrime(17) << endl;
    cout << 1500 << " isPrime " << x.isPrime(1500) << endl;


    for (auto i = x._known.begin(); i != x._known.end(); i++)
    {
        cout << *i << endl;
    }
}
    