#ifndef MAINELEMENT_H
#define MAINELEMENT_H

#include <QWidget>
#include <QObject>
#include <math.h>
#include <QMouseEvent>
#include <QPainter>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <contacts.h>
#include <QFont>




class MainElement : public QWidget
{
    Q_OBJECT
public:
    explicit MainElement(QWidget *parent = 0);
    virtual ~MainElement();

    static void InitConstans();
    //уменьшает или увеливает сетку в scale раз в зависимости от знака
    bool SetScale(float scale);

    virtual QPoint GetPosition()=0;

    virtual void SetPosition(int x, int y)=0;

    virtual void SetMinimumSize()=0;

    virtual void SetContact()=0;

    virtual QVector<Contacts*>& GetArrContacts()=0;
    //Создает да\нет диалог
    bool CreateDialog();

    static int GetSTEP_GRID_X1(void)
    {
        return STEP_GRID_X1;
    }
    static int GetSTEP_GRID_Y1(void)
    {
        return STEP_GRID_Y1;
    }

    static QFont GetFont()
    {
        return font;
    }


private:

static int STEP_GRID_X1;
static int STEP_GRID_Y1;
bool resultDialog;
static QFont font;
QDialog* question;

private slots:
void YesFunc();
void NoFunc();

};

#endif // MAINELEMENT_H
