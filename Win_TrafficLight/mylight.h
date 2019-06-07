#ifndef MYLIGHT_H
#define MYLIGHT_H

#include <QtGui>

const int G_w = 100;
const int G_h = 100;

const int G_r = 50;

class MyLight : public 	QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY (QColor color READ GetColor WRITE SetColor)
public:
    MyLight( QGraphicsItem * parent = 0 );
    ~MyLight();
//灯的颜色
    QColor GetColor() const
    {
        return m_color;

    }

    void SetColor (QColor color)
    {
        if (m_color == color)
        {  //qDebug()<<"lsy";
            return ;
        }
        //qDebug()<<"rhz";
        m_color = color;

    }

   //重写虚函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:
    QColor m_color;

};



class MyView : public QGraphicsView
{
public:
    MyView( QGraphicsScene * scene, QWidget * parent = 0 );
    ~MyView();

protected:
    void resizeEvent ( QResizeEvent * event );
};


#endif // MYLIGHT_H
