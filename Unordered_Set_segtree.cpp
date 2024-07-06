#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 1;

int color[MAXN], start[MAXN], finish[MAXN], euler[MAXN], timer = 0;
vector<int> adj[MAXN];

struct SegmentTree {
    vector<unordered_set<int>> tree;
    int n;

    SegmentTree(int size) : n(size) {
        tree.resize(4 * n);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node].insert(color[euler[start]]);
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node].insert(tree[2 * node].begin(), tree[2 * node].end());
            tree[node].insert(tree[2 * node + 1].begin(), tree[2 * node + 1].end());
        }
    }

    unordered_set<int> query(int node, int start, int end, int L, int R) {
        if (start > R || end < L) {
            return unordered_set<int>();
        }
        if (start >= L && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        auto left = query(2 * node, start, mid, L, R);
        auto right = query(2 * node + 1, mid + 1, end, L, R);
        unordered_set<int> result = left;
        result.insert(right.begin(), right.end());
        return result;
    }
};

void dfs(int u, int p) {
    start[u] = timer;
    euler[timer++] = u;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    finish[u] = timer - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, u, v;
    cin >> N;

    for (int i = 1; i <= N; ++i) {
        cin >> color[i];
    }

    for (int i = 0; i < N - 1; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);

    SegmentTree segTree(N);
    segTree.build(1, 0, N - 1);

    for (int i = 1; i <= N; ++i) {
        auto result = segTree.query(1, 0, N - 1, start[i], finish[i]);
        cout << result.size() << " ";
    }
    cout << endl;

    return 0;
}
