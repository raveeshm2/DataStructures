#include <iostream>

using namespace std;

class SegmentTree{
	int size;
	int *segment;
	int IpSize;
	int nextPower2(int x){
		int res=1;
		while(x>res)
			res=res<<1;
		return res;
	}
	void createSegmentTree(int arr[],int low,int high,int pos){
		if(low==high){
			segment[pos]=arr[low];
			return;
		}
		int mid=low+(high-low)/2;
		createSegmentTree(arr,low,mid,2*pos+1);
		createSegmentTree(arr,mid+1,high,2*pos+2);
		segment[pos]=segment[2*pos+1]+segment[2*pos+2];
	}
	void updateAtIndex(int index,int delta,int low,int high,int pos){
		if(index<low || index>high)
			return;
		
		// index is also equal to low and high
		if(low==high){
			segment[pos]=delta;
			return;
		}
		
		int mid=low+(high-low)/2;
		updateAtIndex(index,delta,low,mid,2*pos+1);
		updateAtIndex(index,delta,mid+1,high,2*pos+2);
		segment[pos]=segment[2*pos+1]+segment[2*pos+2];
	}
	void updateSegmentTreeRange(int start,int end,int delta,int low,int high,int pos){
		if(low>high || start>high || end<low)
			return;
			
		if(low==high){
			segment[pos]=delta;
			return;
		}
		
		int mid=low+(high-low)/2;
		updateSegmentTreeRange(start,end,delta,low,mid,2*pos+1);
		updateSegmentTreeRange(start,end,delta,mid+1,high,2*pos+2);
		segment[pos]=segment[2*pos+1]+segment[2*pos+2];
	}
	int queryTreeRange(int start,int end,int low,int high,int pos){
		// Total Overlap
		if(start<=low && end>=high)
		return segment[pos];
		
		// No Overlap
		if(start>high || end<low)
		return 0;  // change return value according to the problem.
		
		// Partial Overlap
		int mid=low+(high-low)/2;
		int res1=queryTreeRange(start,end,low,mid,2*pos+1);
		int res2=queryTreeRange(start,end,mid+1,high,2*pos+2);
		
		return res1+res2; // change this function according to the problem
	}
	public:
		SegmentTree(int arr[],int length){
			IpSize=length;
			size=nextPower2(length)*2-1;
			segment = new int[size];
			for(int i=0;i<size;i++)
			segment[i]=0; // change this value according to the problem.
			createSegmentTree(arr,0,length-1,0);
		}
		
		void updateAtIndex(int index,int delta){
			updateAtIndex(index,delta,0,IpSize-1,0);
		}
		
		void updateRange(int start,int end,int delta){
			updateSegmentTreeRange(start,end,delta,0,IpSize-1,0);
		}
		int queryRange(int start,int end){
			return queryTreeRange(start,end,0,IpSize-1,0);
		}
};

int main(){
	int arr[]={4,2,7,1,3,6,9,7};
	int size=sizeof(arr)/sizeof(arr[0]);
	SegmentTree tree(arr,size);
	cout << tree.queryRange(0,3) << endl;
	tree.updateRange(1,3,1);
	cout << tree.queryRange(0,3) << endl;
	return 0;
}
