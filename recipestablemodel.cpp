#include "recipestablemodel.h"
#include "recipesservice.h"

RecipesTableModel::RecipesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

RecipesTableModel::RecipesTableModel(const QVector<Recipe> &recipes, QObject *parent)
    : QAbstractTableModel(parent),
      recipes(recipes)
{
}

QVariant RecipesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Description");
            default:
                break;
        }
    }
    return QVariant();
}

int RecipesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return recipes.size();
}

int RecipesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant RecipesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= recipes.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &recipe = recipes.at(index.row());

        switch (index.column()) {
            case 0:
                return recipe.name;
            case 1:
                return recipe.description;
            default:
                break;
        }
    }
    return QVariant();
}



Qt::ItemFlags RecipesTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool RecipesTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++)
    {
        RecipesService::remove(recipes[row+i]);
        recipes.removeAt(row+i);
    }

    endRemoveRows();

    return true;
}

void RecipesTableModel::addRow(const Recipe &recipe)
{
    int newRow = recipes.count();
    RecipesService::add(recipe);
    beginInsertRows(QModelIndex(), newRow, newRow);
    recipes.append(recipe);
    endInsertRows();
}

void RecipesTableModel::editRow(const QModelIndex &index, const Recipe &recipe)
{
    if (!index.isValid())
        return;

    const int row = index.row();
    RecipesService::edit(recipe, recipes.at(row).name);
    recipes.replace(row, recipe);

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
}

Recipe RecipesTableModel::at(int index)
{
    return recipes.at(index);
}

QVector<Recipe> RecipesTableModel::getRecipes()
{
    return recipes;
}


