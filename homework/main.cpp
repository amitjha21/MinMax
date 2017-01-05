#include "homework.h"
#define INF std::numeric_limits<int>::max()
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y
using namespace std;
bool checkArrBound(int, int);
cellSt** copyArr(cellSt **src, cellSt **dest);
int checkScore(cellSt **a);
int MaxValue(cellSt **arr,int d);
int MinValue(cellSt **arr,int d);
int MinValueAB(cellSt **t,int d,int alpha,int beta);
int MinValueAB(cellSt **t,int d,int alpha,int beta);


void freeArray(cellSt **ptr)
{
//cout<<"\nfreeing "<<ptr;
for(int i = 0; i < sizeN; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}

void outputFile(cellSt **outputArr, string moveMade, IdxValues idv)
{
//    int ret=0;
    ofstream outfile;
    outfile.open("output.txt");

    if(outfile.is_open())
    {
        outfile << idv.col<<idv.row<<' '<<moveMade;
        outfile<<endl;
        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                outfile <<outputArr[i][j].occupiedBy;

            }
            outfile << endl;
        }
        outfile.close();
  //      ret = 1;
    }

    else
    {
    //    ret = 0;
        cout << "Unable to open file";
    }
    //freeArray(outputArr);
//    return ret;
}

cellSt** newArray()
{
    cellSt **tArr = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    for (int i=0; i<sizeN; i++)
        tArr[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));
  //cout<< "\ntempArr " <<tArr<<" | Size "<<sizeof(tArr)*sizeN<<endl;
    return tArr;
}

//new Check Raid
cellSt** checkRaidForBlank(cellSt **currArr, cellSt **tempRaid,int i,int j,char my,char op)
{
    int k1,k2,l=1;
//    ValueSt maxRaid;

    cellSt **currArrNew = newArray();
    cellSt **tempRaidNew = newArray();
    cellSt **tempRaidToRet = newArray();
    copyArr(currArr,currArrNew);
    copyArr(tempRaid,tempRaidNew);
    copyArr(tempRaidNew,tempRaidToRet);

    raidPossible = 'N';
    while(l<5)
    {
        tempRaidNew = copyArr(currArrNew,tempRaidNew);
        switch (l)
        {
        case 1:
            k1 = i;
            k2 = j-1;
            break;
        case 2:
            k1 = i;
            k2 = j+1;
            break;
        case 3:
            k1 = i-1;
            k2 = j;
            break;
        case 4:
            k1 = i+1;
            k2 = j;
            break;
        }
        ++l;
        if(checkArrBound(k1,k2) && currArrNew[k1][k2].occupiedBy == my)
        {
            if(checkArrBound(i,j-1) && (currArrNew[i][j-1].occupiedBy == op))
            {
                tempRaidNew[i][j].occupiedBy = my;
                tempRaidNew[i][j-1].occupiedBy = my;
                raidPossible = 'Y';
            }

            if(checkArrBound(i,j+1) && (currArrNew[i][j+1].occupiedBy == op))
            {
                tempRaidNew[i][j].occupiedBy = my;
                tempRaidNew[i][j+1].occupiedBy = my;
                raidPossible = 'Y';
            }
            if(checkArrBound(i-1,j) && (currArrNew[i-1][j].occupiedBy == op))
            {
                tempRaidNew[i][j].occupiedBy = my;
                tempRaidNew[i-1][j].occupiedBy = my;
                raidPossible = 'Y';
            }
            if(checkArrBound(i+1,j) && (currArrNew[i+1][j].occupiedBy == op))
            {
                tempRaidNew[i][j].occupiedBy = my;
                tempRaidNew[i+1][j].occupiedBy = my;
                raidPossible = 'Y';
            }

            if(raidPossible == 'Y')
            {
                copyArr(tempRaidNew,tempRaidToRet);
                freeArray(tempRaidNew);
                freeArray(currArrNew);
                return tempRaidToRet;
            }
        }
    }
     freeArray(tempRaidNew);
     freeArray(currArrNew);
    return tempRaidToRet;
}


