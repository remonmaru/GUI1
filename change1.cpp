//-----------------------------------------------------
//製作日:10/13
//製作者:N.Shun
//内容:盤面変換1
//-----------------------------------------------------
//-----------------------------------------------------

//コメント/////////////////////////////////////////////
///////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////

//ヘッダインクルード///////////////////////////////////////
///////////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;
///////////////////////////////////////////////////////

//キーワード///////////////////////////////////////////
///////////////////////////////////////////////////////

#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
typedef long long ll;

///////////////////////////////////////////////////////

//プロトタイプ宣言/////////////////////////////////////
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////

//グローバル変数///////////////////////////////////////
///////////////////////////////////////////////////////

string s;
///////////////////////////////////////////////////////

//メイン関数///////////////////////////////////////////
///////////////////////////////////////////////////////
int main(){
    
    getline(cin, s);
    
    REP( i, s.size() ){
        if( s[i] == ':') s[i] = '\n';
    }
    
    cout << s << endl;
    
    return 0;
}

///////////////////////////////////////////////////////

//関数/////////////////////////////////////////////////
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
