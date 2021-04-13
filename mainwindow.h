#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recipestablemodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnMenu_clicked();

    void on_btnDelete_clicked();

    void on_btnEdit_clicked();

    void on_tVMain_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    RecipesTableModel *model;
};
#endif // MAINWINDOW_H
