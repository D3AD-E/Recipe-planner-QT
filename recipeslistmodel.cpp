#include "recipeslistmodel.h"

RecipesListModel::RecipesListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

RecipesListModel::RecipesListModel(const QVector<Recipe> &recipes, QObject *parent)
    : QAbstractListModel(parent),
      recipes(recipes)
{

}


int RecipesListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return recipes.size();
}

QVariant RecipesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= recipes.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &recipe = recipes.at(index.row());
        return recipe.name;
    }

    return QVariant();
}


Qt::ItemFlags RecipesListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool RecipesListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i <count; i++)
    {
        recipes.removeAt(row+i);
    }

    endRemoveRows();
    return true;
}

void RecipesListModel::addRow(const Recipe &recipe)
{
    int newRow = recipes.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    recipes.append(recipe);
    endInsertRows();
}

Recipe RecipesListModel::getRecipe(int index)
{
    return recipes.at(index);
}
