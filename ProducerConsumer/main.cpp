#include <QtCore>
#include <QtGui>

QWaitCondition isNotZero;
QWaitCondition isNotOne;


QMutex mutex;

int G_j = 0;

class Producer : public QThread
{
public:
    Producer ( QObject * parent = 0 )
        :QThread(parent)
    {
    }
    ~Producer()
    {
    }

protected:
    void run()
    {
        qDebug()<<"producer";

        for(int i = 0 ; i<3 ; i++)
        {
            msleep(2000);
            mutex.lock();
            if( G_j != 0 )
            {
                isNotZero.wait(&mutex);
            }
            mutex.unlock();

            mutex.lock();
            QString str2 = tr("生产了 ： ");
            qDebug()<<str2<<++G_j;
            isNotOne.wakeAll();
            mutex.unlock();
        }
    }
};

class Consumer : public QThread
{
public :
    Consumer(QObject * parent = 0 )
        :QThread(parent)
    {
    }
    ~Consumer()
    {
    }
protected:
    void run()
    {
        qDebug()<<"Consumer";
        for(int i = 0 ; i<3 ; i++)
        {
            msleep(2000);
            mutex.lock();
            if( G_j != 1 )
            {
                isNotOne.wait(&mutex);
            }
            mutex.unlock();

            mutex.lock();
            QString str2 = tr("消费了 ： ");
            qDebug()<<str2<<G_j--;
            isNotZero.wakeAll();
            mutex.unlock();
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    Producer t1;
    Consumer t2;

    t1.start();
    t2.start();

    t1.wait();
    t2.wait();

    return 0;
}
