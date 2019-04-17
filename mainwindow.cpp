#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textedit = new TextEdit;
    ui->verticalLayout_2->addWidget(textedit);
    ui->verticalLayout_2->setStretch(0, 4);
    ui->verticalLayout_2->setStretch(1, 1);
    manager = new QNetworkAccessManager();
    connect(textedit, &TextEdit::key_enter_pressed, this, &MainWindow::on_pushButton_clicked);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply){
        ui->statusBar->showMessage("");
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
        QString answer = reply->readAll();
        doc = QJsonDocument::fromJson(answer.toUtf8());
        QJsonObject job = doc.object();
        answer = job["content"].toString();
        QStringList lines;
        lines = answer.split("{br}");
        answer = lines.join("<br/>");
        ui->textBrowser->setHtml(answer);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage(tr("Sending..."));
    QString keyword;
    keyword = textedit->toPlainText();
    textedit->clear();
    request.setUrl(QUrl("http://api.qingyunke.com/api.php?key=free&appid=0&msg="+keyword));
    manager->get(request);
}

TextEdit::TextEdit(QWidget *parent): QTextEdit(parent)
{

}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return){
        emit key_enter_pressed();
    }else {
        QTextEdit::keyPressEvent(e);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("Author: Pan\nAPI: <https://www.sojson.com/api/semantic.html"));
}
