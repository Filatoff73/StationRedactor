#include "blockrelay.h"
#include <QSizePolicy>
#include <QDebug>
#include <QDialog>
#include <widget.h>
#include <mainwindow.h>
#include <QTextItem>
#include <QPaintEngine>
#include <QFont>
#include <QMenu>



BlockRelay::BlockRelay(int id, QWidget *parent) : MainElement(parent)
{
    nameBlock = "BlockRelay";
    idBlock=id;
    isMirrorGorizontal=false;
    isMirrorVertical=false;

    positionBlock.setX(0);
    positionBlock.setY(0);

    beginPositionBlock.setX(0);
    beginPositionBlock.setY(0);

     nContactsLeft=1;
     nContactsRight=2;
     nContactsUp=3;
     nContactsDown=4;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=3;
     sizeY=3;

    for(int i=0;i<nContacts;i++)
    {
        arrContacts.append(new Contacts(this));
        arrContacts[i]->show();
    }

    is_dragged=false;
    rotateAngle=0;

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    SetMinimumSize();


}

void BlockRelay::ShowContextMenu(const QPoint& pos)
{
    QPoint globalPos = mapToGlobal(pos);

        QMenu myMenu;
        myMenu.addAction("Отразить по вертикали");
        myMenu.addAction("Отразить по горизонтали");
        myMenu.addAction("Удалить элемент");

        QAction* selectedItem = myMenu.exec(globalPos);
        if (selectedItem)
        {
            QString txt = selectedItem->text();

            if(!txt.compare("Отразить по вертикали"))
            {
                isMirrorVertical=!isMirrorVertical;
                int temp;
                temp = nContactsLeft;
                nContactsLeft=nContactsRight;
                nContactsRight=temp;
                SetContact();
                dynamic_cast<Widget*>(this->parent())->repaint();
            }

            if(!txt.compare("Отразить по горизонтали"))
            {
                isMirrorGorizontal=!isMirrorGorizontal;
                int temp;
                temp = nContactsUp;
                nContactsUp=nContactsDown;
                nContactsDown=temp;
                SetContact();
                dynamic_cast<Widget*>(this->parent())->repaint();

            }

            if(!txt.compare("Удалить элемент"))
            {
                dynamic_cast<Widget*>(this->parent())->DeleteElement(this);
            }

        }



}




void BlockRelay::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter (this);
    QPen pen(Qt::black, 1, Qt::SolidLine);

    painter->setPen(pen);


    painter->save();
    painter->translate(sizeX*GetSTEP_GRID_X1()/2,GetSTEP_GRID_Y1()*sizeY/2);
    if(isMirrorGorizontal)
    {
        QTransform t = painter->worldTransform();
        t.rotate(180, Qt::XAxis);
        painter->setTransform(t);

    }
    if(isMirrorVertical)
    {
        QTransform t = painter->worldTransform();
        t.rotate(180, Qt::YAxis);
        painter->setTransform(t);

    }

    painter->translate(-sizeX*GetSTEP_GRID_X1()/2.0,-GetSTEP_GRID_Y1()*sizeY/2.0);


    DrawBlock(painter);

     //Возврат к исходной системе координат
     painter->restore();

     move(positionBlock);
     painter->end();
     delete painter;

}


void BlockRelay::mouseMoveEvent (QMouseEvent* mouseEvent)
{
    if(is_dragged)
    {
    QPoint q;

    q.setX(mouseEvent->globalPos().x() - beginPositionBlock.x());

    q.setY(mouseEvent->globalPos().y() - beginPositionBlock.y());

    q.setX(CheckToBorderWidth(q.x()));
    q.setY(CheckToBorderHeight(q.y()));

    positionBlock.setX(q.x());
    positionBlock.setY(q.y());

    move(positionBlock);


    dynamic_cast<Widget*>(this->parent())->repaint();


    }

}

void BlockRelay::mousePressEvent(QMouseEvent* mouseEvent)
{

    if (mouseEvent->buttons() == Qt::LeftButton)
        {
                is_dragged=true;
                beginPositionBlock.setX(mouseEvent->globalPos().x() - this->pos().x());
                beginPositionBlock.setY(mouseEvent->globalPos().y() - this->pos().y());           
        }

}

void BlockRelay::mouseReleaseEvent(QMouseEvent* mouseEvent)
{


    //Привязка к сетке после движения
    if(is_dragged)
    {
    int x1,y1;
    x1=mouseEvent->globalPos().x() - beginPositionBlock.x();
    y1=mouseEvent->globalPos().y() - beginPositionBlock.y();

    SetToGrid(x1,y1);
    is_dragged=false;
    }

    dynamic_cast<Widget*>(this->parent())->repaint();
}


