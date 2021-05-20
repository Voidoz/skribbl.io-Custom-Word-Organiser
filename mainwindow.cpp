#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QClipboard>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this, SLOT(open()));
    new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this, SLOT(save()));
    new QShortcut(QKeySequence(tr("Ctrl+C", "Copy Words")), this, SLOT(copy()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(QString fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream output(&file);
        QStringList data = output.readLine().split(',');
        ui->wordList->clear();
        foreach (QString item, data)
            ui->wordList->addItem(item);
        file.close();
    }
}

void MainWindow::save()
{
    if (currentFile.fileName() == "")
    {
        saveAs();
    } else
    {
        QStringList listContent;
        foreach( QListWidgetItem *item, ui->wordList->findItems("*", Qt::MatchWildcard) )
            listContent.append(item->text());

        currentFile.open(QIODevice::WriteOnly);
        currentFile.write(listContent.join(',').toUtf8());
        currentFile.close();
    }
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Skribbl.io Custom Words File"), QStandardPaths::locate(QStandardPaths::DesktopLocation, "", QStandardPaths::LocateDirectory), tr("Skribbl.io Custom Word File (*.skribbl)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);

        QStringList listContent;
        foreach( QListWidgetItem *item, ui->wordList->findItems("*", Qt::MatchWildcard) )
            listContent.append(item->text());

        file.open(QIODevice::WriteOnly);
        file.write(listContent.join(',').toUtf8());
        file.close();
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Skribbl.io Custom Words"), QStandardPaths::locate(QStandardPaths::DesktopLocation, "", QStandardPaths::LocateDirectory), tr("Skribbl.io Custom Word Files (*.skribbl)"));
    if (!fileName.isEmpty())
    {
        loadFile(fileName);
    }

}

void MainWindow::add()
{
    bool ok = true;
    QString text = QInputDialog::getText(this, tr("Add word"),tr("Word:"), QLineEdit::Normal,"", &ok, Qt::MSWindowsFixedSizeDialogHint);

    if (ok && !text.isEmpty())
    {
        ui->wordList->addItem(text);
    }
}

void MainWindow::edit()
{
    if (ui->wordList->currentIndex().isValid())
    {
        bool ok = true;
        QString text = QInputDialog::getText(this, tr("Edit word"),tr("Word:"), QLineEdit::Normal,ui->wordList->currentItem()->text(), &ok, Qt::MSWindowsFixedSizeDialogHint);

        if (ok && !text.isEmpty())
        {
            delete ui->wordList->currentItem();
            ui->wordList->insertItem(ui->wordList->row(ui->wordList->currentItem()), text);
        }
    }
}

void MainWindow::remove()
{
    delete ui->wordList->currentItem();
}

void MainWindow::copy()
{
    QStringList listContent;
    foreach( QListWidgetItem *item, ui->wordList->findItems("*", Qt::MatchWildcard) )
        listContent.append(item->text());

    QClipboard* clip = QGuiApplication::clipboard();
    clip->setText(listContent.join(','));
}
