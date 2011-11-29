#include <QtGui/QApplication>
#include <QMessageBox>

#include <exception>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);

        MainWindow w;
        w.show();

        return a.exec();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(0, "Critical error", e.what());
    }
    catch (...)
    {
        QMessageBox::critical(0, "Critical error", "Unknown error");
    }
}
