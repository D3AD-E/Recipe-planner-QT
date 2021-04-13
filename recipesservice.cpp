#include "recipesservice.h"
#include "recipe.h"
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonrecipehelper.h"
#include <QDir>
#include <QCoreApplication>

RecipesService::RecipesService()
{

}

QJsonObject RecipesService::readFile()
{
    QFile file("../LAB_1/recipes.json");

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Couldn't open file.");
    }
    if(file.size() != 0)
    {
        QJsonParseError jsonParseError;

        QJsonDocument loadDoc = QJsonDocument::fromJson(file.readAll(), &jsonParseError);

        file.close();

        if(jsonParseError.error == jsonParseError.NoError)
            return loadDoc.object();
        else
        {
            throw std::runtime_error("Got error while parsing json");
        }
    }
    else
    {
        QJsonObject empty;
        return empty;
    }
}

void RecipesService::saveFile(const QJsonDocument &json)
{
    QFile saveFile("../LAB_1/recipes.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Couldn't open file");
    }

    saveFile.write(json.toJson());
    saveFile.close();
}

void RecipesService::forceSaveFile(const QJsonDocument &json)
{
    QFile saveFile("recipes.json");
    saveFile.open(QIODevice::WriteOnly);

    saveFile.write(json.toJson());
    saveFile.close();
}

void RecipesService::edit(const Recipe &recipe, const QString& name)
{
    QJsonObject json = readFile();

    json.remove(name);
    json.insert(recipe.name, JsonRecipeHelper::toJson(recipe));

    saveFile(QJsonDocument(json));
}

void RecipesService::remove(const Recipe &recipe)
{
    QJsonObject json = readFile();
    json.remove(recipe.name);
    saveFile(QJsonDocument(json));
}

void RecipesService::remove(const QString& name)
{
    QJsonObject json = readFile();
    json.remove(name);
    saveFile(QJsonDocument(json));
}

void RecipesService::add(const Recipe &recipe)
{
    QJsonObject json = readFile();
    if(json.keys().contains(recipe.name))
    {
        throw std::runtime_error("Key already exists");
    }
    json.insert(recipe.name,JsonRecipeHelper::toJson(recipe));
    saveFile(QJsonDocument(json));
}

void RecipesService::saveRecipes(const QVector<Recipe>& recipes)
{
    QJsonObject allRecepiesObject;

    foreach(auto recipe, recipes)
    {
        allRecepiesObject.insert(recipe.name, JsonRecipeHelper::toJson(recipe));
    }

    saveFile(QJsonDocument(allRecepiesObject));

    return;
}

bool RecipesService::contains(const Recipe &recipe)
{
    QJsonObject json = readFile();
    return json.keys().contains(recipe.name);
}

bool RecipesService::contains(const QString &name)
{
    QJsonObject json = readFile();
    return json.keys().contains(name);
}

void RecipesService::createOverrideEmpty()
{
    QJsonDocument json;
    forceSaveFile(json);
}

QVector<Recipe> RecipesService::loadRecipes()
{
    QVector<Recipe> toRet;
    QJsonObject json = readFile();

    auto jsonRecipeNames = json.keys();

    foreach(auto jsonRecipeName, jsonRecipeNames)
    {
        auto jsonRecipe = json[jsonRecipeName].toObject();
        Recipe toAdd = JsonRecipeHelper::toRecipe(jsonRecipe);
        toAdd.name = jsonRecipeName;
        toRet.append(toAdd);
    }
    return toRet;
}


