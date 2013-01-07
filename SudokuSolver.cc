#include<set>
#include<map>
#include<string>
#include<iostream>
using namespace std;

bool debug = false;

void printFinalOut(map<pair<int,int>,  int>& finalOut, int r1=-1, int c1=-1)
{
  cout<<"===";
  cout<<endl<<" -------------------------------------"<<endl;
  bool shouldBreak = false;
  for(int r=0; r<9 ; ++r){
    for(int c=0; c<9 ; ++c){
      cout<<" | "<<finalOut[make_pair(r,c)];
      if((r1!=-1) && (r==r1 && c==c1)){shouldBreak=true;break;}
    }
    cout<<" |\n -------------------------------------"<<endl;
    if(shouldBreak){break;}
  }  
}

class OneToNineHash
{
private:
  set<int> _data;
  
public:
  OneToNineHash(int n){
    if(n!=0){
      _data.insert(n);
    }
    else{
      for(int n=1; n<=9; ++n){
	_data.insert(n);
      }
    }
  }

  bool find(int n){
    return (_data.find(n)!=_data.end());
  }

  set<int>& getSet(){
    return _data;
  }
  
  void remove(int n){
    if((n>=1) && (n<=9)){
      //cout<<"deleting "<<n<<endl;
      _data.erase(n);
    }
  }

  int get(){
    int retVal = 0;
    if(size()==1){
      set<int>::iterator it = _data.begin();      
      retVal = (*it);
    }
    return retVal;
  }
  
  int size(){return _data.size();}
};

void printSudokuString(string& str){
  int count = 0;
  cout<<" -------------------------------------\n";
  for(int r=0; r<9 ; ++r){
    for(int c=0; c<9 ; ++c){
      char asd = str.at(count);
      cout<<" | "<<asd;
      ++count;
    }
    cout<<" |"<<endl;
    cout<<" -------------------------------------\n";
  }
}

void readString(string& str, map<pair<int,int>,  OneToNineHash*>& hash1)
{
  int count = 0;
  for(int r=0; r<9 ; ++r){
    for(int c=0; c<9 ; ++c){
      char asd = str.at(count);
      hash1[make_pair(r,c)] = new OneToNineHash((asd==' ')? 0 : atoi(&asd));
      ++count;
    }
  }
}

bool canNumberBeAsigned(map<pair<int,int>,  int>& finalOut, int r, int c, int num)
{
  bool retVal = true;
  for(int i=0;i<r;++i){if(finalOut[make_pair(i,c)]==num){retVal=false;break;}}
  if(!retVal){return retVal;}
  for(int i=0;i<c;++i){if(finalOut[make_pair(r,i)]==num){retVal=false;break;}}
  if(!retVal){return retVal;}

  int startRow = -1;
  int startCol = -1;
  if((r>=0 && r<=2) && (c>=0 && c<=2)){startRow=0;startCol=0;}
  if((r>=0 && r<=2) && (c>=3 && c<=5)){startRow=0;startCol=3;}
  if((r>=0 && r<=2) && (c>=6 && c<=8)){startRow=0;startCol=6;}
  if((r>=3 && r<=5) && (c>=0 && c<=2)){startRow=3;startCol=0;}
  if((r>=3 && r<=5) && (c>=3 && c<=5)){startRow=3;startCol=3;}
  if((r>=3 && r<=5) && (c>=6 && c<=8)){startRow=3;startCol=6;}
  if((r>=6 && r<=8) && (c>=0 && c<=2)){startRow=6;startCol=0;}
  if((r>=6 && r<=8) && (c>=3 && c<=5)){startRow=6;startCol=3;}
  if((r>=6 && r<=8) && (c>=6 && c<=8)){startRow=6;startCol=6;}
  
  for(int r2=startRow; r2<startRow+3 ; ++r2){
    for(int c2=startCol; c2<startCol+3 ; ++c2){
      if(r2<r && c2<c){if(finalOut[make_pair(r2,c2)]==num){retVal=false;break;}}
    }
    if(!retVal){break;}
  }
  
  return retVal;
}

