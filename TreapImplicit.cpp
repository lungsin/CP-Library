#include<bits/stdc++.h>

using namespace std;

typedef struct node{
    int prior,size;
    int val;//value stored in the array
    int sum;//whatever info you want to maintain in segtree for each node
    int lazy;//whatever lazy update you want to do
    struct node *l,*r;
}node;
typedef node* pnode;

int sz(pnode t){
    return t?t->size:0;
}
pnode init(int val){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior=rand();ret->size=1;
    ret->val=val;
    ret->sum=val;ret->lazy=0;
    return ret;
}

void fix_node(pnode t){
    if(t){
        t->size=sz(t->l)+1+sz(t->r);//fix size
        t->p = 0;//reset parent
		if(t->l) t->l->p = t;//fix parent of child
        if(t->r) t->r->p = t;//fix parent of child
    }
}

void lazy(pnode t){
    if(!t || !t->lazy)return;
    t->val+=t->lazy;//operation of lazy
    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy=0;
}

void reset(pnode t){
    if(t)t->sum = t->val;
}

void combine(pnode& t,pnode l,pnode r){//combining two ranges of segtree
    if(!l || !r)return void(t = l?l:r);
    t->sum = l->sum + r->sum;
}

void operation(pnode t){//operation of segtree
    if(!t)return;
    reset(t);//reset the value of current node assuming it now represents a single element of the array
    lazy(t->l);lazy(t->r);//imp:propagate lazy before combining t->l,t->r;
    combine(t,t->l,t);
    combine(t,t,t->r);
}

void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
    if(!t)return void(l=r=NULL);
    lazy(t);
    int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)//element at pos goes to left subtree(l)
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else 
        split(t->l,l,t->l,pos,add),r=t;
    fix_node(t);
    operation(t);
}

void merge(pnode &t,pnode l,pnode r){ //l->leftarray,r->rightarray,t->resulting array
    lazy(l);lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
    fix_node(t);
    operation(t);
}

pnode root(pnode t){
    if(!t)return t;
    while(t->p)t = t->p;
    return t;
}

int orderOf(pnode t){
    if(!t)return 0;
    
    int ret = sz(ch->l) + 1;
    while(t->p){
        pnode ch = t; t = t->p;
        if(t->r==t)ret += sz(t->l)+1;
    }
    return ret;
}

/*
Documentation

----- Treap Method -----
int sz(pnode t)                                 : return the size of treap
pnode init(int val)                             : initialize new node with the value val
void fix_node(pnode t)                          : fix the node variable (size and parent)

void merge(pnode &t,pnode l,pnode r)            : merge two treap 
void split(pnode t,pnode &l,pnode &r,int key)   : split two treap , l <=key, r >key
pnode root(pnode t)                             : find the root of the treap
int orderOf(pnode t)                            : find what is the index of t

----- Segment tree method ----
void operation(pnode t)                         : the operation of segment tree, relax the segment
void lazy(pnode t)                              : propagate lazy
void reset(pnode t)                             : reset the segment into the value of single node
void combine(pnode& t,pnode l,pnode r)          : combine two segment
*/