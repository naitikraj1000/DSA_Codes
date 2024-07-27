#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

#define pb push_back
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define ll long long
const int mod = int(1e9 + 7);
// Binary Exponentiation
// Divide and Conquer (Recursion Power Divide)
// Iterative (Binary Representation)
int binExpIter(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = (ans * 1ll * a) % mod;
        }
        a = (a * 1ll * a) % mod;
        b >>= 1; // b/2;
    }
    return ans;
}
int modular_inverse(int a)
{
    return binExpIter(a, mod - 2);
}
int modular_division(int a, int inverse)
{
    // a *(b^-1)
    return (a * 1ll * modular_inverse(inverse)) % mod;
}

int main()
{
    fast int t;
    cin >> t;
    while (t--)
    {
       
    }
    return 0;
}
