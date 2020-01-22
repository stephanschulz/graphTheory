//
//  graph.h
//  emptyExample
//
//  Created by Stephan Schulz on 2020-01-20.
//

#ifndef graph_h
#define graph_h


//https://medium.com/basecs/a-gentle-introduction-to-graph-theory-77969829ead8
//https://medium.com/basecs/finding-the-shortest-path-with-a-little-help-from-dijkstra-613149fbdc8e

//https://www.geeksforgeeks.org/graph-and-its-representations/
//https://www.geeksforgeeks.org/shortest-path-unweighted-graph/

//https://www.sanfoundry.com/cpp-programming-examples-graph-problems-algorithms/

//https://stackoverflow.com/questions/16631514/adjacency-list-implementation-in-c


#define NIL -1
#define INF INT_MAX

class AdjListNode
{
    int v;
    int weight;
    ofVec2f position;
public:
    AdjListNode(int _v, ofVec2f _pos, int _w)
    {
        v = _v;
        position = _pos;
        weight = _w;
    }
    int getV()
    {
        return v;
    }
    int getWeight()
    {
        return weight;
    }
    
    void setPosition(ofVec2f pos){
        position = pos;
    }
    ofVec2f getPosition(){
        return position;
    }
    
    void draw(){
        ofNoFill();
        ofSetColor(255,0,0);
        ofDrawCircle(position,10);
        ofLog()<<v<<", position "<<position;
    }
};

class Graph {
private:
    int verticesAmount; // No. of vertices
    list<AdjListNode> *adjNode;    // Pointer to an array containing adjacency lists
    
public:
    
    
    void setup(int _V)
    {
        this->verticesAmount = _V;
        adjNode = new list<AdjListNode> [this->verticesAmount];
        
        ofLog()<<"setup() adjNode.size() "<<adjNode->size()<<" V "<<_V;
    }
    
    void addEdge(int v, int w, ofVec2f pos, int weight = 1)
    {
        
        AdjListNode node(w, pos, weight);
        adjNode[v].push_back(node); // Add v to u's list
//                *adjNode[v]->setPosition(pos);
        
        ofLog()<<"addEdge() adjNode.size() "<<adjNode->size()<<" v "<<v;
        ofLog()<<"adjNode[v].back().pos "<<adjNode[v].back().getPosition();
    }
    
    
    void draw(){
        //MARK:----draw each node only ones
        // Mark all the vertices as not visited 
        bool *visited = new bool[verticesAmount]; 
        
        // Create an array to store paths 
        int *path = new int[verticesAmount]; 
        int path_index = 0; // Initialize path[] as empty 
        
        // Initialize all vertices as not visited 
        for (int i = 0; i < verticesAmount; i++){ 
            visited[i] = false; 
        }

        
          ofLog()<<"draw() start -------------";
//        list<AdjListNode>::iterator i;
//        for (i = adjNode->begin(); i != adjNode->end(); ++i) 
//        {
//            (*i).getWeight();
//            (*i).getPosition();
//            ofLog()<<"(*i) "<<(*i).getV();
//            (*i).draw();
//        }
        
 
        for(int u=0; u<verticesAmount; u++){
            
            for(auto & one_adjNode :  adjNode[u]){      
                
                ofLog()<<"node v  "<<one_adjNode.getV()<<" u "<<u;
                
                if (!visited[one_adjNode.getV()]){
                    one_adjNode.draw();
                    visited[one_adjNode.getV()] = true;
                }
            }
        }

        ofLog()<<"draw() end -------------";
    }
    //MARK:---check if two nodes are reachable; i.e. a path between them
    // A BFS based function to check whether d is reachable from s.
    bool isReachable(int s, int d)
    {
        // Base case
        if (s == d)
            return true;
        
        // Mark all the vertices as not visited
        bool *visited = new bool[verticesAmount];
        for (int i = 0; i < verticesAmount; i++)
            visited[i] = false;
        
        // Create a queue for BFS
        list<int> queue;
        
        // Mark the current node as visited and enqueue it
        visited[s] = true;
        queue.push_back(s);
        
        // it will be used to get all adjacent vertices of a vertex
        //        list<int>::iterator i;
        list<AdjListNode>::iterator i;
        
        while (!queue.empty())
        {
            // Dequeue a vertex from queue and print it
            s = queue.front();
            queue.pop_front();
            
            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it visited
            // and enqueue it
            for (i = adjNode[s].begin(); i != adjNode[s].end(); ++i)
            {
                // If this adjacent node is the destination node, then return true
                AdjListNode node = *i;
                if (node.getV() == d)
                    return true;
                
                // Else, continue to do BFS
                if (!visited[node.getV()])
                {
                    visited[node.getV()] = true;
                    queue.push_back(node.getV());
                    
                    ofLog()<<node.getV();
                }
            }
        }
        
        return false;
    }
    
