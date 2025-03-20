#include<bits/stdc++.h>
using namespace std;

#define M 5   //row
#define N 5   //col

// pair<int,int> src={4,0};
pair<int,int> dst={2,2};
pair<int,int> cur={4,0};

// vector<pair<int,int>>sign={{0,1},{0,-1},{1,0},{-1,0}};

struct cell{
    // int row,col;
    int weight;
    vector<bool>wall;
    // {0,0,0,0}
    //  T R B L
    cell(int weight,vector<bool>neigh){
        // this->row=row;
        // this->col=col;
        this->weight=weight;
        this->wall=neigh;
    }
};

vector<vector<cell>> celler;

void printCeller(){
    cout<<endl;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(i==cur.first && j==cur.second){
                cout<<celler[i][j].weight<<'.';
                continue;
            }
            cout<<celler[i][j].weight<<" ";
        } cout<<endl;
    }
}

bool LidarInput() {
    cout << "Enter Lidar Signal -> CELL : " << cur.first << " " << cur.second << endl;

    bool top, right, bottom, left;
    cin >> top >> right >> bottom >> left;

    if (cin.fail()) {
        cerr << "Invalid input! Expected four boolean values (0 or 1)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    vector<bool> wall = {top, right, bottom, left};
    celler[cur.first][cur.second].wall = wall;

    if (cur.first > 0) {
        celler[cur.first - 1][cur.second].wall[2] = wall[0]; // Top affects bottom of upper cell
    }
    if (cur.first < M - 1) {
        celler[cur.first + 1][cur.second].wall[0] = wall[2]; // Bottom affects top of lower cell
    }
    if (cur.second > 0) {
        celler[cur.first][cur.second - 1].wall[1] = wall[3]; // Left affects right of left cell
    }
    if (cur.second < N - 1) {
        celler[cur.first][cur.second + 1].wall[3] = wall[1]; // Right affects left of right cell
    }

    return true;
}


void GenerateManhattenDistance(){
    queue<pair<int,int>>q;
    q.push(dst);
    int layer=0;
    vector<vector<bool>> visited(M, vector<bool>(N, false));
    visited[dst.first][dst.second]=true;
    while(!q.empty()){
        int size=q.size();
        while(size-->0){
            pair<int,int> picked=q.front();
            q.pop();
            celler[picked.first][picked.second].weight=layer;
            if (picked.first > 0 && !celler[picked.first][picked.second].wall[0] && !visited[picked.first - 1][picked.second]) { // Top
                q.push({picked.first - 1, picked.second});
                visited[picked.first - 1][picked.second] = true;
            }
            if (picked.second < N - 1 && !celler[picked.first][picked.second].wall[1] && !visited[picked.first][picked.second + 1]) { // Right
                q.push({picked.first, picked.second + 1});
                visited[picked.first][picked.second + 1] = true;
            }
            if (picked.first < M - 1 && !celler[picked.first][picked.second].wall[2] && !visited[picked.first + 1][picked.second]) { // Bottom
                q.push({picked.first + 1, picked.second});
                visited[picked.first + 1][picked.second] = true;
            }
            if (picked.second > 0 && !celler[picked.first][picked.second].wall[3] && !visited[picked.first][picked.second - 1]) { // Left
                q.push({picked.first, picked.second - 1});
                visited[picked.first][picked.second - 1] = true;
            }
        }
        layer++;
    }
}

pair<int, int> pickMinimumNeighbour() {
    int weight = INT_MAX;
    int row = cur.first, col = cur.second;
    string direction = "None";

    // Neighbor offsets for {Top, Right, Bottom, Left}
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<string> directionNames = {"Top", "Right", "Bottom", "Left"};

    for (int i = 0; i < 4; i++) {
        int newRow = cur.first + directions[i].first;
        int newCol = cur.second + directions[i].second;

        if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < N && 
            !celler[cur.first][cur.second].wall[i] &&
            celler[newRow][newCol].weight < weight) {

            weight = celler[newRow][newCol].weight;
            row = newRow;
            col = newCol;
            direction = directionNames[i];
        }
    }

    if (weight == INT_MAX) {
        cout << "No valid movement found, staying in place." << endl;
        return cur;
    }

    cout << "Go: " << direction << endl;
    return {row, col};
}


bool ModifiedFloodFill(){

    while(cur.first!=dst.first || cur.second!=dst.second){
        printCeller();
        if(!LidarInput()){
            cout<<"Error Occured While using the Lidar";
        }
        cout<<"generating manhanten distance\n";
        GenerateManhattenDistance();
        
        pair<int,int> next=pickMinimumNeighbour();
        
        cur=next;
    }
    printCeller();
    cout<<"Arrived at Destination :) "<<endl;
}

int main(){
    for(int i=0;i<M;i++){
        vector<cell>toPush(N,cell(0,{0,0,0,0}));
        celler.push_back(toPush);
    }
    printCeller();

    ModifiedFloodFill();
    return 0;
}