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
    isWorking = false;
}

MainWindow::~MainWindow(){
    delete net;
    delete renderArea;
    delete ui;
}




void MainWindow::on_learnButton_clicked()
{
   // net->LearnNeuroNet(rendImages);
    if(rendImages.size() == 0){
        msgBox.setText("Add some images");
        msgBox.exec();
        return;
    }
    if(isWorking) {
        msgBox.setText("Try again");
        msgBox.exec();
        return;
    }
    isWorking = true;
    std::thread t([&](){
        net->LearnNeuroNet(rendImages);
        onHopfLearned();
    });
    t.detach();
}

void MainWindow::on_recognizeButton_clicked()
{
    if(!net->isLearnt()){
        msgBox.setText("Teach newtork first");
        msgBox.exec();
        return;
    }
    if(isWorking) {
        msgBox.setText("Try again");
        msgBox.exec();
        return;
    }
    isWorking = true;

  //  net->RecognizeImage(renderArea->getim(), result);
    std::thread t([&](){
        NeuroNetwork::Image result;
        net->RecognizeImage(renderArea->getim(), result);
        onHopfRecognized(result);
    });
    t.detach();
}

void MainWindow::on_addButton_clicked()
{

    NeuroNetwork::Image image;
    image.neuros = renderArea->getim();
    image.name = "";
    rendImages.push_back(image);

    QListWidgetItem *wi = new QListWidgetItem("Image" + QString::number(rendImages.size()));
    wi->setFlags(wi->flags () | Qt::ItemIsEditable);
    ui->listWidget->addItem(wi);
 //    ui->listWidget->addItem("Image" + QString::number(rendImages.size()));
}

void MainWindow::on_RemoveButton_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row >= 0){
        rendImages.erase(rendImages.begin()+row);
        delete ui->listWidget->takeItem(row);
    }
}

//void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
//{
//    ui->listWidget->editItem(item);
//}

void MainWindow::onHopfLearned(){
    isWorking = false;
}

void MainWindow::onHopfRecognized(NeuroNetwork::Image res)
{
    resImages = res;
    isWorking = false;
}


void MainWindow::on_ShowR_clicked()
{
    if(isWorking) {
        msgBox.setText("Try again");
        msgBox.exec();
        return;
    }
    renderArea->setim(resImages.neuros);
    renderArea->repaint();
}



void MainWindow::on_clearButton_clicked()
{
    if(isWorking) {
        msgBox.setText("Try again");
        msgBox.exec();
        return;
    }
    vector<char> x(renderArea->getim().size());
    fill(x.begin(), x.end(), -1);
    renderArea->setim(x);
    renderArea->repaint();
}

void MainWindow::on_readButton_clicked()
{
    NeuroNetwork::Image image;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Read from file"),
                                             tr("File name:"), QLineEdit::Normal,
                                             "", &ok);
    if(ok && !text.isEmpty()){
        image.Read(text.toStdString(), 10, 10);
        renderArea->setim(image.neuros);
        renderArea->repaint();
    }
}

void MainWindow::on_saveButton_clicked()
{

    NeuroNetwork::Image image;
    image.neuros = renderArea->getim();
    image.name = "";
    bool ok;
    QString text = QInputDialog::getText(this, tr("Read from file"),
                                             tr("File name:"), QLineEdit::Normal,
                                             "", &ok);
    if(ok && !text.isEmpty()){
        if(!image.Save(text.toStdString(), 10, 10)){
            msgBox.setText("Error");
            msgBox.exec();
        }
    }
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    int i = ui->listWidget->currentRow();
    renderArea->setim(rendImages[i].neuros);
    renderArea->repaint();
}
