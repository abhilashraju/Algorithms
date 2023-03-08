#include<string>
#include<iostream>
#include<unordered_map>
#include<chrono>
#include<vector>
#include <algorithm>
#include "profiler.h"
using namespace std;
using namespace chrono;


class Solution {
    class MyHashFunction {
    public:

        // Use sum of lengths of first and last names
        // as hash function.
        size_t operator()(const pair<int,int>& p) const
        {
            return p.first ^ p.second;
        }
    };

    struct PAIR:pair<size_t,size_t>{
        PAIR():pair(-1,-1){}
        PAIR(size_t f,size_t s):pair(f,s){}
    };
    struct CACHE{
       vector<vector<PAIR>> table;
       CACHE(size_t row,size_t col):table(row,vector<PAIR>(col,PAIR())){

       }
       auto end(){
           return table[0].end();
       }
       auto find(const PAIR& p){
           return table[p.first][p.second]==PAIR() ? table[0].end():table[p.first].begin()+p.second;
       }
       auto& operator[](const PAIR& p){
           return table[p.first][p.second];
       }
    };

    auto maxof(const PAIR& f, const PAIR& s){
        return (f.second-f.first) >( s.second-s.first) ? f:s;
    }
    PAIR longestPalindromeView(char* str,const PAIR& p,CACHE& cache){
        if(cache.find(p)!=end(cache)){
            return cache[p];
        }
        if(p.first == p.second){
            return p;
        }
        if(p.first+1 == p.second && str[p.first]==str[p.second]){
            return cache[p]=p;
        }

        if(str[p.first] == str[p.second]){
            auto subp= longestPalindromeView(str,{p.first+1,p.second-1},cache);
            if(subp.first==p.first+1 && subp.second == p.second-1){
                return cache[p]=p;
            }
        }

        auto longstr2=longestPalindromeView(str,{p.first+1,p.second},cache);
        auto longstr3=longestPalindromeView(str,{p.first,p.second-1},cache);
        return cache[p]=maxof(longstr2,longstr3);
    }
public:
    string longestPalindrome(string s) {
        CACHE cache(s.length(),s.length());
        auto palindrom = longestPalindromeView(s.data(),{0,s.length()-1},cache);
        return {s.data()+palindrom.first,palindrom.second-palindrom.first+1};
    }
};
#if 0
int main(){

    auto print = [](auto str){
        cout<<" Palindrom for " << str << " = " << Solution().longestPalindrome(str)<<"\n";
    };
    print("bab");
    print("babad");
    print("cbbd");
    print("c");
    print("amalayalamm");
    print("aacabdkacaa");
    {
    Profiler p("palindrom");
    print("wsgdzojcrxtfqcfkhhcuxxnbwtxzkkeunmpdsqfvgfjhusholnwrhmzexhfqppatkexuzdllrbaxygmovqwfvmmbvuuctcwxhrmepxmnxlxdkyzfsqypuroxdczuilbjypnirljxfgpuhhgusflhalorkcvqfknnkqyprxlwmakqszsdqnfovptsgbppvejvukbxaybccxzeqcjhmnexlaafmycwopxntuisxcitxdbarsicvwrvjmxsapmhbbnuivzhkgcrshokkioagwidhmfzjwwywastecjsolxmhfnmgommkoimiwlgwxxdsxhuwwjhpxxgmeuzhdzmuqhmhnfwwokgvwsznfcoxbferdonrexzanpymxtfojodcfydedlxmxeffhwjeegqnagoqlwwdctbqnuxngrgovrjesrkjrfjawknbrsfywljscfvnjhczhyeoyzrtbkvvfvofykkwoiclgxyaddhpdoztdhcbauaagjmfzkkdqexkczfsztckdlujgqzjyuittnudpldjvsbwbzcsazjpxrwfafievenvuetzcxynnmskoytgznvqdlkhaowjtetveahpjguiowkiuvikwewmgxhgfjuzkgrkqhmxxavbriftadtogmhlatczusxkktcsyrnwjbeshifzbykqibghmmvecwwtwdcscikyzyiqlgwzycptlxiwfaigyhrlgtjocvajcnqyenxrnjgogeqtvkxllxpuoxargzgcsfwavwbnktchwjebvwwhfghqkcjhuhuqwcdsixrkfjxuzvhjxlyoxswdlwfytgbtqbeimzzogzrlovcdpseoafuxfmrhdswwictsctawjanvoafvzqanvhaohgndbsxlzuymvfflyswnkvpsvqezekeidadatsymbvgwobdrixisknqpehddjrsntkqpsfxictqbnedjmsveurvrtvpvzbengdijkfcogpcrvwyf");
    }
  }
#endif
