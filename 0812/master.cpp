#include <bits/stdc++.h>
#define st first
#define nd second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vii;
typedef vector<ll> vll;

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

void fastio(){ cin.sync_with_stdio(0); cin.tie(0); cout.tie(0); }

vii V;
int ans = 0;

bool chk(){
    for(int i : V) if(i != 0) return true;
    return false;
}

void subtract(){
    for(int &i : V) if(i%2 == 1){
        ans++;
        i--;
    }
}

void divide(){
    for(int &i : V) i /= 2;
    ans++;
}


int main(){
    fastio();
    int N; cin >> N;
    for(int i=0; i<N; i++){
        int k; cin >> k;
        V.push_back(k);
    }

    while(true){
        subtract();
        if(!chk()) break;
        divide();
    }

    cout << ans;
    return 0;
}