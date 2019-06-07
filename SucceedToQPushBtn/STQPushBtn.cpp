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
    //���������ϣ������ֲ�����͸��Ч����
   // QPushButton::paintEvent(event);

    QPainter painter(this);

    if(m_Frame == "frame")
    {
        //����ť��ӱ߿�
        QPen pen(Qt::SolidLine);
        QFont font3("ZYsong18030",24);
        font3.setBold(true);
        pen.setColor(Qt::red);
        painter.setFont(font3);
        painter.setPen(pen);

        painter.drawRect(0,0,150,46);
    }



    //void QPainter::drawPixmap ( int x, int y, int w, int h, const QPixmap & pixmap, int sx, int sy, int sw, int sh )
    //x y ָ���������ĸ��ؼ������Ͻ�
    //sx syָ������ͼƬ�����Ͻ�
    //

    //����ť��ͼ
    painter.drawPixmap(2,2,pixmap,0,0,-1,-1);

    //����ťд��
    QFont font2("lyl",18);
    font2.setBold(true);
    painter.setFont(font2);
    painter.setPen(QColor(64,0,64));

    painter.drawText(rect(),Qt::AlignRight | Qt::AlignCenter,tr("��һ��"));

    //����ĵ�����ʾ��Ϊ�գ���ô����ʾ��ʾ����
    if(m_tip != "")
    {
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        //������
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
    //����ط�ΪʲôҪ��������������ҵ������йأ�
    return QRectF(22,24,31,33);

}

