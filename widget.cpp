#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include "mainelement.h"
#include <QDebug>
#include <QPen>
#include <QScrollBar>
#include <QScrollArea>

#define RIGHT_BORDER 800
#define BOTTOM_BORDER 800


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    MainElement::InitConstans();

    drawContactLine=0;
    beginContact=NULL;
    endContact=NULL;

    nElement=1;
    arrRelay.resize(nElement);

    for(int i=0;i<nElement;i++)
    {
        arrRelay[i] = new BlockRelay(i, this);
        arrRelay[i]->show();
    }

}

void Widget::AddBlockElement()
{
    nElement++;
    arrRelay.resize(nElement);
    arrRelay[nElement-1]  =new BlockRelay(nElement-1, this);
    arrRelay[nElement-1]->show();


repaint();



}




void Widget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter (this);
    DrawGrid(painter);

    painter->setPen(Qt::black);



    if(drawContactLine==2)
    {
        beginContact->SetChecked(false);
        endContact->SetChecked(false);

        if(beginContact->GetNeighbour()==NULL && endContact->GetNeighbour()==NULL && beginContact!=endContact && dynamic_cast<MainElement*>(beginContact->parent())!=dynamic_cast<MainElement*>(endContact->parent()))
        {
        beginContact->SetNeighbour(endContact);
        endContact->SetNeighbour(beginContact);
        }


        beginContact=NULL;
        endContact=NULL;
        drawContactLine=0;

        qDebug()<<"Done"<<endl;

    } 

    DrawNeighbours(painter);


    painter->end();

}


void Widget::mouseMoveEvent (QMouseEvent* mouseEvent)
{

}

void Widget::mousePressEvent(QMouseEvent* mouseEvent)
{


}

void Widget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{

}

void Widget::wheelEvent(QWheelEvent* event)
{
    int x=MainElement::GetSTEP_GRID_X1();
    int y=MainElement::GetSTEP_GRID_Y1();
    if(event->delta()>0)
    {
        if(dynamic_cast<MainElement*>(this->parent())->SetScale(1.1))
        {
            this->setGeometry(0,0,this->size().width()*1.1,this->size().height()*1.1 );

            for(int i=0;i<arrRelay.size();i++)
            {

                int nx = arrRelay[i]->GetPosition().x()/x;
                int ny = arrRelay[i]->GetPosition().y()/y;


                arrRelay[i]->SetPosition(nx*MainElement::GetSTEP_GRID_X1() , ny*MainElement::GetSTEP_GRID_Y1());

                arrRelay[i]->SetMinimumSize();
                arrRelay[i]->SetContact();
                arrRelay[i]->move(arrRelay[i]->GetPosition());



            }


        }
    }

    if(event->delta()<0)
    {
        if(dynamic_cast<MainElement*>(this->parent())->SetScale(-1.1))
        {
            this->setGeometry(0,0,this->size().width()/1.1,this->size().height()/1.1 );

            for(int i=0;i<arrRelay.size();i++)
            {
                int nx = arrRelay[i]->GetPosition().x()/x;
                int ny = arrRelay[i]->GetPosition().y()/y;

                arrRelay[i]->SetPosition(nx*MainElement::GetSTEP_GRID_X1() , ny*MainElement::GetSTEP_GRID_Y1());

               arrRelay[i]->SetMinimumSize();
               arrRelay[i]->SetContact();
               arrRelay[i]->move(arrRelay[i]->GetPosition());




            }


        }
    }
this->repaint();
}




void Widget::DrawGrid(QPainter *painter)
{
    painter->setPen(Qt::SolidLine);
       painter->setPen(QColor(Qt::lightGray));

       for(int k = 0; k <= width()-1; k += MainElement::GetSTEP_GRID_X1())
           painter->drawLine(k, 0, k, height()-1);

       for(int k = 0; k <= height()-1; k += MainElement::GetSTEP_GRID_Y1())
           painter->drawLine(0, k, width()-1, k);

}


QHBoxLayout* Widget::SetWidgetBlocks()
{


    QHBoxLayout *blocks = new QHBoxLayout();

    for (int i = 0; i < arrRelay.size(); ++i)
    {
        blocks->addWidget(arrRelay[i]);
        //arrRelay[i]->SetPosCommutator(2*MainElement::GetSTEP_GRID_X1()*i, 0);
    }

        return blocks;



}

