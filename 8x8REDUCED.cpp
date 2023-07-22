#include <bits/stdc++.h>
using namespace std;
//TOP BOTTOM RIGHT LEFT
#define ROW 8
#define COL 8

  struct node{
     int row,col;
     int wall[4]={true,true,true,true};
     bool nev=false;
  };
  vector<pair<int,int>> trips;
  node celler[ROW][COL];
  node retEarn[ROW][COL];
  pair<int,int>cur={7,0};
  String headc="headtop";

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

  void wallSaver(pair<int,int>temp,bool a[3]){ //LHR
  Serial.print(headc);
  Serial.println("    orientation bolte!");
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
          continue;
        }
  Serial.print(cell[i][j]);Serial.print(' ');
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

void printAns(pair<int,int>start){
    vector<vector<bool>>a(ROW,vector<bool>(ROW,false));
    for(int i=trips.size()-1;i>=0;i--){
        cout<<trips[i].first<<" "<<trips[i].second<<endl;
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
                cout<<ut<<" ";
  Serial.print(ut);Serial.print(" ");
            }Serial.println(' ');
        }
        Serial.println(' ');
    }    
    
}

void queken(queue<pair<int,int>>&q,pair<int,int>pr){
  vector<pair<int,pair<int,int>>>vr;

  if(celler[pr.first][pr.second].wall[0]){ //celler se test krre
    vr.push_back({cell[pr.first-1][pr.second],{pr.first-1,pr.second}});
  }
  if(celler[pr.first][pr.second].wall[1]){
    vr.push_back({cell[pr.first+1][pr.second],{pr.first+1,pr.second}});
  }
  if(celler[pr.first][pr.second].wall[2]){
    vr.push_back({cell[pr.first][pr.second+1],{pr.first,pr.second+1}});
  }
  if(celler[pr.first][pr.second].wall[3]){
    vr.push_back({cell[pr.first][pr.second-1],{pr.first,pr.second-1}});
  }
  int minValue=INT_MAX;
  for(auto it: vr){
        minValue=min(it.first,minValue);
  }
    if(minValue!=INT_MAX && cell[pr.first][pr.second]<=minValue){
      cell[pr.first][pr.second]=minValue+1;
      for(auto it: vr){
        q.push({it.second.first,it.second.second});
      }
    }
}

bool qNeeded(pair<int,int>pr){
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
    return false;
  }
  int firstElement = v[0];
  for (int i = 1; i < v.size(); i++) {
      if (v[i] != firstElement) {
          cout<<" false fekt aahe ithe -> ~q Need\n";
          return false;
      }
  }  
  return true;
}

int bringTheval(int val){
   vector<int>v;
    if(celler[cur.first][cur.second].wall[0]){
        v.push_back(cell[cur.first-1][cur.second]);
    }
    if(celler[cur.first][cur.second].wall[1]){
        v.push_back(cell[cur.first+1][cur.second]);
    }
    if(celler[cur.first][cur.second].wall[2]){
        v.push_back(cell[cur.first][cur.second+1]);
    }
    if(celler[cur.first][cur.second].wall[3]){
        v.push_back(cell[cur.first][cur.second-1]);
    }
    return *min_element(v.begin(),v.end());
}

void solve(){
  queue<pair<int,int>>q;
  q.push(cur);   
  
  bool a[4]={true,true,true,true};
  while(true){
  Serial.print(headc);Serial.print(" PrintKarnyaadhi");

        print(cur.first,cur.second);

        pair<int, int> next={cur.first,cur.second};
        int minVal = cell[cur.first][cur.second];
  Serial.print(" possible directions to go: ");
        //cin>>a[0]>>a[1]>>a[2]; //take input from ultrasonic sensor

        if (Serial.available() >= 7) { 
            for (int i = 0; i < 3; i++) {
              a[i] = Serial.parseInt();
              while (Serial.peek() == ' ' || Serial.peek() == ',' || Serial.peek() == '\t') {
                Serial.read();
              }
            } 
        }



        wallSaver(cur,a);

        if(qNeeded(cur)){
  Serial.println("q kde kam assign ->");
          while(!q.empty()){
            pair<int,int>temp=q.front();
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

        String dir="";
        if(celler[cur.first][cur.second].wall[0]){
            if(cell[cur.first][cur.second]>cell[cur.first-1][cur.second]){
            q.push({cur.first -1, cur.second});
                minVal=cell[cur.first-1][cur.second];
                next={cur.first-1,cur.second};
                dir="Top";
                headc="headtop";
            }
        }

        if (celler[cur.first][cur.second].wall[1]){ 
          if(cell[cur.first][cur.second]>cell[cur.first+1][cur.second]){
          q.push({cur.first +1, cur.second});
            minVal=cell[cur.first+1][cur.second];
            next={cur.first+1,cur.second};
            dir="Bottom";
            headc="headbottom";
          }
        }

        if(celler[cur.first][cur.second].wall[2])
        {
          if(cell[cur.first][cur.second]>cell[cur.first][cur.second+1]){
          q.push({cur.first, cur.second+1});
              minVal=cell[cur.first][cur.second+1];
              next={cur.first,cur.second+1};
              dir="Right";
              headc="headright";
          }
        }

        if (celler[cur.first][cur.second].wall[3]){ 
          if(cell[cur.first][cur.second]>cell[cur.first][cur.second-1]){
              q.push({cur.first, cur.second - 1}); //incase lahan value asel tarch
              minVal=cell[cur.first][cur.second-1];
              next={cur.first,cur.second-1};
              dir="Left";
              headc="headleft";
          }
        }

        if(retTrip[next.first][next.second].nev){
          retTrip[cur.first][cur.second].nev=false;
          trips.pop_back();
  Serial.println(" pop krhe elment yahape! ");
        }

        //Command Directions
        // cur=next;
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
          // retEarn[cur.first][cur.second].nev=true;
          trips.push_back({cur.first,cur.second});
        Serial.println("push krhe yahape ");
        }
        retTrip[cur.first][cur.second].nev=~retTrip[cur.first][cur.second].nev;

        if(cell[cur.first][cur.second]==0){
  Serial.print("input at dst: ");
          // cin>>a[0]>>a[1]>>a[2];

         
           if (Serial.available() >= 7) { 
            for (int i = 0; i < 3; i++) {
              a[i] = Serial.parseInt();
              while (Serial.peek() == ' ' || Serial.peek() == ',' || Serial.peek() == '\t') {
                Serial.read();
              }
            } 
          }

          wallSaver({cur.first,cur.second},a);
          printAns({cur.first,cur.second});
          break;
        }
        //ethically dedicate direction function should called 

  }
}

void retify()
{

  for(int i=0;i<ROW;i++){
      celler[0][i].wall[0]=false;
      celler[ROW-1][i].wall[1]=false;
      celler[i][ROW-1].wall[2]=false;
      celler[i][0].wall[3]=false;
  }
  retTrip[cur.first][cur.second].nev=true;
  trips.push_back({cur.first,cur.second});
  solve();
}
void setup(){
  Serial.begin(9600);
  Serial.print("sdsdsadas");
  // retify(); 
  // deay(20000);
}
bool once=true;
// void loop(){
//   Serial.println("something");
//   if(once==true){
//     once=false;
//   }
// }
