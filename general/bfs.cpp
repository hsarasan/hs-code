#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>

class Graph{

    std::vector<std::pair<int,int>> edges;
    std::set<int> nodes;


        void BFSHelper(int node, std::map<int, bool> & visited, int distance){
            
            if (visited[node]) return;
            std::queue<int> Q;
            visited[node]=true;
            std::cout<<"Visited "<<node<<" distance "<<distance<<std::endl;
            for (const auto & edge: edges){
                if (edge.first==node || edge.second==node){
                    int n;
                    if (edge.first==node) n = edge.second;
                    else n=edge.first;
                    if (!visited[n]){
                        Q.push(n);
                    }
                }
            }
            distance++;
            while(!Q.empty()){
                int n = Q.front();
                BFSHelper(n,visited, distance);
                Q.pop();
            }   
        }
    public:
        void BFS(int node){
            std::map<int, bool> visited;
            BFSHelper(node, visited,0);
        }
        void addEdge(int x, int y){
            edges.push_back({x,y});
            nodes.insert(x);
            nodes.insert(y);
        }
        void printAllEdges(){
            for (const auto & edge: edges){
                std::cout<<"edges "<<edge.first<<","<<edge.second<<std::endl;
            }
        }
        void printAllEdgesFrom(int n){
            for (const auto & edge: edges){
                if (edge.first==n || edge.second==n)
                    std::cout<<"edges "<<edge.first<<","<<edge.second<<std::endl;
            }
        }

};

int main(){
    Graph g;
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,6);
    g.addEdge(3,7);
    g.addEdge(4,8);
    //g.printAllEdges();
    //g.printAllEdgesFrom(2);
    g.BFS(1);
    return 0;
}

