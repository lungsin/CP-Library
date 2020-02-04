#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define repd(i, a, b) for (int i = a; i >= (b); i--)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define pb2 pop_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int INF = 1e9 + 7;
long long INFLL = 2e18;

typedef vector<int>::iterator IterT;
class P {
 public: 
  virtual bool parse(IterT &begin, IterT const &end) = 0;
  virtual ~P() = default;
};

template<class A, class B>
class binary {
 public:
  binary(A left, B right): left_(left), right_(right) {}
  
  auto left() { return left_; } 
  auto right() { return right_; } 
 private: 
  A left_;
  B right_;
};

template<class P>
class unary {
 public:
  unary(P subject): subject_(subject){}
  
  auto subject() { return subject_; } 
 private: 
  P subject_;
};

class terminal : public P {
 public:
  terminal(int s): s_(s) {}
  virtual bool parse(IterT &begin, IterT const &end) {
    if (begin == end || (*begin) != s_) return false;
    begin = next(begin);
    return true;
  } 
 protected:
  int s_;
};

template<class A, class B>
class alternative : public P, public binary<A, B> {
 public:
  alternative(A lhs, B rhs): binary<A, B>(lhs, rhs) {}
  
  virtual bool parse(IterT &begin, IterT const &end) {
    IterT checkpoint = begin;
    return this -> left() -> parse(begin, end) or this -> right() -> parse(begin = checkpoint, end);
  } 
};

template<class A, class B>
class sequential : public P, public binary<A, B> {
 public:
  sequential(A lhs, B rhs): binary<A, B>(lhs, rhs) {}
  virtual bool parse(IterT &begin, IterT const &end) {
    return this -> left() -> parse(begin, end) and
       this -> right() -> parse(begin, end);
  } 
};

template<class T>
class kleene_plus : public P, public unary<T> {
 public:
  kleene_plus(T p): unary<T>(p) {}
  virtual bool parse(IterT &begin, IterT const &end) {
    auto checkpoint = begin;
    bool match = false;
    while (this -> subject() -> parse(begin, end)) {
      checkpoint = begin;
      match = true;
    }
    begin = checkpoint;
    return match;
  }
};

template<class T>
class kleene_star : public P, public unary<T> {
 public:
  kleene_star(T p): unary<T>(p) {}
  
  virtual bool parse(IterT &begin, IterT const &end) {
    auto checkpoint = begin;
    while (this -> subject() -> parse(begin, end)) {
      checkpoint = begin;
    }
    begin = checkpoint;
    return true;
  }
};


template<class A, class B>
shared_ptr<P> operator >> (A&& lhs, B&& rhs) {
  return make_shared<sequential<A, B> > (lhs, rhs);
}

template<class A, class B>
shared_ptr<P> operator | (A&& lhs, B&& rhs) {
  return make_shared<alternative<A, B> > (lhs, rhs);
}

template<class T>
shared_ptr<P> operator + (T&& subject) {
  return make_shared<kleene_plus<T>> (subject);
}

template<class T>
shared_ptr<P> star(T&& subject) {
  return make_shared<kleene_star<T>> (subject);
}

shared_ptr<P> str(int i) {
  return make_shared<terminal>(i);
}

// shared_ptr<P>& var(shared_ptr<P>& v) {
//   return v;
// }

void test(vi a, shared_ptr<P> rule, bool expect) {
  // for (int x : a) {printf("%d ", x);} puts("");
  
  IterT begin = a.begin();
  bool is_partial_match = rule -> parse(begin, a.end());
  bool is_full_match = is_partial_match && (begin == a.end());
  assert(is_full_match == expect);
}

vi generate(int n) {
  vi res;
  for (int i = 0; i < n; i++) {
    res.push_back(1);
    res.push_back(2);
  }
  
  for (int i = 0; i < n; i++) {
    res.push_back(3);
  }
  
  return res;
}

void unit_test_1() {
  cout << "Test begin" << endl;
  shared_ptr<P> A, B;
  assert(A == nullptr);
  
  A = str(1) >> str(2) >> A >> B | str(1) >> str(2) >> B;
  B = str(3);
  
  test({1, 2, 3}, A, true);
  test({1, 2, 1, 2, 3, 3}, A, true);
  test({1, 2, 1, 2, 1, 2, 3, 3, 3}, A, true);
  test({1}, A, false);
  test({1, 2, 1, 2, 1, 3, 3, 3}, A, false);
  
  cout << "AC" << endl;
}

void unit_test_2() {
  cout << "Test begin" << endl;
  shared_ptr<P> A;
  assert(A == nullptr);
  
  A = str(1) >> star(str(2)) | str(3) >> star(str(4));
  
  test({1}, A, true);
  test({1, 2}, A, true);
  test({1, 2, 2, 2, 2, 2, 2, 2, 2}, A, true);
  test({3}, A, true);
  test({3, 4}, A, true);
  test({3, 4, 4, 4, 4, 4, 4}, A, true);
  
  
  test({}, A, false);
  test({1, 3}, A, false);
  test({1, 4}, A, false);
  test({1, 5}, A, false);
  test({1, 2, 2, 2, 2, 2, 2, 2, 2, 3}, A, false);
  test({1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2}, A, false);
  
  test({3, 1}, A, false);
  test({3, 2}, A, false);
  test({3, 3}, A, false);
  test({3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3}, A, false);
  test({3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4}, A, false);
  
  cout << "AC" << endl;
}

void unit_test_expression() {
  shared_ptr<P> expr, factor, term;
  
  expr = factor >> "+" >> expr;
}

int main() {
  unit_test_1();
  unit_test_2();
}