bool isValidSudoku(map<pair<int,int>,  int>& finalOut)
{
  bool isValidOuter = true;
  for(int r=0; r<9 ; ++r){
    for(int c=0; c<9 ; ++c){
      int a = finalOut[make_pair(r,c)];
      bool isValid = true;
      for(int i=0; i<9 ; ++i){if(i!=r){if(finalOut[make_pair(i,c)]==a){isValid=false;break;}}}
      if(isValid==false){isValidOuter=false;break;}
      for(int i=0; i<9 ; ++i){if(i!=c){if(finalOut[make_pair(r,i)]==a){isValid=false;break;}}}
      if(isValid==false){isValidOuter=false;break;}

      int startRow = -1;
      int startCol = -1;
      if((r>=0 && r<=2) && (c>=0 && c<=2)){startRow=0;startCol=0;}
      if((r>=0 && r<=2) && (c>=3 && c<=5)){startRow=0;startCol=3;}
      if((r>=0 && r<=2) && (c>=6 && c<=8)){startRow=0;startCol=6;}

      if((r>=3 && r<=5) && (c>=0 && c<=2)){startRow=3;startCol=0;}
      if((r>=3 && r<=5) && (c>=3 && c<=5)){startRow=3;startCol=3;}
      if((r>=3 && r<=5) && (c>=6 && c<=8)){startRow=3;startCol=6;}

      if((r>=6 && r<=8) && (c>=0 && c<=2)){startRow=6;startCol=0;}
      if((r>=6 && r<=8) && (c>=3 && c<=5)){startRow=6;startCol=3;}
      if((r>=6 && r<=8) && (c>=6 && c<=8)){startRow=6;startCol=6;}

      for(int r1=startRow; r1<startRow+3 ; ++r1){
	for(int c1=startCol; c1<startCol+3 ; ++c1){
	  if(!(r1==r && c1==c)){
	    if(finalOut[make_pair(r1,c1)]==a){isValid=false;break;}
	  }
	}
	if(isValid==false){isValidOuter=false;break;}
      }
      if(isValid==false){isValidOuter=false;break;}
    }
    if(isValidOuter==false){break;}
  }
  return isValidOuter;
}

void permuteHash(map<pair<int,int>,  OneToNineHash*>& hash1, map<pair<int,int>,  int>& finalOut, int r, int c)
{
  if(r<9 && c<9){
    //printFinalOut(finalOut, r, c);
    //cout<<"r:"<<r<<" c:"<<c<<endl;
    for(set<int>::iterator it = hash1[make_pair(r,c)]->getSet().begin(); it != hash1[make_pair(r,c)]->getSet().end(); ++it){
      if(canNumberBeAsigned(finalOut, r, c, *it)){
	finalOut[make_pair(r,c)] = *it;
	if(r==8 & c==8){
	  //check if finalOut is valid sudoku & print if it is
	  if(isValidSudoku(finalOut)){
	    printFinalOut(finalOut);
	    //exit(0);
	  }
	}
	else{
	  if(c+1 < 9){
	    permuteHash(hash1, finalOut, r, c+1);
	  }
	  else{
	    permuteHash(hash1, finalOut, r+1, 0);
	  }
	}
      }
    }
  }
}


