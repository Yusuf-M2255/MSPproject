# include <iostream>
using namespace std;

const long long mod = 1e9 +7;

int main()
{
    char a , b;
    cin >> a >> b;

    long long cap_a = 1 , cap_b = 1;

    for (int i = 1; i <= a ; i++)
    {
        cap_a =((cap_a % mod) *(i % mod)) % mod;
    }
    
    for (int i = 1; i <= b; i++)
    {
        cap_b =((cap_b % mod)*(i % mod)) % mod;
    }

    cout << (cap_b - cap_a + mod) % mod;
}