int checkScore(cellSt **array1)
{
    char currOccupiedBy;
    int currCellScore;
    int youScore = 0,total_cell_X =0, total_cell_O=0;
    for(int i=0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            currOccupiedBy = array1[i][j].occupiedBy;
            currCellScore = array1[i][j].cellValue;
            if(currOccupiedBy==c_x)
            {
                total_cell_X = total_cell_X + currCellScore;
            }
            else if(currOccupiedBy==c_o)
                total_cell_O = total_cell_O + currCellScore;
            else {}
        }
    }
    if(youPlay == c_x)
        youScore = total_cell_X - total_cell_O;
    else
        youScore = total_cell_O - total_cell_X;

   // delete [] array1;
    return youScore;
}

bool noMoreCell(cellSt **arrState)
{
    bool noMoreEmptyCell = true;
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            if(arrState[i][j].occupiedBy == c_bl)
                return false;
        }
    }
    return noMoreEmptyCell;
}

cellSt** copyArr(cellSt **src, cellSt **dest)
{
    for(int i = 0; i<sizeN; ++i)
    {
        for(int j = 0; j<sizeN; ++j)
        {
            dest[i][j].cellValue = src[i][j].cellValue;
            dest[i][j].occupiedBy = src[i][j].occupiedBy;
        }
    }
    return dest;
}

int minimax(cellSt **arr)                                       //call MinMax Algo
{
    char occBy;
    int depth = 0,v=-INF;
    for(int i =0; i<sizeN; ++i)
        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                depth = DEPTH;
                occBy = arr[i][j].occupiedBy;
                if(occBy == c_bl)
                {
                    arr[i][j].occupiedBy = youPlay;
                    rowSol = i;
                    colSol = j;
                    v = MAX(v,MinValue(arr,--depth));

                }
            }
        }
    return v;
}

int MaxValue(cellSt **arrState, int depth)          //MaxValue
{
    char occBy;
    int v = -INF;
    //cout<<"MaxV";
    //cellSt **tempArrayNew = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
   //     tempArrayNew[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));
      cellSt **tempArrayNew = newArray();
      cellSt **tempRaid = newArray();
    tempArrayNew = copyArr(arrState,tempArrayNew);

   // cellSt **tempRaid = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
     //   tempRaid[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    if(depth<1 || noMoreCell(arrState))
    {
        return checkScore(tempArrayNew);
    }

    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)
            {
                tempArrayNew[i][j].occupiedBy = youPlay;
                int temp1 = MinValue(tempArrayNew,depth-1);
                v = MAX(v,temp1);
      //           cout<<endl<<"MinVal: "<<temp1<<"  VStakMax: "<<v<< "  "<<char(j+65)<<i+1;
                tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
    //raid
    //tempArrayNew = copyArr(arrState,tempArrayNew);
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)       //Own piece
            {
                tempRaid = copyArr(tempArrayNew,tempRaid);

                 cellSt **tempArrFor = newArray();
                tempArrFor =  copyArr(tempArrayNew,tempArrFor);
                tempArrayNew =  checkRaidForBlank(tempRaid,tempRaid,i,j,youPlay,oppPlay);
                if(raidPossible =='Y')
                {
                    int temp2 = MinValue(tempArrayNew,depth-1);
                    //v = MAX(v,temp2);
                    if(temp2>v)
                    v = temp2;
     //               cout<<endl<<"MinValR: "<<temp2<<"  VRaidMax: "<<v<< "  "<<char(j+65)<<i+1;
                }
                tempArrayNew = copyArr(tempArrFor,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
  //  delete [] tempArrayNew;
  //  delete [] tempRaid;
   //cout<<"\nFreedMax "<<tempArrayNew<<" "<<tempRaid<<endl;
  freeArray(tempArrayNew);
    freeArray(tempRaid);
    return v;
}

int MinValue(cellSt **arrState, int depth)            //MinValue
{
    char occBy;
    int v = INF;
    //cellSt **tempArrayNew = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
    //    tempArrayNew[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    cellSt **tempArrayNew = newArray();
    tempArrayNew = copyArr(arrState,tempArrayNew);

    cellSt **tempRaid = newArray(); //(cellSt **)malloc(sizeN * sizeof(cellSt *));
    for (int i=0; i<sizeN; i++)
        tempRaid[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    if(depth<1 || noMoreCell(tempArrayNew))
    {
        return checkScore(tempArrayNew);
    }
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)
            {
                tempArrayNew[i][j].occupiedBy = oppPlay;
                int m = MaxValue(tempArrayNew,depth-1);
                v = MIN(v,m);
      //   cout<<endl<<"MaxVal: "<<m<<"  VStakMin: "<<v<< "  "<<char(j+65)<<i+1<<"  depth: "<<depth;
                //tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
                 tempArrayNew[i][j].occupiedBy = c_bl;
            }
        }
    }

