#include <bits/stdc++.h>
#include<windows.h>
using namespace std;
//TOP BOTTOM RIGHT LEFT
#define ROW 8
#define COL 8

  struct node{
     int row,col;
     int wall[4]={true,true,true,true};
     bool nev=false;
  };
  struct Pair{
    int first,second;
    Pair(int a,int b){
      this->first=a;
      this->second=b;
    }
  };

  struct nesPair{
    int x,y,z;
    nesPair(int a,int b,int c){
      this->x=a;
      this->y=b;
      this->z=c;
    }
  };

  vector<Pair > trips;
  node celler[ROW][COL];
  node retEarn[ROW][COL];

  Pair cur(7,0);
  
  string headc="headtop";

  int cell[ROW][COL]={
    {6,5,4,3,3,4,5,6},
    {5,4,3,2,2,3,4,5},
    {4,3,2,1,1,2,3,5},
    {3,2,1,0,0,1,2,3},
    {3,2,1,0,0,1,2,3},
    {4,3,2,1,1,2,3,5},
    {5,4,3,2,2,3,4,5},
    {6,5,4,3,3,4,5,6},
  };

  node retTrip[ROW][COL];

  void wallSaver(Pair temp,bool a[3]){ //LHR
  Serial.println(" orientation bolte !\n");
    if(headc=="headtop"){
      celler[temp.first][temp.second].wall[0]=a[1]; //top
      celler[temp.first][temp.second].wall[2]=a[2]; //right
      celler[temp.first][temp.second].wall[3]=a[0]; //left
    }else if(headc=="headbottom"){
      celler[temp.first][temp.second].wall[1]=a[1]; //bott
      celler[temp.first][temp.second].wall[2]=a[0];  //right
      celler[temp.first][temp.second].wall[3]=a[2]; //left
    }else if(headc=="headright"){
      celler[temp.first][temp.second].wall[1]=a[2]; //bott
      celler[temp.first][temp.second].wall[2]=a[1]; //right
      celler[temp.first][temp.second].wall[0]=a[0]; //top
    }else {
       celler[temp.first][temp.second].wall[0]=a[2]; //top
      celler[temp.first][temp.second].wall[1]=a[0]; //bott
      celler[temp.first][temp.second].wall[3]=a[1]; //left
    }
  }

  void print(int a,int b){
    for(int i=0;i<ROW;i++){
      for(int j=0;j<COL;j++){
        if(i==a&&j==b){
          Serial.print(cell[i][j]);
          Serial.print('.');
          continue;
        }
        Serial.print(cell[i][j]);
        Serial.print(' ');
      }
      Serial.println(' ');
    }
  }

void moveTop(){
  cur.first--;
}
void moveDown(){
  cur.first++;
}
void moveLeft(){
  cur.second--;
}
void moveRight(){
  cur.second++;
}

void printAns(Pair start){
    vector<vector<bool>>a(ROW,vector<bool>(ROW,false));
    for(int i=trips.size()-1;i>=0;i--){
        if(trips[i].first==cur.first&&trips[i].second==cur.second){
            continue;
        }
        if(trips[i].first-1==cur.first){
            moveDown();
        }else if(trips[i].first+1==cur.first){
            moveTop();
        }else if(trips[i].second+1==cur.second){
            moveLeft();
        }else if(trips[i].second-1==cur.second){
            moveRight();
        }

        a[cur.first][cur.second]=true;
        for(auto it: a){
            for(auto ut: it){
            Serial.print(ut);
            Serial.print(' ');
            }
            Serial.println(' ');
        }
        Serial.println(' ');
    }    
}

void queken(queue<Pair >&q,Pair pr){
  vector<nesPair>vr;

  if(celler[pr.first][pr.second].wall[0]){
    vr.push_back(nesPair(cell[pr.first-1][pr.second],pr.first-1,pr.second));
  }
  if(celler[pr.first][pr.second].wall[1]){
    vr.push_back(nesPair(cell[pr.first+1][pr.second],pr.first+1,pr.second));
  }
  if(celler[pr.first][pr.second].wall[2]){
    vr.push_back(nesPair(cell[pr.first][pr.second+1],pr.first,pr.second+1));
  }
  if(celler[pr.first][pr.second].wall[3]){
    vr.push_back(nesPair(cell[pr.first][pr.second-1],pr.first,pr.second-1));
  }
  int minValue=INT_MAX;
  for(int i=0;i<vr.size();i++){
        minValue=(vr[i].x>minValue)?minValue:vr[i].x;
  }
    if(minValue!=INT_MAX && cell[pr.first][pr.second]<=minValue){
      cell[pr.first][pr.second]=minValue+1;
      for(int i=0;i<vr.size();i++){
        q.push({vr[i].y,vr[i].z});
      }
    }
}

bool qNeeded(Pair pr){
  vector<int>v;

if(celler[pr.first][pr.second].wall[0]){
    v.push_back(cell[pr.first-1][pr.second]);
}
if(celler[pr.first][pr.second].wall[1]){
    v.push_back(cell[pr.first+1][pr.second]);
}
if(celler[pr.first][pr.second].wall[2]){
    v.push_back(cell[pr.first][pr.second+1]);
}
if(celler[pr.first][pr.second].wall[3]){
    v.push_back(cell[pr.first][pr.second-1]);
}

  if(v.size()==1){
    Serial.println("q madhe single element aahe\n");
    return false;
  }
  int firstElement = v[0];
  for (int i = 1; i < v.size(); i++) {
      if (v[i] != firstElement) {
          Serial.print(" false fekt aahe ithe -> ~q Need\n");
          return false;
      }
  }  
  return true;
}