    //MARK:---get all bridges ; i.e. only connection between islands
    void bridgeUtil(int u, bool visited[], int disc[], int low[],
                    int parent[])
    {
        // A static variable is used for simplicity, we can avoid use of static
        // variable by passing a pointer.
        static int time = 0;
        
        // Mark the current node as visited
        visited[u] = true;
        
        // Initialize discovery time and low value
        disc[u] = low[u] = ++time;
        
        // Go through all vertices aadjacent to this
        //        list<int>::iterator i;
        //        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        //        {
        list<AdjListNode>::iterator i;
        for (i = adjNode[u].begin(); i != adjNode[u].end(); ++i) 
        {
            //            int v = *i; // v is current adjacent of u
            AdjListNode node = *i;
            
            // If v is not visited yet, then recur for it
            if (!visited[node.getV()])
            {
                parent[node.getV()] = u;
                bridgeUtil(node.getV(), visited, disc, low, parent);
                
                // Check if the subtree rooted with v has a connection to
                // one of the ancestors of u
                low[u] = min(low[u], low[node.getV()]);
                
                // If the lowest vertex reachable from subtree under v is
                // below u in DFS tree, then u-v is a bridge
                if (low[node.getV()] > disc[u])
                    cout << u << " " << node.getV() << endl;
            }
            
            // Update low value of u for parent function calls.
            else if (node.getV() != parent[u])
                low[u] = min(low[u], disc[node.getV()]);
        }
    }
    
    // DFS based function to find all bridges. It uses recursive function bridgeUtil()
    void bridge()
    {
        // Mark all the vertices as not visited
        bool *visited = new bool[verticesAmount];
        int *disc = new int[verticesAmount];
        int *low = new int[verticesAmount];
        int *parent = new int[verticesAmount];
        
        // Initialize parent and visited arrays
        for (int i = 0; i < verticesAmount; i++)
        {
            parent[i] = NIL;
            visited[i] = false;
        }
        
        // Call the recursive helper function to find Bridges
        // in DFS tree rooted with vertex 'i'
        for (int i = 0; i < verticesAmount; i++){
            if (visited[i] == false){
                bridgeUtil(i, visited, disc, low, parent);
            }
        }
    }
    
    //MARK:-----print / get all possible paths from src to dst
    // Prints all paths from 's' to 'd' 
    void printAllPaths(int s, int d) 
    { 
        // Mark all the vertices as not visited 
        bool *visited = new bool[verticesAmount]; 
        
        // Create an array to store paths 
        int *path = new int[verticesAmount]; 
        int path_index = 0; // Initialize path[] as empty 
        
        // Initialize all vertices as not visited 
        for (int i = 0; i < verticesAmount; i++){ 
            visited[i] = false; 
        }
        // Call the recursive helper function to print all paths 
        printAllPathsUtil(s, d, visited, path, path_index); 
    } 
    
    // A recursive function to print all paths from 'u' to 'd'. 
    // visited[] keeps track of vertices in current path. 
    // path[] stores actual vertices and path_index is current 
    // index in path[] 
    void printAllPathsUtil(int u, int d, bool visited[], 
                           int path[], int &path_index) 
    { 
        // Mark the current node and store it in path[] 
        visited[u] = true; 
        path[path_index] = u; 
        path_index++; 
        
        // If current vertex is same as destination, then print 
        // current path[] 
        if (u == d) 
        { 
            for (int i = 0; i<path_index; i++){ 
                cout << path[i] << " "; 
            }
            cout << endl; 
            
        } 
        else // If current vertex is not destination 
        { 
            // Recur for all the vertices adjacent to current vertex 
            /*
             list<int>::iterator i; 
             for (i = adj[u].begin(); i != adj[u].end(); ++i) 
             if (!visited[*i]) 
             printAllPathsUtil(*i, d, visited, path, path_index); 
             */
            
            list<AdjListNode>::iterator i;
            for (i = adjNode[u].begin(); i != adjNode[u].end(); ++i) 
            {
                AdjListNode node = *i;
                if (!visited[node.getV()])
                    printAllPathsUtil(node.getV(), d, visited, path, path_index); 
            }
        } 
        
        // Remove current vertex from path[] and mark it as unvisited 
        path_index--; 
        visited[u] = false; 
    } 
    
    //MARK:----shortest path based on weighted relation
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
    {
        // Mark the current node as visited
        visited[v] = true;
        
        // Recur for all the vertices adjacent to this vertex
        list<AdjListNode>::iterator i;
        for (i = adjNode[v].begin(); i != adjNode[v].end(); ++i)
        {
            AdjListNode node = *i;
            if (!visited[node.getV()])
                topologicalSortUtil(node.getV(), visited, Stack);
        }
        
        // Push current vertex to stack which stores topological sort
        Stack.push(v);
    }
    
    void shortestPath(int s)
    {
        stack<int> Stack;
        int dist[verticesAmount];
        
        // Mark all the vertices as not visited
        bool *visited = new bool[verticesAmount];
        for (int i = 0; i < verticesAmount; i++)
            visited[i] = false;
        
        // Call the recursive helper function to store Topological Sort
        // starting from all vertices one by one
        for (int i = 0; i < verticesAmount; i++)
            if (visited[i] == false)
                topologicalSortUtil(i, visited, Stack);
        
        // Initialize distances to all vertices as infinite and distance
        // to source as 0
        for (int i = 0; i < verticesAmount; i++){
            dist[i] = INF;
        }
        dist[s] = 0;
        
        // Process vertices in topological order
        while (Stack.empty() == false)
        {
            // Get the next vertex from topological order
            int u = Stack.top();
            Stack.pop();
            
            // Update distances of all adjacent vertices
            list<AdjListNode>::iterator i;
            if (dist[u] != INF)
            {
                for (i = adjNode[u].begin(); i != adjNode[u].end(); ++i)
                    if (dist[i->getV()] > dist[u] + i->getWeight())
                        dist[i->getV()] = dist[u] + i->getWeight();
            }
        }
        
        // Print the calculated shortest distances
        for (int i = 0; i < verticesAmount; i++)
            (dist[i] == INF) ? cout << "INF " : cout << dist[i] << " ";
    }
    
};
#endif /* graph_h */
