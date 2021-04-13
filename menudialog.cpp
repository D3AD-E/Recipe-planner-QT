#include "menudialog.h"
#include "ui_menudialog.h"
#include "recipeslistmodel.h"
#include "ingredientslistmodel.h"
#include "ingredientssortproxymodel.h"
#include <QMessageBox>
MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    setupForm();
}

MenuDialog::MenuDialog(const QVector<Recipe> &recipes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog),
    recipes(recipes)
{
    ui->setupUi(this);
    setupForm();
}


MenuDialog::~MenuDialog()
{
    delete ui;
}

void MenuDialog::setupForm()
{
    this->availableModel= new RecipesListModel(recipes, this);
    ui->lVAvailable->setModel(availableModel);

    this->chosenModel=new RecipesListModel(this);
    ui->lVChosen->setModel(chosenModel);

    IngredientsSortProxyModel *proxyModel = new IngredientsSortProxyModel(this);
    requiredModel = new IngredientsListModel(this);
    proxyModel->setSourceModel(requiredModel);
    ui->lVRequired->setModel(proxyModel);

    QObject::connect(ui->lVAvailable->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(on_SelectionChanged(QItemSelection,QItemSelection)));
    QObject::connect(ui->lVChosen->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(on_RowsInsertedChosen(QModelIndex,int,int)));
    QObject::connect(ui->lVChosen->model(), SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), this, SLOT(on_RowsAlmostRemovedChosen(QModelIndex,int,int)));
}

void MenuDialog::on_btnToChosen_clicked()
{
    QModelIndexList indexes =  ui->lVAvailable->selectionModel()->selectedRows();

    if(indexes.empty())
        return;
    for(int i = 0; i<indexes.length();i++)
    {
        chosenModel->addRow(availableModel->getRecipe(indexes[i].row()));
    }
}

void MenuDialog::on_btnCancelChosen_clicked()
{
    QModelIndexList indexes =  ui->lVChosen->selectionModel()->selectedRows();
    if(indexes.empty())
        return;
    chosenModel->removeRows(indexes[0].row(), indexes.length());
}

void MenuDialog::on_SelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    if(selected.empty())
        return;
    int row = selected.indexes()[0].row();
    ui->pTextEditDescription->setPlainText(availableModel->getRecipe(row).toString());
}

void MenuDialog::on_RowsInsertedChosen(const QModelIndex &parent, int start, int end)
{
    foreach(auto ingredient, chosenModel->getRecipe(start).ingredients)
    {
        requiredModel->addIngredient(ingredient);
    }
    ui->lVRequired->model()->sort(0);//works!
}

void MenuDialog::on_RowsAlmostRemovedChosen(const QModelIndex &parent, int start, int end)
{
    foreach(auto ingredient, chosenModel->getRecipe(start).ingredients)
    {
        requiredModel->removeIngredient(ingredient);
    }
    ui->lVRequired->model()->sort(0);//works!
}
