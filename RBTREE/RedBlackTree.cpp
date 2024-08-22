# include "RedBlackTree.h"

template <typename T>
RBNode<T>* RBTree<T>::TreeMinimum(RBNode<T>* cur) const {
    while (cur->lc_ != tNil) {
        cur = cur->lc_;       
    }
    return cur;

}
template <typename T>
void RBTree<T>::LeftRotate(RBNode<T>* x) {
    RBNode<T>* y = x->rc_;
    if (y == tNil) return;
    x->rc_ = y->lc_;
    if (y->lc_ != tNil) y->lc_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_ == tNil) root_ = y;
    else if (x == x->parent_->lc_) x->parent_->lc_ = y;
    else x->parent_->rc_ = y;
    y->lc_ = x;
    x->parent_ = y;   
}
template <typename T>
void RBTree<T>::RightRotate(RBNode<T>* x) {
    RBNode<T>* y = x->lc_;
    if (y == tNil) return;
    x->lc_ = y->rc_;
    if (y->rc_ != tNil) y->rc_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_ == tNil) root_ = y;
    else if (x == x->parent_->lc_) x->parent_->lc_ = y;
    else x->parent_->rc_ = y;
    y->rc_ = x;
    x->parent_ = y;      
}
template <typename T>
RBNode<T>* RBTree<T>::RBInsert(T const& val) {
    RBNode<T>* curPosi = root_; // node being compared with z
    RBNode<T>* targetPosiParent = tNil; // targetPosiParent will be parent of the target node with the value val
    while (curPosi != tNil) { // descending until reaching the sentinel
        targetPosiParent = curPosi;
        if (curPosi->data_ > val) curPosi = curPosi->lc_;
        else curPosi = curPosi->rc_;
    }
    // found the location, create node z, and insert z with its parent, targetPosiParent
    // moreover, make sure that both of z's children are the sentinel and z starts out red
    RBNode<T>* z = new RBNode<T>(val, targetPosiParent, tNil, tNil, RB_RED); 
    if (targetPosiParent == tNil) {
        // tree was empty
        root_ = z;
        root_->color_ = RB_BLACK;
        return z;
    } 
    else if (targetPosiParent->data_ > val) targetPosiParent->lc_ = z;
    else targetPosiParent->rc_ = z;
    RBInsertFixUp(z);
    return z;
}
template <typename T>
void RBTree<T>::RBInsertFixUp(RBNode<T>* z) {
    while (z->parent_->color_ == RB_RED) {
        RBNode<T>* uncle = tNil; // uncle will be z's uncle
        if (z->parent_ == z->parent_->parent_->lc_) { // is z’s parent a left child?
            uncle = z->parent_->parent_->rc_; 
            if (uncle->color_ == RB_RED)  {// are z's parent and uncle both red?
                // case 1:  z's parent and uncle are both red
                z->parent_->color_ = RB_BLACK;
                uncle->color_ = RB_BLACK;
                z->parent_->parent_->color_ = RB_RED;
                z = z->parent_->parent_;
            } else {
                if (z == z->parent_->rc_) {
                    // case 2: uncle is red and 
                    z == z->parent_;
                    LeftRotate(z);
                }
                // case 3
                z->parent_->color_ = RB_BLACK;
                z->parent_->parent_->color_ = RB_RED;
                RightRotate(z->parent_->parent_);
            }
        } else { // same as lines 103~119, but with "lc_" and "rc_" exchanged
            uncle = z->parent_->parent_->rc_;
            if (uncle->color_ == RB_RED) {
                z->parent_->color_ = RB_BLACK;
                uncle->color_ = RB_BLACK;
                z->parent_->parent_->color_ = RB_RED;
                z = z->parent_->parent_;
            } else {
                if (z == z->parent_->lc_) {
                    z= z->parent_;
                    RightRotate(z);
                }
                z->parent_->color_ = RB_BLACK;
                z->parent_->parent_->color_ = RB_RED;
                LeftRotate(z->parent_->parent_);
            }
        }
    }
    root_->color_ = RB_BLACK;
}
template <typename T>
void RBTree<T>::RBTransplant(RBNode<T>* toBeSubstituted, RBNode<T>* vertex) {
    if (toBeSubstituted->parent_ == tNil) root_ = vertex;
    else if (toBeSubstituted == toBeSubstituted->parent_->lc_) toBeSubstituted->parent_->lc_ = vertex;
    else toBeSubstituted->parent_->rc_ = vertex;
    // yes, the assignment to v.p happens unconditionally
    vertex->parent_ = toBeSubstituted->parent_;
}
template <typename T>
void RBTree<T>::RBDeletion(RBNode<T>* z) {
    RBNode<T>* y = z;
    RBColor yOriginalColor = y->color_;
    RBNode<T>* x = tNil;
    if (z->lc_ == tNil) {
        x = z->rc_;
        RBTransplant(z, z->rc_); // replace z by its right child
    } else if (z->rc_ == tNil) {
        x = z->lc_;
        RBTransplant(z, z->lc_); // replace z by its left child
    } else {
        y = TreeMinimum(z->rc_); // y is z's successor
        yOriginalColor = y->color_;
        x = y->rc_;
        if (y != z->rc_) {
            RBTransplant(y, y->rc_);
            y->rc_ = z->rc_;
            y->rc_->parent_ = y;
        } else x->parent_ = y;
        RBTransplant(z, y);
        y->lc_ = z->lc_;
        y->lc_->parent_ = y;
        y->color_ = z->color_;
    }
    if (yOriginalColor == RB_BLACK) RBDeleteFixUp(x);
}
template <typename T>
void RBTree<T>::RBDeleteFixUp(RBNode<T>* x) {
    if (x == x->parent_->lc_) {
        RBNode<T>* w = x->parent_->rc_;
        if (w->color_ == RB_RED) {
            w->color_ = RB_BLACK;
        }

    } else {

    }

}
template <typename T>
void RBTree<T>::Display(RBNode<T>* cur, int depth) {
    if (cur->lc_ != tNil && cur->lc_ != nullptr) Display(cur->lc_, depth + 1);
    for (int i = 0; i < depth; ++i) std::cout << "      ";
    if (cur != root_) {
        if (cur == cur->parent_->lc_) {
            std::cout << "L----";
        } else std::cout << "R----";
    }
    std::cout << "(" << cur->data_ << ")" <<"-"<< colorStr[cur->color_] << "\n";
    if (cur->rc_ != tNil && cur->rc_ != nullptr) Display(cur->rc_, depth + 1);
}
template <typename T>
void RBTree<T>::Display() {
    if (root_ != tNil && root_ != nullptr) Display(root_);
}

template class RBTree<char>;
template class RBTree<int>;
template class RBTree<long long>;
template class RBTree<float>;
template class RBTree<double>;
template class RBTree<std::string>;