#include "jsonrecipehelper.h"
#include <QJsonArray>
JsonRecipeHelper::JsonRecipeHelper()
{

}

QJsonObject JsonRecipeHelper::toJson(Recipe recipe)
{
    QJsonObject recipesObject;
    auto descriptionList = recipe.description.split("\n");

    recipesObject.insert("recipe", QJsonArray::fromStringList(descriptionList));

    foreach(auto ingredient, recipe.ingredients)
    {
        recipesObject.insert(ingredient.name, QJsonValue::fromVariant(QString::number(ingredient.quantity)+" "+ingredient.unit));
    }
    return recipesObject;
}

Recipe JsonRecipeHelper::toRecipe(QJsonObject json)
{
    Recipe recipe;
    auto description = json.value("recipe").toArray();
    foreach(auto line, description)
    {
        if(line == description.last())
        {
            recipe.description.append(line.toString());
            break;
        }
        else
            recipe.description.append(line.toString()+"\n");
    }

    foreach(auto ingredientName, json.keys())
    {
        if(ingredientName == "recipe")
            continue;

        Recipe::Ingredient toAddIngredient;
        toAddIngredient.name = ingredientName;
        QString amount = json[ingredientName].toString();
        toAddIngredient.quantity = amount.section(' ',0,0).toFloat();
        toAddIngredient.unit = amount.section(' ',1).simplified();

        recipe.ingredients.append(toAddIngredient);
    }
    return recipe;
}
