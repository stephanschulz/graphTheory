#include "ofApp.h"

//https://www.sanfoundry.com/cpp-program-find-shortest-path-between-two-vertices-using-dijkstras-algorithm/

//--------------------------------------------------------------
void ofApp::setup(){

    
    vector<ofVec2f> nodeList;
    
    nodeList.push_back(ofVec2f(10,10));
    nodeList.push_back(ofVec2f(200,20));
    
    nodeList.push_back(ofVec2f(350,100));
    nodeList.push_back(ofVec2f(210,180));
    nodeList.push_back(ofVec2f(30,200));
    
   
    
    // Create a graph given in the above diagram
    
    graph_object.setup(12);
    graph_object.addEdge(0, 1, nodeList[1]);
    graph_object.addEdge(0, 4, nodeList[4]);
    
    graph_object.addEdge(1, 0, nodeList[0]);
    graph_object.addEdge(1, 4, nodeList[4]);
    graph_object.addEdge(1, 2, nodeList[2]);
    graph_object.addEdge(1, 3, nodeList[3]);
    
    graph_object.addEdge(2, 1, nodeList[1]);
    //    graph_object.addEdge(2, 5);
    //    graph_object.addEdge(2, 3);
    
    graph_object.addEdge(3, 1, nodeList[1]);
    graph_object.addEdge(3, 4, nodeList[4]);
    //    graph_object.addEdge(3, 2);
    
    graph_object.addEdge(4, 3, nodeList[3]);
    graph_object.addEdge(4, 0, nodeList[0]);
    graph_object.addEdge(4, 1, nodeList[1]);
    
//    graph_object.addEdge(0, 1, nodeList[0]);
//    graph_object.addEdge(0, 4, nodeList[0]);
//    
//    graph_object.addEdge(1, 0, nodeList[1]);
//    graph_object.addEdge(1, 4, nodeList[1]);
//    graph_object.addEdge(1, 2, nodeList[1]);
//    graph_object.addEdge(1, 3, nodeList[1]);
//    
//    graph_object.addEdge(2, 1, nodeList[2]);
////    graph_object.addEdge(2, 5);
////    graph_object.addEdge(2, 3);
//    
//    graph_object.addEdge(3, 1, nodeList[3]);
//    graph_object.addEdge(3, 4, nodeList[3]);
////    graph_object.addEdge(3, 2);
//    
//    graph_object.addEdge(4, 3, nodeList[4]);
//    graph_object.addEdge(4, 0, nodeList[4]);
//    graph_object.addEdge(4, 1, nodeList[4]);
  
    
//    graph_object.setup(12);
//    graph_object.addEdge(0, 1, ofRandom(-10,10));
//    graph_object.addEdge(0, 4, ofRandom(-10,10));
//    
//    graph_object.addEdge(1, 0, ofRandom(-10,10));
//    graph_object.addEdge(1, 4, ofRandom(-10,10));
//    graph_object.addEdge(1, 2, ofRandom(-10,10));
//    graph_object.addEdge(1, 3, ofRandom(-10,10));
//    
//    graph_object.addEdge(2, 1, ofRandom(-10,10));
//    //    graph_object.addEdge(2, 5);
//    //    graph_object.addEdge(2, 3);
//    
//    graph_object.addEdge(3, 1, ofRandom(-10,10));
//    graph_object.addEdge(3, 4, ofRandom(-10,10));
//    //    graph_object.addEdge(3, 2);
//    
//    graph_object.addEdge(4, 3, ofRandom(-10,10));
//    graph_object.addEdge(4, 0, ofRandom(-10,10));
//    graph_object.addEdge(4, 1, ofRandom(-10,10));
    
//    graph_object.addEdge(5, 2);
//    cout << "Enter the source and destination vertices: (0-3)";
    int src, dst;
    src = 0;
    dst = 3;
//    cin >> u >> v;
    //https://www.sanfoundry.com/cpp-program-find-shortest-path-between-two-vertices-using-dijkstras-algorithm/
    if (graph_object.isReachable(src, dst))
        ofLog() << "\nThere is a path from " << src << " to " << dst;
    else
        ofLog() << "\nThere is no path from " << src << " to " << dst;
 
    
    //https://www.geeksforgeeks.org/find-paths-given-source-destination/
    ofLog() << "Following are all different paths from " << src 
    << " to " << dst << endl; 
    graph_object.printAllPaths(src, dst); 
    
    //https://www.sanfoundry.com/cpp-program-find-edge-connectivity-graph/
    //bridges are only connection between two nodes. without this islands would be created
    ofLog() << "\nBridges in graph \n";
    graph_object.bridge();
    
    ofLog() << "Following are shortest distances from source " << src;
    graph_object.shortestPath(src);
    
//    int temp;
//    temp = u;
//    u = v;
//    v = temp;
//    if (graph_object.isReachable(u, v))
//        cout << "\nThere is a path from " << u << " to " << v;
//    else
//        cout << "\nThere is no path from " << u << " to " << v;
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
//    graph_object.update();  
}

//--------------------------------------------------------------
void ofApp::draw(){
    graph_object.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
