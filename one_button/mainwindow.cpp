#include "mainwindow.h"

#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    checkServerButton(new QPushButton("Проверить сервер", this)),
    statusLabel(new QLabel("Нажмите кнопку для проверки", this)),
    networkManager(new QNetworkAccessManager(this))
{
    // Создаем вертикальный лэйаут и добавляем виджеты
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(checkServerButton);
    layout->addWidget(statusLabel);

    // Создаем центральный виджет и устанавливаем лэйаут на него
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключаем сигналы
    connect(checkServerButton, &QPushButton::clicked, this, &MainWindow::on_checkServerButton_clicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onReplyFinished);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_checkServerButton_clicked()
{
    // Устанавливаем URL на наш локальный сервер
    QUrl url("http://localhost:8080");
    QNetworkRequest request(url);

    // Отправляем GET-запрос на сервер
    networkManager->get(request);

    // Обновляем текст статуса, чтобы показать, что идет проверка
    statusLabel->setText("Проверяем сервер...");
}

void MainWindow::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Если ошибок нет, сервер ответил успешно
        statusLabel->setText("Сервер работает");
    } else {
        // В случае ошибки выводим сообщение о недоступности сервера
        statusLabel->setText("Сервер не отвечает");
    }

    // Очищаем ответ, чтобы избежать утечек памяти
    reply->deleteLater();
}
