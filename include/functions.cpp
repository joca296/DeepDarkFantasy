#include "functions.h"


int dRoll(int sideNum, int adv, int dNum)
{
    int r1=0, r2=0,sum=0;
    if(adv == 0)
    {
        for(int i=0; i<dNum; i++)
        {
            sum+=rand()%sideNum+1;
            //cout<<"sum = "<<sum<<" i = "<<i<<endl;
        }
        //cout<<"Rolled: "<<sum<<endl;
        return sum;
    }
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

int randomWeight(const vector<int>& choiceWeight){
    int sum_of_weight = 0;
    for(int i=0; i<choiceWeight.size(); i++) {
        sum_of_weight += choiceWeight[i];
    }
    int rnd = rand()%sum_of_weight;
    for(int i=0; i<choiceWeight.size(); i++) {
        if(rnd < choiceWeight[i]){
            return i;
        }
        rnd -= choiceWeight[i];
    }
    assert(!"should never get here");
}

Document parseFromFile(ifstream *f){
    //converting file to a char* to parse file
    stringstream stream;
    stream<<f->rdbuf();
    string str = stream.str();
    const char* json = str.c_str();
    Document document;
    document.Parse(json);
    return document;
}

void printDamage(const string& actorName,const string& targetName,const string& actionName, int& dmgTotal,const vector<string>& dmgBreakdown, bool critFlag, int actorHero, int targetHero){
    //setting colors for hero or monster names
    colorPrint(actorName,actorHero);
    cout<<" hit ";
    colorPrint(targetName,targetHero);
    cout<<" for "<<dmgTotal<<" damage with ";

    if(actionName[0]=='a') cout<<"an ";
    else cout<<"a ";
    cout<<actionName<<".";
    if(critFlag) cout<<" (crit)";

    //damage breakdown
    cout<<" Breakdown: ";
    for(int i=0; i<dmgBreakdown.size(); i++){
        cout<<dmgBreakdown[i];
        if(i==dmgBreakdown.size()-1)
            cout<<endl;
        else
            cout<<", ";
    }
}

void colorPrint(const string& output,const  string& color) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int col;

    if (color=="gray") col=8;
    else if(color=="blue") col=9;
    else if(color=="green") col=10;
    else if(color=="ltBlue") col=11;
    else if(color=="red") col=12;
    else if(color=="pink") col=13;
    else if(color=="yellow") col=14;
    else if(color=="white") col=7;

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, col);

    cout<<output;

    SetConsoleTextAttribute(hConsole, 7); //set back to black background and white text
}

void colorPrint(const string& output,int hero){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int col;

    if(hero==1) col=10;
    else col=12;

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, col);

    cout<<output;

    SetConsoleTextAttribute(hConsole, 7); //set back to black background and white text
}
int convertToAttribute(int attr){
    return 10+(attr*2);
}