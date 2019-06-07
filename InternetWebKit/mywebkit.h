#ifndef MYWEBKIT_H
#define MYWEBKIT_H

#include <QtGui>
#include <QtWebKit>

class MyWebKit : public QWidget
{
    Q_OBJECT

public:
    MyWebKit(QWidget *parent = 0);
    ~MyWebKit();
private slots:
    void slotLoadUrl();
    void slotLoadStarted();//���ؿ�ʼ
    void slotLoadFinished(bool);//���ؽ���
    void slotLoadProgress(int);
    void slotUrlChanged(QUrl);//URL��ͳһ��Դ��־�ı�
    void slotLinkClicked(QUrl);//����������Ӹı�
private:
    QWebView *webView; //�ṩһ��������������ͱ༭��ҳ
    QLineEdit *lineEdit;//���ı��༭��
    QVBoxLayout *layout;//��ֱ���ڲ���
    QProgressBar *progressBar;//ˮƽ��ֱ������

};

#endif // MYWEBKIT_H
