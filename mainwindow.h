#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "neuronetwork.h"
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void mouseReleaseEvent ( QMouseEvent * event );
    ~MainWindow();

private:
    RenderArea *renderArea;
    NeuroNetwork *net;
    vector<NeuroNetwork::Image> rendImages;

private slots:

    void on_learnButton_clicked();

    void on_recognizeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
