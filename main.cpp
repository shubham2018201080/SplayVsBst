//
//  main.cpp
//  example
//
//  Created by shubham  on 22/10/18.
//  Copyright © 2018 shubham . All rights reserved.
//
#include<iostream>
#include<random>
#include<ctime>

using namespace std;
int search_key=33333;

struct Node{
    int val;
    struct Node* left;
    struct Node* right;
};

void inOrder(Node * root){
    if(!root)
        return;
    inOrder(root->left);
    cout<<root->val<<" ";
    inOrder(root->right);
}


void preOrder(Node * root){
    if(!root)
        return;
    cout<<root->val<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

Node * getNewNode(int key){
	struct Node * node = (struct Node *)malloc(sizeof(struct Node ));
    // Node* node  = new Node;
    node->val = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node * leftRotate(Node * root){
    Node* right = root->right;
    root->right = right->left;
    right->left = root;
    return right;
}

Node * rightRotate(Node * root){
    Node * left = root->left;
    root->left = left->right;
    left->right = root;
    return left;
}

Node * splay(Node * root, int key){
    if(!root)
        return root;
    if(root->val==key)
        return root;
    
    if(root->val<key){
        
        if (!root->right)
            return root;
        
        // Zig case
        if(root->right->val==key){
            if(root->right)
                root = leftRotate(root);
            return root;
        }
        
        
        // Zig Zig case
        if(root->right->val<key){
            root->right->right = splay(root->right->right,key);
            root = leftRotate(root);
            if(root->right)
                return leftRotate(root);
            else
                return root;
        }
        
        // Zig Zag case
        if(root->right->val>key){
            root->right->left = splay(root->right->left,key);
            if(root->right->left)
                root->right = rightRotate(root->right);
            if(root->right)
                return leftRotate(root);
            else
                return root;
        }
        
        
        
    }else{
        
        if (!root->left)
            return root;
        
        // Zig case
        if(root->left->val==key){
            if(root->left)
                root =  rightRotate(root);
            return root;
        }
        
        // Zig Zig case
        if(root->left->val>key){
            root->left->left = splay(root->left->left,key);
             root = rightRotate(root);
            if(root->left)
                return rightRotate(root);
            else
                return root;
        }
        
        // Zig Zag case
        if(root->left->val<key) {
            root->left->right = splay(root->left->right,key);
            if(root->left->right)
                root->left = leftRotate(root->left);
            if(root->left)
                return rightRotate(root);
            else
                return root;
        }
        
    }
    return root;
}


Node * searchSplay(Node *root, int key){
	if(!root){
		cout<<key<<" absent in splay tree\n";
		return root;
	}
    root = splay(root,key);
    if(root->val==key){
    	cout<<key<<" found in splay tree\n";
    }else{
    	cout<<key<<" absent in splay tree\n";
    }
    return root;
}


Node * insertSplayUtility(Node * root, int key){
    if(!root){
        Node * new_node = getNewNode(key);
        return new_node;
    }
    if(root->val==key)
        return root;
    if(root->val<key){
        root->right = insertSplayUtility(root->right,key);
    }else{
        root->left = insertSplayUtility(root->left,key);
    }
    return root;
}

Node * insertSplay(Node * root, int key){
    root = insertSplayUtility(root,key);
    root = splay(root,key);
    return root;
}

Node * deleteSplay(Node * root, int key){
	if(!root)
		return root;
	root = splay(root,key);
	if(root->val!=key){
		cout<<key<<" not present in splay tree\n";
		return root;
	}
	Node * temp = root;
	if(!root->left){
		root=root->right;
	}else{
		root = splay(root->left,key);
		root->right = temp->right;	
	}
	free(temp);
	return root;
}

Node * insertBST(Node * root, int key){
	if(!root){
		Node * new_node = getNewNode(key);
		return new_node;
	}

	if(root->val==key)
		return root;
	if(root->val<key){
		root->right = insertBST(root->right,key);
	}else{
		root->left = insertBST(root->left,key);
	}
	return root;
}

void searchBST(Node * root, int key){
	if(!root){
		cout<<key<<" absent in BST\n";
		return;
	}
	if(root->val==key){
		cout<<key<<" found in BST\n";
		return;
	}
	if(root->val<key)
		searchBST(root->right, key);
	else
		searchBST(root->left, key);
	return;
}

Node * findMinInBST(Node * root){
	if(!root)
		return root;
	while(root->left){
		root = root->left;
	}
	return root;
}

Node * deleteBST(Node * root, int key){
	if(!root)
		return root;
	if(root->val==key){
		if(root->left && root->right){
			Node * temp = root;
			Node * min = findMinInBST(root->right);
			root = root->right;
			min->left = temp->left;
			free(temp);
			return root;
		}else if(!root->right){
			return root->left;
		}else{
			return root->right;
		}
	}
	if(root->val<key)
		root->right = deleteBST(root->right, key);
	else
		root->left = deleteBST(root->left, key);
	return root;
}

int main(){
    int r;
    int start_s=clock();
    cin>>r;
    Node * splay_root = getNewNode(r);
    Node * bst_root = getNewNode(r);
    while(cin>>r){
    	// splay_root = insertSplay(splay_root,r);
    	bst_root = insertBST(bst_root,r);
    }
    int stop_s=clock();
    cout << "Time Taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    

    cout<<splay_root->val<<" "<<bst_root->val<<endl;
   
    // start_s=clock();
    // splay_root = searchSplay(splay_root,search_key);
    // stop_s=clock();
    // cout << "Time Taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    // start_s=clock();
    // splay_root = searchSplay(splay_root,search_key);
    // stop_s=clock();
    // cout << "Time Taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    start_s=clock();
    searchBST(bst_root,search_key);
    stop_s=clock();
    cout << "Time Taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    start_s=clock();
    searchBST(bst_root,search_key);
    stop_s=clock();
    cout << "Time Taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    
}

















