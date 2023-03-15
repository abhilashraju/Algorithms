#include<string>
#include<iostream>
#include<algorithm>
#include"profiler.h"
#include"verify.h"
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:

    auto collapsed(string_view p,string_view c){
        unordered_map<char,int> m;
        auto iter = find_if(begin(p),end(p),[&](auto v){
            m[v]++;
            return find(begin(c),end(c),v)==end(c);
        });
        return pair{m['?'],distance(begin(p),iter)};
    }
    struct Myhash
    {
        auto operator()( const pair<int,int>& p)const{
            return p.first ^ p.second;
        }
    };
//      using CACHE = unordered_map<pair<int,int>,bool,Myhash>;

    struct CACHE{
       vector<vector<int>> table;
       CACHE(size_t row,size_t col):table(row,vector<int>(col,-1)){

       }
       auto end(){
           return table[0].end();
       }
       auto find(const pair<int,int>& p){
           return table[p.first][p.second]== -1 ? table[0].end():table[p.first].begin()+p.second;
       }
       auto& operator[](const pair<int,int>& p){
           return table[p.first][p.second];
       }
    };
      auto handlesinglereplacer(string_view s,string_view p, int srcindex,int patternindex, CACHE& cache)
      {

          return cache[{srcindex,patternindex}]=s.length()?isMatchDP(s.substr(1),p.substr(1),srcindex+1,patternindex+1,cache):false;
      }
      auto handleWildchar(string_view s,string_view p, int srcindex,int patternindex, CACHE& cache){
          if(p.length()==1){
              return cache[{srcindex,patternindex}]=true;
          }
          auto [chartoskip,nextcharindex]=collapsed(p,"*?");
          if(nextcharindex>=p.length()){
              return cache[{srcindex,patternindex}]=chartoskip <= s.length();
          }
          auto c=p[nextcharindex];
          auto iter = find(s.begin(),s.end(),c);
          auto dist=distance(s.begin(),iter);
          while(iter != end(s) && chartoskip>dist){
              iter = find(iter+1,s.end(),c);
              dist=distance(s.begin(),iter);
          }
          while(iter != s.end()){

              auto result=isMatchDP(s.substr(dist),p.substr(nextcharindex),srcindex+dist,patternindex+nextcharindex,cache);
              if(result){
                  return cache[{srcindex,patternindex}]=result;

              }
              iter = find(iter+1,s.end(),c);
              dist=distance(s.begin(),iter);
          }
          return cache[{srcindex,patternindex}]=false;
      }

      bool isMatchDP(string_view s , string_view p,int srcindex,int patternindex,CACHE& cache)
      {
          if(p.length()==0 && s.length()>0){
              return false;
          }
          if(p.length()==0 && s.length()==0){
              return true;
          }
          if(cache.find({srcindex,patternindex})!=end(cache)){
              return cache[{srcindex,patternindex}];
          }

          if(p[0]=='*'){
              return handleWildchar(s,p,srcindex,patternindex,cache);
          }
          if(p[0]=='?'){
              return handlesinglereplacer(s,p,srcindex,patternindex,cache);
          }
          if(p[0]==s[0]){
              return cache[{srcindex,patternindex}]=isMatchDP(s.substr(1),p.substr(1),srcindex+1,patternindex+1,cache);
          }
          return cache[{srcindex,patternindex}]=false;
      }
      bool isMatch(string s,string p)
      {
          CACHE cache(s.length()+1,p.length()+1);
          return isMatchDP(s,p,0,0,cache);
      }
};

int main()
{
    auto print=[](auto s,auto p){
        cout<<" Source = "<< s <<" ";
        cout<< " Pattern = "<<p<<" ";
        bool b=Solution().isMatch(s,p);
        cout<<" Result = "<<(b? "true":"false");
        cout<<"\n";
        return b;
    };
    verify(print("aa","a")==false);
    verify(print("aa", "*")==true);
    verify(print("cb","?a")==false);
    verify(print("cb","?b")==true);
    verify(print("cba","?b*")==true);
    verify(print("abhilash","abhila*")==true);
    verify(print("abhilash","a?????sh")==true);
    verify(print("abhilash","a*sh")==true);
    verify(print("acdcb","a*c?b")==false);
    verify(print("acdcb","a*c*b")==true);;
    verify(print("acdcb","a*c??b")==true);
    verify(print("acdcb","a*cb")==true);
    verify(print("","******")==true);
    verify(print("","?")==false);
    verify(print("a","?")==true);
    verify(print("a","")==false);
    verify(print("","")==true);
    verify(print("bcd","??")==false);
    verify(print("c","*?*")==true);
    verify(print("mississippi","m??*ss*?i*pi")==false);
    verify(print("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
                 "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb")==false);
    verify(print("b","?*?")==false);
    verify(print("b","??*")==false);
    verify(print("b","?*")==true);
    verify(print("b","*?")==true);
    verify(print("bbbab","*??a?")==true);
    verify(print("abaa","*?*a")==true);


}