//raid
    tempArrayNew = copyArr(arrState,tempArrayNew);
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            //if(occBy == oppPlay)       //Own piece
            if(occBy == c_bl)
            {
                tempRaid = copyArr(tempArrayNew,tempRaid);

                //ValueSt minRaid = checkRaid(tempRaid,tempRaid,i,j,oppPlay,youPlay,'I');
                cellSt **tempArrFor = newArray();
                tempArrFor =  copyArr(tempArrayNew,tempArrFor);
                tempArrayNew = checkRaidForBlank(tempRaid,tempRaid,i,j,oppPlay,youPlay);

                if(raidPossible == 'Y')
                {
                    int m = MaxValue(tempArrayNew,depth-1);
                    //v = MIN(v,m);
                    if(v>m)
                    v = m;
           //        cout<<endl<<"MaxValueR "<<m<<"  VRaidMin: "<<v<< "  "<<char(j+65)<<i+1<<"  depth: "<<depth;
                }

                tempArrayNew = copyArr(tempArrFor,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
   // delete [] tempArrayNew;
   // delete [] tempRaid;
   // cout<<"\nFreedMin "<<tempArrayNew<<" "<<tempRaid<<endl;
    freeArray(tempArrayNew);
    freeArray(tempRaid);
    return v;
}

//Alphabeta
int MaxValueAB(cellSt **arrState, int depth,int alpha, int beta)          //MaxValue
{
    char occBy;
//    int v = -INF;
    //cout<<"MaxV";
    //cellSt **tempArrayNew = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
     //   tempArrayNew[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    cellSt **tempArrayNew = newArray();
    tempArrayNew = copyArr(arrState,tempArrayNew);
    cellSt **tempRaid = newArray();
    //cellSt **tempRaid = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
     //   tempRaid[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    if(depth<1 || noMoreCell(arrState))
    {
        return checkScore(tempArrayNew);
    }

    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)
            {
                tempArrayNew[i][j].occupiedBy = youPlay;
                int temp1 = MinValueAB(tempArrayNew,depth-1,alpha,beta);
                alpha = MAX(alpha,temp1);
                if(beta <= alpha)
                    {
                   //  freeArray(tempArrayNew);
                   // freeArray(tempRaid);
                    return beta;
                    }
                tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
    //raid
    tempArrayNew = copyArr(arrState,tempArrayNew);
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)       //Own piece
            {
                tempRaid = copyArr(tempArrayNew,tempRaid);

                //    ValueSt maxRaid1 = checkRaid(tempRaid,tempRaid,i,j,youPlay,oppPlay,'X');
                tempArrayNew =  checkRaidForBlank(tempRaid,tempRaid,i,j,youPlay,oppPlay);
                if(raidPossible =='Y')
                {
                    int temp2 = MinValueAB(tempArrayNew,depth-1,alpha,beta);
                    alpha = MAX(alpha,temp2);
                }
                if(beta <= alpha)
                    {
                     freeArray(tempArrayNew);
                    freeArray(tempRaid);
                    return beta;
                    }

                tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
    freeArray(tempArrayNew);
    freeArray(tempRaid);
    return alpha;
}

int MinValueAB(cellSt **arrState, int depth, int alpha, int beta)            //MinValue
{
    char occBy;
//    int v = INF;
    //cellSt **tempArrayNew = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
    //    tempArrayNew[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));
    cellSt **tempArrayNew = newArray();
    tempArrayNew = copyArr(arrState,tempArrayNew);
    cellSt **tempRaid = newArray();
    //cellSt **tempRaid = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    //for (int i=0; i<sizeN; i++)
     //   tempRaid[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    if(depth<1 || noMoreCell(tempArrayNew))
    {
        return checkScore(tempArrayNew);
    }
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            if(occBy == c_bl)
            {
                tempArrayNew[i][j].occupiedBy = oppPlay;
                int m = MaxValueAB(tempArrayNew,depth-1,alpha,beta);
                beta = MIN(beta,m);
                 if(beta <= alpha)
                {
                  //   freeArray(tempArrayNew);
                  //  freeArray(tempRaid);
                    return alpha;
                }
                tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }

//raid
    tempArrayNew = copyArr(arrState,tempArrayNew);
    for(int i =0; i<sizeN; ++i)
    {
        for(int j=0; j<sizeN; ++j)
        {
            occBy = tempArrayNew[i][j].occupiedBy;
            //if(occBy == oppPlay)       //Own piece
            if(occBy == c_bl)
            {
                tempRaid = copyArr(tempArrayNew,tempRaid);
                tempArrayNew = checkRaidForBlank(tempRaid,tempRaid,i,j,oppPlay,youPlay);
                if(raidPossible == 'Y')
                {
                    int m = MaxValueAB(tempArrayNew,depth-1,alpha,beta);
                    beta = MIN(beta,m);
                }
                if(beta <= alpha)
                {
                     freeArray(tempArrayNew);
                    freeArray(tempRaid);
                    return alpha;
                }
                tempArrayNew = copyArr(arrState,tempArrayNew);   //After one iterarion we nee to check for more
            }
        }
    }
//    delete [] tempArrayNew;
 //   delete [] tempRaid;
    // cout<<"\nFreed"<<tempArrayNew<<" "<<tempRaid;
    freeArray(tempArrayNew);
    freeArray(tempRaid);

    return beta;
}


bool checkArrBound(int i, int j)
{
    if(i>-1 && j>-1 && i<sizeN && j<sizeN)
        return true;

    return false;
}



int maxVal(ValueSt *a,int sizeToSearch)
{
    int maxV = a[0].score,idx=0;
    //int s = sizeN * sizeN;
    cout<<"\nValue Arr:\n";
    cout<<" "<<a[0].score<<" "<<a[0].row<<" "<<a[0].col<<"  "<<a[0].movev<<endl;
    for(int i= 1; i<=sizeToSearch; ++i)
    {
        cout<<" "<<a[i].score<<" "<<a[i].row<<" "<<a[i].col<<"  "<<a[0].movev<<endl;
        if(maxV<a[i].score)
        {
            maxV = a[i].score;
            idx = i;
        }
    }
    cout<<endl;
    return idx;
}


int minValFun(ValueSt *a,int sizeToSearch)
{
    int minV = a[0].score,idx=0;
    //int s = sizeN * sizeN;
    cout<<"\nValue Arr:\n";
    cout<<" "<<a[0].score<<" "<<a[0].row<<" "<<a[0].col<<"  "<<a[0].movev<<endl;
    for(int i= 1; i<=sizeToSearch; ++i)
    {
        cout<<" "<<a[i].score<<" "<<a[i].row<<" "<<a[i].col<<"  "<<a[0].movev<<endl;
        if(minV>a[i].score)
        {
            minV = a[i].score;
            idx = i;
        }
    }
    cout<<endl;
    return idx;
}

//index convertoer

IdxValues idxConv(int row, int col)
{
    IdxValues ret;
    ret.col = (int)col + 65;
    ret.row = row + 1;
    return ret;
}

int main()
{
    string data = "";
    char *datat,*tempCellVal;

    ifstream infile;
    infile.open("input.txt");
    moveVal = ' ';
    moveFinal = " ";

    if(infile.is_open())
    {
        // cout << "Reading from the file" << endl;
        if(getline(infile, data))
            sizeN = atoi (data.c_str());
        infile.close();
    }


    cellSt **mainArray = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    for (int i=0; i<sizeN; i++)
        mainArray[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));

    cellSt **tempArray = (cellSt **)malloc(sizeN * sizeof(cellSt *));
    for (int i=0; i<sizeN; i++)
        tempArray[i] = (cellSt *)malloc(sizeN * sizeof(cellSt));


    infile.open("input.txt");
    if(infile.is_open())
    {
        while(getline(infile, data))
        {
            //cout << data << endl;

            ++fileLineCount;

            if(fileLineCount == 1)
            {

            }
            else if(fileLineCount == 2)
            {
                MODE = data;

            }
            else if(fileLineCount == 3)
            {
                youPlay = (char)data[0];
                oppPlay = youPlay == c_x? c_o:c_x;
            }
            else if(fileLineCount == 4)
                DEPTH = atoi (data.c_str());
            else if(fileLineCount <= 4+sizeN)
            {

                datat = (char*)data.c_str();
                tempCellVal = strtok (datat," ");

                colCount = -1;
                ++rowCount;
                while (tempCellVal != NULL)
                {
                    ++colCount;
                    cellVal = atoi (tempCellVal);
                    //mainMatrix(rowCount,colCount).cellValue = cellVal;
                    mainArray[rowCount][colCount].cellValue = cellVal;
                    tempCellVal = strtok (NULL," ");
                }
            }
            else
            {
                datat = (char*)data.c_str();
                //tempCellVal = strtok (datat," ");
                //colCount = -1;
                ++rowCountState;
                for(int j = 0; j<sizeN; ++j)
                {
                    //string temp = (char*)datat[j];
                    //mainMatrix(rowCountState,j).occupiedBy = datat[j];
//                    cout<< temp<<endl;
                    if((char)data[j]==c_x || (char)data[j]==c_o || (char)data[j]==c_bl)
                        mainArray[rowCountState][j].occupiedBy = (char)data[j];
                }
            }

            data = "";
        }
        infile.close();
    }


    tempArray = copyArr(mainArray,tempArray);
    /*
    for( int i= 0; i< sizeN; ++i)
    {
        for(int j = 0; j<sizeN; ++j)
            cout << " " << mainArray[i][j].cellValue<<'('<< mainArray[i][j].occupiedBy<<')';
        cout << endl;
    }
    */

//tempArray = mainArray;

    // std::copy(&mainArray[0][0], &mainArray[0][0]+sizeN*sizeN,&tempArray[0][0]);


//cout<< minimax(mainArray) << endl<<rowSol<<" "<<colSol<<endl;
//*-----------------
    if(MODE == c_mm)
    {
        char occBy;
        int depth = 0,outputRet,maxValSoFar=-INF;

        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                depth = DEPTH;
                moveVal = ' ';
                mainArray = copyArr(tempArray,mainArray);
                occBy = mainArray[i][j].occupiedBy;
                if(occBy == c_bl)
                {
                    mainArray[i][j].occupiedBy = youPlay;
                    outputRet = MinValue(mainArray,depth - 1);
  //                  cout<<endl<<"=====>OutRet(s)= "<<outputRet<<"  "<<idxConv(i,j).col<<idxConv(i,j).row<<"  depth: "<<depth;
                    if(maxValSoFar<outputRet)
                    {

                        maxValSoFar = outputRet;
                        rowSol = i;
                        colSol = j;
                        moveSol = "Stake";

                    }
  //                   cout<<endl<<"=====>MaxSoFar(s)= "<<maxValSoFar<<"  outputRet(S)"<<outputRet<<"   "<<idxConv(i,j).col<<idxConv(i,j).row<<"  depth: "<<depth;
                    //valueArray[k].movev = moveVal;
                }
            }
        }

