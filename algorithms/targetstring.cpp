#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
bool canConstruct(std::string_view target, const vector<string>& keys, map<string_view, bool>& cache)
{
    if(cache.find(target) != end(cache)) return cache[target];
    if(target.empty()) return true;
    for(auto i=0;i<=target.length();i++){
        auto substr=target.substr(0,i);
        if(std::find_if(begin(keys),end(keys),[&](auto v){return v==substr;}) != end(keys)){
           return  cache[target] = canConstruct(target.substr(i),keys,cache);
        }
    }
    return false;
}
int countConstruct(std::string_view target, const vector<string>& keys, map<string_view,int>& cache)
{
    if(cache.find(target) != end(cache)){return cache[target];}
    if(target.empty()) return 1;
    int count=0;
    for(auto i=0;i<=target.length();i++){
        auto substr=target.substr(0,i);
        if(std::find_if(begin(keys),end(keys),[&](auto v){return v==substr;}) != end(keys)){
            count +=countConstruct(target.substr(i),keys,cache);
        }
    }
    return cache[target]=count;
}

vector<vector<string>> allConstruct(std::string_view target, const vector<string>& keys,map<string_view,vector<vector<string>>>& cache)
{
    if(cache.find(target)!=end(cache)){return cache[target];}
    if(target.empty()) return {{""}};
    vector<vector<string>> patterns;
    for(auto i=0;i<=target.length();i++){
        auto substr=target.substr(0,i);
        if(std::find_if(begin(keys),end(keys),[&](auto v){return v==substr;}) != end(keys)){
            auto subpatterns=allConstruct(target.substr(i),keys,cache);
            std::transform(begin(subpatterns),end(subpatterns),std::back_inserter(patterns),[&](auto& v){
                vector<string> newVec;
                newVec.push_back(string(substr));
                std::copy(begin(v),end(v),std::back_inserter(newVec));
                return newVec;
            });

        }
    }
    return cache[target]=patterns;
}
#if(0)
int main(){
    auto print=[](auto a, auto b,auto func){
        cout<< a << " from {";
        for(auto v:b){
            cout<< v<<",";
        }
        cout<<"} = ";
        func(a,b);
    };
    auto canConstructPrinter=[](auto a, auto b){
        map<string_view,bool> cache;
        cout<<(canConstruct(a,b,cache)?"true" : "false ")<<"\n";

    };
    auto countConstructPrinter=[](auto a, auto b){
        map<string_view,int> cache;
        cout<<countConstruct(a,b,cache)<<"\n";

    };

    auto allConstructPrinter=[](auto a, auto b){
        map<string_view,vector<vector<string>>> cache;
        cout<<"{";
        for(auto& v : allConstruct(a,b,cache)){
            cout<<" {";
            for(auto k:v){
                cout<<k<<",";
            }
            cout<<"} ,";
        }
        cout<<"}\n";

    };
    auto makeKeys=[](auto... keys){
        std::vector v{string(keys)...};
        return v;
    };
    //can construct
    print("abcdefg",makeKeys("a","bc","fg","de"),canConstructPrinter);
    print("abcdefg",makeKeys("a","bc","fg"),canConstructPrinter);
    print("abcdefg",makeKeys("a","bcd","fg","de"),canConstructPrinter);
    print("abcadefg",makeKeys("a","bc","fg","de"),canConstructPrinter);
    print("",makeKeys("a","bc","fg"),canConstructPrinter);

    //count construct
    print("abcdefg",makeKeys("a","bc","fg","de","b","c","d","e","f","g"),countConstructPrinter);
    print("abcdefg",makeKeys("a","bc","fg"),countConstructPrinter);
    print("abcdefg",makeKeys("a","bcd","fg","de"),countConstructPrinter);
    print("abcadefg",makeKeys("a","bc","fg","de"),countConstructPrinter);
    print("",makeKeys("a","bc","fg"),countConstructPrinter);

    //all construct
    print("abcdefg",makeKeys("a","bc","fg","de","b","c","d","e","f","g"),allConstructPrinter);
    print("abcdefg",makeKeys("a","bc","fg"),allConstructPrinter);
    print("abcdefg",makeKeys("a","bcd","fg","de"),allConstructPrinter);
    print("abcadefg",makeKeys("a","bc","fg","de"),allConstructPrinter);
    print("",makeKeys("a","bc","fg"),allConstructPrinter);
}
#endif
