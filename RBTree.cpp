#include <iostream>
#define BLACK 0
#define RED 1

using namespace std;

class Node{
	public:
	int key;
	Node *parent,*left,*right;
	bool color;
		Node(int key){
		this->key=key;
		parent=left=right=NULL;
		color=RED;
	}
};

class RBTree{
	Node *root;
	Node *insertUtil(Node *root, Node *pt){
		if(root==NULL)
			return pt;
		else if(pt->key<root->key){
			pt->parent=root;
			root->left=insertUtil(root->left,pt);
		}
		else{
			pt->parent=root;
			root->right=insertUtil(root->right,pt);
		}
	}
	void leftRotate(Node *x){
		Node *y=x->right;
		Node *T=y->left;
		if(x->parent){
			if(x==x->parent->left)
			x->parent->left=y;
			else
			x->parent->right=y;
		}
		else
		root=y;
		y->parent=x->parent;
		x->parent=y;
		y->left=x;
		x->right=T;
		if(T)
		T->parent=x;
	}
	void rightRotate(Node *y){
		Node *x=y->left;
		Node *T=x->right;
		if(y->parent){
		if(y==y->parent->left)
		y->parent->left=x;
		else
		y->parent->right=x;
		}
		else
		root=x;
		x->parent=y->parent;
		y->parent=x;
		x->right=y;
		y->left=T;
		if(T)
		T->parent=y;
	}
	void fixUp(Node *pt){
		Node *par,*grandPar,*uncle;
		while(pt->parent && pt->parent->color==RED){
			par=pt->parent;
			grandPar=par->parent;
			if(par==grandPar->left){
				uncle=grandPar->right;
				if(uncle && uncle->color==RED){   // Case 1: Uncle is Red
					par->color=BLACK;
					uncle->color=BLACK;
					grandPar->color=RED;
					pt=grandPar;
				}
				else{
					if(pt==par->right){  // Case 2: Left Right Case
						pt=par;
						leftRotate(pt);
						par=pt->parent;
					}
					par->color=BLACK;  // Case 3: Left Left Case
					grandPar->color=RED;
					rightRotate(grandPar);
				}
			}
			else{
				uncle=grandPar->left;
				if(uncle && uncle->color==RED){
					par->color=BLACK;
					uncle->color=BLACK;
					grandPar->color=RED;
					pt=grandPar;
				}
				else{
					if(pt==par->left){
						pt=par;
						rightRotate(pt);
						par=pt->parent;
					}
					par->color=BLACK;
					grandPar->color=RED;
					leftRotate(grandPar);
				}
			}	
		}
		root->color=BLACK; 
	}
	void inOrderUtil(Node *root){
		if(!root)
		return;
		inOrderUtil(root->left);
		cout << root->key << " " << root->color  << endl;
		inOrderUtil(root->right);
	}
	void preOrderUtil(Node* root){
		if(!root)
			return;
		cout << root->key << " ";
		if(root->color==RED)
		cout << "RED" << endl;
		else
		cout << "BLACK" << endl;
		preOrderUtil(root->left);
		preOrderUtil(root->right);
	}
	public:
		RBTree(){
			root=NULL;
		}
		void insert(int key){
			Node *pt = new Node(key);
			root=insertUtil(root,pt);
			fixUp(pt);
		}
		void inOrder(){
			inOrderUtil(root);
		}
		void preOrder(){
			preOrderUtil(root);
		}
};

int main(){
	RBTree tree;
	tree.insert(22);

	tree.insert(5);
	tree.insert(9);
	
	tree.insert(33);
	
	tree.insert(11);
	tree.insert(6);
	tree.insert(2);
	tree.insert(7);
	tree.insert(55);
	tree.insert(8);
	
	
	tree.preOrder();
	return 0;
}
