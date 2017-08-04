#include <bits/stdc++.h>

using namespace std;

class Trie{
	class TrieNode{
		public:
		int count;
		map<char,TrieNode*> hash;
		TrieNode(){
			count=0;
		}
	};
	TrieNode *root;
	bool deleteRecursive(TrieNode *curr,string str,int index){
		if(index==str.size()){
			if(curr->count==0)  // string does not exist in Trie
				return false;
			else{
				if(curr->count>0)
					curr->count--;
				// do not delete if one or more strings are present below the current node, or one or more occurneces of current string are remaining
				if(curr->hash.size()>0 || curr->count) 
					return false;
				else
					return true;
			}
		}
		if(curr->hash.find(str[index])==curr->hash.end())
			return false;  // string does exist
		else{
			bool res=deleteRecursive(curr->hash[str[index]],str,index+1);
			if(res){ 
				TrieNode *temp=curr->hash[str[index]];
				curr->hash.erase(str[index]);
				delete temp;
				return (curr->hash.size()==0);  //delete the current node if hash is empty
			}
			else
				return false;
		}
	}
	public:
	Trie(){
		root = new TrieNode();
	}
	void insertString(string str){
		TrieNode *curr=root;
		for(int i=0;i<str.size();i++){
			if(curr->hash.find(str[i])==curr->hash.end())
				curr->hash[str[i]]=new TrieNode();
			curr=curr->hash[str[i]];
		}
		curr->count++;
	}
	
	// returns the no of occurences of a given string
	int queryString(string str){
		TrieNode *curr=root;
		for(int i=0;i<str.size();i++){
			if(curr->hash.find(str[i])==curr->hash.end())
				return 0;
			else
				curr=curr->hash[str[i]];
		}
		return curr->count;
	}
	
	void deleteString(string str){
		deleteRecursive(root,str,0);
	}
	
	void update(string oldString,string newString){
		deleteString(oldString);
		insertString(newString);
	}
	
	bool isExist(string str){
		return queryString(str);
	}
};

int main(){
	Trie trie;
	trie.insertString("abc");
	trie.insertString("abgl");
	trie.insertString("cdf");
	trie.insertString("abcd");
	trie.insertString("lmn");
	trie.insertString("abc");
	cout << trie.queryString("abc") << endl;
	cout << trie.queryString("lmn") << endl;
	cout << trie.queryString("cde") << endl;
	cout << trie.queryString("mqr") << endl;
	cout << trie.queryString("abgl") << endl;
	trie.deleteString("abc");
	trie.deleteString("lmn");
	cout << trie.queryString("abc") << endl;
	cout << trie.queryString("abcd") << endl;
	cout << trie.queryString("lmn") << endl;
	trie.deleteString("abc");
	cout << trie.queryString("abc") << endl;
	cout << trie.queryString("abcd") << endl;
	trie.deleteString("abc");
	cout << trie.queryString("abc") << endl;
	cout << trie.queryString("abcd") << endl;
	trie.deleteString("abcd");
	cout << trie.queryString("abc") << endl;
	cout << trie.queryString("abcd") << endl;
	return 0;
}
