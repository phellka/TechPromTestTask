#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , running(true)
{
    ui->setupUi(this);
    ui->labelCounterSpeed->setText(QString("Counter speed = %1u/s").arg(1 / counterSpeed));
    ui->tableView->setModel(&list);

    if (dbManager.connect()) {
        dbManager.createTable();
        loadData();
    } else {
        QMessageBox::critical(this, "Database Error", "Unable to connect to database");
    }

    startCounterThread();
}

MainWindow::~MainWindow()
{
    stopCounterThread();
    delete ui;
}

void MainWindow::on_pushButtonDel_clicked()
{
    std::lock_guard<std::mutex> lock(counterMutex);
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (!select->hasSelection()){
        QMessageBox::information(this, "Info", "to delete an item, select the item");
        return;
    }
    int row = select->selectedRows().at(0).row();
    list.DeleteCounterByIndex(row);
}


void MainWindow::on_pushButtonSave_clicked()
{
    std::lock_guard<std::mutex> lock(counterMutex);
    if (dbManager.saveCounters(list.getCounters())) {
        QMessageBox::information(this, "Info", "Data saved to database");
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to save data to database");
    }
}


void MainWindow::on_pushButtonAdd_clicked()
{
    std::lock_guard<std::mutex> lock(counterMutex);
    list.AddNewCounter();
}

void MainWindow::loadData()
{
    QVector<CounterEntity> counters = dbManager.loadCounters();
    for (const CounterEntity& counter : counters) {
        list.AddCounter(counter);
    }
}

void MainWindow::startCounterThread()
{
    counterThread = std::thread(&MainWindow::incrementCounters, this);
}

void MainWindow::stopCounterThread()
{
    running = false;
    if (counterThread.joinable()){
        counterThread.join();
    }
}

void MainWindow::incrementCounters()
{
    while (running) {
        {
            std::lock_guard<std::mutex> lock(counterMutex);
            for (int i = 0; i < list.rowCount(); ++i) {
                list.increaseCounter(i);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 / counterSpeed)));
    }
}
