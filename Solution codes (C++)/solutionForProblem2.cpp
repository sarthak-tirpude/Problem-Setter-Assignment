#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<iostream>
#include<chrono>
#include<array>
#include<ctime>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<map>
#include<stack>
#include<numeric>
#include<functional>
#include<tuple>
#include<vector>
#include<string>
#include<set>
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<list>
#include<climits> 
#include<stdlib.h>
#include<iomanip> 
#include<fstream>
#include<sstream>
#include<queue>
#include<bitset>
#include<cstdlib>
#include <chrono>
 
using namespace std;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
}; 
 
void __print(int x) {cout << x;}
void __print(long x) {cout << x;}
void __print(long long x) {cout << x;}
void __print(unsigned x) {cout << x;}
void __print(unsigned long x) {cout << x;}
void __print(unsigned long long x) {cout << x;}
void __print(float x) {cout << x;}
void __print(double x) {cout << x;}
void __print(long double x) {cout << x;}
void __print(char x) {cout << '\'' << x << '\'';}
void __print(const char *x) {cout << '\"' << x << '\"';}
void __print(const string &x) {cout << '\"' << x << '\"';}
void __print(bool x) {cout << (x ? "true" : "false");}
 
template <typename T, typename V>
void __print(const pair<T, V> &x);
template <typename T>
void __print(const vector<T> &x);
template<typename T>
void __print(const T &x);
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cout << '{'; __print(x.first); cout << ','; __print(x.second); cout << "}";}
template<typename T, typename V, typename U>
void __print(const tuple<T, V, U> &x) {cout << '{'; __print(get<0>(x)); cout << ','; __print(get<1>(x));cout << ',' << get<2>(x); cout << "}";}
template<typename T>
void __print(vector<T> &x) {cout << "{";for(int u69=0;u69<x.size();u69++){__print(x[u69]);cout << (u69+1==x.size()?"":",");};cout << "}";}
template<typename T>
void __print(const T &x) {int f = 0; cout << '{'; for (auto &i: x) cout << (f++ ? "," : ""), __print(i); cout << "}";}
void _print() {cout << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cout << ","; _print(v...);}
 
#define int long long int
 
#define rev(s) reverse(all(s))
#define all(n) n.begin(),n.end()
#define rep(i,a,n) for(int i=a;i<n;++i)
#define fr(n) for(int i=0;i<n;++i)
 
 
#define mii map<int,int>
#define ms multiset<int>
#define double long double
#define endl "\n"
#define vvi vector<vector<int>>
#define vvc vector<vector<char>>
#define vvb vector<vector<bool>>
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define pb push_back 
#define each(seq) for(auto &e: seq)
#define sz(a) (int)a.size()
#define inf 1e18
#define umii unordered_map<int,int>
#define debug(x...) cout << "[" << #x << "] = ["; _print(x)          
#define ff first
#define ss second
#define pii pair<int,int>
#define yes cout<<"YES\n";
#define no cout<<"NO\n";
 
int mod=(int)(1000000007);
 
int gcd(int a, int b){  
    if(a<b) swap(a,b);
    return b == 0 ? a : gcd(b, a % b);   
}
int lcm(int a,int b){ return (a*b)/gcd(a,b); } 
int ceil(int a,int b){ return (a+b-1)/b; }
int binary_exponentiation(int a,int b){
    a%=mod;
    int result = 1,base = a, exp = b;
    while (exp > 0) {
        if (exp & 1){
            result = result * base;
            result %= mod;
        }
        base = base * base;
        base %= mod;
        exp >>= 1;
    }
    return result%mod;
}
int modularInv(int a){
    return binary_exponentiation(a,mod-2);
}
int binary_exponentiation_wm(int a,int b){
    int result = (int)1,base = a, exp = b;
    while (exp > 0) {
        if (exp & 1){
            result = result * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return result;
}


int getHash(int l,int r,vector<int> &hash){
    if(l>r) return 0ll;
    int ans = hash[r] % mod;
    if(l){
        ans = (ans % mod + mod - hash[l-1] % mod) % mod;
        ans = (ans % mod * modularInv(binary_exponentiation(31,l)) % mod) % mod;
    }
    return ans;
}
int solution(string input){
    int n = input.size();
    string cur;
    vector<int> hash(n);
    int hs = 0;
    int p_pow = 1ll;
    for(int i = 0;i < n; ++i){
        hs = (hs % mod + (input[i] - 'a' + 1ll)*p_pow % mod) % mod;
        hash[i] = hs;
        p_pow = (p_pow % mod * 31ll) % mod;
    }
    set<int> st;
    for(int i=0;i<n;++i){
        int prevHash = getHash(0,i-1,hash), nextHash = getHash(i+1,n-1,hash);
        nextHash = (nextHash * binary_exponentiation(31ll,i)) % mod;
        st.insert(prevHash + nextHash);
    }
    return st.size();
    
}
void solve(){
    

    string s;cin>>s;
    cout<<solution(s)<<endl;
    

    




    
    
    

}
int32_t main()
//int main()
{
 
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin) ;
        freopen("output.txt","w",stdout) ;
    #endif
 
    //makes interactive problems slower:
    ios_base::sync_with_stdio(0) ; 
    cin.tie(0) ; 
    cout.tie(0) ;

    int t = 1 ; 
    cin >> t ;

    int n=t;

    while ( t-- ) {   
        //cout<<"Case #"<<n-t<<": ";
        solve() ;   
    }

 
    return 0 ;
 
}