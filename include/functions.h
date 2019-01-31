#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

#ifndef DEEPDARKFANTASY_FUNCTIONS_H
#define DEEPDARKFANTASY_FUNCTIONS_H

int dRoll(int sideNum = 20, int adv = 0);

int dRoll(int sideNum, int adv){
    srand(time(NULL));
    int r1=0, r2=0;
    if(adv == 0) return rand()%sideNum+1;
    if(adv>0)
    {
        r1 = rand()%sideNum+1;
        // cout<<"r1 = "<<r1<<endl;
        r2 = rand()%sideNum+1;
        //cout<<"r2 = "<<r2<<endl;
        adv--;
        while(adv>0)
        {
            r1<r2? r1= rand()%sideNum+1 : r2 = rand()%sideNum+1;
            /* cout<<"r1 = "<<r1<<endl;
             cout<<"r2 = "<<r2<<endl;*/
            adv--;
        }

        return r1>r2 ? r1:r2;
    }
    if(adv<0)
    {
        r1 = rand()%sideNum+1;
        //cout<<"r1 = "<<r1<<endl;
        r2 = rand()%sideNum+1;
        //cout<<"r2 = "<<r2<<endl;
        adv--;
        while(adv<0)
        {
            r1>r2? r1= rand()%sideNum+1 : r2 = rand()%sideNum+1;
            /*cout<<"r1 = "<<r1<<endl;
            cout<<"r2 = "<<r2<<endl;*/
            adv++;
        }
        return r1>r2 ? r2:r1;
    }
    return 0;
}

#endif //DEEPDARKFANTASY_FUNCTIONS_H
