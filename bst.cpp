#include<iostream>

using namespace std;

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


Node * getNewNode(int key){
    struct Node * node = (struct Node *)malloc(sizeof(struct Node ));
    // Node* node  = new Node;
    node->val = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertBST(Node* node, int key) { 
    /* If the tree is empty, return a new node */
    if (node == NULL) return getNewNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->val) 
        node->left  = insertBST(node->left, key); 
    else if (key > node->val) 
        node->right = insertBST(node->right, key);    
  
    /* return the (unchanged) node pointer */
    return node; 
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
	cout<<"<--------------- BST ---------------->"<<endl;
	Node * bst_root = NULL;
	int c,key;
	while(1){
		cout<<"1.insert"<<endl;
		cout<<"2.search"<<endl;
		cout<<"3.delete"<<endl;
		cout<<"4.print(inorder)"<<endl;
		cout<<"0.exit"<<endl;
		cin>>c;
		if(c==1){
			cout<<"Enter key to be inserted ";
			cin>>key;
			bst_root = insertBST(bst_root,key);
		}else if(c==2){
			cout<<"Enter key to be searched ";
			cin>>key;
			searchBST(bst_root,key);
		}else if(c==3){
			cout<<"Enter key to be deleted ";
			cin>>key;
			bst_root = deleteBST(bst_root,key);
		}else if(c==4){
			cout<<"The tree is ";
			inOrder(bst_root);
			cout<<endl;
		}else if(c==0){
			break;
		}
	}
}
