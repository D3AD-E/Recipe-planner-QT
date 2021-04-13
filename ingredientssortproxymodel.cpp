#include "ingredientssortproxymodel.h"


IngredientsSortProxyModel::IngredientsSortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool IngredientsSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
}
