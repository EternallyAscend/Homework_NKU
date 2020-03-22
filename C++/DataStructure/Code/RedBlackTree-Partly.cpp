#include<iostream>
using namespace std;
class node {
    friend class rbt;
private:
    bool colourIsRed;
    int value;
    node* left;
    node* right;
    node* parent;
public:
    node();
    node(int value, node *parent);
    ~node();
    void vlr();
};
node::node() {}
node::node(int value, node *parent) :colourIsRed(true), value(value), parent(parent), left(NULL), right(NULL) {}
node::~node() {}
void node::vlr() {
    cout <<" "<< this->value;
    if (this->colourIsRed)cout << "(R)";
    else cout << "(B)";
    if (this->left != NULL)this->left->vlr();
    if (this->right != NULL)this->right->vlr();
}
class rbt {
    friend class node;
private:
    node* root;
public:
    rbt();
    ~rbt();
    void insert(int value);
    node* insertCheck(node *Node);
    void del(int value);
    node* deleteCheck(node *Node);
    void output();
    node* BBNodeCheck(node *Node);
    void getMinAndMax();
    void LL(node *Node);
    void LR(node *Node);
    void RL(node *Node);
    void RR(node *Node);
};
rbt::rbt() :root(NULL) {}
rbt::~rbt() {}
void rbt::insert(int value) {
    node *temp = this->root;
    if (temp == NULL) {
        this->root = new node(value, NULL);
        this->root->colourIsRed = false;
        return;
    }
    while (1) {
        if (temp->value > value) {
            if (temp->left != NULL) { temp = temp->left; }
            else {
                temp->left=new node(value,temp);
                temp=temp->left;
                break;
            }
        }
        else {
            if (temp->right != NULL) { temp = temp->right; }
            else {
                temp->right=new node(value,temp);
                temp=temp->right;
                break;
            }
        }
    }
    while (temp != NULL) { temp = insertCheck(temp); }
}//insert value and go check.
node* rbt::insertCheck(node *Node) {
    if (Node->parent == NULL) {//This node is the root
        Node->colourIsRed = false;
        return NULL;
    }
    if (Node->parent->parent == NULL) {//It maybe useless, the root cannot be red.
        Node->parent->colourIsRed = false;
        return NULL;
    }
    if (Node->parent->colourIsRed) {//No opportunity to have any brother, so check uncle and grandfather.
        node *uncle;
        if (Node->parent->parent->left == Node->parent) {
            uncle = Node->parent->parent->right;
            if (uncle != NULL) {//uncle must be a red Node here.----this idea is wrong!
                if(uncle->colourIsRed){
                    Node->parent->colourIsRed = uncle->colourIsRed = false;
                    Node->parent->parent->colourIsRed = true;
                    return Node->parent->parent;
                }
                else{
                    if(Node->parent->left==Node){
                        Node->parent->parent->colourIsRed=true;
                        Node->parent->colourIsRed=false;
                        LL(Node->parent->parent);
                        return Node->parent;
                    }
                    if(Node->parent->right==Node){
                        Node->colourIsRed=false;
                        Node->parent->parent->colourIsRed=true;
                        LR(Node->parent->parent);
                        return Node;
                    }
                }
            }
            else {//Node doesn't have uncle turn around.
                if (Node->parent->left == Node) {
                    Node->parent->colourIsRed=false;
                    Node->parent->parent->colourIsRed=true;
                    LL(Node->parent->parent);
                    return NULL;
                }
                else {
                    Node->colourIsRed=false;
                    Node->parent->parent->colourIsRed=true;
                    LR(Node->parent->parent);
                    return NULL;
                }
                return NULL;
            }
        }
        else {//uncle is the left
            uncle = Node->parent->parent->left;
            if (uncle != NULL) {//uncle must be a red node here.
                if(uncle->colourIsRed){
                    Node->parent->colourIsRed = uncle->colourIsRed = false;
                    Node->parent->parent->colourIsRed = true;
                    return Node->parent->parent;
                }
                else{
                    if(Node->parent->right==Node){
                        Node->parent->colourIsRed=false;
                        Node->parent->parent->colourIsRed=true;
                        RR(Node->parent->parent);
                        return Node->parent;
                    }
                    if(Node->parent->left==Node){
                        Node->colourIsRed=false;
                        Node->parent->parent->colourIsRed=true;
                        RL(Node->parent->parent);
                        return Node;
                    }
                }
            }
            else {//Node doesn't have uncle turn around.
                if (Node->parent->left == Node) {
                    Node->colourIsRed=false;
                    Node->parent->parent->colourIsRed=true;
                    RL(Node->parent->parent);
                    return NULL;
                }
                else {
                    Node->parent->parent->colourIsRed=true;
                    Node->parent->colourIsRed=false;
                    RR(Node->parent->parent);
                    return NULL;
                }
                return NULL;
            }
        }
    }
    else return NULL;//Red Node with Black Parent Needn't to be adjusted.
}//insert process check.
void rbt::del(int value) {
    node *temp = this->root;
    if (temp == NULL)return;
    while (temp != NULL) {
        if (temp->value == value) { break; }
        if (temp->value < value) { temp = temp->right; }
        if (temp == NULL) { break; }
        if (temp->value > value) { temp = temp->left; }
        if (temp == NULL) { break; }
    }
    node *del = temp;
    if (del == NULL) { return; }
    while (temp != NULL) {
        if (temp != NULL) { del = temp; }
        temp = deleteCheck(temp);
    }
    if (del->parent != NULL) {
        if (del->parent->left == del) { del->parent->left = NULL; }
        if (del->parent->right == del) { del->parent->right = NULL; }
    }
    if (del == this->root) { this->root = NULL; }
    if(del!=NULL) delete del;
}//search value and go check.
node* rbt::deleteCheck(node *Node) {
    bool leftSon = false;
    bool rightSon = false;
    if (Node->left != NULL) leftSon = true;
    if (Node->right != NULL) rightSon = true;
    if (leftSon || rightSon) {//Node has son or sons.
        node *exchange = NULL;
        if (!leftSon) { exchange = Node->right; }//Node only has right son.
        if (!rightSon) { exchange = Node->left; }//Node only has left son.
        if (leftSon&&rightSon) {//Node has two sons, go to find the front step of the Node and exchange them;
            //exchange = Node->left;
            //while (exchange->right != NULL) { exchange = exchange->right; }
            exchange=Node->right;
            while(exchange->left!=NULL){exchange=exchange->left;}
        }
        if (exchange == NULL);
        int value = Node->value;
        Node->value = exchange->value;
        exchange->value = value;
        return exchange;
    }
    else {//Node doesn't have any son.
        if (Node->colourIsRed) {
            if(Node->parent!=NULL){
                if(Node->parent->left==Node){Node->parent->left=NULL;}
                if(Node->parent->right==Node){Node->parent->right=NULL;}
            }
            return NULL;
        }//Node is red with no son, delete directly.
        else {//Node is black with no son,
            if (Node == this->root) { return NULL; }//Node is root, delete directly.
            else {
                if (Node->parent->colourIsRed) {//Red Parent must has a Black uncle.
                    if (Node->parent->left == Node) {
                        RR(Node->parent);
                        Node->parent->left=NULL;
                        if(Node->parent->right!=NULL){insertCheck(Node->parent->right);}
                    }
                    else {
                        LL(Node->parent);
                        Node->parent->left=NULL;
                        if(Node->parent->left!=NULL){insertCheck(Node->parent->left);}
                    }
                }
                else {//Black Node with Black parent.
                    node *uncle;
                    if (Node->parent->left == Node) {
                        uncle = Node->parent->right;//Uncle must be there for black leaf of black parent.
                        if (uncle->colourIsRed) {
                            uncle->colourIsRed = false;
                            RR(Node->parent);
                            if(Node->parent->right!=NULL){Node->parent->right->colourIsRed=true;}
                        }
                        else {
                            if (uncle->left != NULL) {//If uncle has it must be red.
                                uncle->left->colourIsRed = false;
                                Node->parent->colourIsRed=false;
                                RL(Node->parent);
                                return NULL;
                            }
                            if (uncle->right != NULL) {//If uncle has it must be red.
                                uncle->right->colourIsRed = false;
                                RR(Node->parent);
                                return NULL;
                            }
                            uncle->colourIsRed = true;
                            node *cache = Node->parent;
                            Node->parent->left=NULL;
                            while(cache!=NULL){cache=BBNodeCheck(cache);}
                            return NULL;
                        }
                    }
                    else {
                        uncle = Node->parent->left;
                        if (uncle->colourIsRed) {
                            uncle->colourIsRed = false;
                            Node->parent->colourIsRed=false;
                            LL(Node->parent);
                            if(Node->parent->left!=NULL){Node->parent->left->colourIsRed=true;}
                        }
                        else {
                            if (uncle->left != NULL) {//If uncle has it must be red.
                                uncle->left->colourIsRed = false;
                                LL(Node->parent);
                                return NULL;
                            }
                            if (uncle->right != NULL) {//If uncle has it must be red.
                                uncle->right->colourIsRed = false;
                                LR(Node->parent);
                                return NULL;
                            }
                            uncle->colourIsRed = true;
                            node *cache = Node->parent;
                            Node->parent->right=NULL;
                            while(cache!=NULL){cache=BBNodeCheck(cache);}
                            return NULL;
                        }
                    }
                }
            }
        }
        return NULL;
    }
}//delete process check.
void rbt::output() {
    if (this->root != NULL) {
//        this->root->vlr();
        cout<<this->root->value<<"(B)";
        if(this->root->left!=NULL){this->root->left->vlr();}
        if(this->root->right!=NULL){this->root->right->vlr();}
    }
    else cout << "Null";
}
node *rbt::BBNodeCheck(node *Node) {
    node *uncle;
    if(Node->parent==NULL){return NULL;}//Node==this->root
    else{//Can't Up Node->parent is this->root
        if(Node->parent->left==Node){
            uncle=Node->parent->right;
            if(Node->parent->colourIsRed){
                RR(Node->parent);
                if(Node->parent->left!=NULL){insertCheck(Node->parent->left);}
                return NULL;
            }
            //if(uncle==NULL){return NULL;}//uncle can't be nullptr
            if(uncle->colourIsRed){
                uncle->colourIsRed=false;
                RR(Node->parent);
                return NULL;
            }
            else{
                if(uncle->left!=NULL&&uncle->left->colourIsRed){
                    uncle->left->colourIsRed=false;
                    RL(Node->parent);
                    return NULL;
                }
                if(uncle->right!=NULL&&uncle->right->colourIsRed){
                    uncle->right->colourIsRed=false;
                    RR(Node->parent);
                    return NULL;
                }
                uncle->colourIsRed=true;
                return Node->parent;
            }
        }
        else{
            uncle=Node->parent->left;
            if(Node->parent->colourIsRed){
                LL(Node->parent);
                if(Node->parent->right!=NULL){insertCheck(Node->parent->right);}
                return NULL;
            }
            //if(uncle==NULL){return NULL;}//uncle can't be nullptr
            if(uncle->colourIsRed){
                uncle->colourIsRed=false;
                LL(Node->parent);
                return NULL;
            }
            else{
                if(uncle->left!=NULL&&uncle->left->colourIsRed){
                    uncle->left->colourIsRed=false;
                    LL(Node->parent);
                    return NULL;
                }
                if(uncle->right!=NULL&&uncle->right->colourIsRed){
                    uncle->right->colourIsRed=false;
                    LR(Node->parent);
                    return NULL;
                }
                uncle->colourIsRed=true;
                return Node->parent;
            }
        }
    }
}
void rbt::getMinAndMax() {
    if (this->root == NULL) { return; }
    else {
        node* min = this->root;
        node* max = this->root;
        while (min->left != NULL) { min = min->left; }
        while (max->right != NULL) { max = max->right; }
        cout <<endl<< min->value << " " << max->value << endl;
    }
}
void rbt::LL(node *Node) {
    node *temps = Node->left;
    if (Node->parent == NULL) { this->root = temps; }
    else {
        if (Node->parent->left == Node) { Node->parent->left = temps; }
        else { Node->parent->right = temps; }
    }
    temps->parent = Node->parent;
    Node->left = temps->right;
    if (temps->right != NULL) { temps->right->parent = Node; }
    temps->right = Node;
    Node->parent = temps;
}
void rbt::LR(node *Node) {
    node *tempss = Node->left->right;
    if (Node->parent == NULL) { this->root = tempss; }
    else {
        if (Node->parent->left == Node) { Node->parent->left = tempss; }
        else { Node->parent->right = tempss; }
    }
    tempss->parent = Node->parent;
    Node->left->right = tempss->left;
    if (tempss->left != NULL) { tempss->left->parent = Node->left; }
    tempss->left = Node->left;
    Node->left->parent = tempss;
    Node->left = tempss->right;
    if (tempss->right != NULL) { tempss->right->parent = Node; }
    tempss->right = Node;
    Node->parent = tempss;
}
void rbt::RL(node *Node) {
    node *tempss = Node->right->left;
    if (Node->parent == NULL) { this->root = tempss; }
    else {
        if (Node->parent->left == Node) { Node->parent->left = tempss; }
        else { Node->parent->right = tempss; }
    }
    tempss->parent = Node->parent;
    Node->right->left = tempss->right;
    if (tempss->right != NULL) { tempss->right->parent = Node->right; }
    tempss->right = Node->right;
    Node->right->parent = tempss;
    Node->right = tempss->left;
    if (tempss->left != NULL) { tempss->left->parent = Node; }
    tempss->left = Node;
    Node->parent = tempss;
}
void rbt::RR(node *Node) {
    node *temps = Node->right;
    if (Node->parent == NULL) { this->root = temps; }
    else {
        if (Node->parent->left == Node) { Node->parent->left = temps; }
        else { Node->parent->right = temps; }
    }
    temps->parent = Node->parent;
    Node->right = temps->left;
    if (temps->left != NULL) { temps->left->parent = Node; }
    temps->left = Node;
    Node->parent = temps;
}
int main(void) {
    int n, m;
    rbt test;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> m;
        test.insert(m);
    }
    test.output();
    test.getMinAndMax();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> m;
        test.del(m);
    }
    test.output();
    return 0;
}
