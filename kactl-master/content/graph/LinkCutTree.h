/**
 * Author: N/A
 * Date: 2016-07-25
 * Source:  N/A
 * Description: Represents a forest of unrooted trees. You can add and remove
 * edges (as long as the result is still a forest), and check whether
 * two nodes are in the same tree.
 * Time: All operations take amortized O(\log N).
 * Status: Fuzz-tested a bit for N <= 20
 */
#pragma once

struct LCT {
	struct Node {
		int val;
		int sum;
		bool rev;
		Node *p, *c[2];
		Node(int val) : val(val), sum(val), rev(0), p(), c() {}
	};
	
	int getDir(Node *n) { return n->p->c[1] == n; }
	int getSum(Node *n) { return n ? n->sum : 0; }
	bool isRoot(Node *n) { return !n->p || n->p->c[getDir(n)] != n; }

	void connect(Node *p, Node *n, int dir) {
		if (p) p->c[dir] = n;
		if (n) n->p = p;
	}

	void push(Node *n) {
		if (!n) return;
		if (n->rev) {
			swap(n->c[0], n->c[1]);
			if (n->c[0]) n->c[0]->rev ^= true;
			if (n->c[1]) n->c[1]->rev ^= true;
			n->rev = false;
			n->sum = getSum(n->c[0]) + getSum(n->c[1]) + n->val;
		}
	}

	void update(Node *n) {
		push(n); push(n->c[0]); push(n->c[1]);
		n->sum = getSum(n->c[0]) + getSum(n->c[1]) + n->val;
	}

	void rotate(Node *n) {
		int dir = getDir(n);
		Node *p = n->p;
		if (isRoot(p)) n->p = p->p;
		else connect(p->p, n, getDir(p)); 
		connect(p, n->c[!dir], dir); 
		connect(n, p, !dir);
		update(p); update(n);
	}

	Node *splay(Node *n) {
		while (!isRoot(n)) {
			Node *p = n->p;
			if (!isRoot(p)) push(p->p);
			push(p);
			push(n);
			if (!isRoot(p)) rotate(getDir(n) == getDir(p) ? p : n); rotate(n);
		}
		push(n);
		return n;
	}

	Node *access(Node *n) {
		splay(n);
		n->c[1] = nullptr; 
		update(n);
		Node *last = n;
		while (n->p) {
			last = n->p;
			splay(n->p);
			n->p->c[1] = n;
			update(n->p);
			splay(n);
		}
		push(n);
		update(n);
		return last;
	}

	Node *evert(Node *n) {
		access(n);
		n->rev ^= true;
		return n;
	}

	Node *getRoot(Node *n) {
		access(n);
		while(true) {
			push(n);
			if (n->c[0]) n = n->c[0];
			else break;
		}
		splay(n);
		return n;
	}

	void link(Node *a, Node *b) {
		evert(a);
		a->p = b;
	}

	void cut(Node *a, Node *b) { // a is the parent
		evert(a);
		access(b);
		assert(b->c[0] == a);
		b->c[0] = nullptr;
		a->p = nullptr;
		update(b);
	}
};
// }}}
