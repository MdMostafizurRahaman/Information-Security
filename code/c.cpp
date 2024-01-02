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
        for(int  i = 0; i < n; i++){
            if(v[i] == n){
                cout << "Yes " << i + 1 << endl;
                if(v[i] == v[i + 1]){
                    i += 2;
                }
            }
            else if(v[i] < n && n < v[i + 1]){
                cout << "No " << i + 2 << endl;
                if( i == n - 1){
                    break;
                }
            }
        }
    }
}