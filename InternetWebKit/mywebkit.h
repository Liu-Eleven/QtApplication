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
    void slotLoadStarted();//下载开始
    void slotLoadFinished(bool);//下载结束
    void slotLoadProgress(int);
    void slotUrlChanged(QUrl);//URL的统一资源标志改变
    void slotLinkClicked(QUrl);//所点击的连接改变
private:
    QWebView *webView; //提供一个窗口用来浏览和编辑网页
    QLineEdit *lineEdit;//行文本编辑器
    QVBoxLayout *layout;//垂直窗口布局
    QProgressBar *progressBar;//水平或垂直进度条

};

#endif // MYWEBKIT_H
