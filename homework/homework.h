#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <memory>
#include <deque>
#include <algorithm>
#include <malloc.h>
#include <exception>
#include <fstream>
#include <ctime>


char const c_mm[] = "MINIMAX";
char const c_ab[] = "ALPHABETA";
char const c_comp[] = "COMPETITION";
char const c_x = 'X';
char const c_o = 'O';
char const c_bl = '.';

typedef struct cellSt
	{
		int cellValue;
		char occupiedBy;
	} cellSt;
typedef struct ValueSt
	{
		int score;
		int row;
		int col;
		char movev;
	} ValueSt;
	typedef struct IdxValues
	{
        int row;
        char col;
        std::string attack;
	}IdxValues;

int sizeN, DEPTH,rowCount =-1, colCount=-1,cellVal=-1, fileLineCount=0,rowCountState=-1;
int final_Score_YouPlay=0, final_Score_Opp=0;
int rowSol,colSol,finalScore;
std::string MODE,moveFinal,moveSol="Stake";
char youPlay,oppPlay,moveVal;
char raidPossible = 'N';




