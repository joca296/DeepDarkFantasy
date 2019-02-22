#include "statusEffect.h"

statusEffect::statusEffect(string name)
{
    ifstream f;
    string path;
    jname=path;
    if(PLATFORM_NAME == "windows") path = "statusEffects\\"+name+".json";
    else path = "./heroClasses/"+name+".json";
    f.open(path);
    if(f.is_open())
    {
        const Document& document = parseFromFile(&f);
        val=document["Value"].GetInt();
        saving_throw_skill=document["SavingThrowSkill"].GetString();
        saveDC=document["SaveDC"].GetInt();

        const Value& a = document["Affects"];

        for(SizeType i = 0; i<a.Size(); i++)
        {
            affects.push_back(a[i].GetString());
        }

    }

}


