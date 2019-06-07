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

    progressBar->reset();//进度条清零
    progressBar->setMaximum(100);//进度条最大值为100
    webView->load(QUrl("http://www.baidu.com"));//进入百度网页
    lineEdit->setText("http://www.baidu.com");

    //设置连接代理权限为所有连接，这样点击网页的内容就可以连接到该内容的网页
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //SIGNAL(returnPressed()),是当我们把网址在编辑行输入完成，回车信号
    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(slotLoadUrl()));
    //SIGNAL(loadStarted())，网页开始下载信号
    connect(webView,SIGNAL(loadStarted()),this,SLOT(slotLoadStarted()));
    //SIGNAL(loadFinished(bool))，网页下载结束信号
    connect(webView,SIGNAL(loadFinished(bool)),this,SLOT(slotLoadFinished(bool)));
    //SIGNAL(loadProgress(int))，进度条信号
    connect(webView,SIGNAL(loadProgress(int)),this,SLOT(slotLoadProgress(int)));
    //SIGNAL(linkClicked(QUrl))，单击网页内容进行连接信号
    connect(webView,SIGNAL(linkClicked(QUrl)),this,SLOT(slotLinkClicked(QUrl)));


}

MyWebKit::~MyWebKit()
{

}

void MyWebKit::slotLoadUrl()
{
    qDebug()<<tr("获取编辑框内容地址");
    //获取下载行编辑内容地址网页
    webView->load(lineEdit->text());
}
void MyWebKit::slotLoadStarted()
{
    qDebug()<<tr("开始下载");
    setWindowTitle(tr("开始下载"));
}

void MyWebKit::slotLoadFinished(bool flag)
{
    qDebug()<<tr("加载完毕");
    flag ? setWindowTitle(tr("加载完毕!")) : setWindowTitle(tr("加载失败！"));
}
void MyWebKit::slotLoadProgress(int value)
{
    qDebug()<<tr("进度条的值");
    //进度条的值
    progressBar->setValue(value);

}
void MyWebKit::slotUrlChanged(QUrl url)
{
    qDebug()<<tr("网址改变");
    lineEdit->setText(url.toString());

}
void MyWebKit::slotLinkClicked(QUrl url)
{
    qDebug()<<tr("单击网址");
    //把行文本的内容设为当前点击内容的网址
    lineEdit->setText(url.toString());
    //下载该网页
    webView->load(url);

}
