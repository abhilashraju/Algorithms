#include <vector>
#include <iostream>
#include <map>
#include <optional>
using namespace std;
optional<vector<int>> bestCoins(int amt, const vector<int>& coins,map<int,vector<int>>& bestCache){
    if(bestCache.find(amt)!=end(bestCache)){return bestCache[amt];}
    if(amt < 0) return nullopt;
    if(amt == 0) return vector<int>{};
    optional<vector<int>> denominations;

    for(auto coin:coins){
        vector<int> current;
        current.push_back(coin);

        auto subdeno=bestCoins(amt-coin,coins,bestCache);
        if(subdeno.has_value()){
            if(subdeno.value().size()){
                std::copy(begin(*subdeno),end(*subdeno),std::back_inserter(current));
            }
            if(!denominations || denominations.value().size()> current.size()){
                denominations=current;
            }
        }
    }

    if(denominations){
        bestCache[amt]=denominations.value();
    }
    return denominations;


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
