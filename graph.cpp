#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph{
	int size;
	vector<vector<int> > graph;
	vector<bool> visited;
	bool isDirected;
	void emptyVisited(){
		fill(visited.begin(),visited.end(),false);
	}
	void bfsUtil(int root){
		if(!visited[root]){
			queue<int> q;
			q.push(root);
			visited[root]=true;
			while(!q.empty()){
				int temp=q.front();
				q.pop();
				cout << temp << " ";
				for(vector<int>::iterator it=graph[temp].begin();it!=graph[temp].end();it++){
					if(!visited[*it]){
						q.push(*it);
						visited[*it]=true;
					}
				}
			}
		}
	}
	void dfsUtil(int root){
		if(!visited[root]){
			stack<int> s;
			s.push(root);
			visited[root]=true;
			while(!s.empty()){
				int temp=s.top();
				s.pop();
				cout << temp << " ";
				for(vector<int>::iterator it=graph[temp].begin();it!=graph[temp].end();it++){
					if(!visited[*it]){
						s.push(*it);
						visited[*it]=true;
					}
				}
			}
		}
	}
	void dfsRecurUtil(int root){
		if(!visited[root]){
			cout << root << " ";
			visited[root]=true;
			for(vector<int>::iterator it=graph[root].begin();it!=graph[root].end();it++)
			dfsRecurUtil(*it);
		}
	}
	public:
	Graph(int size,bool isDirected=false){
		this->size=size;
		graph.resize(size+1);
		visited.resize(size+1);
		this->isDirected=isDirected;
	}
	void addEdge(int s1,int s2){
		graph[s1].push_back(s2);
		if(!isDirected)
		graph[s2].push_back(s1);
	}
	void bfs(){
		emptyVisited();
		for(int i=1;i<=size;i++)
			bfsUtil(i);
	}
	void dfs(){
		emptyVisited();
		for(int i=1;i<=size;i++)
			dfsUtil(i);
	}
	void dfsRecursive(){
		emptyVisited();
		for(int i=1;i<=size;i++)
			dfsRecurUtil(i);
	}
};


int main(){
	Graph g(8,true);
	g.addEdge(1,5);
	g.addEdge(1,3);
	g.addEdge(3,2);
	g.addEdge(2,4);
	g.addEdge(4,5);
	g.addEdge(5,6);
	g.addEdge(7,8);
	cout << "BFS: " << endl;
	g.bfs();
	cout << endl;
	cout << "DFS: " << endl;
	g.dfs();
	cout << endl;
	cout << "DFS Recursive: " << endl;
	g.dfsRecursive();
	cout << endl;
	return 0;
}
