#include"profiler.h"
#include<iostream>
#include<optional>
#include<vector>
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

    ListNode* reverse(ListNode* head,ListNode** newHead,int reminder){

        if(head->next && reminder >1){
            auto oldHead=*newHead;
            auto tail = reverse(head->next,newHead,reminder-1);
            if(oldHead != *newHead){
                head->next=tail->next;
                tail->next=head;
            }
            return head;
        }
        if(reminder>1){
            return head;
        }

        if(newHead)
            *newHead=head;
        return head;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        //return reverseKGroupImpl(head,k,k).value();
        ListNode* newHead=head;
        auto tail =reverse(head,&newHead,k);
        while(tail && tail->next){
            tail=reverse(tail->next,&tail->next,k);
        }
        return newHead;
    }
};
#if 0
int main(){
    auto print=[](auto list , int k){
      cout<<"input\n";
      auto temp=list;
      while (temp) {
          cout<<temp->val<<"->";
          temp=temp->next;
      }
      cout<<"rotation count = "<<k<<"\noutput\n";
      auto reversed=Solution().reverseKGroup(list,k);
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

    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),2);
    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),4);
    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),5);
    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),6);
    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),11);
    print(make_list({1,2,3,4,5,6,7,8,9,10,11}),12);
}
#endif
