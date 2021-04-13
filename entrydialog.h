#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include "recipe.h"
#include "ingredientstablemodel.h"
namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(QWidget *parent = nullptr);
    EntryDialog(Recipe recipe, QWidget *parent = nullptr);
    ~EntryDialog();
    Recipe getRecipe() const;
    bool getEditing() const;

private slots:
    void on_btnRemIngredient_clicked();

    void on_btnAddIngredient_clicked();

    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnAddNew_clicked();


private:
    Ui::EntryDialog *ui;
    IngredientsTableModel* model;

    Recipe recipe;
    bool editing;
    void setupRecipeForSending();
    void setupForm();
    bool checkRecipeForm();

    QVector<QString> checkIngredients();
};

#endif // ENTRYDIALOG_H
