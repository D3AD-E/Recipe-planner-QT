#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menudialog.h"
#include "recipesservice.h"
#include <QMessageBox>
#include <QString>
#include "recipestablemodel.h"
#include "entrydialog.h"
#include "exceptionhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<Recipe> recipes;
    try {
        recipes = RecipesService::loadRecipes();
    }  catch (const std::runtime_error &err) {
        ExceptionHandler::showToUser(this, err);
        RecipesService::createOverrideEmpty();
    }

    this->model = new RecipesTableModel(recipes, this);
    ui->tVMain->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    EntryDialog *dialog = new EntryDialog(this);
    if(dialog->exec()== QDialog::Accepted)
    {
        //we know we were adding not editing
        auto recipe = dialog->getRecipe();
        try {
            model->addRow(recipe);
        }  catch (const std::runtime_error &err) {
            ExceptionHandler::showToUser(this, err);
        }

    }
}

void MainWindow::on_btnMenu_clicked()
{
    MenuDialog *menu = new MenuDialog(model->getRecipes(), this);
    menu->exec();
}

void MainWindow::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Are you sure that you want to delete recipe?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QModelIndexList indexes =  ui->tVMain->selectionModel()->selectedRows();
        try {
            ui->tVMain->model()->removeRows(indexes.at(0).row(), indexes.count(), QModelIndex());
        }  catch (const std::runtime_error &err) {
            ExceptionHandler::showToUser(this, err);
        }
    }
}

void MainWindow::on_btnEdit_clicked()
{
    QModelIndexList indexes =  ui->tVMain->selectionModel()->selectedRows();
    EntryDialog *dialog = new EntryDialog(model->at(indexes[0].row()), this);
    if(dialog->exec()== QDialog::Accepted)
    {
        auto recipe = dialog->getRecipe();
        try {
            if(dialog->getEditing())
                model->editRow(indexes[0], recipe);
            else
                model->addRow(recipe);
        }  catch (const std::runtime_error &err) {
            ExceptionHandler::showToUser(this, err);
        }
    }
}

void MainWindow::on_tVMain_doubleClicked(const QModelIndex &index)
{
    EntryDialog *dialog = new EntryDialog(model->at(index.row()), this);
    if(dialog->exec()== QDialog::Accepted)
    {
        auto recipe = dialog->getRecipe();
        try {
            if(dialog->getEditing())
                model->editRow(index,recipe);
            else
                model->addRow(recipe);
        }  catch (const std::runtime_error &err) {
            ExceptionHandler::showToUser(this, err);
        }
    }
}
