#include "exceptionhandler.h"
#include <QMessageBox>
ExceptionHandler::ExceptionHandler()
{

}

void ExceptionHandler::showToUser(QWidget* parent, const QString &errText)
{
    QMessageBox::critical(parent, "Got exception", errText, QMessageBox::Ok);
}

void ExceptionHandler::showToUser(QWidget* parent, const std::runtime_error &err)
{
    showToUser(parent, err.what());
}
