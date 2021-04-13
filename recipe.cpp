#include "recipe.h"

Recipe::Recipe()
{

}

QString Recipe::toString()
{
    QString toRet = name+"\n";
    toRet+=description+"\n";
    for(int i =0; i <ingredients.length();i++)
    {
        toRet+=ingredients[i].name+" "+QString::number(ingredients[i].quantity)+" "+ingredients[i].unit;
        if(i!=ingredients.length()-1)
            toRet+="\n";
    }
    return toRet;
}

