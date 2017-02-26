#include <iostream>

using namespace std;

struct Node{
	Node *parent;
	Node *left;
	int data;
	Node *right;
};

class BST{
	Node *root;
	Node* createNode(int data,Node* parent){
		Node *temp = new Node();
		temp->data=data;
		temp->left=NULL;
		temp->right=NULL;
		temp->parent=parent;
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
		cout << temp->data << " ";
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
			return true;
		}
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
	tree.inOrder();
	if(tree.deleteNode(10))
	tree.inOrder();
	if(tree.deleteNode(15))
	tree.inOrder();
	if(tree.deleteNode(17))
	tree.inOrder();
	if(tree.deleteNode(10))
	tree.inOrder();
	if(tree.deleteNode(12))
	tree.inOrder();
	if(tree.deleteNode(3))
	tree.inOrder();
	if(tree.deleteNode(7))
	tree.inOrder();
	return 0;
}
