#ifndef RECIPESSERVICE_H
#define RECIPESSERVICE_H
#include "recipe.h"
#include <QVector>
#include <QJsonObject>
class RecipesService
{
    //provides access (CRUD) to json file
public:
    RecipesService();
    static void edit(const Recipe& recipe, const QString& name);
    static void remove(const Recipe& recipe);
    static void remove(const QString& name);
    static void add(const Recipe& recipe);
    static QVector<Recipe> loadRecipes();
    static void saveRecipes(const QVector<Recipe>& recipes);
    static bool contains(const Recipe& recipe);
    static bool contains(const QString& name);
    static void createOverrideEmpty();
private:
    static QJsonObject readFile();
    static void saveFile(const QJsonDocument& json);
    static void forceSaveFile(const QJsonDocument& json);
};

#endif // RECIPESSERVICE_H
