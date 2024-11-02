#include "mainwindow.h"

#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    checkServerButton(new QPushButton("Проверить сервер", this)),
    sendMatrixButton(new QPushButton("Отправить матрицу", this)),
    statusLabel(new QLabel("Нажмите кнопку для проверки", this)),

    lMatrixLabel(new QLabel("Матрица L:", this)),
    uMatrixLabel(new QLabel("Матрица U:", this)),
    pMatrixLabel(new QLabel("Матрица P:", this)),

    networkManager(new QNetworkAccessManager(this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(checkServerButton);
    layout->addWidget(sendMatrixButton);
    layout->addWidget(statusLabel);
    layout->addWidget(lMatrixLabel);
    layout->addWidget(uMatrixLabel);
    layout->addWidget(pMatrixLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(checkServerButton, &QPushButton::clicked, this, &MainWindow::on_checkServerButton_clicked);
    connect(sendMatrixButton, &QPushButton::clicked, this, &MainWindow::on_sendMatrixButton_clicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onReplyFinished);
}

MainWindow::~MainWindow()
{
    // Здесь можно добавить очистку ресурсов, если нужно
}

void MainWindow::on_checkServerButton_clicked()
{
    QUrl url("http://localhost:8080");
    QNetworkRequest request(url);
    networkManager->get(request);
    statusLabel->setText("Проверяем сервер...");
}

void MainWindow::on_sendMatrixButton_clicked()
{
    QUrl url("http://localhost:5001/lu_decomposition");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonArray matrix;
    matrix.append(QJsonArray{1, 2, 3});
    matrix.append(QJsonArray{4, 5, 6});
    matrix.append(QJsonArray{7, 8, 9});

    QJsonObject json;
    json["matrix"] = matrix;
    QJsonDocument doc(json);

    networkManager->post(request, doc.toJson());
    statusLabel->setText("Отправляем матрицу...");
}

void MainWindow::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject json = doc.object();

        QJsonArray L = json["L"].toArray();
        QJsonArray U = json["U"].toArray();
        QJsonArray P = json["P"].toArray();

        // Преобразуем матрицы L, U, P в строки для отображения
        lMatrixLabel->setText("Матрица L:\n" + matrixToString(L));
        uMatrixLabel->setText("Матрица U:\n" + matrixToString(U));
        pMatrixLabel->setText("Матрица P:\n" + matrixToString(P));

        statusLabel->setText("Сервер работает");
    } else {
        statusLabel->setText("Ошибка соединения");
    }
    reply->deleteLater();
}

// Вспомогательная функция для преобразования JSON массива в строку
QString MainWindow::matrixToString(const QJsonArray &matrix)
{
    QString result;
    for (const auto &row : matrix) {
        QJsonArray rowArray = row.toArray();
        QString rowString;
        for (const auto &value : rowArray) {
            rowString += QString::number(value.toDouble()) + " ";
        }
        result += rowString.trimmed() + "\n";
    }
    return result.trimmed();
}
