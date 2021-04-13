#ifndef JSONRECIPEHELPER_H
#define JSONRECIPEHELPER_H
#include <QJsonObject>
#include "recipe.h"


class JsonRecipeHelper
{
    //converts recipes to json representation and vice versa
public:
    JsonRecipeHelper();
    static QJsonObject toJson(Recipe recipe);
    static Recipe toRecipe(QJsonObject json);
};

#endif // JSONRECIPEHELPER_H
