#ifndef INGREDIENTSLISTMODEL_H
#define INGREDIENTSLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <recipe.h>
class IngredientsListModel : public QAbstractListModel
{
    //used in menu dialog with proxy model
    Q_OBJECT

public:
    explicit IngredientsListModel(QObject *parent = nullptr);

    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    //bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void addIngredient(const Recipe::Ingredient& ingredient);
    void removeIngredient(const Recipe::Ingredient& ingredient);
private:
    QVector<Recipe::Ingredient> ingredients;
};

#endif // INGREDIENTSLISTMODEL_H
