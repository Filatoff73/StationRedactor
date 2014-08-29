#include "contacts.h"
#include <QSizePolicy>

#include <QScrollArea>
#include <widget.h>

Contacts::Contacts(QWidget* parent) : QWidget(parent)
{
    idContact=0;
    num=0;
    labelContact = "0";
    positionContact.setX(0);
    positionContact.setY(0);
    colorContact=Qt::black;
    isChecked=false;

    neighbourContact=NULL;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    SetMinimumSizeContatct();



}

void Contacts::SetMinimumSizeContatct()
{
    r = MainElement::GetSTEP_GRID_X1()/8;
    setMinimumSize(2.0*r+0.1, 2.0*r+0.1);
    setMaximumSize(2.0*r+0.1, 2.0*r+0.1);

}

 void Contacts::MoveContacts()
 {
     if(contactOrientation==Left)
     {

         move(positionContact.x(), positionContact.y()-r/2.0);

     }

     if(contactOrientation==Bottom)
     {
         move(positionContact.x()-r/2.0, positionContact.y()-r);

     }

     if(contactOrientation==Right)
     {
         move(positionContact.x()-r, positionContact.y()-r/2.0);

     }

     if(contactOrientation==Top)
     {
         move(positionContact.x()-r/2.0, positionContact.y());

     }
 }

void Contacts::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);
    painter->setPen(colorContact);
    painter->drawEllipse(0,0, r, r);
    MoveContacts();




    painter->end();

}

void Contacts::mousePressEvent(QMouseEvent* mouseEvent)
{

 if (mouseEvent->buttons() == Qt::LeftButton)
     {
        //если у контакта нет соседей
        if( neighbourContact==NULL )
        {
            if(!isChecked)
                SetChecked(true);
            else
                SetChecked(false);


            int a=dynamic_cast<Widget*>(this->parent()->parent())->GetDrawContactLine();
            a++;
            if(a==1) //Начало отрисовки контакта
                dynamic_cast<Widget*>(this->parent()->parent())->SetBeginDrawContact(this);
            if(a==2) //Есть возможность отрисовки контакта
               {
                    dynamic_cast<Widget*>(this->parent()->parent())->SetEndDrawContact(this);
               }

            dynamic_cast<Widget*>(this->parent()->parent())->SetDrawContactLine(a);
        }

        else //если есть соседи, выделить контакт
            if(neighbourContact!=NULL && neighbourContact->GetNeighbour()!=NULL )
            {
                if(!isChecked || !neighbourContact->GetIsChecked())
                {
                    this->SetChecked(true);
                    neighbourContact->SetChecked(true);
                }
                else
                    {
                        neighbourContact->SetChecked(false);
                        this->SetChecked(false);

                    }
            }

    }
}
