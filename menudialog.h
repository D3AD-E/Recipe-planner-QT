#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "recipe.h"
#include "recipeslistmodel.h"
#include <QItemSelection>
#include "ingredientslistmodel.h"
namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = nullptr);
    MenuDialog(const QVector<Recipe>& recipes, QWidget *parent = nullptr);
    ~MenuDialog();

private slots:
    void on_btnToChosen_clicked();

    void on_btnCancelChosen_clicked();

    void on_SelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

    void on_RowsInsertedChosen(const QModelIndex & parent, int start, int end);

    void on_RowsAlmostRemovedChosen(const QModelIndex & parent, int start, int end);

private:
    Ui::MenuDialog *ui;
    QVector<Recipe> recipes;
    void setupForm();

    RecipesListModel *chosenModel;
    RecipesListModel *availableModel;
    IngredientsListModel *requiredModel;
};

#endif // MENUDIALOG_H
