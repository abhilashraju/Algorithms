#include<vector>
#include<algorithm>
#include<tuple>
#include <iostream>
using namespace std;
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {

        auto iter =partition(begin(nums),end(nums),[](auto v){return v>0;});
        auto dist=distance(begin(nums),iter);
        for(int i=0; i<dist;i++){
            if(nums[i]<=dist){
                nums[std::abs(nums[i])-1]=-std::abs(nums[std::abs(nums[i])-1]);
            }
        }
        for(int i=0; i<dist;i++){
            if(nums[i]>0){
                return i+1;
            }
        }
        return dist+1;

    }
};
#if 0
int main(){
    auto print=[](vector<int> v){
        cout<<"Input \n";
        for(auto e:v){
            cout<<e<<",";
        }
        cout<<"\n Missing = " << Solution().firstMissingPositive(v)<<"\n";
    };

//    print({1,-2,3,5,6,4,-8});
//    print({-1,-2,-3,-5,-6,-4,-8});
//    print({-1,2,3,5,6,-4,8});
//    print({1,2,3,5,6,4,7});
    print({1,1});
}
#endif
