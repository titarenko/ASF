#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AsfFile.h"
#include "from_string.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    file(0),
    statusFormat("Frame %1 (timestamp %2)")
{
    ui->setupUi(this);
    prepareUi();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete file;
}

void MainWindow::on_actionOpen_ASF_triggered()
{
    loadFile();
    prepareUi();
    populateUi();
    setFrame(0);
}

void MainWindow::on_actionSave_ASF_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, "Save ASF", ".", "ASF files (*.asf)");

    if (!fileName.isNull())
    {
        save(fileName.toStdString().c_str());
    }
}

void MainWindow::on_actionSave_GZipped_ASF_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, "Save GZipped ASF", ".", "GZipped ASF files (*.asf.gz)");

    if (!fileName.isNull())
    {
        save(fileName.toStdString().c_str());
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About",
        "ASF Viewer\nby Constantin Titarenko, 2011\n"
        "\nEmail: constantin.titarenko@gmail.com"
        "\nWeb: http://about.me/constantin.titarenko");
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    setFrame(value);
}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "Open ASF", ".", "ASF files (*.asf);;GZipped ASF files (*.asf.gz)");

    if (fileName.isNull()) return;

    delete file;
    file = new AsfFile(fileName.toStdString().c_str(), 1024);
}

void MainWindow::prepareUi()
{
    bool fileIsLoaded = file;

    ui->dockWidget->setEnabled(fileIsLoaded);
    ui->centralWidget->setEnabled(fileIsLoaded);

    ui->dockWidget->setEnabled(fileIsLoaded);
    ui->centralWidget->setEnabled(fileIsLoaded);

    ui->actionSave_ASF->setEnabled(fileIsLoaded);
    ui->actionSave_GZipped_ASF->setEnabled(fileIsLoaded);
}

void MainWindow::populateUi()
{
    if (!file) return;

    ui->tableWidget->setRowCount(file->getHead().size());

    int row = 0;
    for (asf_head::const_iterator pair = file->getHead().begin();
         pair != file->getHead().end(); ++pair)
    {
        ui->tableWidget->setItem(row, 0,
            new QTableWidgetItem(pair->first.c_str()));
        ui->tableWidget->setItem(row++, 1,
            new QTableWidgetItem(pair->second.c_str()));
    }

    ui->horizontalSlider->setMaximum(file->getFramesCount() - 1);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setValue(0);
}

void MainWindow::setFrame(int index)
{
    if (!file) return;

    AsfFrame frame = file->getFrame(index);

    QImage image((const uchar*) frame.getData(),
        frame.getWidth(), frame.getHeight(), QImage::Format_Indexed8);

    ui->label->setPixmap(QPixmap::fromImage(image));

    int frameNumber = index + from_string<int>(file->getHead().at("START_FRAME"));
    int frameTimestamp = frame.getTimestamp();

    ui->statusBar->showMessage(
        statusFormat.arg(QString::number(frameNumber),
                         frameTimestamp == -1
                            ? "N/A"
                            : QString::number(frameTimestamp)));
}

void MainWindow::save(const char *fileName)
{
    if (!file) return;
    file->save(fileName);
}
