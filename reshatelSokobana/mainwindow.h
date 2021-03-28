#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_level1_clicked();

    void on_start_clicked();

    void on_level2_clicked();

    void on_level3_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<QWidget*>> setk;
    void load_level(std::string filename);
    std::vector<std::string> level;
    void pokasji(std::string&);
};
#endif // MAINWINDOW_H
