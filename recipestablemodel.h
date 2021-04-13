#ifndef RECIPESTABLEMODEL_H
#define RECIPESTABLEMODEL_H

#include <QAbstractTableModel>
#include "recipe.h"


class RecipesTableModel : public QAbstractTableModel
{
    //model used in MainWindow
    Q_OBJECT

public:
    explicit RecipesTableModel(QObject *parent = nullptr);
    RecipesTableModel(const QVector<Recipe> &recipes, QObject *parent = nullptr);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void addRow(const Recipe& recipe);

    void editRow(const QModelIndex &index, const Recipe &recipe);

    Recipe at(int index);

    QVector<Recipe> getRecipes();

private:
    QVector<Recipe> recipes;
};

#endif // RECIPESTABLEMODEL_H
