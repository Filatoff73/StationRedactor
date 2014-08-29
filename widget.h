#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include "blockrelay.h"
#include "mainelement.h"
#include <QObject>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent (QMouseEvent* mouseEvent);
      void mousePressEvent(QMouseEvent* mouseEvent);
      void mouseReleaseEvent(QMouseEvent* mouseEvent);
       void wheelEvent(QWheelEvent* event);

    void DrawGrid(QPainter *painter);
    QHBoxLayout* SetWidgetBlocks();

    void DrawNeighbours(QPainter* painter);

    int GetDrawContactLine()
    {
        return drawContactLine;
    }

    void SetDrawContactLine(int a)
    {
        drawContactLine=a;
    }



    void SetBeginDrawContact(Contacts* a1)
    {
        beginContact=a1;
    }

    void SetEndDrawContact(Contacts* a1)
    {
        endContact=a1;
    }

    void DeleteConnectionLine();
    void AddBlockElement();


    ~Widget();

private:
    Ui::Widget *ui;

    int nElement;
    int drawContactLine;
    Contacts* beginContact;
    Contacts* endContact;

    QVector <MainElement*> arrRelay;


};

#endif // WIDGET_H
