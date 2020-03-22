#include <iostream>
using namespace std;
class node{
    friend class avlt;
private:
    int value;
    int height;
    node* left;
    node* right;
    node* parent;
public:
    node(int value,node* parent):value(value),height(1),left(nullptr),right(nullptr),parent(parent){}
    ~node(){}
    void vlr(){
        cout<<this->value<<" ("<<this->height<<"); ";
        if(this->left!=nullptr){this->left->vlr();}
        if(this->right!=nullptr){this->right->vlr();}
    }
    void Ascend(){
        int left,right;
        left=right=0;
        if(this->left!=nullptr){left=this->left->height;}
        if(this->right!=nullptr){right=this->right->height;}
        this->height=left>right?left+1:right+1;
        if(this->parent!=nullptr){this->parent->Ascend();}
    }
};
class avlt{
    friend class node;
private:
    node* root;
public:
    avlt():root(nullptr){}
    ~avlt(){deleteNode(this->root);}
    void deleteNode(node* Node){
        if(Node!= nullptr){
            if(Node->left!= nullptr){deleteNode(Node->left);}
            if(Node->right!= nullptr){deleteNode(Node->right);}
            delete Node;
        }
        else return;
    }
    void insert(int value){
        if(this->root==nullptr){this->root=new node(value,nullptr);return;}
        node* temp=this->root;
        while(1){
            if(temp->value>value){
                if(temp->left==nullptr){
                    temp->left=new node(value,temp);
                    temp=temp->left;
                    break;
                }
                else{temp=temp->left;}
            }
            else{
                if(temp->right==nullptr){
                    temp->right=new node(value,temp);
                    temp=temp->right;
                    break;
                }
                else{temp=temp->right;}
            }
        }
        temp->Ascend();
        while(temp!=nullptr){temp=insertCheck(temp);}
        this->output();
        cout<<endl;
    }
    void del(int value){
        node* temp=this->root;
        if(temp==nullptr){return;}
        else{
            while(temp!=nullptr){
                if(temp->value==value){break;}
                if(temp->value>value){temp=temp->left;}
                else{temp=temp->right;}
            }
        }
        while(temp!=nullptr){temp=deleteCheck(temp);}
        this->output();
        cout<<"            -"<<value<<endl;
    }
    node* insertCheck(node *Node){
        if(Node->parent==nullptr){return nullptr;}
        if(Node->parent->parent==nullptr){return nullptr;}
        else{
            int l,r,sl,sr;
            l=r=sl=sr=0;
            if(Node->parent->parent->left!=nullptr){l=Node->parent->parent->left->height;}
            if(Node->parent->parent->right!=nullptr){r=Node->parent->parent->right->height;}
            if(l-r==2){
                if(Node->parent->parent->left->left!=nullptr){sl=Node->parent->parent->left->left->height;}
                if(Node->parent->parent->left->right!=nullptr){sr=Node->parent->parent->left->right->height;}
                if(sl>sr){return LL(Node->parent->parent);}
                if(sl<sr){return LR(Node->parent->parent);}
            }
            if(l-r==-2){
                if(Node->parent->parent->right->left!=nullptr){sl=Node->parent->parent->right->left->height;}
                if(Node->parent->parent->right->right!=nullptr){sr=Node->parent->parent->right->right->height;}
                if(sl>sr){return RL(Node->parent->parent);}
                if(sl<sr){return RR(Node->parent->parent);}
            }
			return Node->parent;
        }
    }
    node* deleteCheck(node *Node){
        bool leftSon=false;
        bool rightSon=false;
        if(Node->left!=nullptr){leftSon=true;}
        if(Node->right!=nullptr){rightSon=true;}
        if(leftSon||rightSon){
            node* exchange=nullptr;
            if(!leftSon){exchange=Node->right;}
            if(!rightSon){exchange=Node->left;}
            if(exchange==nullptr){
                exchange=Node->right;
                while(exchange->left!=nullptr){exchange=exchange->left;}
            }
            Node->value=exchange->value;
            return exchange;
        }
        else{
            node* temp=nullptr;
            if(Node->parent==nullptr){
                this->root=nullptr;
                delete Node;
                return nullptr;
            }
            if(Node->parent->left==Node){Node->parent->left=nullptr;}
            if(Node->parent->right==Node){Node->parent->right=nullptr;}
            Node->parent->Ascend();
            temp=Node->parent;
            while(temp!=nullptr){temp=deleteAscend(temp);}
            delete Node;
            return nullptr;
        }
    }
    node* deleteAscend(node* Node){
        node* temp=Node->parent;
        int l,r,sl,sr;
        l=r=sl=sr=0;
        if(Node->left!=nullptr){l=Node->left->height;}
        if(Node->right!=nullptr){r=Node->right->height;}
        if(l-r==2){
            if(Node->left->left!=nullptr){LL(Node);}
            else if(Node->left->right!=nullptr){LR(Node);}
        }
        if(l-r==-2){
            if(Node->right->left!=nullptr){RL(Node);}
            else if(Node->right->right!=nullptr){RR(Node);}
        }
        return temp;
    }
    void output(){if(this->root!=nullptr)this->root->vlr();}
    node* LL(node* Node){
        node* temps=Node->left;
        if(Node->parent==nullptr){this->root=temps;}
        else{
            if(Node->parent->left==Node){Node->parent->left=temps;}
            else{Node->parent->right=Node;}
        }
        temps->parent=Node->parent;
        Node->left=temps->right;
        if(temps->right!=nullptr){temps->right->parent=Node;}
        temps->right=Node;
        Node->parent=temps;
        Node->Ascend();
        return temps;
    }
    node* LR(node* Node){
        node* tempss=Node->left->right;
        if(Node->parent==nullptr){this->root=tempss;}
        else{
            if(Node->parent->left==Node){Node->parent->left=tempss;}
            else{Node->parent->right=tempss;}
        }
        tempss->parent=Node->parent;
        Node->left->right=tempss->left;
        if(tempss->left!= nullptr){tempss->left->parent=Node->left;}
        tempss->left=Node->left;
        Node->left->parent=tempss;
        Node->left=tempss->right;
        if(tempss->right!=nullptr){tempss->right->parent=Node;}
        tempss->right=Node;
        Node->parent=tempss;
        tempss->left->Ascend();
        Node->Ascend();
        return tempss;
    }
    node* RL(node* Node){
        node* tempss=Node->right->left;
        if(Node->parent==nullptr){this->root=tempss;}
        else{
            if(Node->parent->left==Node){Node->parent->left=tempss;}
            else{Node->parent->right=tempss;}
        }
        tempss->parent=Node->parent;
        Node->right->left=tempss->right;
        if(tempss->right!=nullptr){tempss->right->parent=Node->right;}
        tempss->right=Node->right;
        Node->right->parent=tempss;
        Node->right=tempss->left;
        if(tempss->left!=nullptr){tempss->left->parent=Node;}
        tempss->left=Node;
        Node->parent=tempss;
        tempss->right->Ascend();
        Node->Ascend();
        return tempss;
    }
    node* RR(node* Node){
        node* temps=Node->right;
        if(Node->parent==nullptr){this->root=temps;}
        else{
            if(Node->parent->left==Node){Node->parent->left=temps;}
            else{Node->parent->right=temps;}
        }
        temps->parent=Node->parent;
        Node->right=temps->left;
        if(temps->left!=nullptr){temps->left->parent=Node;}
        temps->left=Node;
        Node->parent=temps;
        Node->Ascend();
        return temps;
    }
};
int main() {
    int n,m;
    cin>>n;
    avlt tree;
    for(int i=0;i<n;i++){
        cin>>m;
        tree.insert(m);
    }
    tree.output();
    cout<<endl<<"delete"<<endl;
    for(int i=0;i<n;i++){
        cin>>m;
        tree.del(m);
    }
    tree.output();
    system("pause");
    return 0;
}
