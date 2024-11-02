#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkServerButton_clicked();   // Слот для проверки сервера
    void on_sendMatrixButton_clicked();    // Слот для отправки матрицы
    void onReplyFinished(QNetworkReply* reply); // Слот для обработки ответа от сервера

private:
    QPushButton *checkServerButton;  // Кнопка для проверки сервера
    QPushButton *sendMatrixButton;   // Кнопка для отправки матрицы
    QLabel *statusLabel;             // Метка для отображения статуса
    QLabel *lMatrixLabel;            // Метка для отображения матрицы L
    QLabel *uMatrixLabel;            // Метка для отображения матрицы U
    QLabel *pMatrixLabel;            // Метка для отображения матрицы P
    QNetworkAccessManager *networkManager; // Менеджер сетевых запросов

    QString matrixToString(const QJsonArray &matrix); // Объявляем функцию для преобразования матрицы в строку
};

#endif // MAINWINDOW_H
