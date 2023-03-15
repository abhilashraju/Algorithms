#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<numeric>
#include"BinaryTreePrinter.h"
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//class Solution {
//public:

//    void printPath(const vector<vector<TreeNode*>>& paths1){

//         for(auto& p:paths1){
//             cout<<"{";
//             for(auto n:p){
//                 cout<<n->val<<",";
//             }
//             cout<<"}\n";
//         }
//    }
//    vector<vector<TreeNode*>> traverseRight(TreeNode* root,vector<TreeNode*> pathSofar){
//        vector<vector<TreeNode*>> paths;
//        while (root!=nullptr) {
//            pathSofar.push_back(root);
//            paths.push_back(pathSofar);
//            root=root->right;
//        }
//        return paths;
//    }

//    vector<vector<TreeNode*>> zigzigPaths(TreeNode* root,vector<TreeNode*> pathSofar,TreeNode* right){
//        if(root == nullptr){
//            return  vector<vector<TreeNode*>>{};
//        }
//        pathSofar.push_back(root);
//        vector<vector<TreeNode*>> paths;
//        paths.push_back({root});
//        paths.push_back(pathSofar);


//        if(root->left==nullptr && right != nullptr){
//            auto chainedpath=zigzigPaths(right,pathSofar,nullptr);
//            copy(chainedpath.begin(),chainedpath.end(),back_inserter(paths));
//        }
//        auto leftpaths=zigzigPaths(root->left,pathSofar,right);
//        copy(leftpaths.begin(),leftpaths.end(),back_inserter(paths));
//        if(root->right != right){
//            auto rightpaths=zigzigPaths(root->right,pathSofar,right);
//            copy(rightpaths.begin(),rightpaths.end(),back_inserter(paths));
//        }



//        if(root->left){
//            auto leftpathfromleft=zigzigPaths(root->left,vector<TreeNode*>{root},root->right);
//            copy(leftpathfromleft.begin(),leftpathfromleft.end(),back_inserter(paths));
//        }
//        if(root->right){
//            auto p=traverseRight(root->right,vector<TreeNode*>{root});
//            copy(p.begin(),p.end(),back_inserter(paths));
//            auto leftpathfromright=zigzigPaths(root->right,vector<TreeNode*>{root},nullptr);
//            copy(leftpathfromright.begin(),leftpathfromright.end(),back_inserter(paths));
//        }
//        return paths;
//    }
//    template<typename InsertIter>
//    void merge(const vector<vector<TreeNode*>>& path1, const vector<vector<TreeNode*>>& path2,InsertIter iter){
//        if(path1.empty()){
//            copy(path2.begin(),path2.end(),iter);
//            return;
//        }
//        if(path2.empty()){
//            copy(path1.begin(),path1.end(),iter);
//            return;
//        }
//        for(auto path:path1){
//            transform(path2.begin(),path2.end(),iter,[&](auto& p){
//                vector<TreeNode*> prepended;
//                copy(begin(path),end(path),back_inserter(prepended));
//                copy(begin(p),end(p),back_inserter(prepended));
//                return prepended;
//            });
//        }
//    }

//    int maxPathSum(TreeNode* root){
//         auto paths1=zigzigPaths(root->left,vector<TreeNode*>{root},root->right);
//         if(root->right){
//             auto p=traverseRight(root->right,vector<TreeNode*>{root});
//             copy(p.begin(),p.end(),back_inserter(paths1));
//             auto paths2=zigzigPaths(root->right->left,vector<TreeNode*>{root->right},root->right->right);
//             copy(paths2.begin(),paths2.end(),back_inserter(paths1));
//         }
//        paths1.push_back({root});



////         printPath(paths1);

//         auto max= accumulate(begin(paths1),end(paths1),pair{-1000,vector<TreeNode*>{}},[](auto sofar,auto& p)->pair<int,vector<TreeNode*>>{
//             auto sum= accumulate(begin(p),end(p),0,[](auto innersofar,auto n){
//                 return innersofar+n->val;
//             });
//             return sofar.first<sum ? pair(sum,p):sofar;
//          });
//         printPath({max.second});
//         return max.first;
//    }

//};

class Solution {
public:
    int maxPathFrom(TreeNode* root, int& sofar){
        if(root ==nullptr){
            return 0;
        }
        int leftmax=max(0,maxPathFrom(root->left,sofar)) ;
        int rightmax=max(0,maxPathFrom(root->right,sofar));
        sofar= max(sofar, leftmax + rightmax +root->val);
        return max(leftmax,rightmax)+root->val;

    }
    int maxPathSum(TreeNode* root){
        int sofar={-1000};
        maxPathFrom(root,sofar);
        return sofar;
    }
};
#if 0
int main(){
    auto print=[](TreeNode* root){
      cout<<"Input = \n";

      BinaryTreePrinter<TreeNode>().printTree(root);

      cout<<"\npaths\n"<< Solution().maxPathSum(root);

      cout<<" is result \n";
    };

    print(BinaryTreePrinter<TreeNode>().makeTree({"1","2","3"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-10","9","20","null","null","15","7"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-10"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"1","2"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"1","null","2"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"1","-2","-3","1","3","-2","null","-1"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"5","4","8","11","null","13","4","7","2","null","null","null","1"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"2","-1"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-6","null","3","2"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-1","5","null","4","null","null","2","-4"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-2","null","-3"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"2","-1","-2"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"1","null","2","null","3","null","4","null","5"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"1","null","2","null","3"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"5","null","-2","1","-1","null","null","null","4"}));

    print(BinaryTreePrinter<TreeNode>().makeTree({"-1","null","9","-6","3","null","null","null","-2"}));

    print(BinaryTreePrinter<TreeNode>().makeTree({"7","null","2","3","-7"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"-6","null","3","2"}));

    print(BinaryTreePrinter<TreeNode>().makeTree({"5","4","8","11","null","13","4","7","2","null","null","null","1"}));
    print(BinaryTreePrinter<TreeNode>().makeTree({"8","9","-6","null","null","5","9"}));

}
#endif
