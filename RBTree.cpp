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
	bool isNULL(Node *x){
		return(x->key==-1 && x->left==NULL && x->right==NULL);
	}
	Node *insertUtil(Node *root, Node *pt){
		if(root==NULL || isNULL(root))
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
	void RbInsertFixUp(Node *pt){
		Node *par,*grandPar,*uncle;
		while(pt->parent && pt->parent->color==RED){
			par=pt->parent;
			grandPar=par->parent;
			if(par==grandPar->left){
				uncle=grandPar->right;
				if(uncle->color==RED){   // Case 1: Uncle is Red
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
				if(uncle->color==RED){
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
	void RbDeleteFixUp(Node *x){
		Node *s=NULL;
		while(x!=root && x->color==BLACK){
			if(x==x->parent->left){
				s=x->parent->right;
				if(s->color==RED){  // Case 1 Red Sibling
					s->color=BLACK;
					x->parent->color=RED;
					leftRotate(x->parent);
					s=x->parent->right;
				}
				if(s->left->color==BLACK && s->right->color==BLACK){ // Case 2 and Case 3
					s->color=RED;
					if(x->parent->color==BLACK)
					x=x->parent;
					else{ // Case 3
						x->parent->color=BLACK;
						break;
					}
				}
				else{
					if(s->right->color==BLACK){ // Case 4
						s->left->color=BLACK;
						s->color=RED;
						rightRotate(s);
						s=x->parent->right;
					}
					s->color=x->parent->color;  // Case 5
					x->parent->color=BLACK;
					s->right->color=BLACK;
					leftRotate(x->parent);
					break;
				}
			}
			else{
				s=x->parent->left;
				if(s->color==RED){  // Case 1 Red Sibling
					s->color=BLACK;
					x->parent->color=RED;
					rightRotate(x->parent);
					s=x->parent->left;
				}
				if(s->left->color==BLACK && s->right->color==BLACK){ // Case 2 and Case 3
					s->color=RED;
					if(x->parent->color==BLACK)
					x=x->parent;
					else{ // Case 3
						x->parent->color=BLACK;
						break;
					}
				}
				else{
					if(s->left->color==BLACK){ // Case 4
						s->right->color=BLACK;
						s->color=RED;
						leftRotate(s);
						s=x->parent->left;
					}
					s->color=x->parent->color;  // Case 5
					x->parent->color=BLACK;
					s->left->color=BLACK;
					rightRotate(x->parent);
					break;
				}
			}
		}
	}
	void preOrderUtil(Node* root){
		if(root==NULL || isNULL(root))
			return;
		cout << root->key << " ";
		if(root->color==RED)
		cout << "RED" << endl;
		else
		cout << "BLACK" << endl;
		preOrderUtil(root->left);
		preOrderUtil(root->right);
	}
	void deleteNodeUtil(Node *root,int key){
			if(!root || isNULL(root))
				return;
			else if(key<root->key)
				return deleteNodeUtil(root->left,key);
			else if(key>root->key)
				return deleteNodeUtil(root->right,key);
			else if(key==root->key){
				if(isNULL(root->left) || isNULL(root->right)){
					Node *temp=!isNULL(root->left)?root->left:root->right;
					transplant(root,temp);
					if(root->color==BLACK){
						if(temp->color==RED)
							temp->color=BLACK;
						else
							RbDeleteFixUp(temp);
					}
					delete root;
				}
				else{
					Node *succ=findSmallest(root->right);
					root->key=succ->key;
					deleteNodeUtil(root->right,succ->key);
				}
			}
			else return;
	}
	public:
		RBTree(){
			root=NULL;
		}
		void insert(int key){
			Node *pt = new Node(key);
			pt->left=new Node(-1);
			pt->left->color=BLACK;
			pt->left->parent=pt;
			pt->right=new Node(-1);
			pt->right->color=BLACK;
			pt->right->parent=pt;
			root=insertUtil(root,pt);
			RbInsertFixUp(pt);
		}
		void inOrder(){
			inOrderUtil(root);
		}
		void preOrder(){
			preOrderUtil(root);
		}
		Node* search(Node *root,int key){
			if(key<root->key)
				return search(root->left,key);
			else if(key>root->key)
				return search(root->right,key);
			else
				return root;
		}
		
		void transplant(Node *u,Node *v){
			if(!u->parent)
				root=v;
			else if (u==u->parent->left)
				u->parent->left=v;
			else
				u->parent->right=v;
			v->parent=u->parent;
		}
		Node* findSmallest(Node *root){
			if(root->left && !isNULL(root->left))
				return findSmallest(root->left);
			else
				return root;
		}
	
		void deleteNode(int key){
			deleteNodeUtil(root,key);
		}
		
};

int main(){
	RBTree tree;
	tree.insert(22);
	tree.preOrder();

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
	
	cout << endl;
	
	tree.deleteNode(9);
	
	tree.preOrder();
	
	tree.deleteNode(7);
	cout << endl;
	tree.preOrder();
	
	tree.deleteNode(55);
	cout << endl;
	tree.preOrder();
	
	tree.deleteNode(11);
	cout << endl;
	tree.preOrder();
	
	tree.deleteNode(22);
	cout << endl;
	tree.preOrder();
	tree.deleteNode(33);
		cout << endl;
	tree.preOrder();
	tree.deleteNode(6);
		cout << endl;
	tree.preOrder();
	tree.deleteNode(8);
		cout << endl;
	tree.preOrder();
	tree.deleteNode(2);
		cout << endl;
	tree.preOrder();
		tree.deleteNode(5);
		cout << endl;
	tree.preOrder();
	
	
	tree.deleteNode(7);
		cout << endl;
	tree.preOrder();

	tree.insert(17);
	cout << endl;
	tree.preOrder();

	
	
	return 0;
}
