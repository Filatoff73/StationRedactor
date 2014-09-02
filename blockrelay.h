#ifndef BLOCKRELAY_H
#define BLOCKRELAY_H
#include "mainelement.h"
#include "contacts.h"
#include <QString>
#include <QList>
#include <QRadioButton>

class BlockRelay : public MainElement
{
public:
    BlockRelay(int id, QWidget *parent = 0);
    ~BlockRelay();

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent (QMouseEvent* mouseEvent);
      void mousePressEvent(QMouseEvent* mouseEvent);
      void mouseReleaseEvent(QMouseEvent* mouseEvent);

      //Прорисовка геометрии блока
      void DrawBlock(QPainter*& painter);

      //привязка к сетке
      void SetToGrid(int x1,int y1);

      virtual QPoint GetPosition()
      {
          return positionBlock;
      }

      virtual void SetPosition(int x, int y)
      {
          positionBlock.setX(x);
          positionBlock.setY(y);
      }

      virtual void SetMinimumSize();


      int GetNcontacts()
      {
          return nContacts;
      }

      virtual QVector<Contacts*>& GetArrContacts()
      {
          return arrContacts;
      }

      void SetContact();

      void ChangeNumberContacts();


private:
    QString nameBlock;
    int idBlock;
    QPoint positionBlock;
    QPoint beginPositionBlock;
    bool is_dragged; //Режим движения
    int nContactsLeft;
    int nContactsRight;
    int nContactsUp;
    int nContactsDown;
    int nContacts;

    bool isMirrorGorizontal;
    bool isMirrorVertical;

    int sizeX, sizeY;//размеры (в клетках) релейного блока

    int rotateAngle;
    QVector <Contacts*> arrContacts;

private slots:
    void ShowContextMenu(const QPoint&);



};

#endif // BLOCKRELAY_H
