#include <iostream>
#include <vector>

extern "C"{
  #include <sylvan.h>
  #include <lace.h>
}
  #include<fstream>

using namespace std;
using namespace sylvan;
int cnfsize = 0;

bool decodeBoard(uint32_t *board, string FEN){
  int boardPos = 0;
  bool boardRead = false;
  for (int i = 0; i < FEN.size(); i++){
    if(isdigit(FEN[i])){
      int digit = FEN[i]-48;
      for(int j = 0; j<digit; j++){
        board[boardPos] = 0;
        boardPos += 1;
      }
    }
    else{
      switch(FEN[i]) {
          case 'k' : board[boardPos]=1;
                     boardPos += 1;
                   break;
          case 'q' : board[boardPos]=2;
                     boardPos += 1;
                   break;
          case 'r' : board[boardPos]=3;
                     boardPos += 1;
                   break;
          case 'b' : if(boardRead){
                        board[64] = 1;
                        return true;
                      }
                     board[boardPos]=4;
                     boardPos += 1;
                   break;
          case 'n' : board[boardPos]=5;
                     boardPos += 1;
                   break;
          case 'p' : board[boardPos]=6;
                     boardPos += 1;
                   break;
          case 'K' : board[boardPos]=7;
                     boardPos += 1;
                   break;
          case 'Q' : board[boardPos]=8;
                     boardPos += 1;
                   break;
          case 'R' : board[boardPos]=9;
                     boardPos += 1;
                   break;
          case 'B' : board[boardPos]=10;
                     boardPos += 1;
                   break;
          case 'N' : board[boardPos]=11;
                     boardPos += 1;
                   break;
          case 'P' : board[boardPos]=12;
                     boardPos += 1;
                   break;
          case '/' : break;
          case 'w' : board[64] = 0;
                   return true;
          case ' ' : boardRead = true;
      }
    }    
  }
  return true;
}


int main(int argc, const char *argv[]) {

    int n_workers = 1; // auto-detect
    lace_init(n_workers, 0);
    lace_startup(0, NULL, NULL);
    LACE_ME;

    // use at most 512 MB, nodes:cache ratio 2:1, initial size 1/32 of maximum
    sylvan_set_limits(512*1024*1024, 1, 5);
    sylvan_init_package();
    sylvan_init_mtbdd();
    /* ... do stuff ... */
    sylvan_gc_disable();

    //lddmc_protect()

    MDD db = lddmc_false;
    uint32_t b[65];
    uint32_t*board = b;
    string line;
    ifstream myfile("../newtestdata.txt");
    if (myfile.is_open()){
      while(getline(myfile, line)){
        decodeBoard(board, line);
        db = lddmc_union_cube(db, b, 65);
        for(int i = 0; i<65; i++){
          cout << board[i] << " ";
          board[i] = 0;
        }
        cout << endl;
        cout << "number of nodes " << lddmc_nodecount(db) << endl;
      }
      myfile.close();
    }
/*
    uint32_t b[65];

    b[0] = 0;
    b[1] = 1;
*/
    //lddmc_union_cube(db, b, 65);

    exit(0);  // (faster than "return", which will invoke the destructors)
    //delete cnf;
}
