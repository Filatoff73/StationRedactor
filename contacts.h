#ifndef CONTACTS_H
#define CONTACTS_H
#include "QWidget"
#include <QColor>

enum Orientation
{
   Left,
   Bottom,
   Right,
   Top
};




class Contacts : public QWidget
{
public:
    Contacts(QWidget* parent=0);

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* mouseEvent);

    void SetPositionContact(QPoint& a)
    {
        positionContact=a;
    }

     QPoint GetPositionContact()
    {
        return positionContact;
    }

    void SetNeighbour(Contacts* neighbour)
    {
        neighbourContact = neighbour;
    }

    Contacts* GetNeighbour()
    {
        return neighbourContact;
    }

    int GetNumContact()
    {
        return num;
    }

    int GetIdContact()
    {
        return idContact;
    }

    void SetIdContact(int a)
    {
        idContact=a;
    }

    QColor& GetColorContact()
    {
        return colorContact;
    }

    void SetColorContact(QColor a)
    {
        colorContact=a;
    }

    void SetChecked(bool a)
    {
        if(a==true)
        {
            isChecked=true;
            colorContact = Qt::red;
        }
        if(a==false)
        {
            isChecked=false;
            colorContact = Qt::black;
        }
    }

    bool GetIsChecked()
    {
        return isChecked;
    }

    void SetOrientation(Orientation a)
    {
        contactOrientation=a;
    }

    Orientation Getorientation()
    {
        return contactOrientation;
    }

    void MoveContacts();

    void SetMinimumSizeContatct();

    ~Contacts();


private:
    int idContact;
    int num;
    QString labelContact;
    QPoint positionContact;
    QColor colorContact;
    bool isChecked;
    Contacts* neighbourContact;
    Orientation contactOrientation;
    float r;
};

#endif // CONTACTS_H
