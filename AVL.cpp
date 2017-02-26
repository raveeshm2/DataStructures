#include <iostream>

using namespace std;

struct Node{
	Node *parent;
	Node *left;
	int data;
	Node *right;
	int height;
};

class BST{
	Node *root;
	Node* createNode(int data,Node* parent){
		Node *temp = new Node();
		temp->data=data;
		temp->left=NULL;
		temp->right=NULL;
		temp->parent=parent;
		temp->height=1;
	}
	void leftRotate(Node *x){
		Node *y=x->right;
		Node *temp=y->left;
		if(x->parent){
		if(x->parent->left==x)
		x->parent->left=y;
		else
		x->parent->right=y;
		}
		else
		root=y;
		y->parent=x->parent;
		x->parent=y;
		y->left=x;
		x->right=temp;
		if(temp)
		temp->parent=x;
		x->height = max(getHeight(x->left), getHeight(x->right))+1;
    	y->height = max(getHeight(y->left), getHeight(y->right))+1;
	}
	void rightRotate(Node *y){
		Node *x=y->left;
		Node *temp=x->right;
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
		y->left=temp;
		if(temp)
		temp->parent=y;
		y->height = max(getHeight(y->left), getHeight(y->right))+1;
		x->height = max(getHeight(x->left), getHeight(x->right))+1;
	}
	bool insertUtil(Node **temp,int data,Node *parent){
			if(!(*temp)){
				Node *newNode = createNode(data,parent);
				(*temp)=newNode;
				return true;
			}else{
				if(data>(*temp)->data)
					insertUtil(&((*temp)->right),data,(*temp));
				else if(data<(*temp)->data)
					insertUtil(&((*temp)->left),data,(*temp));
				else
				return false;
				(*temp)->height=1+max(getHeight((*temp)->left),getHeight((*temp)->right));
				int balance=getBalance(*temp);
				
				// Left Left Case
			    if (balance > 1 && data < (*temp)->left->data)
			        rightRotate(*temp);
			 
			    // Right Right Case
			    if (balance < -1 && data > (*temp)->right->data)
			        leftRotate(*temp);
			 
			    // Left Right Case
			    if (balance > 1 && data > (*temp)->left->data)
			    {
			        leftRotate((*temp)->left);
			        rightRotate((*temp));
			    }
			    // Right Left Case
			    if (balance < -1 && data < (*temp)->right->data)
			    {
			        rightRotate((*temp)->right);
			        leftRotate((*temp));
			    }
				
			}
	}
	void inOrderUtil(Node *temp){
		if(!temp)
		return;
		inOrderUtil(temp->left);
		cout << temp->data << " ";
		inOrderUtil(temp->right);
	}
	void preOrderUtil(Node *temp){
		if(!temp)
		return;
		cout << "Data: " << temp->data << endl;
		cout << "Height: " << getHeight(temp) << endl;
		preOrderUtil(temp->left);
		preOrderUtil(temp->right);
	}
	void postOrderUtil(Node *temp){
		if(!temp)
		return;
		postOrderUtil(temp->left);
		postOrderUtil(temp->right);
		cout << temp->data << " ";
	}
	Node* findMinUtil(Node *temp){
		if(!temp)
			return NULL;
		else{
			if(temp->left)
				return findMinUtil(temp->left);
			else
				return temp;
		}
	}
	int findMaxUtil(Node *temp){
		if(!temp)
			return -1;
		else{
			if(temp->right)
				return findMaxUtil(temp->right);
			else
				return temp->data;
		}
	}
	Node* findNodeUtil(Node *temp,int data){
		if(!temp)
			return NULL;
		else if(data > temp->data)
			return findNodeUtil(temp->right,data);
		else if(data < temp->data)
			return findNodeUtil(temp->left,data);
		else
			return temp;
	}
	int getHeight(Node *temp){
		if(temp)
		return temp->height;
		else
		return 0;
	}
	int max(int a,int b){
		return a>b?a:b;
	}
	int getBalance(Node *n){
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
	}
	bool deleteNodeUtil(Node **root,int data){
		if(!(*root))
			return false;
		else if(data>(*root)->data)
			deleteNodeUtil(&((*root)->right),data);
		else if(data<(*root)->data)
			deleteNodeUtil(&((*root)->left),data);
		else{
			if(!((*root)->left) || !((*root)->right)){
				Node *temp = (*root)->left?(*root)->left:(*root)->right;
				if(temp){
					(*root)->data=temp->data;
					(*root)->left=temp->left;
					(*root)->right=temp->right;
					if(temp->left)
						temp->left->parent=(*root);
					if(temp->right)
						temp->right->parent=(*root);
				}
				else{
					temp=(*root);
					(*root)=NULL;
				}
			delete temp;		
			}
			else{
				Node* succ = findSuccessor((*root));
				(*root)->data=succ->data;
				deleteNodeUtil(&((*root)->right),succ->data);
			}
		}
		if(!(*root))
			return true;

		(*root)->height = 1 + max(getHeight((*root)->left),getHeight((*root)->right));
	    int balance = getBalance(*root);
	 
	    if (balance > 1 && getBalance((*root)->left) >= 0)
	        rightRotate(*root);

	    if (balance > 1 && getBalance((*root)->left) < 0)
	    {
	        leftRotate((*root)->left);
	        rightRotate(*root);
	    }
	 
	    if (balance < -1 && getBalance((*root)->right) <= 0)
	        leftRotate(*root);
	 
	    if (balance < -1 && getBalance((*root)->right) > 0)
	    {
	        rightRotate((*root)->right);
	        leftRotate(*root);
	    }

	    return true;

	}	
	public:
		BST(){
			root=NULL;
		}
		bool insertNode(int data){
			return insertUtil(&root,data,root);
		}
		void inOrder(){
			cout << endl;
			inOrderUtil(root);
		}
		void preOrder(){
			cout << endl;
			preOrderUtil(root);
		}
		void postOrder(){
			cout << endl;
			postOrderUtil(root);
		}
		int findMin(){
			Node *temp=findMinUtil(root);
			if(temp)
			return temp->data;
			else
			return -1;
		}
		int findMax(){
			return findMaxUtil(root);
		}
		Node* findNode(int data){
			return findNodeUtil(root,data);
		}
		int* deleteDuplicate(int *arr,int &size){
			int *temp = new int[size],j=0;
			for(int i=0;i<size;i++)
				if(insertNode(arr[i])){
					temp[j]=arr[i];
					j++;
				}
			delete[] arr;
			size=j;
			int* brr = new int[size];
			for(int i=0;i<size;i++)
			brr[i]=temp[i];
			delete[] temp;
			return brr;
		}
		Node* findSuccessor(Node* temp){
			if(temp->right)
			return findMinUtil(temp->right);
		}
		bool deleteNode(int data){
			return deleteNodeUtil(&root,data);
		}
		
};

void removeDuplicate(BST tree){
	int size;
	cout << "Enter array size: ";
	cin >> size;
	int *arr = new int[size];
	cout << "Enter array elements: ";
	for(int i=0;i<size;i++)
		cin >> arr[i];
	arr=tree.deleteDuplicate(arr,size);
	cout << endl <<  "Non-duplicated: " << endl;
	for(int i=0;i<size;i++)
		cout << arr[i] << endl;
}

int main(){
	BST tree;
	tree.insertNode(7);
	tree.insertNode(3);
	tree.insertNode(15);
	tree.insertNode(10);
	tree.insertNode(17);
	tree.insertNode(12);
	tree.insertNode(19);
	tree.preOrder();
	tree.deleteNode(10);
	tree.preOrder();
	return 0;
}
