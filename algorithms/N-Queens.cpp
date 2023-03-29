#include<iostream>
#include"verify.h"
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution {
public:

    struct HASH
    {
        vector<vector<int>> table;
        int N;

        HASH(int N):table(N,vector(N,0)),N(N){}
        int& operator[](const pair<int,int>& p){
            return table[p.first][p.second];
        }
        const int& operator[](const pair<int,int>& p)const{
            return table[p.first][p.second];
        }
        friend HASH place(HASH& current,const pair<int,int>& p){
            HASH old=current;
            current[p]=true;
            for(int j=0;j<current.N;j++){
                 current[{p.first,j}]=true;
            }
            for(int i=0;i<current.N;i++){
                 current[{i,p.second}]=true;
            }
            auto filllowerdiagonal=[&](auto p){
                int i=p.first-1;
                int j=p.second-1;
                while(i>=0 && j>=0){
                     current[{i--,j--}]=true;
                }
            };
            auto fillupperdiagonal=[&](auto p){
                int i=p.first+1;
                int j=p.second+1;
                while(i<current.N && j<current.N){
                     current[{i++,j++}]=true;
                }
            };
            auto filltoprightdiagonal=[&](auto p){
                int i=p.first-1;
                int j=p.second+1;
                while(i>=0 && j<current.N){
                     current[{i--,j++}]=true;
                }
            };
            auto fillbottomleftdiagonal=[&](auto p){
                int i=p.first+1;
                int j=p.second-1;
                while(i<current.N && j>=0){
                     current[{i++,j--}]=true;
                }
            };
           // filllowerdiagonal(p);
            fillupperdiagonal(p);
           // filltoprightdiagonal(p);
            fillbottomleftdiagonal(p);
            return old;
        }
        struct AvailIter
        {
            const HASH& hash;
            pair<int,int> current;
            AvailIter(const HASH& h):hash(h),current(findnext({0,0})){


            }
            pair<int,int> findnext(const pair<int,int>& p){
                for(int i=p.first;i<hash.N;i++){
                    for(int j=p.second;j<hash.N;j++){
                        if(hash[{i,j}]==0){
                            return pair{i,j};
                        }
                    }
                }
                return pair{hash.N,hash.N};
            }
            AvailIter operator++(){
                auto next=pair{current.first,current.second+1};
                if(next.second>=hash.N){
                    next=pair{current.first+1,0};
                }
                current=findnext(next);
                return *this;
            }
            pair<int,int> operator*(){
                return current;
            }
            friend bool operator==(const AvailIter& iter1,const AvailIter& iter2){
                return &iter1.hash==&iter2.hash
                        && iter1.current == iter2.current;
            }
            friend bool operator!=(const AvailIter& iter1,const AvailIter& iter2){
                return !(iter1==iter2);
            }
        };
        AvailIter begin()const{
            return AvailIter(*this);
        }
        AvailIter end()const{
            auto iter=AvailIter(*this);
            iter.current={N,N};
            return iter;
        }
    };
    void printboard(vector<pair<int,int>>& board ){
        cout<<"\n";
        for(int i=0;i<board.size();i++){

            for(int j=0;j<board.size();j++){
                if(find(begin(board),end(board),pair{i,j}) != end(board)){
                    cout<<'Q'<<" ";
                }else{
                    cout<<'.'<<" ";
                }
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    void print(vector<vector<pair<int,int>>>& board)
    {
        for(auto& p:board){
            printboard(p);
        }
    }


    auto fillstring(int p,int n){
        string s(n,'.');
        s[p]='Q';
        return s;
    };
    void search(HASH& current,int ith,int N,vector<string>& cursolun, vector<vector<string>>& all){


        if(ith==N){
            for(auto o:current){
                cursolun[o.first]=(fillstring(o.second,N));
                auto found =find_if(all.begin(),all.end(),[&](auto& v){
                    return equal(v.begin(),v.end(),cursolun.begin(),cursolun.end());
                });
                if(found==all.end()){
                    all.push_back(cursolun);
                }
                cursolun[o.first]="";

            }
            return ;
        }
        auto iter = current.begin();
        while(iter != end(current)){
            auto o=*iter;
            auto old=place(current,o);
            cursolun[o.first]=(fillstring(o.second,N));
            search(current,ith+1,N,cursolun,all);
            cursolun[o.first]="";
            current=std::move(old);
            ++iter;
        }


    }
    vector<vector<string>> solveNQueens(int n) {

        if(n==1){
            return {{"Q"}};
        }
        vector<vector<pair<int,int>>> configs;
        HASH current(n);

        vector<vector<string>> all;
        for(int j=0;j<n;j++){
            vector<string> currentsolution(n,"");
            auto old=place(current,{0,j});
            currentsolution[0]=(fillstring(j,n));
            search(current,2,n,currentsolution,all);
            current=std::move(old);
        }
        return all;
    }
};

int main(){

    auto print=[](int n){
      cout<<"Dimensions = "<< n<<"\n";
      auto pos=Solution().solveNQueens(n);
      cout<<"{\n";
      for(auto& c:pos){
          cout<<"{\n";
          for(auto& v:c){
              cout<<v<<"\n";
          }
          cout<<"}\n";
      }
      cout<<"}\n";
      return pos;
    };

//    print(1);
//    print(2);
//    print(3);
    verify(print(4)==vector<vector<string>>{{".Q..","...Q","Q...","..Q."},
                                            {"..Q.","Q...","...Q",".Q.."}});
    verify(print(5)==vector<vector<string>>{{"Q....","..Q..","....Q",".Q...","...Q."},
                                            {"Q....","...Q.",".Q...","....Q","..Q.."},
                                            {".Q...","...Q.","Q....","..Q..","....Q"},
                                            {".Q...","....Q","..Q..","Q....","...Q."},
                                            {"..Q..","Q....","...Q.",".Q...","....Q"},
                                            {"..Q..","....Q",".Q...","...Q.","Q...."},
                                            {"...Q.","Q....","..Q..","....Q",".Q..."},
                                            {"...Q.",".Q...","....Q","..Q..","Q...."},
                                            {"....Q",".Q...","...Q.","Q....","..Q.."},
                                            {"....Q","..Q..","Q....","...Q.",".Q..."}});
    print(6);
}
