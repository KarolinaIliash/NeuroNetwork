#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <thread>
#include <atomic>
#include <QMessageBox>
#include <QInputDialog>
using namespace std;

#include "renderarea.h"
#include "neuronetwork.h"


namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    atomic<bool> isWorking;
    RenderArea *renderArea;
    NeuroNetwork *net;
    vector<NeuroNetwork::Image> rendImages;
    NeuroNetwork::Image resImages;
    QMessageBox msgBox;

private slots:

    void on_learnButton_clicked();

    void on_recognizeButton_clicked();

    void on_addButton_clicked();

    void on_RemoveButton_clicked();

    //void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_ShowR_clicked();

    void on_clearButton_clicked();

    void on_readButton_clicked();

    void on_saveButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

   private:
    void onHopfLearned();
    void onHopfRecognized(NeuroNetwork::Image res);
};

#endif // MAINWINDOW_H
