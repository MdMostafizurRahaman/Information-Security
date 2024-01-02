#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<int>v;
    for(int i = 0; i < t; i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    int q;
    cin >> q;
    while (q--){
        int n;
        cin >> n;
        int c = 0;
        
        auto z = lower_bound(v.begin(), v.end(), n);
        
        if(v[z-v.begin()]==n){
            cout << "Yes " << (z-v.begin()) + 1 << endl;
        }
        else{
            cout << "No " << (z-v.begin()) + 1<< endl;
        }
    }
}