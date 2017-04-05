#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent):
    QWidget(parent)
{
    setN(10);
    setElement(5,5,1);
}

void RenderArea::setN(int nn){
    n = nn;
    x.resize(n*n);
    fill(x.begin(), x.end(), -1);
}

char RenderArea::getElement(int i, int j){
    if(n == 0) return -1;
    return x[i*n+j];
}

void RenderArea::setElement(int i, int j, char c){
    if(n == 0) return;
    x[i*n+j] = (c<0)? -1:1;
}

void RenderArea::setim(vector<char> newx){
    if(newx.size() != x.size()) return;
    x = newx;
}

vector<char> RenderArea::getim(){
    return x;
}

void RenderArea::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setBrush(Qt::white);
    p.drawRect(0, 0, width()-1, height()-1);

    p.setPen(Qt::black);
    p.setBrush(Qt::red);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            drawElement(p, i, j);
    }

//    int startX = 0;
//    int startY = 0;
//    for(int i = 1; i <= 100; i++){
//           p.drawRect(QRect(startX, startY, 5, 5));
//          if(i % 10 ) {startX+=5;}
//          else {
//              startX = 0;
//              startY+=5;
//          }

//    }
}

void RenderArea::drawElement(QPainter &p, int i, int j){
    char c = getElement(i, j);
    double siz = min(width(), height()) - 10;
    double esiz = siz/n;

    double posX = (width() -siz)/2;
    double posY = (height()-siz)/2;

    p.setPen(Qt::black);
    if(c < 0) p.setBrush(Qt::white);
    else      p.setBrush(Qt::black);

    p.drawRect(posX + j*esiz, posY + i*esiz, esiz, esiz);
}

void RenderArea::findRectangle(int mouseX, int mouseY, int& i, int& j){
    double siz = min(width(), height()) - 10;
    double esiz = siz/n;
    double posX = (width() -siz)/2;
    double posY = (height()-siz)/2;
    if(mouseX < posX || mouseX > posX + siz || mouseY < posY || mouseY > posY + siz){
        i = -1; j = -1; return;
    }
    j = floor((mouseX - posX) / esiz);
    i = floor((mouseY - posY)/ esiz);
}

void RenderArea::mouseReleaseEvent ( QMouseEvent * event )
    {
      int xM = event->x();
      int yM = event->y();
      int i, j;
      findRectangle(xM, yM, i, j);
      if(i != -1 && j != -1){
      char c;
      c = (getElement(i, j) == -1) ? 1 : -1;
      setElement(i, j, c);
      repaint();}
    }

