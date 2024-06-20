#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

// MAX SIZE OF TREE (Can be modified)
const int MAXN=100005;

// NUMBER OF TESTS DONE
const int T=10000;

//ADJACENCY LIST
vector<int> adj[MAXN];

//ANCESTOR LIST(CENTROID ANCESTORS)
vector<int> ancestors[MAXN];

//VERTICES THAT HAVE ALREADY BEEN REMOVED
bool removed[MAXN];

//SIZE OF SUBTREE OF VERTEX
int sz[MAXN];

//FLAG TO SHOW OUTPUT SMALL EXAMPLE
bool test=0;

/**
 * Calculate the size of a subtree when rooting the tree at a specific vertex.
 * The size of the subtree is stored in array sz.
 * @param curNode current vertex being visited.
 * @param parent parent of current vertex.
 * @return size of subtree of vertex.
 */
int getSize(int curNode, int parent = -1) {

	sz[curNode] = 1;

	for (int x : adj[curNode]) {

		if (x == parent || removed[x])  continue;

		sz[curNode] += getSize(x, curNode);

	}

	return sz[curNode];

}

/**
 * Finds the centroid of a tree.
 * @param curNode current vertex being visited.
 * @param sizeOfTree size of tree of which centroid is trying to be found.
 * @param parent parent of current vertex.
 * @return centroid of the tree.
 */

int getCentroid(int curNode, int sizeOfTree, int parent = -1) {

	for (int x : adj[curNode]) {

		if (x == parent || removed[x])  continue; 

		if (sz[x] * 2 > sizeOfTree) {

			return getCentroid(x, sizeOfTree, curNode);

		}

	}

	return curNode;

}

/**
 * Finds (centroid ancestors) of a vertex.
 * @param curNode current vertex being visited.
 * @param centroid centroid of tree being currently visited.
 * @param parent parent of current vertex.
 */

void getAncestors(int curNode, int centroid, int parent){
  for(int x:adj[curNode]){
    if (x==parent || removed[x]) { 
      continue; 
    }
    getAncestors(x, centroid, curNode);
  }
  ancestors[curNode].push_back(centroid);
}


/**
 * Builds the centroid decomposition.
 * @param curNode current vertex being visited.
 */

void centroidDecomposition(int curNode) {

	int centroid = getCentroid(curNode, getSize(curNode));

  for(int x:adj[centroid]){
    if (removed[x]) continue; 
    getAncestors(x, centroid, centroid);
  }

	removed[centroid] = true;

	for (int x: adj[centroid]) {

		if (removed[x]) { continue; }

		centroidDecomposition(x);

	}

}


int main(){
  //Test to print results of an example(only executed if flag test is set to true).
  if(test){
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[3].push_back(5);
    adj[3].push_back(6);
    adj[4].push_back(3);
    adj[5].push_back(3);
    adj[5].push_back(7);
    adj[5].push_back(8);
    adj[6].push_back(3);
    adj[6].push_back(9);
    adj[7].push_back(5);
    adj[7].push_back(10);
    adj[8].push_back(5);
    adj[9].push_back(6);
    adj[9].push_back(11);
    adj[10].push_back(7);
    adj[10].push_back(12);
    adj[11].push_back(9);
    adj[11].push_back(13);
    adj[11].push_back(14);
    adj[12].push_back(10);
    adj[13].push_back(11);
    adj[14].push_back(11);
    adj[14].push_back(15);
    adj[15].push_back(14);

    for(int i=1;i<=15;i++){
      cout << "VERTEX " << i << ":" << endl;
      for(int x:adj[i]){
        cout << x << " ";
      }
      cout << endl;
    }

    cout << endl;
    centroidDecomposition(1);
    cout << "CENTROID DECOMPOSITION" << endl;
    cout << "ANCESTORS" << endl;
    for (int i=1;i<=15;i++){
      cout << "VERTEX " << i << ":" << endl;
      for (int x:ancestors[i]){
        cout << x << " ";
      }
      cout << endl;
    }
  }
  else{
    //reads the random generated data from inputData.txt file
    freopen("inputData.txt", "r", stdin);
    string inputData, delimeter=",", s;
    getline(cin, inputData);
    vector<int> data;
    int pos;
    while((pos=inputData.find(delimeter))!=string::npos){
      s=inputData.substr(0, pos);
      data.push_back(stoi(s));
      inputData.erase(0, pos+1);
    }
    fclose(stdin);
    // File that stores execution time based on size of n.
    freopen("dataNormal.txt", "w", stdout);
    long double startTime, endTime, totalTime;
    for (int i=2;i<=T;i++){
      for (int j=0;j<=i;j++){
          removed[j]=0;
          ancestors[j].clear();
          sz[j]=0;
      }
      int randNode=data[i-2];
      adj[i].push_back(randNode);
      adj[randNode].push_back(i);
      startTime=(long double)omp_get_wtime();
      centroidDecomposition(1);
      endTime=(long double)omp_get_wtime();
      totalTime=endTime-startTime;
      cout << fixed << setprecision(20) << totalTime << endl;
      cout << ", ";
    }
    fclose(stdout);
    // File to print results of centroid decomposition of random tree with T vertices.
    freopen("serialTest.txt", "w", stdout);
    for (int i=1;i<=T;i++){
      cout << "VERTEX " << i << ":" << endl;
      for (int x:ancestors[i]){
        cout << x << " ";
      }
      cout << endl;
    }
    fclose(stdout);
  }
}