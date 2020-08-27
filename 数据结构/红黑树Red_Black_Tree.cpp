#include <cstdio>
#define MAXN 100005

#define pp p->p
#define iscl(x) ((x) != NULL &&(x)->p != NULL && (x)->p->le == (x))
#define iscr(x) ((x) != NULL &&(x)->p != NULL && (x)->p->ri == (x))

template<typename T>
class redblacktree{
    
private:
    enum ColorRB{RED,BLACK};
    struct Node;

    //Node* _nil=new Node();//如何实现哨兵？？
    Node* _root=NULL;    ////根节点位置

    void insert_FixUp(Node*);
    void left_Rotate(Node*);
    void right_Rotate(Node*);
    void transplant(Node*,Node*);
    void erase(Node*);
    void erase_FixUp(Node*);


public:
    class iterator;

    // redblacktree() : _root(NULL), _hot(NULL) {}
    iterator begin();
    iterator end();
    iterator rend();
    iterator find(T);
    iterator insert(T);
    iterator lower_bound(T);
    iterator upper_bound(T);
    void erase(T);
    bool empty();

};

template<typename T>
struct redblacktree<T>::Node{
    T key;
    ColorRB color;//RED BLACK
    Node* p;//parent
    Node* le;
    Node* ri;
    int size;

    //Node():color(BLACK){}
    Node(T k,ColorRB c,Node* pa,Node* l,Node* r)
        :key(k),color(c),p(pa),le(l),ri(r),size(1){}

    Node* succ(){
        Node* cur=this;
        
        if(cur->ri==NULL){//没右孩子
            while(iscr(cur))
                cur=cur->p;
            cur=cur->p;
        }
        else{//有右孩子
            cur=cur->ri;
            while(cur->le!=NULL)
                cur=cur->le;
        }
        return cur;
        
        //return cur->move(1);??
    }

    Node* pred(){
        Node* cur=this;
        
        if(cur->le==NULL){
            while(iscl(cur))
                cur=cur->p;
            cur=cur->p;
        }
        else{
            cur=cur->le;
            while(cur->ri!=NULL)
                cur=cur->ri;
        }
        return cur;
        
        //return cur->move(-1);
    }

    int rank(){
        Node* cur=this;
        int cnt=0;
        while(cur!=NULL){
            cnt++;
            if(cur->le!=NULL)
                cnt+=cur->le->size;
            while(iscl(cur)){
                cur=cur->p;
            }
            cur=cur->p;
        }
        return cnt;
    }

    Node* move(int x){//非递归实现
        Node* cur=this;
        int cnt=0;
        while(cnt!=x){
            if(cnt<x){//cur偏移在右边
                if(cur->ri==NULL || cnt+cur->ri->size<x){//cur偏移在p
                    cnt++;
                    if(cur->ri!=NULL)
                        cnt+=cur->ri->size;
                    while(iscr(cur)){//父亲在左
                        cur=cur->p;
                    }//确保父亲一定在右，否则无
                    if(iscl(cur)){//父亲在左
                        cur=cur->p;//偏移父亲
                    }
                    else{
                        return NULL;
                    }
                }
                else{//cur偏移在右孩子左右
                    cur=cur->ri;//偏移到右孩子
                    cnt++;
                    if(cur->le!=NULL)
                        cnt+=cur->le->size;
                }
            }
            else{//cur偏移在左边
                if(cur->le==NULL || cnt-cur->le->size>x){//cur偏移在p
                    cnt--;
                    if(cur->le!=NULL)
                        cnt-=cur->le->size;
                    while(iscl(cur)){//父亲在右
                        cur=cur->p;
                    }//确保父亲一定在左，否则无
                    if(iscr(cur)){//父亲在左
                        cur=cur->p;//偏移父亲
                    }
                    else{//
                        return NULL;
                    }
                }
                else{//cur偏移在左孩子左右
                    cur=cur->le;//偏移到左孩子
                    cnt--;
                    if(cur->ri!=NULL)
                        cnt-=cur->ri->size;
                }
            }
        }
        return cur;
    }
};

template<typename T>
class redblacktree<T>::iterator{
    
private:

    Node* _node;

public:

    T operator*() {
        return _node->key;
    }

    iterator& operator++(){
        _node=_node->succ();
        return *this;
    }

    iterator operator++(int){
        iterator tem=*this;
        _node=_node->succ();
        return tem;
    }

    iterator& operator--(){
        _node=_node->pred();
        return *this;
    }

    iterator operator--(int){
        iterator tem=*this;
        _node=_node->pred();
        return tem;
    }

    bool operator==(const iterator b)const{
        return _node==b._node;
    }

    bool operator!=(const iterator b)const{
        return _node!=b._node;
    }

