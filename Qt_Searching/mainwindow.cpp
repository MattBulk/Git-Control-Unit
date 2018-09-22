#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Qt Searcher", tr("Are you sure?\n"),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes)
        event->ignore();
    else
        event->accept();
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->comboBox->currentText();
    if(this->_theSeeker.setQuery(str))
        this->_theSeeker.search();
    else qDebug("Query is incorrect");
}

void MainWindow::init()
{
    QStringList list;
    list << "alpha" << "beta" << "gamma" << "epsilon";
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentText("((this > 32) || (domani != 45)) && ieri < (lui == 43)");
    this->_theSeeker.setTokens(QRegularExpression("((==|\\!=|<[>=]?|>=?|\\|\\||\\&\\&))"));
}
