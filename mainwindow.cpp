#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea(this);
    renderArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout_2->insertWidget(0, renderArea);
    net = new NeuroNetwork;
}

MainWindow::~MainWindow(){
    delete ui;
}




void MainWindow::on_learnButton_clicked()
{
    net->LearnNeuroNet(rendImages);
}

void MainWindow::on_recognizeButton_clicked()
{
    NeuroNetwork::Image result;
    net->RecognizeImage(renderArea->getim(), result);
    renderArea->setim(result.neuros);
    renderArea->repaint();
}

void MainWindow::on_addButton_clicked()
{
    NeuroNetwork::Image image;
    image.neuros = renderArea->getim();
    image.name = "";
    rendImages.push_back(image);
}