    int operator-(const iterator b){
        return _node->rank()-b._node->rank();
    }

    iterator operator+(const int b){
        return iterator(_node->move(b));
    }

    iterator operator-(const int b){//没试过，test later
        return iterator(_node->move(-b));
    }

    iterator(Node* x = NULL) : _node(x) {}//??

};

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::begin() {
    Node* cur=_root;
    Node* tem=NULL;
    while(cur!=NULL){
        tem=cur;
        cur=cur->le;
    }
    return iterator(tem);
}

template<typename T>
bool redblacktree<T>::empty() {
    return _root==NULL;
}

//TODO: 实现end-- 并移除rend
template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::end() {
    return iterator(NULL);
}

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::rend() {
    Node* cur=_root;
    Node* tem=NULL;
    while(cur!=NULL){
        tem=cur;
        cur=cur->ri;
    }
    return iterator(tem);
}

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::find(T key) {//找第一个Key，否则NULL
    Node* cur=_root;
    while(cur!=NULL&&cur->key!=key){
        if(cur->key<key)
            cur=cur->ri;
        else
            cur=cur->le;
    }
    return iterator(cur);
}

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::lower_bound(T key) {//找第一个Key
    Node* cur=_root;
    Node* tem=NULL;
    while(cur!=NULL){
        tem=cur;
        if(cur->key<key)
            cur=cur->ri;
        else
            cur=cur->le;
    }
    if(tem->key<key)
        tem=tem->succ();
    return iterator(tem);
}

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::upper_bound(T key) {//否则NULL
    Node* cur=_root;
    Node* tem=NULL;
    while(cur!=NULL){
        tem=cur;
        if(key<cur->key)
            cur=cur->le;
        else
            cur=cur->ri;
    }
    if(!(key<tem->key))
        tem=tem->succ();
    return iterator(tem);
}

template<typename T>
void redblacktree<T>::left_Rotate(Node* cur){
    Node* tem=cur->ri;

    cur->ri=tem->le;//adopt tem-left
    if(tem->le!=NULL){
        tem->le->p=cur;
    }

    //drop cur,adopt tem
    if(cur->p==NULL)
        _root=tem;
    else if(iscl(cur))
        cur->p->le=tem;
    else
        cur->p->ri=tem;
    tem->p=cur->p;

    tem->le=cur;//adopt cur
    cur->p=tem;

    cur->size=(cur->le==NULL?0:cur->le->size)+(cur->ri==NULL?0:cur->ri->size)+1;
    tem->size=(tem->le==NULL?0:tem->le->size)+(tem->ri==NULL?0:tem->ri->size)+1;
}

template<typename T>
void redblacktree<T>::right_Rotate(Node* cur){
    Node* tem=cur->le;
    cur->le=tem->ri;//adopt tem-right
    if(tem->ri!=NULL){
        tem->ri->p=cur;
    }

    //adopt tem
    if(cur->p==NULL)
        _root=tem;
    else if(iscr(cur))
        cur->p->ri=tem;
    else
        cur->p->le=tem;
    tem->p=cur->p;

    tem->ri=cur;//adopt cur
    cur->p=tem;

    cur->size=(cur->le==NULL?0:cur->le->size)+(cur->ri==NULL?0:cur->ri->size)+1;
    tem->size=(tem->le==NULL?0:tem->le->size)+(tem->ri==NULL?0:tem->ri->size)+1;
}

template<typename T>
typename
redblacktree<T>::iterator redblacktree<T>::insert(T key) {
    Node* cur=_root;
    Node* tem=NULL;
    while(cur!=NULL){  //find
        tem=cur;
        tem->size++;
        if(key<cur->key)
            cur=cur->le;
        else cur=cur->ri;
    }
    cur = new Node(key,RED,tem,NULL,NULL);
    if(tem==NULL)//root is empty
        _root=cur;
    else if(key<tem->key)
        tem->le=cur;
    else tem->ri=cur;
    insert_FixUp(cur);
    return iterator(cur);
}

template<typename T>
void redblacktree<T>::insert_FixUp(Node* cur){
    Node* uncle;
    while(cur->p!=NULL && cur->p->color==RED){
        if(iscl(cur->p)){
            uncle=cur->pp->ri;
            if(uncle!=NULL && uncle->color==RED){//case 1:red-red*2-black
                cur->p->color=BLACK;
                uncle->color=BLACK;
                cur->pp->color=RED;
                cur=cur->pp;
            }
            else{
                if(iscr(cur)){//case 2 -> case 3
                    cur=cur->p;
                    left_Rotate(cur);
                }
                //case 3
                cur->p->color=BLACK;
                cur->pp->color=RED;
                right_Rotate(cur->pp);
            }
        }
        else{
            uncle=cur->pp->le;
            if(uncle!=NULL && uncle->color==RED){//case 1:red-red*2-black
                cur->p->color=BLACK;
                uncle->color=BLACK;
                cur->pp->color=RED;
                cur=cur->pp;
            }
            else{
                if(iscl(cur)){//case 2 -> case 3
                    cur=cur->p;
                    right_Rotate(cur);
                }
                //case 3
                cur->p->color=BLACK;
                cur->pp->color=RED;
                left_Rotate(cur->pp);
            }
        }
    }
    _root->color=BLACK;
}

