#include "ingredientstablemodel.h"

IngredientsTableModel::IngredientsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

IngredientsTableModel::IngredientsTableModel(const QVector<Recipe::Ingredient> &ingredients, QObject *parent)
    : QAbstractTableModel(parent),
    ingredients(ingredients)
{

}

QVariant IngredientsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Quantity");
            case 2:
                return tr("Units");
            default:
                break;
        }
    }
    return QVariant();
}


int IngredientsTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ingredients.length();
}

int IngredientsTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant IngredientsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= ingredients.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &ingredient = ingredients.at(index.row());

        switch (index.column()) {
            case 0:
                return ingredient.name;
            case 1:
                return QString::number(ingredient.quantity);
            case 2:
                return ingredient.unit;
            default:
                break;
        }
    }
    return QVariant();
}

bool IngredientsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto ingredient = ingredients.value(row);

        switch (index.column())
        {
            case 0:
            {
                ingredient.name = value.toString().simplified().toLower();
                break;
            }
            case 1:
                ingredient.quantity = value.toFloat();
                break;
            case 2:
                ingredient.unit = value.toString().simplified().toLower();
                break;
            default:
                return false;
        }
        ingredients.replace(row, ingredient);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    return false;
}

Qt::ItemFlags IngredientsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool IngredientsTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i <count; i++)
    {
        Recipe::Ingredient toAdd;
        toAdd.quantity=0;
        //would give 99e-33 otherwise
        ingredients.insert(row+i, toAdd);
    }
    endInsertRows();
    return true;
}


bool IngredientsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i <count; i++)
    {
        ingredients.removeAt(row+i);
    }

    endRemoveRows();
    return true;
}

QVector<Recipe::Ingredient> IngredientsTableModel::getIngredients()
{
    return ingredients;
}

