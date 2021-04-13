#include "entrydialog.h"
#include "ui_entrydialog.h"
#include "ingredientstablemodel.h"
#include <QMessageBox>
#include "recipesservice.h"

EntryDialog::EntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);
    setupForm();
}

EntryDialog::EntryDialog(Recipe recipe, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog),
    recipe(recipe)
{
    ui->setupUi(this);
    editing = true;
    setupForm();
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

Recipe EntryDialog::getRecipe() const
{
    return recipe;
}

bool EntryDialog::getEditing() const
{
    return editing;
}

void EntryDialog::on_btnRemIngredient_clicked()
{
    QModelIndexList indexes =  ui->tVIngredients->selectionModel()->selectedIndexes();
    int countRow = indexes.count();
    for( int i = countRow; i > 0; i--)
        ui->tVIngredients->model()->removeRows(indexes.at(i-1).row(),1, QModelIndex());
}

void EntryDialog::on_btnAddIngredient_clicked()
{
    ui->tVIngredients->model()->insertRows(ui->tVIngredients->model()->rowCount(),1, QModelIndex());
}

void EntryDialog::on_btnCancel_clicked()
{
    close();
}

void EntryDialog::on_btnOk_clicked()
{
    if(!checkRecipeForm())
        return;
    setupRecipeForSending();
    accept();
}

void EntryDialog::on_btnAddNew_clicked()
{
    editing = false;
    if(!checkRecipeForm())
        return;

    setupRecipeForSending();
    accept();
}

void EntryDialog::setupRecipeForSending()
{
    recipe.description = ui->pTextEditDescription->toPlainText();
    recipe.name = ui->lERecipeName->text();
    recipe.ingredients = model->getIngredients();
}

void EntryDialog::setupForm()
{
    this->model = new IngredientsTableModel(this->recipe.ingredients, this);

    ui->tVIngredients->setModel(model);

    ui->tVIngredients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->pTextEditDescription->setPlainText(recipe.description);
    ui->lERecipeName->setText(recipe.name);

    //we are already adding new, no point in 2 buttons with same functionality
    if(!editing)
        ui->btnAddNew->setVisible(false);

    recipe.name.isEmpty()? setWindowTitle("New recipe") : setWindowTitle(recipe.name);
}

bool EntryDialog::checkRecipeForm()
{
    QVector<QString> errMessages;
    QVector<QString> warnMessages;
    if(ui->lERecipeName->text().isEmpty())
    {
        errMessages += "Recipe name is empty";
    }
    else if(!editing)
    {
        if(RecipesService::contains(ui->lERecipeName->text()))
            errMessages += "Recipe with this name already exists";
    }

    errMessages.append(checkIngredients());

    if(!errMessages.isEmpty())
    {
        QMessageBox msgBox;
        QString finalErrMessage;
        foreach(auto message, errMessages)
        {
             finalErrMessage+=message+"\n";
        }
        msgBox.setText(finalErrMessage);
        msgBox.exec();
        return false;
    }

    if(ui->pTextEditDescription->toPlainText().isEmpty())
    {
        warnMessages += "Description is empty.\n";
    }
    if(model->getIngredients().isEmpty())
    {
        warnMessages += "No ingredints were provided.\n";
    }
    if(!warnMessages.isEmpty())
    {
        QMessageBox::StandardButton reply;
        QString finalWarningMessage;
        foreach(auto message, warnMessages)
        {
             finalWarningMessage+=message+"\n";
        }
        reply = QMessageBox::warning(this, "Confirm", finalWarningMessage+"Proceed?", QMessageBox::Yes|QMessageBox::No);
        return reply == QMessageBox::Yes;
    }
    return true;
}

QVector<QString> EntryDialog::checkIngredients()
{
    auto ingredients = model->getIngredients();

    QVector<QString> errors;
    QMap<QString,bool> namesOccuringMultipleTimes;

    int emptyNameCount = 0;
    int emptyUnitCount = 0;
    bool hasBannedWord = false;
    foreach(auto ingredient, ingredients)
    {
        if(ingredient.unit.isEmpty())
            emptyUnitCount++;
        if(ingredient.name.isEmpty())
        {
            emptyNameCount++;
            continue;
        }

        if(ingredient.name == "recipe")
             hasBannedWord = true;

        if(namesOccuringMultipleTimes.contains(ingredient.name))
        {
            if(!namesOccuringMultipleTimes[ingredient.name])
            {
                //if we see this nmae for 2 time we add error to error list, and change value to true, therefore only 1 error message per name
                namesOccuringMultipleTimes[ingredient.name] = true;
                errors.append("Multiple occurences of name: " + ingredient.name);
            }
        }
        else
        {
            namesOccuringMultipleTimes.insert(ingredient.name, false);
        }
    }
    if(emptyNameCount==1)
    {
        errors.append("Ingredient name missing");
    }
    else if(emptyNameCount>1)
    {
        errors.append("Multiple ingredients names missing");
    }

    if(emptyUnitCount==1)
    {
        errors.append("Ingredient unit missing");
    }
    else if(emptyUnitCount>1)
    {
        errors.append("Multiple ingredients units missing");
    }

    if(hasBannedWord)
        errors.append("Not allowed. Ingredient name: recipe");

    return errors;
}
