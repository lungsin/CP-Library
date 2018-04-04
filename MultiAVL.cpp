#include <bits/stdc++.h>
using namespace std;

#define _L cur->l
#define _R cur->r
#define param node* cur

struct node {
  node *l, *r;
  int h, sz, val, num;
  node() {l = r = NULL;}
  node(int val): val(val) {l = r = NULL; h = sz = num = 1; }
};

int getH(param) { return (cur == NULL) ? 0 : cur->h; }
int getSz(param) { return (cur == NULL) ? 0 : cur->sz; }
int getBF(param) { return (cur == NULL) ? 0 : (getH(_L) - getH(_R)); }

node* root = NULL;

void fix(param) {
  if (cur == NULL) return;
  cur->h = max(getH(_L), getH(_R)) + 1;
  cur->sz = getSz(_L) + getSz(_R) + cur->num;
}

node* rotateRight(param) {
  node* tmp = _L;
  _L = tmp->r;
  tmp->r = cur;
  fix(cur); fix(tmp); return tmp;
}

node* rotateLeft(param) {
  node* tmp = _R;
  _R = tmp->l;
  tmp->l = cur;
  fix(cur); fix(tmp); return tmp;
}

node* balance(param) {
  fix(cur);
  if (getBF(cur) < -1) {
    if (getBF(_R) > 0) _R = rotateRight(_R);
    cur = rotateLeft(cur);
  } else if (getBF(cur) > 1) {
    if (getBF(_L) < 0) _L = rotateLeft(_L);
    cur = rotateRight(cur);
  }
  return cur;
}


node* insert(param, int val) {
  if (cur == NULL) return new node(val);
  if (val == cur->val) {
    cur->num++;
    fix(cur);
    return cur;
  } else if (val < cur->val) _L = insert(_L, val);
  else if (val > cur->val) _R = insert(_R, val);
  return balance(cur);
}

node* remove(param, int val, int num) {
  if (cur == NULL) assert(0);
  if (val < cur->val) {
    _L = remove(_L, val, num);
  } else if (val > cur->val) {
    _R = remove(_R, val, num);
  } else {
    cur->num -= num;
    if (cur->num > 0) return balance(cur);
    if (_L == NULL && _R == NULL) {
      delete cur;
      return NULL;
    }
    if (_L == NULL) {
      node* tmp = _R; delete cur;
      return tmp;
    }
    if (_R == NULL) {
      node* tmp = _L; delete cur;
      return tmp;
    }
    node* rep = _L;
    while (rep->r != NULL) rep = rep->r;
    cur->val = rep->val;
    cur->num = rep->num;
    _L = remove(_L, cur->val, cur->num);
  }
  return balance(cur);
}

int main() {
  root = NULL;
  for (int i = 0; i < 10; i++) root = insert(root, i), printf("%d\n", getSz(root));
  for (int i = 0; i < 10; i++) root = insert(root, i), printf("%d\n", getSz(root));
  for (int i = 0; i < 10; i++) root = remove(root, i, 2), printf("%d\n", getSz(root));
}
