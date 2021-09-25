#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N,M;
int num[(int)1e5+10];
int arr[(int)4e5+10];

//1,n,1
//build segtree, l,r belongs to arr[v]
void build(int l, int r, int v){
    if(l==r){
        arr[v] = num[l];
    }
    else{
        int m = (l+r)/2;
        build(l,m,v*2);
        build(m+1,r,v*2+1);
        arr[v] = min(arr[v*2],arr[v*2+1]);
    }
}
//update segtree node
void update(int l, int r, int v, int idx, int val){
    if(l==r){
        arr[v] = val;
    } else{
        int m = (l+r)/2;
        if(idx<=m) update(l,m,2*v,idx,val);
        else update(m+1,r,2*v+1,idx,val);
        arr[v] = min(arr[v*2],arr[v*2+1]);
    }
}
//return tl,tr query
int query(int l, int r, int tl, int tr, int v){
    if(tl<=l && r<=tr){
        return arr[v];
    }
    if(tl>tr){
        return INT_MAX;
    }
    int m = (l+r)/2;
    return min(query(l,m,tl,min(m,tr), v*2),query(m+1,r,max(tl,m+1),tr,v*2+1));
}


int main() {
    //cin.sync_with_stdio(0);
    //cin.tie(0);
    cin>>N>>M;

    for(int i = 1; i<=N; i++){
        cin >> num[i];
    }
    build(1,N,1);
    for(int i = 0,j,k; i<M; i++){
        char c;
        cin>>c;
        cin>>j>>k;
        if(c=='Q'){
            cout<<query(1,N,j+1,k+1,1)<<"\n";
        }
        if(c=='M'){
            update(1,N,1,j+1,k);
        }
    }

    return 0;
}