int bringTheval(int val){
  //  vector<int>v; 
   int miin=INT_MAX;
    if(celler[cur.first][cur.second].wall[0]){
        // v.push_back(cell[cur.first-1][cur.second]);
        miin=(cell[cur.first-1][cur.second]<miin)?cell[cur.first-1][cur.second]:miin;
    }
    if(celler[cur.first][cur.second].wall[1]){
        // v.push_back(cell[cur.first+1][cur.second]);
        miin=(cell[cur.first+1][cur.second]<miin)?cell[cur.first+1][cur.second]:miin;
    }
    if(celler[cur.first][cur.second].wall[2]){
        // v.push_back(cell[cur.first][cur.second+1]);
        miin=(cell[cur.first][cur.second+1])<miin?cell[cur.first][cur.second+1]:miin;
    }
    if(celler[cur.first][cur.second].wall[3]){
        // v.push_back(cell[cur.first][cur.second-1]);
        miin=(cell[cur.first][cur.second-1]<miin)?cell[cur.first][cur.second-1]:miin;
    }
    return miin;
}

void solve(){
  queue<Pair>q;
  q.push(cur);   
  
  bool a[4]={true,true,true,true};
  while(true){
        Serial.print(headc);
        Serial.println("                       Print karnyadhi !\n");
        
        print(cur.first,cur.second);

        Pair next=Pair(cur.first,cur.second);
        int minVal = cell[cur.first][cur.second];
        Serial.print("possible directions to go: ");
        // cin>>a[0]>>a[1]>>a[2]; //take input from ultrasonic sensor
        wallSaver(cur,a);

        if(qNeeded(cur)){
          while(!q.empty()){
            Pair temp=q.front();
            queken(q,temp);
            q.pop();
          }
        }
        // else{
        //   while(!q.empty())q.pop();
        // }

        if(bringTheval(cell[cur.first][cur.second]>=cell[cur.first][cur.second])){
          cell[cur.first][cur.second]=bringTheval(cell[cur.first][cur.second])+1;
        }

        string dir="";
        if(celler[cur.first][cur.second].wall[0]){
            if(cell[cur.first][cur.second]>cell[cur.first-1][cur.second]){
            q.push(Pair(cur.first -1, cur.second));
                minVal=cell[cur.first-1][cur.second];
                next=Pair(cur.first-1,cur.second);
                dir="Top";
                headc="headtop";
            }
        }

        if (celler[cur.first][cur.second].wall[1]){ 
          if(cell[cur.first][cur.second]>cell[cur.first+1][cur.second]){
          q.push(Pair(cur.first +1, cur.second));
            minVal=cell[cur.first+1][cur.second];
            next=Pair(cur.first+1,cur.second);
            dir="Bottom";
            headc="headbottom";
          }
        }

        if(celler[cur.first][cur.second].wall[2])
        {
          if(cell[cur.first][cur.second]>cell[cur.first][cur.second+1]){
          q.push(Pair(cur.first,cur.second+1));
              minVal=cell[cur.first][cur.second+1];
              next=Pair(cur.first,cur.second+1);
              dir="Right";
              headc="headright";
          }
        }

        if (celler[cur.first][cur.second].wall[3]){ 
          if(cell[cur.first][cur.second]>cell[cur.first][cur.second-1]){
              q.push(Pair(cur.first, cur.second - 1)); //incase lahan value asel tarch
              minVal=cell[cur.first][cur.second-1];
              next=Pair(cur.first,cur.second-1);
              dir="Left";
              headc="headleft";
          }
        }

        if(retTrip[next.first][next.second].nev){
          retTrip[cur.first][cur.second].nev=false;
          trips.pop_back();
        }

        //Command Directions
        if(dir=="Top"){
          moveTop();
          headc="headtop";
        }else if(dir=="Bottom"){
          moveDown();
          headc="headbottom";
        }else if(dir=="Right"){
          moveRight();
          headc="headright";
        }else {
          moveLeft();
          headc="headleft";
        }

        if(!retTrip[cur.first][cur.second].nev){
          trips.push_back({cur.first,cur.second});
        }
        retTrip[cur.first][cur.second].nev=~retTrip[cur.first][cur.second].nev;

        if(cell[cur.first][cur.second]==0){
          cin>>a[0]>>a[1]>>a[2];
          wallSaver({cur.first,cur.second},a);
          printAns({cur.first,cur.second});
          break;
        }
        //ethically dedicate direction function should called 
  }
}

int main()
{

  for(int i=0;i<ROW;i++){
      celler[0][i].wall[0]=false;
      celler[ROW-1][i].wall[1]=false;
      celler[i][ROW-1].wall[2]=false;
      celler[i][0].wall[3]=false;
  }
  retTrip[cur.first][cur.second].nev=true;
  trips.push_back(Pair(cur.first,cur.second));
  solve();
  return 0;
}
