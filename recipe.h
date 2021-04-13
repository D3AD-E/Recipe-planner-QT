#ifndef RECIPE_H
#define RECIPE_H
#include <QString>
#include <QVector>
#include <QMap>

class Recipe
{
public:
    struct Ingredient {
        QString name;
        float quantity;
        QString unit;
    };

    Recipe();
    QString name;
    QString description;
    QVector<Ingredient> ingredients;

    QString toString();
};

#endif // RECIPE_H
