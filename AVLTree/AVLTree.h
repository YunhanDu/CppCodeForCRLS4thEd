#ifndef AVLSearchTree_h
#define AVLSearchTree_h
// author: Claude Du
#include "TreeNode.h" 
template <typename T>
inline bool Balanced(const TreeNode<T>* x) { return stature(x->lc_) == stature(x->rc_); }
template <typename T>
inline int BalFac(const TreeNode<T>* x) {
    return (stature(x->lc_) - stature(x->rc_));
}
template <typename T>
inline bool AvlBalanced(const TreeNode<T>* x) {
    return (-2 < BalFac(x)) && (BalFac(x) < 2);
}

template <typename T>
inline TreeNode<T>* TallerChild(const TreeNode<T>* x) {
    if (stature(x->lc_) > stature(x->rc_)) return x->lc_;
    if (stature(x->lc_) < stature(x->rc_)) return x->rc_;
    return (x-> parent_ == nullptr) || (x == x->parent_->lc_) ? x->lc_ : x->rc_;   
}
template <typename T> class AVLTree {
protected:
    int size_; TreeNode<T>* root_; // size_ means # of nodes
    virtual int UpdateHeight(TreeNode<T>* node);
    void UpdateHeightAbove(TreeNode<T>* node);
    void Display(TreeNode<T>* cur, int depth = 0);
    void Transplant(TreeNode<T>* toBeSuAVLTreeituted, TreeNode<T>* vertex);
public:
    AVLTree() : size_(0), root_(nullptr) {}    
    ~AVLTree() { 
        if (size_ > 0) {
            std::cout << "Hi, my job is done. " << "\n";
            std::cout << Remove(root_);
        }
    }
    int size() const { return size_; }
    int height() const { return stature(root_); }
    bool empty() const { return root_ == nullptr; }
    TreeNode<T>* root() const { return root_; }
    TreeNode<T>* TreeMinimum() const {
        if (root_ == nullptr) return root_; 
        return TreeMinimum(root_); 
    }
    // read operations:
    TreeNode<T>* TreeMinimum(TreeNode<T>* cur) const;
    TreeNode<T>* TreeMaximum() const {
        if (root_ == nullptr) return root_; 
        return TreeMaximum(root_); 
    }
    TreeNode<T>* TreeMaximum(TreeNode<T>* cur) const;
    TreeNode<T>* TreeSuccessor(TreeNode<T>* cur) const;
    TreeNode<T>* TreePredecessor(TreeNode<T>* cur) const;
    // search
    TreeNode<T>*& TreeSearch(T const& keyVal);
    TreeNode<T>*& TreeSearchRecursive(TreeNode<T>*& cur, T const& keyVal);
    TreeNode<T>* TreeSearchIterative(TreeNode<T>* cur, T const& keyVal);
    void LeftRotate(TreeNode<T>* x);
    void RightRotate(TreeNode<T>* x);
    // insertion
    TreeNode<T>* TreeInsert(T const& val);
    void InsertRebalance(TreeNode<T>* x);
    // deletion
    bool TreeDeletion(T const& val);
    void TreeDeletion(TreeNode<T>*& cur);
    void TreeDeletion2(TreeNode<T>* cur);
    void DeleteRebalance(TreeNode<T>* z);
    int Remove(TreeNode<T>* x);
    
    void PosiBalance(TreeNode<T>* x);
    // Traversal
    template <typename VST>
    void travLevel(VST& visit) { if (root_) root_->travLevel(visit); }
    template <typename VST>
    void travelPre(VST& visit) { if (root_) root_->travelPre(visit); }
    template <typename VST>
    void travelIn(VST& visit) { if (root_) root_->travelIn(visit); }
    template <typename VST>
    void travelPost(VST& visit) { if (root_) root_->travelPost(visit); }
    
    void Display();
}; 
#endif /*AVLTree_h*/