//*----------------
//Raid
       // mainArray = copyArr(tempArray,mainArray);
//int p =-1;
        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                depth = DEPTH;
                mainArray = copyArr(tempArray,mainArray);
                occBy = mainArray[i][j].occupiedBy;

                if(occBy == c_bl)
                {

                    mainArray = checkRaidForBlank(mainArray,mainArray,i,j,youPlay,oppPlay);

                    if(raidPossible == 'Y')
                    {
                        //mainArray[i][j].occupiedBy = youPlay;

                        outputRet = MinValue(mainArray,depth-1);
                        //cout<<endl<<"=====>OutRet(R)= "<<outputRet<<"  "<<idxConv(i,j).col<<idxConv(i,j).row<<"  depth: "<<depth;
                        if(outputRet>maxValSoFar)
                        {
                            maxValSoFar = outputRet;
                            rowSol = i;
                            colSol = j;
                            moveSol = "Raid";

                        }
   //                      cout<<endl<<"=====>MaxSoFar(R)= "<<maxValSoFar<<"  "<<"outputRet(R)"<<outputRet<<"   "<<idxConv(i,j).col<<idxConv(i,j).row<<"  depth: "<<depth;
                    }
                }
            }
        }
    }
    else if(MODE == c_ab)                   //AlphaBeta
    {
        char occBy;
        int depth = 0,outputRet,maxValSoFar=-INF;

        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                depth = DEPTH;
                moveVal = ' ';
                mainArray = copyArr(tempArray,mainArray);
                occBy = mainArray[i][j].occupiedBy;
                if(occBy == c_bl)
                {
                    mainArray[i][j].occupiedBy = youPlay;
                    outputRet = MinValueAB(mainArray,depth - 1,-INF,INF);
  //                  cout<<endl<<"OutRet(s)= "<<outputRet<<"  "<<idxConv(i,j).col<<idxConv(i,j).row;
                    if(maxValSoFar<outputRet)
                    {
                        maxValSoFar = outputRet;
                        rowSol = i;
                        colSol = j;
                        moveSol = "Stake";
                    }
                    //valueArray[k].movev = moveVal;
                }
            }
        }

