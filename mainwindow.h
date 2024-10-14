#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <thread>
#include <atomic>
#include <mutex>

#include "CounterEntity.h"
#include "listcounters.h"
#include "DatabaseManager.h"

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
    void on_pushButtonDel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAdd_clicked();

private:
    Ui::MainWindow *ui;
    double counterSpeed = 2;
    ListCounters list;
    DatabaseManager dbManager;
    std::thread counterThread;
    std::atomic<bool> running;
    std::mutex counterMutex;



    void loadData();
    void startCounterThread();
    void stopCounterThread();
    void incrementCounters();
};
#endif // MAINWINDOW_H