void BlockRelay::SetToGrid(int x1,int y1)
{
    QPoint q;

    x1 = CheckToBorderWidth(x1);
    y1 = CheckToBorderHeight(y1);

    if(x1%GetSTEP_GRID_X1() <= GetSTEP_GRID_X1()/2)
        q.setX(x1 - x1%GetSTEP_GRID_X1());

    if(y1%GetSTEP_GRID_Y1() <= GetSTEP_GRID_Y1()/2)
        q.setY(y1 - y1%GetSTEP_GRID_Y1());


    if(x1%GetSTEP_GRID_X1() > GetSTEP_GRID_X1()/2)
        q.setX(x1 + (GetSTEP_GRID_X1() - x1%GetSTEP_GRID_X1()) );

    if(y1%GetSTEP_GRID_Y1() > GetSTEP_GRID_Y1()/2)
        q.setY(y1 + (GetSTEP_GRID_Y1() - y1%GetSTEP_GRID_Y1()));




    positionBlock.setX(q.x());


    positionBlock.setY(q.y());




        move(positionBlock);



}

void BlockRelay::SetMinimumSize()
{
    setMinimumSize((sizeX+0.5)*GetSTEP_GRID_X1(), (sizeY+0.5)*GetSTEP_GRID_Y1());
    setMaximumSize((sizeX+0.5)*GetSTEP_GRID_X1(), (sizeY+0.5)*GetSTEP_GRID_Y1());
}

void BlockRelay::DrawBlock(QPainter*& painter)
{
    painter->drawRect(0.1*GetSTEP_GRID_X1(), 0.1*GetSTEP_GRID_Y1(), (sizeX-0.2)*GetSTEP_GRID_X1(), (sizeY-0.2)*GetSTEP_GRID_Y1() );

    //QFont font = &GetFont();
    painter->setFont(GetFont());

    painter->drawText(this->size().height()/2, this->size().width()/2, nameBlock);

    SetContact();

}

void BlockRelay::SetContact()
{
    int k=0;
    for(int i=0;i<nContactsLeft;++i)
    {
            float interval = sizeY/(nContactsLeft+1.0);
            QPoint q;
            q.setX(0);
            q.setY(i*interval*GetSTEP_GRID_Y1()+interval*GetSTEP_GRID_Y1());
            arrContacts[k]->SetPositionContact(q);
            arrContacts[k]->SetOrientation(Left);
            arrContacts[k]->SetMinimumSizeContatct();
            arrContacts[k]->MoveContacts();


            k++;

    }


    for(int i=0;i<nContactsDown;++i)
    {
             float interval = (sizeX-1.0)/(nContactsDown+1.0);

           // painter->drawLine(i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1(), sizeY*GetSTEP_GRID_Y1() ,i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1() , (sizeY-0.5)*GetSTEP_GRID_Y1());

            QPoint q;
            q.setX(i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1());
            q.setY(sizeY*GetSTEP_GRID_Y1());
            arrContacts[k]->SetPositionContact(q);
            arrContacts[k]->SetOrientation(Bottom);
            arrContacts[k]->SetMinimumSizeContatct();
            arrContacts[k]->MoveContacts();

            k++;
    }

    for(int i=0;i<nContactsRight;++i)
    {
            float interval = sizeY/(nContactsRight+1.0);

           // painter->drawLine((sizeX-0.5)*GetSTEP_GRID_X1(), i*interval*GetSTEP_GRID_Y1()+interval*GetSTEP_GRID_Y1(), sizeX*GetSTEP_GRID_X1(), i*interval*GetSTEP_GRID_Y1()+interval*GetSTEP_GRID_Y1());

            QPoint q;
            q.setX(sizeX*GetSTEP_GRID_X1());
            q.setY(i*interval*GetSTEP_GRID_Y1()+interval*GetSTEP_GRID_Y1());
            arrContacts[k]->SetPositionContact(q);
            arrContacts[k]->SetOrientation(Right);
            arrContacts[k]->SetMinimumSizeContatct();
            arrContacts[k]->MoveContacts();


            k++;


    }

    for(int i=0;i<nContactsUp;++i)
    {
             float interval = (sizeX-1.0)/(nContactsUp+1.0);

            //painter->drawLine(i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1(), 0 ,i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1() , 0.5*GetSTEP_GRID_Y1());

            QPoint q;
            q.setX(i*interval*GetSTEP_GRID_X1()+interval*GetSTEP_GRID_X1() + 0.5*GetSTEP_GRID_X1());
            q.setY(0);
            arrContacts[k]->SetPositionContact(q);
            arrContacts[k]->SetOrientation(Top);
            arrContacts[k]->SetMinimumSizeContatct();
            arrContacts[k]->MoveContacts();


            k++;
    }



}


BlockRelay::~BlockRelay()
{
    for(int i=0;i<arrContacts.size();i++)
    {
        delete arrContacts[i];
    }
}

