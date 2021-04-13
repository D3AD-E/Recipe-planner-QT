#ifndef INGREDIENTSSORTPROXYMODEL_H
#define INGREDIENTSSORTPROXYMODEL_H
#include <QSortFilterProxyModel>
#include <QModelIndex>

class IngredientsSortProxyModel : public QSortFilterProxyModel
{
    //used in menu dialog
    Q_OBJECT
public:

    explicit IngredientsSortProxyModel(QObject *parent = nullptr);
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // INGREDIENTSSORTPROXYMODEL_H
