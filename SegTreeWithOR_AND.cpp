#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
const int INF = (1LL << 60) - 1;

struct SegmentTree
{
    int n;
    vector<int> st, lazy;
    bool isOR;

    void init(int _n, bool _isOR)
    {
        n = _n;
        isOR = _isOR;
        st.resize(4 * n, isOR ? 0 : INF);
        lazy.resize(4 * n, isOR ? 0 : INF);
    }

    void push(int node, int start, int end)
    {
        if (isOR ? lazy[node] != 0 : lazy[node] != INF)
        {
            st[node] = isOR ? (st[node] | lazy[node]) : (st[node] & lazy[node]);
            if (start != end)
            {
                lazy[2 * node + 1] = isOR ? (lazy[2 * node + 1] | lazy[node]) : (lazy[2 * node + 1] & lazy[node]);
                lazy[2 * node + 2] = isOR ? (lazy[2 * node + 2] | lazy[node]) : (lazy[2 * node + 2] & lazy[node]);
            }
            lazy[node] = isOR ? 0 : INF;
        }
    }

    void update(int node, int start, int end, int l, int r, int val)
    {
        push(node, start, end);
        if (start > r || end < l)
            return;
        if (l <= start && end <= r)
        {
            lazy[node] = isOR ? (lazy[node] | val) : (lazy[node] & val);
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node + 1, start, mid, l, r, val);
        update(2 * node + 2, mid + 1, end, l, r, val);
        st[node] = isOR ? (st[2 * node + 1] | st[2 * node + 2]) : (st[2 * node + 1] & st[2 * node + 2]);
    }

    int query(int node, int start, int end, int l, int r)
    {
        push(node, start, end);
        if (start > r || end < l)
            return isOR ? 0 : INF;
        if (l <= start && end <= r)
            return st[node];
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r);
        int right = query(2 * node + 2, mid + 1, end, l, r);
        return isOR ? (left | right) : (left & right);
    }

    void update(int l, int r, int val)
    {
        update(0, 0, n - 1, l, r, val);
    }

    int query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }

    vector<int> getArray()
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = query(i, i);
        }
        return arr;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    SegmentTree orTree, andTree;
    orTree.init(n, true); // OR tree

    vector<vector<int>> queries;
    for (int i = 0; i < q; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--; // 0-based indexing
        queries.push_back({l, r, x});
        orTree.update(l, r, x);
    }

    // Construct the array from OR tree
    vector<int> arr = orTree.getArray();

    // Build AND tree with the constructed array
    andTree.init(n, false); // AND tree
    for (int i = 0; i < n; i++)
    {
        andTree.update(i, i, arr[i]);
    }

    bool possible = true;
    for (int i = 0; i < queries.size(); i++)
    {
        int l = queries[i][0], r = queries[i][1], x = queries[i][2];
        if (andTree.query(l, r) != x)
        {
            possible = false;
            break;
        }
    }

    if (!possible)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
