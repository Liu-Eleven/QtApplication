#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui>

class SucceedTOQPB : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY (QString frame READ GetFrame WRITE SetFrame)
    Q_PROPERTY (QString tip READ GetTip WRITE SetTip)

public:
    SucceedTOQPB(QWidget *parent = 0);
    ~SucceedTOQPB();

    QString GetFrame()
    {
        return m_Frame;
    }

    void SetFrame(QString str)
    {
        m_Frame = str;
    }

    QString GetTip()
    {
        return m_tip;
    }

    void SetTip(QString strTip)
    {
        m_tip = strTip;
    }

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);

    void leaveEvent ( QEvent * event );

    QRectF boundingRect() const;

private:
    QString m_Frame;
    QString m_tip;

};

#endif // WIDGET_H
