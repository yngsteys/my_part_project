#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkServerButton_clicked();      // Обработчик нажатия кнопки
    void onReplyFinished(QNetworkReply* reply); // Обработчик ответа от сервера

private:
    QPushButton *checkServerButton;
    QLabel *statusLabel;
    QNetworkAccessManager *networkManager;
};
#endif // MAINWINDOW_H
