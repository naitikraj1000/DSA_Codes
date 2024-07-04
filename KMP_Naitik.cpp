// Description: String Matching Algorithm
// Author: Naitik Raj
#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<int> lps;

void computeLPS(string p)
{

    // lps[i]=(length of the longest proper prefix which is also a suffix of the string p[0...i])
    // proper means prefix should not be equal to the string itself or empty string
    // suffix means suffix should not be equal to the string itself or empty string
    // that's why lps[0]=0

    // AAA -> lps in this case is 2 prefix=(0..1) and suffix=(1..2)
    // not 3 as AAA is not a proper prefix or suffix

    // in simple terms at least one charcter index should be different in both prefix and suffix
    int n = p.size();
    lps.resize(n);

    lps[0] = 0;

    for (int i = 1; i < n; i++)
    {
        int len = lps[i - 1];

        while (p[len] != p[i] && len > 0)
        {
            len = lps[len - 1];
        }

        if (p[len] == p[i])
        {
            lps[i] = len + 1;
        }
        else
        {
            lps[i] = 0;
        }
    }
}

int KMP(string s, string p)
{
    int n = s.size();
    int m = p.size();

    int ans = 0;
    int i = 0, j = 0;

    while (i < n)
    {
        if (s[i] == p[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            ans++;
            j = lps[j - 1];
        }
        else if (i < n && s[i] != p[j])
        {

            if (j!= 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return ans;
}
int main()
{
    string s;
    cin >> s;
    string p;
    cin >> p;

    computeLPS(p);

    cout << KMP(s, p) << "\n";

    // for(auto x:lps)
    // {
    //     cout<<x<<" ";
    // }
    // cout<<"\n";
}

// AABCABCD
// AABCAABCD
