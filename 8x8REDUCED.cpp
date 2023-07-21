#include<Vector.h>
using namespace std;
//TOP BOTTOM RIGHT LEFT
#define ROW 8
#define COL 8

  struct node{
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
  struct NEESPair{
    int x,y,z;
    NEESPair(int a,int b,int c){
      this->x=a;
      this->y=b;
      this->z=c;
    }
  };

struct queue {
    Pair* array[100];
    int frontIndex;    // It stores the index of an element which is present at the top of a queue.
    int rearIndex;     // It tells us the next position in the array where the element is to be inserted.
    int maxSize = 100; // It stores the total capacity of an array.
    int size=0;          // It stores the number of elements which are being present in the array.

    queue(int ss) {
        maxSize = ss;
        frontIndex = -1;
        rearIndex = 0;
        this->size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    Pair front() {
        if (frontIndex == -1) {
            return;
        }
        return *array[frontIndex];
    }

    void push(Pair elem) {
        if (size == maxSize) {
            return;
        }

        if (frontIndex == -1) {
            frontIndex = 0;
        }
        array[rearIndex] = new Pair(elem); // Create a new Pair object on the heap and store its pointer in the array
        rearIndex++;
        size++;
    }

    Pair pop() {
        if (frontIndex == -1) {
            // Return a default-initialized Pair if queue is empty
            return;
        }
        Pair temp = *array[frontIndex];
        delete array[frontIndex]; // Deallocate the memory allocated on the heap
        for (int i = 0; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        rearIndex--;
        size--;
        if (size == 0) {
            frontIndex = -1;
            rearIndex = 0;
        }
        return temp;
    }
};

  Vector<Pair> trips;
  node celler[ROW][COL];
  node retEarn[ROW][COL];

  Pair cur(7,0);
  
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
    // Vector<Vector<bool>>a(ROW,Vector<bool>(ROW,false));
    int a[ROW][ROW];
    for(int i=0;i<ROW;i++){
      for(int j=0;j<ROW;j++)a[i][j]=false;
    }
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
        // for(auto it: a){
        //     for(auto ut: it){
        //     Serial.print(ut);
        //     Serial.print(' ');
        //     }
        //     Serial.println(' ');
        // }
        // Serial.println(' ');
    }    
}

void queken(queue &q,Pair pr){
  Vector<NEESPair>vr;
  if(celler[pr.first][pr.second].wall[0]){
    vr.push_back(NEESPair(cell[pr.first-1][pr.second],pr.first-1,pr.second));
  }
  if(celler[pr.first][pr.second].wall[1]){
    vr.push_back(NEESPair(cell[pr.first+1][pr.second],pr.first+1,pr.second));
  }
  if(celler[pr.first][pr.second].wall[2]){
    vr.push_back(NEESPair(cell[pr.first][pr.second+1],pr.first,pr.second+1));
  }
  if(celler[pr.first][pr.second].wall[3]){
    vr.push_back(NEESPair(cell[pr.first][pr.second-1],pr.first,pr.second-1));
  }
  int minValue=INT8_MAX;
  for(int i=0;i<vr.size();i++){
        minValue=(vr[i].x>minValue)?minValue:vr[i].x;
  }
    if(minValue!=INT8_MAX && cell[pr.first][pr.second]<=minValue){
      cell[pr.first][pr.second]=minValue+1;
      for(int i=0;i<vr.size();i++){
        q.push(Pair(vr[i].y,vr[i].z));
      }
    }
}

bool qNeeded(Pair pr){
  Vector<int>v;

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
  //  Vector<int>v; 
   int miin=INT8_MAX;
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
  queue q(256);
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
          while(!q.isEmpty()){
            Pair temp=q.front();
            queken(q,temp);
            q.pop();
          }
        }
        // else{
        //   while(!q.isEmpty())q.pop();
        // }

        if(bringTheval(cell[cur.first][cur.second]>=cell[cur.first][cur.second])){
          cell[cur.first][cur.second]=bringTheval(cell[cur.first][cur.second])+1;
        }

        String dir="";
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
          // cin>>a[0]>>a[1]>>a[2];
          // wallSaver({cur.first,cur.second},a);
          // printAns({cur.first,cur.second});
          break;
        }
        //ethically dedicate direction function should called 
  }
}

int retify()
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
void setup(){
  retify();
}
void loop(){
  
}
