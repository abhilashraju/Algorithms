#include<vector>
#include<algorithm>
#include<tuple>
#include <iostream>
#include <numeric>
using namespace std;
class Solution {
public:
    auto movingAvarage(const auto& input,int N,auto ins){
        auto val = std::accumulate(begin(input),begin(input)+N,0);
        auto secb= begin(input);
        std::advance(secb,N);
        *ins = val;
        auto init = std::make_pair(ins,val);
        auto collector = [](auto sofar,auto p){
            *sofar.first = sofar.second-p.first+p.second;
            return sofar; 
        };
        auto zipper = [](auto first, auto second){
            return make_pair(first,second);
        };
        std::inner_product(begin(input),end(input)-N-1,secb,init,collector,zipper);
    }
    auto movingAvarage(const auto& input,int N)
    {
        std::vector<int> results;
        movingAvarage(input,N,std::back_inserter(results));
        return results;
    }
};
#if 1
int main(){
    auto print=[](vector<int> v,int N){
        cout<<"\nInput \n";
        for(auto e:v){
            cout<<e<<",";
        }
        cout<<"\nOutput \n";
        for(auto e:Solution().movingAvarage(v,N)){
            cout<<e<<",";
        }
    };

//    print({1,-2,3,5,6,4,-8});
//    print({-1,-2,-3,-5,-6,-4,-8});
//    print({-1,2,3,5,6,-4,8});
//    print({1,2,3,5,6,4,7});
    print({1,1,1,1,1,1},1);
    print({1,1,1,1,1,1},2);
    print({1,1,1,1,1,1},3);
    print({1,1,1,1,1,1},4);
    print({1,1,1,1,1,1},5);
}
#endif
