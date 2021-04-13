#include "ingredientslistmodel.h"

IngredientsListModel::IngredientsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int IngredientsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return ingredients.size();
}

QVariant IngredientsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= ingredients.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        const auto &ingredient = ingredients.at(index.row());
        return ingredient.name+" "+QString::number(ingredient.quantity)+" "+ingredient.unit;
    }

    return QVariant();

}

Qt::ItemFlags IngredientsListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool IngredientsListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i <count; i++)
    {
        ingredients.removeAt(row+i);
    }

    endRemoveRows();
    return true;
}

void IngredientsListModel::addIngredient(const Recipe::Ingredient &ingredient)
{
    for(int i =0; i<ingredients.length();i++)
    {
        if(ingredients[i].name == ingredient.name && ingredients[i].unit == ingredient.unit)
        {
            ingredients[i].quantity+=ingredient.quantity;
            emit dataChanged(index(i, 0), index(i, 0), {Qt::DisplayRole, Qt::EditRole});
            return;
        }
    }

    int newRow = ingredients.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    ingredients.append(ingredient);
    endInsertRows();
}

void IngredientsListModel::removeIngredient(const Recipe::Ingredient &ingredient)
{
    for(int i =0; i<ingredients.length();i++)
    {
        if(ingredients[i].name == ingredient.name && ingredients[i].unit == ingredient.unit)
        {
            ingredients[i].quantity-=ingredient.quantity;
            if(ingredients[i].quantity<=0)
            {
                removeRows(i,1);
            }
            else
            {
                emit dataChanged(index(i, 0), index(i, 0), {Qt::DisplayRole, Qt::EditRole});
            }
            return;
        }
    }

    throw std::runtime_error("Cannot remove non-existent ingredient");
}
