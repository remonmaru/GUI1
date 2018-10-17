//-----------------------------------------------------
//製作日:10/13
//製作者:M.Tomoki
//内容:最悪の最良 (２手)
//-----------------------------------------------------
//-----------------------------------------------------

//コメント/////////////////////////////////////////////
///////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////

//ヘッダインクルード///////////////////////////////////
///////////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;
///////////////////////////////////////////////////////

//キーワード///////////////////////////////////////////
///////////////////////////////////////////////////////
typedef long long ll;
typedef pair<int, int> pii;
#define FOR(i,a,b)   for(ll i = (a); i < (b); i++ )
#define REP(i, n)    FOR(i,0,n)
const ll mod = 1000000007;
const ll inf = 1000000100;
const int debug = 0;
///////////////////////////////////////////////////////

//プロトタイプ宣言/////////////////////////////////////
///////////////////////////////////////////////////////
inline bool check(int cur_col, pii cur_p, int mov_info);
pair<int, pii> solve(int turn, pii mov_red);
int scoring();
int B_dfs( int x, int y, int sum );
int R_dfs( int x, int y, int sum );
///////////////////////////////////////////////////////

//グローバル変数///////////////////////////////////////
///////////////////////////////////////////////////////
int H, W;//盤面の縦と横
bool fR[15][15];//訪問フラグ
bool fB[15][15];//訪問フラグ
int dx[] = { 0, 1, 0, -1, -1, 1, 1, -1 };//8近傍x移動
int dy[] = { -1, 0, 1, 0, -1, -1, 1, 1 };//8近傍y移動
int grand_point[15][15];//盤面の数字
string grand_color[15][15];//盤面の色
pii player_p[2][2]; // [i][j]: 赤(i=0), 青(i=1)チームそれぞれの駒([j])の座標(y,x) 0-indexed
string color[3] = { "R", "B", "W" };
///////////////////////////////////////////////////////

//メイン関数///////////////////////////////////////////
///////////////////////////////////////////////////////
int main(){
    
    // †高速化†
    cin.tie(0);
    ios::sync_with_stdio(false);
    ///
    
    // 入力パート (位置情報は赤色, 青色の順の入力とした。)
    cin >> H >> W;
    REP(i, H) REP(j, W) cin >> grand_point[i][j];
    REP(i, H) REP(j, W) cin >> grand_color[i][j];
    REP(i, 4) cin >> player_p[i/2][i%2].second >> player_p[i/2][i%2].first;
    if( debug ) cout << "入力完了" <<endl;
    ///
    
    pair<int, pii> ans = solve(0, pii(-1, -1));
    
    if( debug ) cout << "2ターン後で最大の得点 : " << ans.first << endl;
    
    string str[2];
    str[0] = to_string(ans.second.first % 8);
    if (ans.second.first >= 8 && debug ) str[0] += "B";
    
    str[1] = to_string(ans.second.second % 8);
    if (ans.second.second >= 8 && debug ) str[0] += "B";
    
    
    if( debug )cout << "そのときの移動方法 : ";
    cout << str[0] << " " << str[1] << endl;
    
    
    if (debug) {
        cout << "現在の得点(赤ポイント-青ポイント) : ";
        cout << scoring() << endl;
    }
    
    return 0;
}
///////////////////////////////////////////////////////

//関数/////////////////////////////////////////////////
///////////////////////////////////////////////////////

// 意味のある行動かどうかの判定
inline bool check(int cur_col, pii cur_p, int mov_info) {
    int ny = cur_p.first + dy[mov_info%8], nx = cur_p.second + dx[mov_info%8];
    string col = cur_col == 0 ? "R" : "B";
    string col_s = cur_col == 1 ? "R" : "B";
    
    if (!(nx >= 0 && nx < W && ny >= 0 && ny < H)) return false;
    
    if (mov_info < 8) {
        if (grand_color[ny][nx] == col_s) return false;
        
    }
    else {
        if (grand_color[ny][nx] == col) {
            if (grand_point[ny][nx] >= 0) return false;
        }
        else if( grand_color[ny][nx] == "W" ){
            return false;
        }
    }
    return true;
}

