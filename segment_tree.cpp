#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct sweep_ops {
    ll pos, val; // x_axis, val
    ll lt, rt; // y_axis
    bool operator< (const sweep_ops& ca) {
        return pos < ca.pos;
    }
    sweep_ops():pos(0), val(0), lt(0), rt(0) {}
    sweep_ops(ll a, ll b, ll c, ll d):pos(a), val(b), lt(c), rt(d) {}
};

vector<sweep_ops> Sweep_ops;
vector<ll> y_seg;

class segment_tree {
public:
    struct node {
        ll cover; // total cover times
        ll weight; // if it cover > 0, return weight
        ll length; // else, return length
        ll lazy_tag;
        node(): cover(0), weight(0), length(0), lazy_tag(0) {}
    };

    segment_tree (ll seg_len) {
        _seg.assign(1 + (seg_len << 2), node());
        build(1, 1, seg_len);
    }

    void build(int id, int tl, int tr) {
        int mid = (tl + tr) >> 1;   // [l, mid] [mid+1, r]
        if (tl == tr) {
            _seg[id].weight = y_seg[tl] - y_seg[tl-1];
            return;
        }
        build(2*id, tl, mid);
        build(2*id+1, mid+1, tr);
        _seg[id].weight = _seg[2*id].weight + _seg[2*id+1].weight;
    }

    void push_down(int id) {
        ll x = _seg[id].lazy_tag;
        _seg[2*id].lazy_tag += x;
        _seg[2*id].cover += x;
        _seg[2*id+1].lazy_tag += x;
        _seg[2*id+1].cover += x;

        _seg[id].lazy_tag = 0;
    }

    void push_up(int id) {
        _seg[id].cover = min(_seg[2*id].cover, _seg[2*id+1].cover);
        ll tmp_len = 0;
        if (_seg[2*id].cover > _seg[id].cover)
            tmp_len += _seg[2*id].weight;
        else
            tmp_len += _seg[2*id].length;

        if (_seg[2*id+1].cover > _seg[id].cover)
            tmp_len += _seg[2*id+1].weight;
        else
            tmp_len += _seg[2*id+1].length;
        _seg[id].length = tmp_len;
    }

    void update (int id, int l, int r, int tl, int tr, ll val) {
        if (tl >= l && tr <= r) {
            _seg[id].cover += val;
            _seg[id].lazy_tag += val;
            return;
        }
        if (_seg[id].lazy_tag)
            push_down(id);

        int mid = (tl + tr) >> 1;   // [l, mid] [mid+1, r]
        if (mid >= l) {
            update(2*id, l, r, tl, mid, val);
        }

        if (mid + 1 <= r) {
            update(2*id+1, l, r, mid+1, tr, val);
        }

        push_up(id);
    }

    ll query() {
        if (_seg[1].cover)
            return _seg[1].weight;
        return _seg[1].length;
    }
private:
    vector<node> _seg;
};

void solve()
{
    int n;
    cin>> n;
    ll x1, y1, x2, y2;
    Sweep_ops.assign(2 * n, sweep_ops());
    y_seg.assign(2 * n, 0);
    for (int i = 0; i < n; i++) {
        cin>> x1>> y1>> x2>> y2;
        Sweep_ops[i] =  sweep_ops(x1, 1, y1, y2);
        Sweep_ops[i + n] =  sweep_ops(x2, -1, y1, y2);
        y_seg[i] = y1;
        y_seg[i + n] = y2;
    }
    sort(Sweep_ops.begin(), Sweep_ops.end());
    sort(y_seg.begin(), y_seg.end());
    y_seg.erase(unique(y_seg.begin(), y_seg.end()), y_seg.end());
    ll seg_leng = y_seg.size() - 1; // 对从 1 开始计数的线段创建线段树
    segment_tree seg(seg_leng);

    // actually begins here
    ll ans = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        int j = i;
        while (j < 2*n-1 && Sweep_ops[j+1].pos == Sweep_ops[j].pos)
            j++;
        if (j == 2 * n - 1)
            break;

        for (int k = i; k <= j; k++) {
            ll lt = lower_bound(y_seg.begin(), y_seg.end(), Sweep_ops[k].lt) - y_seg.begin() + 1;
            ll rt = lower_bound(y_seg.begin(), y_seg.end(), Sweep_ops[k].rt) - y_seg.begin();
            seg.update(1, lt, rt, 1, (int)seg_leng, Sweep_ops[k].val);
        }
        // here Sweep_ops[i].pos == Sweep_ops[j].pos
        i = j;
        ans += seg.query() * (Sweep_ops[i + 1].pos - Sweep_ops[i].pos);
    }
    cout<< ans<<endl;
}


int main()
{
    cin.sync_with_stdio(false);
    solve();
    return 0;
}