void Widget::DeleteConnectionLine()
{
    for(int i=0;i<arrRelay.size();i++)
    {
        QVector <Contacts*> tempContacts = arrRelay[i]->GetArrContacts();
        for(int j=0;j<tempContacts.size();j++)
        {
            if( tempContacts[j]->GetNeighbour()!=NULL && tempContacts[j]->GetIsChecked() )
            {

                    if(arrRelay[i]->CreateDialog())
                    {

                        tempContacts[j]->SetChecked(false);
                        tempContacts[j]->GetNeighbour()->SetChecked(false);
                        tempContacts[j]->GetNeighbour()->SetNeighbour(NULL);
                        tempContacts[j]->SetNeighbour(NULL);
                        repaint();

                    }
                    else
                    {
                        tempContacts[j]->SetChecked(false);
                        tempContacts[j]->GetNeighbour()->SetChecked(false);
                        repaint();

                    }


            }
        }


    }



}

void Widget::DrawNeighbours(QPainter* painter)
{
    for(int i=0;i<arrRelay.size();i++)
    {
        QVector <Contacts*> tempContacts = arrRelay[i]->GetArrContacts();




        for(int j=0;j<tempContacts.size();j++)
        {
            if(tempContacts[j]->GetNeighbour()!=NULL)
            {
                for(int i1=i+1;i1<arrRelay.size();i1++)
                {
                    QVector <Contacts*> tempContacts2 = arrRelay[i1]->GetArrContacts();

                    for(int j1=0;j1<tempContacts2.size();j1++)
                    {
                        if(tempContacts2[j1]->GetNeighbour()!=NULL && tempContacts2[j1]->GetNeighbour() == tempContacts[j])
                        {
                           // painter->drawLine(tempContacts[j]->GetPositionContact()+dynamic_cast<BlockRelay*>(tempContacts[j]->parent())->pos(), tempContacts2[j1]->GetPositionContact()+dynamic_cast<BlockRelay*>(tempContacts2[j1]->parent())->pos());

                            QPen pen = painter->pen();
                            pen.setColor(tempContacts[j]->GetColorContact());
                            painter->setPen(pen);



                            int xpos1 = tempContacts[j]->GetPositionContact().x()+dynamic_cast<BlockRelay*>(tempContacts[j]->parent())->pos().x();
                            int ypos1 = tempContacts[j]->GetPositionContact().y()+dynamic_cast<BlockRelay*>(tempContacts[j]->parent())->pos().y();

                            int xpos2 = tempContacts2[j1]->GetPositionContact().x()+dynamic_cast<BlockRelay*>(tempContacts2[j1]->parent())->pos().x();
                            int ypos2 = tempContacts2[j1]->GetPositionContact().y()+dynamic_cast<BlockRelay*>(tempContacts2[j1]->parent())->pos().y();


                            qDebug()<<"xpos1="<<xpos1<<endl;
                            qDebug()<<"ypos1="<<ypos1<<endl;
                            qDebug()<<"xpos2="<<xpos2<<endl;
                            qDebug()<<"ypos2="<<ypos2<<endl;


                            if(xpos1<=xpos2)
                            {
                            painter->drawLine(xpos1, ypos1, fabs((xpos1-xpos2)/2.0) + xpos1, ypos1);
                            painter->drawLine(fabs((xpos1-xpos2)/2.0) + xpos1, ypos1, fabs((xpos1-xpos2)/2.0) + xpos1, ypos2 );
                            painter->drawLine(fabs((xpos1-xpos2)/2.0) + xpos1, ypos2, xpos2, ypos2 );
                            }

                            if(xpos1>xpos2)
                            {
                            painter->drawLine(xpos1, ypos1, fabs((xpos1-xpos2)/2.0) + xpos2, ypos1);
                            painter->drawLine(fabs((xpos1-xpos2)/2.0) + xpos2, ypos1, fabs((xpos1-xpos2)/2.0) + xpos2, ypos2 );
                            painter->drawLine(fabs((xpos1-xpos2)/2.0) + xpos2, ypos2, xpos2, ypos2 );
                            }




                        }
                    }

                }
            }
        }
    }
}




Widget::~Widget()
{
    delete ui;
    for (int i = 0; i < arrRelay.size(); ++i)
    {
        delete arrRelay[i];
    }
}
