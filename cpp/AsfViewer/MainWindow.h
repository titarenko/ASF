#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AsfFile.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_ASF_triggered();
    void on_actionSave_ASF_triggered();
    void on_actionSave_GZipped_ASF_triggered();
    void on_actionAbout_triggered();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    AsfFile* file;
    QString statusFormat;

    void loadFile();
    void prepareUi();
    void populateUi();
    void setFrame(int index);

    void save(const char* fileName);
};

#endif // MAINWINDOW_H
