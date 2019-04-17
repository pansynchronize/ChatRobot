#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QTextEdit>
#include <QMessageBox>

class TextEdit : public QTextEdit{
    Q_OBJECT
public:
    TextEdit(QWidget* parent=nullptr);
    void keyPressEvent(QKeyEvent *e) override;
signals:
    void key_enter_pressed();
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QNetworkAccessManager* manager;
    QNetworkRequest request;
    QJsonDocument doc;
    TextEdit* textedit;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
