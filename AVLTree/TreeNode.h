#ifndef TreeNode_h
#define TreeNode_h
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <cmath>
using std::vector;
using std::queue;
using std::stack;
#define stature(node) ((node) ? (node)->height_ : -1)
typedef enum {RB_RED, RB_BLACK} RBColor;
template<typename T> struct TreeNode {
    T data_;
    TreeNode<T>* parent_;
    TreeNode<T>* lc_;
    TreeNode<T>* rc_;
    int height_;
    RBColor color_;
    TreeNode() : parent_(nullptr), lc_(nullptr), rc_(nullptr), height_(0), color_(RB_RED){}
    TreeNode(T data, TreeNode<T>* parent = nullptr, TreeNode<T>* lc = nullptr,
             TreeNode<T>* rc = nullptr, int h = 0, RBColor c = RB_RED) : 
             data_(data), parent_(parent), lc_(lc), rc_(rc), height_(0), color_(c) {}
    TreeNode<T>* insertAsLC(T const& lcVal);
    TreeNode<T>* insertAsRC(T const& lcVal);
    void Display() { display(this, 0); }
    // TreeNode<T>* LeftRotate();
    // TreeNode<T>* RightRotate();
    // Traversal Method
    template <typename VST> void travelLevel(VST& visit) { TravelLevel(this, visit); }
    template <typename VST> void travelPre(VST& visit) { TravelPreIterative(this, visit); }
    template <typename VST> void travelIn(VST& visit) { TravelInIterative(this, visit); }
    template <typename VST> void travelPost(VST& visit) { TravelPostRecursive(this, visit);}
    bool operator< (TreeNode const& bn) { return data_ < bn.data_; }
    bool operator== (TreeNode const& bn) {return data_ < bn.data_; }
};
template <typename T> void display(TreeNode<T>* cur, int depth);
// 1 level traversal
template <typename T, typename VST>  
void TravelLevel(TreeNode<T>* node, VST& visit) {
    queue<TreeNode<T>*> levelQue;
    
    levelQue.push(node);
    while (!levelQue.empty()) {
        TreeNode<T>* cur = levelQue.front();
        visit(cur);
        levelQue.pop();
        if (cur->lc_) {
            levelQue.push(cur->lc_);
        }
        if (cur->rc_) {
            levelQue.push(cur->rc_);
        }
    }
}
// 2.2 Iterative version of inorderTraversal
template <typename T, typename VST>
void TravelInIterative(TreeNode<T>* node, VST& visit) {
    stack<TreeNode<T>*> stk;
    TreeNode<T>* cur = node;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->lc_;
            continue;        
        }
        cur = stk.top();
        stk.pop();
        visit(cur);
        cur = cur->rc_;
    } 
}

// 3.2 Iterative version of Preorder traversal
template <typename T, typename VST>
void TravelPreIterative(TreeNode<T>* node, VST& visit) {
    stack<TreeNode<T>*> stk;
    TreeNode<T>* cur = node;
    stk.push(cur);
    while (!stk.empty()) {
        cur = stk.top();
        stk.pop();
        if (cur->rc_) stk.push(cur->rc_);
        if (cur->lc_) stk.push(cur->lc_);
        visit(cur);
    } 
}

// 4.1 recursive version of Postorder traversal
template <typename T, typename VST>
void TravelPostRecursive(TreeNode<T>* node, VST& visit) {
    if (!node) return;
    TravelPostRecursive(node->lc_, visit);
    TravelPostRecursive(node->rc_, visit);
    visit(node);    
}



#endif /*TreeNode_h*/