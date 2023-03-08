#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
    template<typename Iter,typename OutIter>
    void merge_recurs(Iter iter1b,Iter iter1e,Iter iter2b,Iter iter2e,OutIter out){
        if(*iter1b<=*iter2b){
            auto lower =lower_bound(iter1b,iter1e,*iter2b);
            copy(iter1b,lower,out);
            out=*iter2b;
            advance(iter2b,1);
            if(lower !=iter1e && iter2b != iter2e){
                merge_recurs(lower,iter1e,iter2b,iter2e,out);
                return;
            }
            if(lower == iter1e){
                copy(iter2b,iter2e,out);
                return;
            }
            copy(lower,iter1e,out);
            return;
        }
        merge_recurs(iter2b,iter2e,iter1b,iter1e,out);

    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {


        if(nums1.size() && nums2.size()){
            std::vector<int> outer;
            merge_recurs(begin(nums1),end(nums1),begin(nums2),end(nums2),std::back_inserter(outer));
            return (outer.size()%2) ? outer[outer.size()/2] : double(outer[outer.size()/2-1] + outer[outer.size()/2])/2;
        }
        else if(nums1.size()){
            return (nums1.size()%2) ? nums1[nums1.size()/2] : double(nums1[nums1.size()/2 -1] + nums1[nums1.size()/2 ])/2;
        }
        return (nums2.size()%2) ? nums2[nums2.size()/2] : double(nums2[nums2.size()/2 -1] + nums2[nums2.size()/2 ])/2;
    }
};
#if 0
int main()
{
    vector vec1{1,3};
    vector vec2{2};
    cout << Solution().findMedianSortedArrays(vec1,vec2)<< "\n";

    vector vec3{1,3};
    vector vec4{2,4};
    cout << Solution().findMedianSortedArrays(vec3,vec4)<< "\n";

    vector vec5{1,2,3,4,4,5,5};
    vector vec6{6,7,8,9,10,10,11,12,13};
    cout << Solution().findMedianSortedArrays(vec5,vec6)<< "\n";

    vector vec7{1,2,3,4,4,5,5};
    vector<int> vec8;
    cout << Solution().findMedianSortedArrays(vec7,vec8)<< "\n";

    cout << Solution().findMedianSortedArrays(vec8,vec7)<< "\n";
}
#endif
