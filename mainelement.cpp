#include "mainelement.h"
#include <QDebug>
#include <QLabel>
#include <widget.h>

int MainElement::STEP_GRID_X1=0;
int MainElement::STEP_GRID_Y1=0;
QFont MainElement::font;

MainElement::MainElement(QWidget *parent) : QWidget(parent)
{
    resultDialog=false;
    question = new QDialog;



    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));


}


bool MainElement::CreateDialog()
{
    QPushButton okButton,cancelButton;

    okButton.setText(tr("OK"));
    cancelButton.setText(tr("Cancel"));

    QHBoxLayout layout;

    layout.addWidget(&cancelButton);
    layout.addWidget(&okButton);

    QLabel text;

    text.setText("Удалить линию соединения?");
    layout.setDirection(QBoxLayout::BottomToTop);
    layout.addWidget(&text);

     question->setLayout(&layout);

     QObject::connect(&okButton, SIGNAL(clicked()), this, SLOT(YesFunc()));
     QObject::connect(&cancelButton, SIGNAL(clicked()), this, SLOT(NoFunc()));
     question->setVisible(true);
     question->show();
     question->exec();

   return resultDialog;

}

bool MainElement::SetScale(float scale)
{
    if(scale>=0)
    {   
        int tempX = STEP_GRID_X1;
        int tempY = STEP_GRID_Y1;


        STEP_GRID_X1*= fabs(scale);
        STEP_GRID_Y1*= fabs(scale);

        if(tempX==STEP_GRID_X1 || tempY == STEP_GRID_Y1)
        {
            STEP_GRID_X1+= 1;
            STEP_GRID_Y1+= 1;
        }

        int fontSize = (int)STEP_GRID_X1/5.0;
        if(fontSize>=1)
            font.setPixelSize(fontSize);
        else
            font.setPixelSize(1);

        return true;
    }

    if(scale<0 && STEP_GRID_X1>2 && STEP_GRID_Y1>2)
    {
        int tempX = STEP_GRID_X1;
        int tempY = STEP_GRID_Y1;


        STEP_GRID_X1/= fabs(scale);
        STEP_GRID_Y1/= fabs(scale);

        if(tempX==STEP_GRID_X1 || tempY == STEP_GRID_Y1)
        {
            STEP_GRID_X1-= 1;
            STEP_GRID_Y1-= 1;
        }

        int fontSize = (int)STEP_GRID_X1/5.0;
        if(fontSize>=1)
            font.setPixelSize(fontSize);
        else
            font.setPixelSize(1);

        return true;
    }

    return false;
}

void MainElement:: YesFunc()
{
    resultDialog=true;
    question->close();
}

void MainElement:: NoFunc()
{
    resultDialog=false;
    question->close();
}

void MainElement::InitConstans()
{
    STEP_GRID_X1 = 60;
    STEP_GRID_Y1 = 60;
    font.setPixelSize(STEP_GRID_X1/5.0);

}



int MainElement::CheckToBorderWidth(int x)
{
    if( x > dynamic_cast<Widget*>(this->parent())->size().width())
        return dynamic_cast<Widget*>(this->parent())->size().width();

    if( x < 0 )
        return 0;

    return x;


}

int MainElement::CheckToBorderHeight(int y)
{
    if( y > dynamic_cast<Widget*>(this->parent())->size().height())
        return dynamic_cast<Widget*>(this->parent())->size().height();

    if( y < 0 )
        return 0;

    return y;
}




MainElement::~MainElement()
{
    delete question;
}


