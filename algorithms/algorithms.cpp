#include <vector>
#include <iostream>
#include <map>
#include <optional>
using namespace std;
optional<vector<int>> bestCoins(int amt, const vector<int>& coins,map<int,vector<int>>& bestCache){
    vector<int> denominations;
    if(amt < 0) return nullopt;
    if(amt == 0) return vector<int>{};
    if(bestCache.find(amt)!=end(bestCache)){return bestCache[amt];}
    for(auto coin:coins){
        vector<int> current;
        current.push_back(coin);

        auto subdeno=bestCoins(amt-coin,coins,bestCache);
        if(subdeno.has_value()){
            if(subdeno.value().size()){
                std::copy(begin(*subdeno),end(*subdeno),std::back_inserter(current));
            }
            if(denominations.size()==0 || denominations.size()> current.size()){
                denominations=current;
            }
        }
    }

    if(denominations.size()){
        bestCache[amt]=denominations;
        return denominations;
    }
    return nullopt;


}
int main(){
    auto printer= [](auto vec){
        cout <<"{";
        for(auto v: vec){
            cout<<v<<",";
        }
        cout <<"}\n";

    };
    auto findDenominations=[](int amt,const  vector<int>& coins){
        map<int,vector<int>> bestCache;
        return bestCoins(amt,coins,bestCache).value_or(vector<int>());
    };
    printer(findDenominations(50,{50,21,1}));
    printer(findDenominations(50,{21,1}));
    printer(findDenominations(50,{21,2,1}));
    printer(findDenominations(50,{21}));
}
