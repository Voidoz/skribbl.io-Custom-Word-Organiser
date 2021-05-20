#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QFile currentFile;

    void loadFile(QString fileName);

public slots:
    void save();
    void saveAs();
    void open();

    void add();
    void edit();
    void remove();

    void copy();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
