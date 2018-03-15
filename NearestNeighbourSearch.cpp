#include <bits/stdc++.h>
 
using namespace std;

const int D = 2;
const int N = 1<<17;
const long long INF = 2000000000000000007;
 
struct Point {
	int p[D];
	bool operator !=(const Point &a) const {
        for (int i = 0; i < D; i++) 
            if (p[i] != a.p[i]) 
                return true;
		return false;
	}
};

long long distance(Point a, Point b) {
    long long ans=0;
    for(int i=0;i<D;i++) ans+=(a.p[i]-b.p[i])*1ll*(a.p[i]-b.p[i]);
    return ans;
}

// Usage: insert all Point first, then call build()

struct NearestNeighbor {
    struct kd_node {
        int axis, value;
        Point p;
        kd_node *left, *right;
    };
    
    struct cmp_Points {
        int axis;
        cmp_Points(){}
        cmp_Points(int x): axis(x) {}
        bool operator () (const Point &a, const Point &b) const {
            return a.p[axis]<b.p[axis];
        }
    };
    
    typedef kd_node* node_ptr;
    
    int n;
    vector<Point> arr;
    node_ptr root;
    
    void build_tree(node_ptr &node, int from, int to, int axis) {
        if(from>to) {
            node=NULL;
            return;
        }
    
        node=new kd_node();
    
        if(from==to) {
            node->p=arr[from];
            node->left=NULL;
            node->right=NULL;
            return;
        }
    
        int mid=(from+to)/2;
    
        nth_element(arr.begin()+from,arr.begin()+mid,arr.begin()+to+1,cmp_Points(axis));
        node->value=arr[mid].p[axis];
        node->axis=axis;
        
        int naxis = (axis == D - 1) ? 0 : axis + 1;
        build_tree(node->left,from,mid,naxis);
        build_tree(node->right,mid+1,to,naxis);
    }
    
    void nearest_neighbor(node_ptr node, Point q, Point &ans) {
        #define dist distance(ans, q)
        if(node==NULL) return;
    
        if(node->left==NULL && node->right==NULL) {
            if(q!=node->p) {
                if (distance(ans, q) > distance(node->p,q)){
                    ans = node->p;
                }
            }
            return;
        }
    
        if(q.p[node->axis]<=node->value) {
            nearest_neighbor(node->left, q, ans);
            if(q.p[node->axis]+sqrt(dist)>=node->value) 
                nearest_neighbor(node->right, q, ans);
        }
    
        else {
            nearest_neighbor(node->right, q, ans);
            if(q.p[node->axis]-sqrt(dist)<=node->value) 
                nearest_neighbor(node->left, q, ans);
        }
        #undef dist
    }
    
    void insert(Point p) {
        arr.push_back(p);
    }
    
    void build() {
        n = arr.size();
		build_tree(root,0,n - 1,0);
    }
    
    void clear() {
        arr.clear();
    }
    
    Point nearest_neighbor(Point x) {
        Point p = x;
        p.p[0] += 1e9;
		nearest_neighbor(root, x, p);
        return p;
    }
} KD;


int tests, n;
Point arr[N];

int main() {
	int i;
 
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &n);
        KD.clear();
		for(i=0;i<n;i++) {
			scanf("%d %d", &arr[i].p[0], &arr[i].p[1]);
            KD.insert(arr[i]);
		}
        
        KD.build();
 
		for(i=0;i<n;i++) {
			Point p = KD.nearest_neighbor(arr[i]);
            long long ans = distance(p, arr[i]);
			printf("%lld\n", ans);
		}
	}
 
	return 0;
}