pair<int, pii> solve(int turn, pii mov_red) {
    vector<pair<int, string> > change_log; // 盤面変更前の情報 (y*100+x, 色)
    pii prev_player_p[2][2]; // 移動前のプレイヤーの位置
    REP(i, 2) REP(j, 2) prev_player_p[i][j] = player_p[i][j];
    
    int cur_col = turn & 1; // 現在のプレイヤーの色
    pair<int, pii> res = make_pair(-inf, pii(-1, -1));
    
    // 行動のパターンをすべて試す。
    pii mov_pat; // 2駒の行動パターン
    for (mov_pat.first = 0; mov_pat.first < 16; mov_pat.first++) {
        if (!check(cur_col, player_p[cur_col][0], mov_pat.first)) continue;
        for (mov_pat.second = 0; mov_pat.second < 16; mov_pat.second++) {
            if (!check(cur_col, player_p[cur_col][1], mov_pat.second)) continue;
            
            // 行動処理
            if (cur_col == 1) {
                // mov_red : 赤駒の動き
                // mov_pat : 青駒の動き
                bool imp_flag[2][2] = {}; // 行動が不可能であるかのフラグ
                pii tar_p[2][2]; // 行動の対象マス
                int mov_inf[2][2]; // 移動情報のまとめ
                
                mov_inf[0][0] = mov_red.first;
                mov_inf[0][1] = mov_red.second;
                mov_inf[1][0] = mov_pat.first;
                mov_inf[1][1] = mov_pat.second;
                
                // 衝突判定
                REP(i, 2) REP(j, 2) tar_p[i][j] = pii(player_p[i][j].first + dy[mov_inf[i][j]%8], player_p[i][j].second + dx[mov_inf[i][j]%8]);
                
                REP(i, 4) FOR(j, i + 1, 4) {
                    if (tar_p[i/2][i%2] == tar_p[j/2][j%2]) {
                        imp_flag[i/2][i%2] = imp_flag[j/2][j%2] = true;
                    }
                }
                
                // 行動
                REP(i, 2) REP(j, 2) if (!imp_flag[i][j]) {
                    if (mov_inf[i][j] < 8) {
                        player_p[i][j] = tar_p[i][j];
                    }
                    int ny = tar_p[i][j].first, nx = tar_p[i][j].second;
                    change_log.push_back(make_pair(ny*100 + nx, grand_color[ny][nx]));
                    grand_color[ny][nx] = grand_color[ny][nx] == "W" ? (i == 0 ? "R" : "B") : "W";
                }
                
            }
            
            int cur_score; // これから得られる最大得点
            if (turn != 3) cur_score = -solve(turn + 1, mov_pat).first;
            else cur_score = -scoring();
            
            if (res.first < cur_score) {
                res = make_pair(cur_score, mov_pat);
            }
            
            // 復元
            REP(i, change_log.size()) {
                pair<int, string>& cur = change_log[i];
                int ny = cur.first / 100;
                int nx = cur.first % 100;
                grand_color[ny][nx] = cur.second;
            }
            change_log.clear();
            REP(i, 2) REP(j, 2) player_p[i][j] = prev_player_p[i][j];
            
        }
    }
    
    return res;
}

//得点計算プログラム
int scoring(){
    //得点の初期化
    int R_point = 0;
    int B_point = 0;
    int temp;
    
    REP( i, H ){
        REP( j, W ){
            //i行目j列目の要素をfalseで初期化
            fR[i][j] = false;
            fB[i][j] = false;
        }
    }
    
    REP( i, H ){
        REP( j, W ){
            //i行目j列目の要素が'R'なら盤面の点数を加算
            if( grand_color[i][j] == "R" ) R_point += grand_point[i][j];
            //i行目j列目の要素が'B'なら盤面の点数を加算
            if( grand_color[i][j] == "B" ) B_point += grand_point[i][j];
        }
    }
    
    //深さ優先探索で領域ポイントを計算
    REP( i, H ){
        REP( j, W ){
            temp = R_dfs( j, i, 0 );
            if( temp != -1 ) R_point += temp;
            temp = B_dfs( j, i, 0 );
            if( temp != -1 ) B_point += temp;
        }
    }
    
    if( debug ) cout<<R_point-B_point<<endl;
    return R_point-B_point;
}


//赤さんの領域ポイントについて深さ優先探索
int R_dfs( int x, int y, int sum ){
    //自分の色は領域ポイントにならない
    if( grand_color[y][x] == "R" ) return sum;
    //盤面の端の辺なら領域ポイントは0となる
    if( y == 0 || y == H-1 || x == 0 || x == W-1 ) return -1;
    //一度訪問した場所は探索しない
    if( fR[y][x] ) return sum;
    //訪問フラグを接地
    fR[y][x] = true;
    //4近傍に掘り下げる
    REP( i, 4 ) sum = R_dfs( x+dx[i], y+dy[i], sum );
    //盤面の点数を加算
    if( sum != -1 ) sum += abs(grand_point[y][x]);
    return sum;
}
//青さんの領域ポイントについて深さ優先探索
int B_dfs( int x, int y, int sum ){
    //自分の色は領域ポイントにならない
    if( grand_color[y][x] == "B" ) return sum;
    //盤面の端の辺なら領域ポイントは0となる
    if( y == 0 || y == H-1 || x == 0 || x == W-1 ) return -1;
    //一度訪問した場所は探索しない
    if( fB[y][x] ) return sum;
    //訪問フラグを接地
    fB[y][x] = true;
    //4近傍に掘り下げる
    REP( i, 4 ) sum = B_dfs( x+dx[i], y+dy[i], sum );
    //盤面の点数を加算
    if( sum != -1 ) sum += abs(grand_point[y][x]);
    return sum;
}
///////////////////////////////////////////////////////
