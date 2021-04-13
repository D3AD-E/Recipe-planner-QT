#ifndef RECIPESLISTMODEL_H
#define RECIPESLISTMODEL_H

#include <QAbstractListModel>
#include "recipe.h"


class RecipesListModel : public QAbstractListModel
{
    //model used in menu dialog
    Q_OBJECT

public:
    explicit RecipesListModel(QObject *parent = nullptr);
    RecipesListModel(const QVector<Recipe> &recipes, QObject *parent = nullptr);
    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void addRow(const Recipe& recipe);

    Recipe getRecipe(int index);
private:
    QVector<Recipe> recipes;
};

#endif // RECIPESLISTMODEL_H
