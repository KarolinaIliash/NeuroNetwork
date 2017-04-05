#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QWidget>
#include <vector>
#include <cmath>
#include <QMouseEvent>
using namespace std;

class RenderArea: public QWidget{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

private:
    int n;
    vector<char> x;

public:
    void setN(int nn);
    char getElement(int i, int j);
    void setElement(int i, int j, char c);
    void findRectangle(int mouseX, int mouseY, int& i, int& j);
    void setim(vector<char> newx);
     void mouseReleaseEvent ( QMouseEvent * event );
    vector<char> getim();

private:
    void paintEvent(QPaintEvent *);
    void drawElement(QPainter &p, int i, int j);
};

#endif // RENDERAREA_H
