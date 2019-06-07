#include "mywebkit.h"

MyWebKit::MyWebKit(QWidget *parent)
    : QWidget(parent)
{
    webView =new QWebView(this);
    lineEdit = new QLineEdit(this);
    layout = new QVBoxLayout(this);
    progressBar = new QProgressBar(this);

    layout->addWidget(lineEdit);
    layout->addWidget(webView);
    layout->addWidget(progressBar);
    setLayout(layout);

    progressBar->reset();//����������
    progressBar->setMaximum(100);//���������ֵΪ100
    webView->load(QUrl("http://www.baidu.com"));//����ٶ���ҳ
    lineEdit->setText("http://www.baidu.com");

    //�������Ӵ���Ȩ��Ϊ�������ӣ����������ҳ�����ݾͿ������ӵ������ݵ���ҳ
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //SIGNAL(returnPressed()),�ǵ����ǰ���ַ�ڱ༭��������ɣ��س��ź�
    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(slotLoadUrl()));
    //SIGNAL(loadStarted())����ҳ��ʼ�����ź�
    connect(webView,SIGNAL(loadStarted()),this,SLOT(slotLoadStarted()));
    //SIGNAL(loadFinished(bool))����ҳ���ؽ����ź�
    connect(webView,SIGNAL(loadFinished(bool)),this,SLOT(slotLoadFinished(bool)));
    //SIGNAL(loadProgress(int))���������ź�
    connect(webView,SIGNAL(loadProgress(int)),this,SLOT(slotLoadProgress(int)));
    //SIGNAL(linkClicked(QUrl))��������ҳ���ݽ��������ź�
    connect(webView,SIGNAL(linkClicked(QUrl)),this,SLOT(slotLinkClicked(QUrl)));


}

MyWebKit::~MyWebKit()
{

}

void MyWebKit::slotLoadUrl()
{
    qDebug()<<tr("��ȡ�༭�����ݵ�ַ");
    //��ȡ�����б༭���ݵ�ַ��ҳ
    webView->load(lineEdit->text());
}
void MyWebKit::slotLoadStarted()
{
    qDebug()<<tr("��ʼ����");
    setWindowTitle(tr("��ʼ����"));
}

void MyWebKit::slotLoadFinished(bool flag)
{
    qDebug()<<tr("�������");
    flag ? setWindowTitle(tr("�������!")) : setWindowTitle(tr("����ʧ�ܣ�"));
}
void MyWebKit::slotLoadProgress(int value)
{
    qDebug()<<tr("��������ֵ");
    //��������ֵ
    progressBar->setValue(value);

}
void MyWebKit::slotUrlChanged(QUrl url)
{
    qDebug()<<tr("��ַ�ı�");
    lineEdit->setText(url.toString());

}
void MyWebKit::slotLinkClicked(QUrl url)
{
    qDebug()<<tr("������ַ");
    //�����ı���������Ϊ��ǰ������ݵ���ַ
    lineEdit->setText(url.toString());
    //���ظ���ҳ
    webView->load(url);

}
