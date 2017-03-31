#include <iostream>

using namespace std;

class Node{
	public:
	int key,height;
	Node *left,*right;
	Node(int key){
		this->key=key;
		left=right=NULL;
		height=1;
	}
};

class AVLTree{
	Node *root;
	int height(Node *x){
		if(x)
			return x->height;
		else
			return 0;
	}
	Node* leftRotation(Node *x){
		Node *y=x->right;
		Node *T=y->left;
		y->left=x;
		x->right=T;
		x->height=max(height(x->left),height(x->right))+1;
		y->height=max(height(y->left),height(y->right))+1;
		return y;
	}
	Node* rightRotation(Node *y){
		Node *x=y->left;
		Node *T=x->right;
		x->right=y;
		y->left=T;
		y->height=max(height(y->left),height(y->right))+1;
		x->height=max(height(x->left),height(x->right))+1;
		return x;
	}
	int getBalance(Node *temp){
		if(temp)
		return height(temp->left)-height(temp->right);
		else
		return 0;
	}
	Node* insertUtil(Node* root,Node* pt){
		if(!root)
		return pt;
		else if(pt->key<root->key)
		root->left=insertUtil(root->left,pt);
		else if(pt->key>root->key)
		root->right=insertUtil(root->right,pt);
		else
		return pt;
		
		// Ancestors Updation from here
		root->height=max(height(root->left),height(root->right))+1;
		int balance=getBalance(root);
		if(balance>1 && pt->key < root->left->key){ // Left Left Case
			return rightRotation(root);
		}
		if(balance>1 && pt->key > root->left->key){ // Left Right Case
			root->left=leftRotation(root->left);
			return rightRotation(root);
		}
		if(balance<-1 && pt->key > root->right->key){ // Right Right Case
			leftRotation(root);
		}
		if(balance<-1 && pt->key < root->right->key){ // Right Left Case
		root->right=rightRotation(root->right);
		return leftRotation(root);
		}
		return root;
	}
	Node* findMin(Node *x){
		if(x->left)
		return findMin(x->left);
		else
		return x;
	}
	Node* deleteNodeUtil(Node* root,int key){
		if(!root)
		return root;
		else if(key<root->key)
		root->left=deleteNodeUtil(root->left,key);
		else if(key>root->key)
		root->right=deleteNodeUtil(root->right,key);
		else{
			if(!root->left || !root->right){  // One child Case
				Node *temp=root->left?root->left:root->right;
				if(!temp){
					temp=root;
					root=NULL;
				}
				else
					(*root)=(*temp);
				delete temp;
			}
			else{
				Node *succ=findMin(root->right);
				root->key=succ->key;
				root->right=deleteNodeUtil(root->right,succ->key);
			}
		}
		if(!root)
			return root;
			
		root->height=max(height(root->left),height(root->right))+1;
		int balance=getBalance(root);
		
		if(balance>1 && getBalance(root->left)>=0){ // Left Left Case
			return rightRotation(root);
		}
		if (balance>1 && getBalance(root->left)<0){ // Left Right Case
			root->left=leftRotation(root->left);
			return rightRotation(root);
		}
		if(balance<-1 && getBalance(root->right)<=0){ // Right Right Case
			return rightRotation(root);
		}
		if(balance<-1 && getBalance(root->right)>0){ // Right Left Case
			root->right=rightRotation(root->right);
			return leftRotation(root);
		}
		
		return root;
	}
	void preOrderUtil(Node *temp){
		if(!temp)
		return;
		cout << temp->key << " " << temp->height << endl;
		preOrderUtil(temp->left);
		preOrderUtil(temp->right);	
	}
	public:
	AVLTree(){
		root=NULL;
	}
	void insert(int key){
		Node *pt = new Node(key);
		root=insertUtil(root,pt);
	}
	void deleteNode(int key){
		root=deleteNodeUtil(root,key);
	}
	void preOrder(){
		preOrderUtil(root);
	}
};

int main(){
	AVLTree avl;
	avl.insert(5);
	avl.insert(3);
	avl.insert(79);
	avl.insert(34);
	avl.insert(13);
	avl.insert(1);
	avl.deleteNode(79);
	avl.preOrder();
	return 0;
}
