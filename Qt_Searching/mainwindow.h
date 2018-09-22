#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <seeker.h>
#include <seekertokenizer.h>
#include <seekerparser.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void init();

private:
    void closeEvent(QCloseEvent *event);

    Ui::MainWindow *ui;

    Seeker _theSeeker;
};

#endif // MAINWINDOW_H
