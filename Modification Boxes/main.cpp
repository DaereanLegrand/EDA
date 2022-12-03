#include "bits/stdc++.h"
#include <cstddef>
#include <vector>

using namespace std;

struct node {
	int val;
	node* next;
	node(int n = 0):
        val(n)
	{
        
	}
};

struct linkedlist {
    node *begin, *end;
    int num;

    linkedlist()
    {
        begin = new node;
        end = NULL;
    }

    node*
    operator[] (int i)
    {
        node *cur = begin;
        for (int i = 0; i < num; i++) {
            cur = cur->next;
        }
        return cur;
    }

    void
    assign(int n, int *arr)
    {
        num = n;
        begin->val = arr[0];
        node *cur = begin;
        for (int i = 1; i < n; i++) {
            node *temp = new node(arr[i]);
            cur->next = temp;
            cur = temp;
        }
        cur->next = end;
    }

};

class modbox {
    public:
    linkedlist ll;
    int nodecapacity;
    int version;
    int limcapacity;
    vector<pair<int, int>> mods;

    modbox(int *arr, int n = 0, int limcap = 20):
        nodecapacity(n), limcapacity(limcap), version(0)
    {
        node *root = new node;
        mods = vector<pair<int, int>>(limcapacity);
        ll.assign(nodecapacity, arr);
    }

    void 
    addmod(int idx, int val)
    { 
            node *modnode = ll[idx];
            mods[version + 1] = {idx, val};
            version++;
    }

    void
    querymod(int ver)
    {
        node *cur = ll.begin;
        for (int i = 0; i < nodecapacity; i++) {
            if (mods[ver].first != i)
                cout << cur->val << " ";
            else 
                cout << mods[ver].second << " ";
            if (cur->next != NULL)
                cur = cur->next;
            else break;
        }
        cout << endl;
    }
};

int 
main(int argc, char *argv[])
{
    int n = 5;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    cout << "Creating modbox...\n";
    modbox mb(arr, 5, 20);
    cout << "Doing query in 0...\n";
    mb.querymod(0);
    cout << "Doinf mod...\n";
    mb.addmod(0, 10);
    cout << "Doing query in 1...\n";
    mb.querymod(1);
    cout << "Doing query in 0...\n";
    mb.querymod(0);
    return 0;
    /*
	int A[] = {1,2,3,4,5};
	int n = sizeof(A)/sizeof(int);

	for (int i=0; i<n; i++)
	    arr[i] = A[i];

    node* root = new node(NULL, NULL, 0);
	build(root, 0, n-1);

	version[0] = root;

	version[1] = new node(NULL, NULL, 0);
	upgrade(version[0], version[1], 0, n-1, 4, 1);

	version[2] = new node(NULL, NULL, 0);
	upgrade(version[1],version[2], 0, n-1, 2, 10);

	cout << "In version 1 , query(0,4) : ";
	cout << query(version[1], 0, n-1, 0, 4) << endl;

	cout << "In version 2 , query(3,4) : ";
	cout << query(version[2], 0, n-1, 3, 4) << endl;

	cout << "In version 0 , query(0,3) : ";
	cout << query(version[0], 0, n-1, 0, 3) << endl;
	return 0;
    */
}

