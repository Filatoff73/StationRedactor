#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizePolicy>
#include <QLayout>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainWidget = new Widget();

        ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
     ui->scrollArea->setWidget(mainWidget);
     ui->scrollArea->show();


     //QObject::connect(ui->scrollArea->verticalScrollBar(),SIGNAL(sliderReleased()), mainWidget, SLOT(repaint()));
     //QObject::connect(ui->scrollArea->horizontalScrollBar(),SIGNAL(sliderReleased()), mainWidget, SLOT(repaint()));

        QObject::connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(DeleteButton()));
        QObject::connect(ui->addBlock,SIGNAL(clicked()),this,SLOT(AddBlock()));



}

void MainWindow::DeleteButton()
{
    mainWidget->DeleteConnectionLine();
}

void MainWindow::AddBlock()
{
    mainWidget->AddBlockElement();


}


MainWindow::~MainWindow()
{
    delete ui;
    delete mainWidget;
}
