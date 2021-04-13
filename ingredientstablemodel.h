#ifndef INGREDIENTSTABLEMODEL_H
#define INGREDIENTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <recipe.h>
class IngredientsTableModel : public QAbstractTableModel
{
    //used in entry dialog
    Q_OBJECT

public:
    explicit IngredientsTableModel(QObject *parent = nullptr);
    IngredientsTableModel(const QVector<Recipe::Ingredient> &ingredients, QObject *parent = nullptr);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;


    QVector<Recipe::Ingredient> getIngredients();
private:
    QVector<Recipe::Ingredient> ingredients;
};

#endif // INGREDIENTSTABLEMODEL_H
