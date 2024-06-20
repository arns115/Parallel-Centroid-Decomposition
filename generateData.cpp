#include <bits/stdc++.h>
using namespace std;

// NUMBER OF TESTS DONE
const int T=10000;

//FLAG TO MAKE TREE HAVE VERTICES WITH HIGH NUMBER OF ADJACENT VERTICES OR NOT
bool highAdjacency=1;

//DETERMINES HOW MANY VERTICES MUST HAVE HIGH NUMBER OF ADJACENT VERTICES WHEN FLAG IS SET TO TRUE
int r=10;

int main(){
  // Use current time as seed for random generator 
  srand(time(0));
   // File that stores inputData generated randomly
  freopen("inputData.txt", "w", stdout);
  for(int i=2;i<=T;i++){
    // Edge is created between vertex i and vertex smaller than i.
    // If highAdjacency is set to true edges are only added between vertex i and one of the first r vertices.
    int randNode=(rand()%min((highAdjacency ? r:(int)1e9), i-1))+1;
    cout << randNode <<  ",";
  }
  fclose(stdout);
}