// author Yunhan Du
#include "TreeNode.h"
#include <string>

template<typename T> TreeNode<T>* TreeNode<T>::insertAsLC(T const& lcVal) {
    lc_ = new TreeNode<T>(lcVal, this);
    return lc_;
}
template<typename T> TreeNode<T>* TreeNode<T>::insertAsRC(T const& rcVal) {
    rc_ = new TreeNode<T>(rcVal, this);
    return rc_;
}

template <typename T> void display(TreeNode<T>* cur, int depth) {
    if (cur-> lc_ != nullptr) display(cur->lc_, depth + 1);
    for (int i = 0; i < depth; ++i) {
        std::cout << "     ";
    }
    if (cur->parent_ != nullptr) {
        if ( cur == cur->parent_->lc_) {
            printf("┌───");
        } else printf("└───");
    }
    std::cout << "[" << cur->data_ << "] " << "\n";
    if (cur->rc_ != nullptr) display(cur->rc_, depth + 1);
}
template class TreeNode<char>;
template class TreeNode<int>;
template class TreeNode<long long>;
template class TreeNode<float>;
template class TreeNode<double>;
template class TreeNode<std::string>;


