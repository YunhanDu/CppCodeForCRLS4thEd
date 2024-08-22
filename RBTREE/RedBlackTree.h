#ifndef BlackRedTree_h
#define BlackRedTree_h
// author: Claude Du
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using std::vector;
typedef enum {RB_RED, RB_BLACK} RBColor;

template <typename T>
struct RBNode {
    T data_;
    RBNode<T>* parent_;
    RBNode<T>* lc_;
    RBNode<T>* rc_;
    RBColor color_;
    // RBNode() : lc_(nullptr), rc_(nullptr), color_(RB_RED) {};
    RBNode(T data = 0, RBNode<T>* parent = nullptr, RBNode<T>* lc = nullptr,
            RBNode<T>* rc = nullptr, RBColor color = RB_RED) : 
            data_(data), parent_(parent), lc_(lc), rc_(rc), color_(color) {}
};

template <typename T> 
class RBTree {
private:
    RBNode<T>* root_;
    RBNode<T>* tNil;
    const vector<std::string> colorStr{"RED", "BLK"};
    void Display(RBNode<T>* cur, int depth = 0);
public:
    RBTree() {
        tNil = new RBNode<T>();
        tNil->color_ = RB_BLACK;
        root_ = tNil;
    }
    RBNode<T>* TreeMinimum(RBNode<T>* cur) const;
    void LeftRotate(RBNode<T>* x);
    void RightRotate(RBNode<T>* x);
    // insertion
    RBNode<T>* RBInsert(T const& val);
    void RBInsertFixUp(RBNode<T>* z);
    // deletion
    void RBTransplant(RBNode<T>* toBeSubstituted, RBNode<T>* vertex);
    // bool RBDeletion(T const& val);
    void RBDeletion(RBNode<T>* z);
    void RBDeleteFixUp(RBNode<T>* z);
    // debug
    void Display();


};

#endif /*BinarySearchTree_h*/