//TODO delete all
//Now delete 1
template<typename T>
void redblacktree<T>::erase(T key){
    Node* cur=_root;
    while(cur!=NULL&&cur->key!=key){
        if(cur->key<key)
            cur=cur->ri;
        else
            cur=cur->le;
    }
    erase(cur);
}

template<typename T>
void redblacktree<T>::erase(Node* cur){
    if(cur==NULL) return;
    Node* rep;
    if(cur->le!=NULL && cur->ri!=NULL){//双子换后继
        rep=cur->succ();//后继在右
        //swap key
        T temp=rep->key;
        rep->key=cur->key;
        cur->key=temp;
        //redirect cur
        cur=rep;
    }//确保最多只有一个儿子
    if(cur->le==NULL){
        rep=cur->ri;
    }
    else{
        rep=cur->le;
    }
    if(cur->color==BLACK && (rep==NULL || rep->color==BLACK))
        erase_FixUp(cur);
    transplant(cur,rep);
    if(cur->color==BLACK && rep!=NULL)
        rep->color=BLACK;
    Node* tem=cur->p;
    while(tem!=NULL){
        tem->size--;
        tem=tem->p;
    }
    delete cur;
}

template<typename T>
void redblacktree<T>::erase_FixUp(Node* cur){
    Node* sib;
    while(cur->p!=NULL && cur->color==BLACK){
        if(iscl(cur)){
            sib=cur->p->ri;
            if(sib!=NULL && sib->color==RED){//sib是红的
                cur->p->color=RED;
                sib->color=BLACK;
                left_Rotate(cur->p);
                sib=cur->p->ri;
            }//确保sibling是黑的
            if(sib!=NULL && sib->le!=NULL && sib->le->color==RED){//sib有斜红孩子
                sib->color=RED;
                sib->le->color=BLACK;
                right_Rotate(sib);
            }//如果sib有红孩子确保是直线
            if(sib!=NULL && sib->ri!=NULL && sib->ri->color==RED){//sib有直线红孩子
                sib->color=sib->p->color;
                sib->p->color=BLACK;
                left_Rotate(sib->p);
                break;
            }//搞定
        }
        else{
            sib=cur->p->le;
            if(sib!=NULL && sib->color==RED){//sib是红的
                cur->p->color=RED;
                sib->color=BLACK;
                right_Rotate(cur->p);
                sib=cur->p->le;
            }//确保sibling是黑的
            if(sib!=NULL && sib->ri!=NULL && sib->ri->color==RED){//sib有斜红孩子
                sib->color=RED;
                sib->ri->color=BLACK;
                left_Rotate(sib);
            }//如果sib有红孩子确保是直线
            if(sib!=NULL && sib->le!=NULL && sib->le->color==RED){//sib有直线红孩子
                sib->color=sib->p->color;
                sib->p->color=BLACK;
                right_Rotate(sib->p);
                break;
            }//搞定
        }
        cur=cur->p;
    }
    cur->color=BLACK;
}

template<typename T>
void redblacktree<T>::transplant(Node* cur,Node* curc){
    if(cur->p==NULL)
        _root=curc;
    else if(iscl(cur))
        cur->p->le=curc;
    else cur->p->ri=curc;
    if(curc!=NULL)
        curc->p=cur->p;
}




int n;
redblacktree<int> r;
redblacktree<int>::iterator ite;

int main(){

    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        int opt,x;
        scanf("%d %d", &opt, &x);
        if(opt==1){
            r.insert(x);
        }
        else if(opt==2){
            r.erase(x);
        }
        else if(opt==3){
            ite=r.lower_bound(x);
            if(ite==r.end()){
                printf("%d\n",r.rend()-r.begin()+2);
            }
            else printf("%d\n",ite-r.begin()+1);
        }
        else if(opt==4){
            printf("%d\n",*(r.begin()+(x-1)));
        }
        else if(opt==5){
            ite=r.lower_bound(x);
            if(ite==r.end()){
                printf("%d\n",*(r.rend()));
            }
            else printf("%d\n",*(ite-1));
        }
        else{
            printf("%d\n",*(r.upper_bound(x)));
        }
    }
    return 0;
}