int main()
{
  string a = "39   2  6 5  86   2       3 3 7       1 6 8       1 9 4       7   43  5 8  6   32";
  //a = "1   7  3 83 6       29  6 86    49 7 9     5 3 75    42 3  91       2 43 4  8   9";
	 //a = "49    761  2 6 458  6   923  3246   7 4  12         345    8    1 6   42   7  1  ";
	 a = "8          36      7  9 2   5   7       457     1   3   1    68  85   1  9    4  ";
  printSudokuString(a);  
  map<pair<int,int>,  OneToNineHash*> hash1;

  readString(a, hash1);

  int prevHowManySolved = 0;
  while(true){
    int howManySolved = 0;
    map<int, int> aaa;
    for(int i=0;i<=9;++i){aaa[i] =0;}
    for(int r=0; r<9 ; ++r){
      for(int c=0; c<9 ; ++c){
	aaa[hash1[make_pair(r,c)]->size()] = aaa[hash1[make_pair(r,c)]->size()] + 1;
	if(hash1[make_pair(r,c)]->get() != 0){++howManySolved;}
      }
    }
    //for(int i=0;i<=9;++i){cout<<"aaa["<<i<<"] = "<<aaa[i]<<endl;}

    if(prevHowManySolved == howManySolved){break;}
    prevHowManySolved = howManySolved;

    for(int r=0; r<9 ; ++r){
      for(int c=0; c<9 ; ++c){
	int locVar = hash1[make_pair(r,c)]->get();
	if(locVar != 0){
	  for(int i1=0;i1<9;++i1){
	    if(i1!=r){
              if(hash1[make_pair(i1,c)]->find(locVar)){
		if(debug){cout<<"hash1[make_pair("<<i1<<","<<c<<")]->remove("<<locVar<<")\n";}
		hash1[make_pair(i1,c)]->remove(locVar);
	      }
	    }
	  }
	  for(int i1=0;i1<9;++i1){
	    if(i1!=c){
              if(hash1[make_pair(r,i1)]->find(locVar)){
		if(debug){cout<<"hash1[make_pair("<<r<<","<<i1<<")]->remove("<<locVar<<")\n";}
		hash1[make_pair(r,i1)]->remove(locVar);
	      }
	    }
	  }

	  //find out which square, and remove from that square
	  int locIdx = -1;
	  switch(r){
	  case 0:case 1:case 2:
	    switch(c){
	    case 0:case 1:case 2:
	      locIdx = 0;
	      break;
	    case 3:case 4:case 5:
	      locIdx = 1;
	      break;
	    case 6:case 7:case 8:
	      locIdx = 2;
	      break;
	    }
	    break;
	    ////////////////////
	  case 3:case 4:case 5:
	    switch(c){
	    case 0:case 1:case 2:
	      locIdx = 3;
	      break;
	    case 3:case 4:case 5:
	      locIdx = 4;
	      break;
	    case 6:case 7:case 8:
	      locIdx = 5;
	      break;
	    }
	    break;
	    /////////////
	  case 6:case 7:case 8:
	    switch(c){
	    case 0:case 1:case 2:
	      locIdx = 6;
	      break;
	    case 3:case 4: case 5:
	      locIdx = 7;
	      break;
	    case 6:case 7:case 8:
	      locIdx = 8;
	      break;
	    }
	    break;
	  }

	  int startRow = -1;
	  int startCol = -1;
	  if(locIdx==0){startRow=0;startCol=0;}
	  if(locIdx==1){startRow=0;startCol=3;}
	  if(locIdx==2){startRow=0;startCol=6;}
	  if(locIdx==3){startRow=3;startCol=0;}
	  if(locIdx==4){startRow=3;startCol=3;}
	  if(locIdx==5){startRow=3;startCol=6;}
	  if(locIdx==6){startRow=6;startCol=0;}
	  if(locIdx==7){startRow=6;startCol=3;}
	  if(locIdx==8){startRow=6;startCol=6;}
	  for(int r1=startRow; r1<startRow+3 ; ++r1){
	    for(int c1=startCol; c1<startCol+3 ; ++c1){
	      if(!(r1==r && c1==c)){
		if(hash1[make_pair(r1,c1)]->find(locVar)){
		  if(debug){cout<<"hash1[make_pair("<<r1<<","<<c1<<")]->remove("<<locVar<<")\n";}
		  hash1[make_pair(r1,c1)]->remove(locVar);
		}
	      }
	    }
	  }
	  if(debug){cout<<"===\n";}
	}
      }
    }
  }

  map<pair<int,int>,  int> finalOut;
  permuteHash(hash1, finalOut, 0, 0);
  
  for(int r=0; r<9 ; ++r){
    for(int c=0; c<9 ; ++c){
      delete hash1[make_pair(r,c)];
    }
  }
  return 0;
}