//*----------------
//Raid
        mainArray = copyArr(tempArray,mainArray);

        for(int i =0; i<sizeN; ++i)
        {
            for(int j=0; j<sizeN; ++j)
            {
                depth = DEPTH;
                mainArray = copyArr(tempArray,mainArray);
                occBy = mainArray[i][j].occupiedBy;

                if(occBy == c_bl)
                {

                    mainArray = checkRaidForBlank(mainArray,mainArray,i,j,youPlay,oppPlay);

                    if(raidPossible == 'Y')
                    {
                        mainArray[i][j].occupiedBy = youPlay;
                        outputRet = MinValueAB(mainArray,depth-1,-INF,INF);
   //                     cout<<endl<<"OutRet(R)= "<<outputRet<<"  "<<idxConv(i,j).col<<idxConv(i,j).row;
                        if(outputRet>maxValSoFar)
                        {
                            maxValSoFar = outputRet;
                            rowSol = i;
                            colSol = j;
                            moveSol = "Raid";
                        }
                    }
                }
            }
        }

    }
//finalScore = maxValSoFar;

    tempArray[rowSol][colSol].occupiedBy = youPlay;
    IdxValues id = idxConv(rowSol,colSol);
    if(moveSol == "Raid")
    {
        if(checkArrBound(rowSol,colSol-1) && tempArray[rowSol][colSol-1].occupiedBy == oppPlay)
            tempArray[rowSol][colSol-1].occupiedBy = youPlay;
        if(checkArrBound(rowSol,colSol+1) && tempArray[rowSol][colSol+1].occupiedBy == oppPlay)
            tempArray[rowSol][colSol+1].occupiedBy = youPlay;
        if(checkArrBound(rowSol-1,colSol) && tempArray[rowSol-1][colSol].occupiedBy == oppPlay)
            tempArray[rowSol-1][colSol].occupiedBy = youPlay;
        if(checkArrBound(rowSol+1,colSol) && tempArray[rowSol+1][colSol].occupiedBy == oppPlay)
            tempArray[rowSol+1][colSol].occupiedBy = youPlay;
    }
   // cout<<endl<<"Final Score:- "<<finalScore<<endl<<"  Row:- "<<rowSol<<"   Col:- "<<colSol<<endl;
  // cout<<endl<<"  "<<id.col<<id.row<<" "<< moveSol;
  //  cout<<endl<<"\nSolution for "<<youPlay<<";   Depth: "<<DEPTH<<endl<<endl;
    /*
    for( int i= 0; i< sizeN; ++i)
    {
        for(int j = 0; j<sizeN; ++j){
            //cout << " " << tempArray[i][j].cellValue<<'('<< tempArray[i][j].occupiedBy<<')';
            cout << tempArray[i][j].occupiedBy;
            }
        cout << endl;
    }
    */
    outputFile(tempArray,moveSol,id);
    freeArray(mainArray);
    freeArray(tempArray);

    return 0;
}
