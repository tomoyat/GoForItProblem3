/*
  LICENSE : BSDlicense
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

bool serchWord(int spos, int skip,string &str,string &tar){
  for(int p = spos, idx = 0; p < str.size() && idx < tar.size(); p += skip, idx++){
    if( str[p] != tar[idx] )return false;
    if( idx == tar.size() - 1 )return true;
  }
  return false;
}

int main(int argc, char *argv[]){
  if( argc != 2 ){ return 0; }
  string str; //入力文字列
  cin >> str;
  string tar = argv[1]; //キーワード
  string rtar = tar; // キーワードを反転させたもの
  reverse(rtar.begin(), rtar.end());

  set< pair<int,int> > ans;
  
  for(int i = 0; i < str.size(); i++){
    // 入力のi番目がキーワードの最初の文字と同じかどうか
    if( str[i] != tar[0] && str[i] != rtar[0] )continue;

    for(int j = 1; i + j < str.size(); j++){
      // iからjスキップさせる場合をしらべる
      if( !serchWord(i,j,str,tar) && !serchWord(i,j,str,rtar) )continue;
      ans.insert( make_pair(j,i+1) );
    }
  }

  for(set< pair<int,int> >::iterator it = ans.begin(); it != ans.end(); it++){
    cout << it->first << " , " << it->second << endl;
  }
  return 0;
}
