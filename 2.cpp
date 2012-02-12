/*
  LICENSE : BSDlicense
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <vector>

using namespace std;

void serchWord(const vector< vector<int> > &table,
	       const vector<int> &tar, set< pair<int,int> > &ans,int strsize){

  for(int i=0; i<table[tar[0]].size(); i++){
    // キーワードの１文字目よりも後にある２文字目のアルファベットの位置を調べる
    int j = upper_bound(table[tar[1]].begin(), table[tar[1]].end(), table[tar[0]][i]) - table[tar[1]].begin();
    for(; j < table[tar[1]].size(); j++){
      int skip = table[tar[1]][j] - table[tar[0]][i];
      int pos = table[tar[0]][i];
      bool flg = true;
      // キーワードの最後までスキップしたら入力より大きくなるか調べる
      if( pos + skip*((int)tar.size() - 1) >= strsize )break;
      for(int k=0; k<tar.size(); k++){
	// スキップした位置に次のキーワードの文字があるか調べる
	if( !binary_search(table[tar[k]].begin(),table[tar[k]].end(), pos )){
	  flg = false; break;
	}
	pos += skip;
      }
      if( flg ){ ans.insert( make_pair(skip, table[tar[0]][i]) ); }
    }
  }
  return;
}

int main(int argc, char *argv[]){

  if( argc != 2 ){ return 0; }
  string str; 
  cin >> str;
  string tar = argv[1];
  string rtar = tar;
  reverse(rtar.begin(), rtar.end());

  vector<int> tarNum, rtarNum;
  for(int i=0; i<tar.size(); i++){
    tarNum.push_back(tar[i] - 'a');
    rtarNum.push_back(rtar[i] - 'a');
  }

  vector< vector<int> > table(26,vector<int>(0));
  for(int i=0; i<26; i++)table[i].reserve(str.size() / 26);

  for(int i=0; i<str.size(); i++){
    int idx = str[i] - 'a'; if( idx < 0 || 25 < idx )return 0;
    table[idx].push_back(i+1);
  }

  for(int i=0; i<table.size(); i++){
    sort(table[i].begin(), table[i].end());
  }

  set< pair<int,int> > ans;
  serchWord(table,tarNum,ans,str.size());
  serchWord(table,rtarNum,ans,str.size());
  
  for(set< pair<int,int> >::iterator it = ans.begin(); it != ans.end(); it++){
    cout << it->first << " , " << it->second << endl;
  }
  return 0;
}
