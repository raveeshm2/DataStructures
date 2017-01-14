#include <iostream>
#include <cmath>
using namespace std;

class heap{
	int size,arr[100];
	void maxheapify(int i){
			if(i>=size)
			return;
			int temp=arr[i];
			if(2*i+1<size && arr[2*i+1]>temp)
			temp=arr[2*i+1];
			if(2*i+2<size && arr[2*i+2]>temp)
			temp=arr[2*i+2];
			if(2*i+1<size && temp==arr[2*i+1]){
				swap(arr[i],arr[2*i+1]);
				maxheapify(2*i+1);
			}else if(2*i+2<size && temp==arr[2*i+2]){
				swap(arr[i],arr[2*i+2]);
				maxheapify(2*i+2);
			}
		}
		void buildMaxHeap(){
			int i = ceil(size/2)-1;
			while(i>=0){
				maxheapify(i);
				i--;
			}
		}
	public:
		void init(int temp[],int size){
			this->size=size;
			for(int i=0;i<size;i++)
			arr[i]=temp[i];
			buildMaxHeap();
		}
		void insert(int x){
			arr[size++]=x;
			int i=size-1,p=ceil(i/2)-1;
			while(p>=0 && arr[i]>arr[p]){
				swap(arr[i],arr[p]);
				i=p;
				p=ceil(i/2)-1;
			}
		}
		int findMax(){
			if(!isEmpty())
			return arr[0];
		}
		bool isEmpty(){
			if(size>0)
			return false;
			else
			return true;
		}
		void deleteMax(){
			if(!isEmpty()){
				arr[0]=arr[--size];
				maxheapify(0);
			}
		}
		void heapSort(int temp[],int size){
			init(temp,size);
			for(int i=size-1;i>=0;i--){
				temp[i]=findMax();
				deleteMax();
			}
		}
		
		void print(){
			for(int i=0;i<size;i++)
				cout << arr[i] << endl;
		}
};

int main(){
	heap h;
	int arr[]={7,2,4,1,99,11};
	int size=sizeof(arr)/sizeof(int);
	h.init(arr,size);
	h.insert(101);
	h.print();
	return 0;
}
