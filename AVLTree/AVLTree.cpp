#include "AVLTree.h"
template <typename T> int AVLTree<T>::UpdateHeight(TreeNode<T>* node) {
    node->height_ = 1 + std::max(stature(node->lc_), stature(node->rc_));
    return node->height_;
}
template <typename T> void AVLTree<T>::UpdateHeightAbove(TreeNode<T>* node) {
    while (node) {
        UpdateHeight(node);
        node = node->parent_;
    }
}

template <typename T> TreeNode<T>* AVLTree<T>::TreeMinimum(TreeNode<T>* cur) const {
    while (cur->lc_ != nullptr) {
        cur = cur->lc_;
    } 
    return cur;  
}
template <typename T> TreeNode<T>* AVLTree<T>::TreeMaximum(TreeNode<T>* cur) const {
    while (cur->rc_ != nullptr) {
        cur = cur->rc_;
    } 
    return cur;  
}
template <typename T> TreeNode<T>* AVLTree<T>::TreeSuccessor(TreeNode<T>* cur) const {
    if (cur->rc_ != nullptr) return TreeMinimum(cur->rc_);
    TreeNode<T>* y = cur->parent_;
    while (y != nullptr && cur == y->rc_) {
        cur = y;
        y = y->parent_;
    }
    return y;
}
template <typename T> TreeNode<T>* AVLTree<T>::TreePredecessor(TreeNode<T>* cur) const {
    if (cur->lc_ != nullptr) return TreeMaximum(cur->lc_);
    TreeNode<T>* y = cur->parent_;
    while (y != nullptr && cur == y->lc_) {
        cur = y;
        y = y->parent_;
    }
    return y;
}
template <typename T> TreeNode<T>*& AVLTree<T>::TreeSearch(T const& keyVal) {
    return TreeSearchRecursive(root_, keyVal);    
}
template <typename T> TreeNode<T>*& AVLTree<T>::TreeSearchRecursive(TreeNode<T>*& cur, T const& keyVal) {
    if (cur == nullptr || keyVal == cur->data_) return cur;
    if (keyVal < cur->data_)
        return TreeSearchRecursive(cur->lc_, keyVal);
    return TreeSearchRecursive(cur->rc_, keyVal);      
}
template <typename T> TreeNode<T>* AVLTree<T>::TreeSearchIterative(TreeNode<T>* cur, T const& keyVal) {
    while (cur != nullptr && keyVal != cur->data_) {
        if (keyVal < cur->data_) cur = cur->lc_;
        else cur = cur->rc_;
    }
    return cur;
}

