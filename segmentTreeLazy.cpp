#include <iostream>

using namespace std;

class SegmentTree{
	int size;
	int *segment,*lazy;
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
	void updateSegmentTreeRangeLazy(int start,int end,int delta,int low,int high,int pos){
		if(low>high)
			return;
			
		if(lazy[pos]!=0){ // check if all propagations upto this point has been done
			segment[pos]=lazy[pos]*(high-low+1); // change this function according to the problem
			if(low!=high){ // check if not leaf
				lazy[2*pos+1]=lazy[pos];
				lazy[2*pos+2]=lazy[pos];
			}
			lazy[pos]=0;
		}
		
		if(start>high || end<low) // no overlap
			return;
			
		// Total Overlap
		if(start<=low && end>=high){
			segment[pos]=delta*(high-low+1); // change this function according to the problem
			if(low!=high){
				// Passing the propagations below in lazy tree
				lazy[2*pos+1]=delta;
				lazy[2*pos+2]=delta;
			}
			return;   // return to avoid further updations
		}
			
		// Partial Overlap	
		int mid=low+(high-low)/2;
		updateSegmentTreeRangeLazy(start,end,delta,low,mid,2*pos+1);
		updateSegmentTreeRangeLazy(start,end,delta,mid+1,high,2*pos+2);
		segment[pos]=segment[2*pos+1]+segment[2*pos+2]; // change this function accordingly.
	}
	int queryTreeRangeLazy(int start,int end,int low,int high,int pos){
		if(low>high)
			return 0;
		
		if(lazy[pos]!=0){
			segment[pos]=lazy[pos]*(high-low+1);
			if(low!=high){
				lazy[2*pos+1]=lazy[pos];
				lazy[2*pos+2]=lazy[pos];
			}
			lazy[pos]=0;
		}
				
		// Total Overlap
		if(start<=low && end>=high)
		return segment[pos];
		
		// No Overlap
		if(start>high || end<low)
		return 0;  // change return value according to the problem.
		
		// Partial Overlap
		int mid=low+(high-low)/2;
		int res1=queryTreeRangeLazy(start,end,low,mid,2*pos+1);
		int res2=queryTreeRangeLazy(start,end,mid+1,high,2*pos+2);
		
		return res1+res2; // change this function according to the problem
	}
	public:
		SegmentTree(int arr[],int length){
			IpSize=length;
			size=nextPower2(length)*2-1;
			segment = new int[size];
			lazy = new int[size];
			for(int i=0;i<size;i++){
				// change this value according to the problem.
				segment[i]=0; 
				lazy[i]=0;
			}
			createSegmentTree(arr,0,length-1,0);
		}
		
		void updateAtIndex(int index,int delta){
			updateAtIndex(index,delta,0,IpSize-1,0);
		}
		
		void updateRangeLazy(int start,int end,int delta){
			updateSegmentTreeRangeLazy(start,end,delta,0,IpSize-1,0);
		}
		int queryRangeLazy(int start,int end){
			return queryTreeRangeLazy(start,end,0,IpSize-1,0);
		}
};

int main(){
	int arr[]={4,2,7,1,3,6,9,7};
	int size=sizeof(arr)/sizeof(arr[0]);
	SegmentTree tree(arr,size);
	cout << tree.queryRangeLazy(2,6) << endl;
	tree.updateRangeLazy(2,6,3);
	cout << tree.queryRangeLazy(2,6) << endl;
	return 0;
}
