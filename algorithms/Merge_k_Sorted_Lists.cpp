#include <vector>
#include<algorithm>
#include<iostream>
using namespace std;
  struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ret=nullptr;
        ListNode* next=nullptr;
        while(lists.size()){

            auto iter =min_element(begin(lists),end(lists),[](auto node1,auto node2){
                if(node1 && node2){
                    return node1->val < node2->val;
                }
                if(node1){
                    return true;
                }
                return false;

            });
            if(*iter == nullptr){
                return ret;
            }
            if(ret==nullptr){
                ret=*iter;
                next=ret;
            }else{
                next->next=*iter;
                next=next->next;
            }
            auto nextofselected=(*iter)->next;
            lists.erase(iter);
            if(nextofselected!=nullptr)
                lists.push_back(nextofselected);



        }
        return ret;
    }
};
#if(0)
int main(){
    auto print=[](auto& list){
      cout<<"input\n";
      for(auto temp:list){
          while (temp) {
              cout<<temp->val<<"->";
              temp=temp->next;
          }
          cout<<"\n";
      }

      auto reversed=Solution().mergeKLists(list);
      while (reversed) {
          cout<<reversed->val<<"->";
          reversed=reversed->next;
      }
      cout<<"\n";
    };

    auto make_list=[](const vector<int>& vec){
        ListNode* nod=nullptr;
        for(auto iter=vec.rbegin();iter!=vec.rend();iter++){
            nod=new ListNode(*iter,nod);
        }
        return nod;
    };
    vector<ListNode*> vect={

          make_list({1,4,5}),
          make_list({1,3,4}),
          make_list({2,6})

    };
    print(vect);
    vector<ListNode*> empty={};
    print(empty);

    vector<ListNode*> emptyempty={{}};
    print(emptyempty);


}
#endif
