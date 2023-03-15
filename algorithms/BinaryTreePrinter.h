#ifndef BINARYTREEPRINTER_H
#define BINARYTREEPRINTER_H
#include<vector>
#include<deque>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;
template<typename TreeNode>
struct BinaryTreePrinter
{
    auto linearise(TreeNode* root,vector<string>& vect)->void{

        deque<TreeNode*> queue;
        queue.push_back(root);
        while(!queue.empty()){
            auto node=queue.front();
            if(node){
                vect.push_back(to_string(node->val));
                queue.push_back(node->left);
                queue.push_back(node->right);
            }else{
                vect.push_back("N");
                if(find_if_not(begin(queue),end(queue),[](auto v){return v==nullptr;}) != end(queue)){
                    queue.push_back(nullptr);
                    queue.push_back(nullptr);
                }
            }
            queue.pop_front();
        }

    }
    auto printTree(TreeNode* root){
        vector<string> vect;
        linearise(root,vect);
        auto s=vect.size();
        int depth= log2(s)+1;
        int nodecounter=0;
        int totaldepth=depth;
        auto printspace=[](auto space,auto num){
            space -= num.length();
            while(space-->0)cout<<" ";
            cout<<num;
        };
        while(depth>0){

            int levelcount=pow(2,totaldepth-depth);
            for(int i=0;i<levelcount && nodecounter<vect.size();i++){
                printspace(i!=0? 2*pow(2,depth+1):pow(2,depth+1),vect[nodecounter++]);
            }
            cout<<"\n\n";
            depth--;
        }
    }

    auto makeNode(const string& val)->TreeNode*{
        if(val=="null"){
            return nullptr;
        }
        return new TreeNode(atoi(val.data()));
    };
    auto makeTree(vector<string> vals){
        vector<TreeNode*> nodes;
        nodes.push_back(new TreeNode(atoi(vals.front().data())));
        auto root=nodes[0];
        vals.erase(begin(vals));
        while(vals.size()){
            if(nodes[0]==nullptr){
                nodes.erase(begin(nodes));
                continue;
            }
            auto left=vals.front();vals.erase(vals.begin());
            nodes[0]->left=makeNode(left);
            nodes.push_back(nodes[0]->left);

            if(vals.size()){
                auto right=vals.front();vals.erase(vals.begin());
                nodes[0]->right=makeNode(right);
                nodes.push_back(nodes[0]->right);
            }
            nodes.erase(begin(nodes));
        }
        return root;

    };

};
#endif // BINARYTREEPRINTER_H
