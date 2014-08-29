#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widget.h>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Widget* mainWidget;

private slots:
    void DeleteButton();
    void AddBlock();
};

#endif // MAINWINDOW_H
