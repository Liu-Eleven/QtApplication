#include "STQPushBtn.h"

SucceedTOQPB::SucceedTOQPB(QWidget *parent)
    : QPushButton(parent)
{
    qDebug()<<"outside";
    //this->setAutoRepeat(true);
    //this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    m_Frame = "";
    m_tip = "";


}

SucceedTOQPB::~SucceedTOQPB()
{

}


void SucceedTOQPB::paintEvent(QPaintEvent *)
{
  //  qDebug()<<"paintEvent";

    QPixmap pixmap(":/images/net.bmp");
    //下面这句加上，就体现不出来透明效果了
   // QPushButton::paintEvent(event);

    QPainter painter(this);

    if(m_Frame == "frame")
    {
        //给按钮添加边框
        QPen pen(Qt::SolidLine);
        QFont font3("ZYsong18030",24);
        font3.setBold(true);
        pen.setColor(Qt::red);
        painter.setFont(font3);
        painter.setPen(pen);

        painter.drawRect(0,0,150,46);
    }



    //void QPainter::drawPixmap ( int x, int y, int w, int h, const QPixmap & pixmap, int sx, int sy, int sw, int sh )
    //x y 指定绘制在哪个控件的左上角
    //sx sy指定绘制图片的左上角
    //

    //给按钮贴图
    painter.drawPixmap(2,2,pixmap,0,0,-1,-1);

    //给按钮写字
    QFont font2("lyl",18);
    font2.setBold(true);
    painter.setFont(font2);
    painter.setPen(QColor(64,0,64));

    painter.drawText(rect(),Qt::AlignRight | Qt::AlignCenter,tr("捞一捞"));

    //如果的到的提示不为空，那么把提示显示出来
    if(m_tip != "")
    {
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        //画矩形
        painter.setBrush(Qt::blue);
        painter.drawRect(55,3,18,18);

        QFont font("ZYsong18030",11);
        //font.setPointSize(11);
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(QColor(255,255,255));
        painter.drawText(56,3,18,18,Qt::AlignCenter,GetTip());
    }

    return;
}

void SucceedTOQPB::enterEvent(QEvent *)
{
   // qDebug()<<"come in";
    SetFrame("frame");

}

void SucceedTOQPB::leaveEvent ( QEvent * )
{
   // qDebug()<<"leave out";
    SetFrame("");
}
QRectF SucceedTOQPB::boundingRect() const
{
    //这个地方为什么要传这个参数？跟我的恋爱有关！
    return QRectF(22,24,31,33);

}

