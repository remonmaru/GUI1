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

int p[2];
///////////////////////////////////////////////////////

//メイン関数///////////////////////////////////////////
///////////////////////////////////////////////////////
int main(){
    
    cin >> p[0] >> p[1];
    
    REP( i, 2 ){
    		if( p[i] == 0 ) puts("上");
    		if( p[i] == 1 ) puts("右");
    		if( p[i] == 2 ) puts("下");
    		if( p[i] == 3 ) puts("左");
    		if( p[i] == 4 ) puts("左上");
    		if( p[i] == 5 ) puts("右上");
    		if( p[i] == 6 ) puts("右下");
    		if( p[i] == 7 ) puts("左下");
    }
}

///////////////////////////////////////////////////////

//関数/////////////////////////////////////////////////
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