template <typename T> TreeNode<T>* AVLTree<T>::TreeInsert(T const& val) {
    TreeNode<T>* targetPosiParent = nullptr;
    TreeNode<T>* curPosi = root_;
    while (curPosi != nullptr) {
        targetPosiParent = curPosi;
        if (val < curPosi->data_) curPosi = curPosi->lc_;
        else curPosi = curPosi->rc_;
    }
    TreeNode<T>* newNode = new TreeNode<T>(val, targetPosiParent);
    ++size_;
    // if tree is empty
    if (targetPosiParent == nullptr) {
        root_ = newNode;   
        return newNode;
    }
    if (val < targetPosiParent->data_) {
       targetPosiParent->lc_ = newNode; 
    } else targetPosiParent->rc_ = newNode;
    UpdateHeightAbove(newNode);
    InsertRebalance(newNode);
    return newNode;
}
template <typename T> bool AVLTree<T>::TreeDeletion(T const& val) {
    TreeNode<T>*& cur = TreeSearch(val);
    if (cur == nullptr) return false;
    TreeDeletion2(cur); 
    return true;  
}
// Intro To Algo's Method
template <typename T> void AVLTree<T>::Transplant(TreeNode<T>* toBeSuAVLTreeituted, TreeNode<T>* vertex) {
    if (toBeSuAVLTreeituted->parent_ == nullptr) root_ = vertex;
    else if (toBeSuAVLTreeituted == toBeSuAVLTreeituted->parent_->lc_) {
        toBeSuAVLTreeituted->parent_->lc_ = vertex;
    } else toBeSuAVLTreeituted->parent_->rc_ = vertex;
    if (vertex != nullptr) vertex->parent_ = toBeSuAVLTreeituted->parent_;
}
template <typename T> void AVLTree<T>::TreeDeletion2(TreeNode<T>* cur) {
    TreeNode<T>* target = cur->parent_; // find the lowest node whose height may need to updated
    if (cur->lc_ == nullptr) {
        Transplant(cur, cur->rc_); // replace cur by its right child
        
    } else if (cur->rc_ == nullptr) {
        Transplant(cur, cur->lc_); // replace cur by its left child    
    } else {
        TreeNode<T>* y = TreeMinimum(cur->rc_);
        if (y->parent_ != cur) { // is y farther down the tree?
            Transplant(y, y->rc_); // replace y by its right child
            y->rc_ = cur->rc_; // z's right child becomes
            y->rc_->parent_ = y; // y's right child
        }
        Transplant(cur, y); // replace cur by its successor y
        y->lc_ = cur->lc_; // and give z's left child to y
        y->lc_->parent_ = y; // which had no left child
        target = (y->rc_ == nullptr) ? y : y-> rc_;     
    }
    UpdateHeightAbove(target);
    DeleteRebalance(target);
    --size_;
}
// 邓俊辉的取巧办法，我并不喜欢,有点取巧走后门的感觉
template <typename T> void AVLTree<T>::TreeDeletion(TreeNode<T>*& cur) {
    TreeNode<T>* toBeDeleted = cur; // 
    TreeNode<T>* succ = nullptr;
    if (cur->lc_ == nullptr) {
        cur = cur->rc_;
        succ = cur;
    } else if (cur->rc_ == nullptr) {
        cur = cur->lc_;
        succ = cur;
    } else {
        toBeDeleted = TreeMinimum(toBeDeleted->rc_);
        std::swap(cur->data_, toBeDeleted->data_);
        TreeNode<T>* u = toBeDeleted->parent_;
        succ = toBeDeleted->rc_;
        if (u == cur) u->rc_ = succ;
        else u->lc_ = succ;
    }
    if (succ != nullptr) succ->parent_ = toBeDeleted->parent_;
    UpdateHeightAbove(toBeDeleted->parent_);
    --size_;
    delete toBeDeleted;
    toBeDeleted = nullptr;    
}
template <typename T> void AVLTree<T>::LeftRotate(TreeNode<T>* x) {
    TreeNode<T>* y = x->rc_;
    if (y == nullptr) return;
    x->rc_ = y->lc_;
    if (y->lc_ != nullptr) y->lc_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) root_ = y;
    else if (x == x->parent_->lc_) x->parent_->lc_ = y;
    else x->parent_->rc_ = y;
    x->parent_ = y;
    y->lc_ = x;    
    UpdateHeightAbove(x);
}
template <typename T> void AVLTree<T>::RightRotate(TreeNode<T>* x) {
    TreeNode<T>* y = x->lc_;
    if (y == nullptr) return;
    x->lc_ = y->rc_;
    if (y->rc_ != nullptr) y->rc_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) root_ = y;
    else if (x == x->parent_->lc_) x->parent_->lc_ = y;
    else x->parent_->rc_ = y;
    x->parent_ = y;
    y->rc_ = x; 
    UpdateHeightAbove(x);   
}
template <typename T> void AVLTree<T>::PosiBalance(TreeNode<T>* g) {
    TreeNode<T>* p = TallerChild(g);
    TreeNode<T>* v = TallerChild(p);
    if ( p == g->rc_) {
        if (v == p->rc_) {
            LeftRotate(g);  
        } else {
            RightRotate(p);
            LeftRotate(g);
        }
    } else {
        if (v == p->lc_) {
            RightRotate(g);  
        } else {
            LeftRotate(p);
            RightRotate(g);
        }        
    }
}
template <typename T> void AVLTree<T>::InsertRebalance(TreeNode<T>* x) {
    TreeNode<T>* g = x->parent_;
    while (g != nullptr) {
        if (!AvlBalanced(g)) {
            PosiBalance(g);
        } else {
            g = g->parent_;
        }
    }
}
template <typename T> void  AVLTree<T>::DeleteRebalance(TreeNode<T>* target) {
    TreeNode<T>* g = target;
    while (g != nullptr) {
        if (!AvlBalanced(g)) {
            PosiBalance(g);
        }
        g = g->parent_;
    }
}
template <typename T> int AVLTree<T>::Remove(TreeNode<T>* x) {
    // cut the pointer from parent node
    TreeNode<T>* &pointerOfParent = (x->parent_ == nullptr) ? root_ : ((x == x->parent_->lc_) ? x->parent_->lc_ : x->parent_->rc_);
    pointerOfParent = nullptr;
    // Remove all the nodes of this subtree
    // use Preorder way to remove all the nodes.
    UpdateHeightAbove(x->parent_);
    int toBeDel = 0;
    auto del =[&toBeDel](TreeNode<T>* cur) {
        delete cur;
        cur = nullptr;
        ++toBeDel;
    };
    x->travelPre(del);
    size_ -= toBeDel;
    return toBeDel;
}
template <typename T> void AVLTree<T>::Display() {
    std::cout << "\n";
    if (root_ != nullptr) Display(root_);
    else std::cout << "Empty";
    std::cout << "\n";
}
template <typename T>
void AVLTree<T>::Display(TreeNode<T>* cur, int depth) {
    if (cur->lc_) Display(cur->lc_, depth + 1);

    for (int i=0; i < depth; i++)
        printf("     ");

    if (cur->parent_ != nullptr) {
        if ( cur == cur->parent_->lc_) {
            printf("L----");
        } else printf("R----");
    }
    std::cout << "[" << cur->data_ << "] - (" << cur->height_ << ")" << "\n";
    if (cur->rc_) Display(cur->rc_, depth + 1);    
}

template class AVLTree<char>;
template class AVLTree<int>;
template class AVLTree<long long>;
template class AVLTree<float>;
template class AVLTree<double>;
template class AVLTree<std::string>;