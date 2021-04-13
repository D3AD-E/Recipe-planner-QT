#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H
#include <QString>
#include <QWidget>
class ExceptionHandler
{
    //shows used message about what failed in program
public:
    ExceptionHandler();
    static void showToUser(QWidget* parent, const QString& errText);
    static void showToUser(QWidget* parent, const std::runtime_error& err);
};

#endif // EXCEPTIONHANDLER_H
