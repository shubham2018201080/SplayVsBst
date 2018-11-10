#include<iostream>
#include<ctime>

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
        cout<<key<<" is absent in splay tree\n";
        return root;
    }
    root = splay(root,key);
    if(root->val==key){
        cout<<key<<" found in splay tree\n";
    }else{
        cout<<key<<" is absent in splay tree\n";
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
    cout<<key<<" deleted from splay tree\n";
    return root;
}


int main(){
	cout<<"<--------------- Splay Tree ---------------->"<<endl;
	Node * splay_root = NULL;
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
			splay_root = insertSplay(splay_root,key);
		}else if(c==2){
			cout<<"Enter key to be searched ";
			cin>>key;
			splay_root = searchSplay(splay_root,key);
		}else if(c==3){
			cout<<"Enter key to be deleted ";
			cin>>key;
			splay_root = deleteSplay(splay_root,key);
		}else if(c==4){
			cout<<"The tree is ";
			inOrder(splay_root);
			cout<<endl;
		}else if(c==0){
			break;
		}
	}
}










