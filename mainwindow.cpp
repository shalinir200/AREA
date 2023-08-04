#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include<QtWidgets>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modified = false;
    scribbling = false;
    line = false;
    //rect = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;


    InitialX=0;
    InitialY = 0;
    FinalX = 0;
    FinalY = 0;
    MousePressed = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
//scribble
void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        //scribbling = true;
    }
//line

    MousePressed = true;
    InitialX = event->pos().x();
    InitialY = event->pos().y();
}
//scribble
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) )
        drawLineTo(event->pos());
//line

    if ((event->type() == QEvent::MouseMove) )
        {
            QPainter painter(this);
            QPen pen(Qt::green);
            painter.setPen(pen);
            painter.drawLine(InitialX, InitialY, FinalX, FinalY);
            update(); // update your view
            FinalX = event->pos().x();
            FinalY = event->pos().y();
//rectangle
            QPainter rect(this);
            QPen poo(Qt::red);
            rect.setPen(poo);
            rect.drawRect(InitialX, InitialY, FinalX, FinalY);
            update();
//cricle
            QPainter circle(this);
            QPen sil(Qt::yellow);
            circle.setPen(sil);
            circle.drawEllipse(InitialX, InitialY, FinalX, FinalY);
            update();
        }
        update();
}


//scribble
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
       // scribbling = false;
    }
//line
    MousePressed = false;
}

//scribble
void MainWindow::paintEvent(QPaintEvent *event)
{
    if(ui->radioButton->isChecked()){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
    }

//line
    if(ui->radioButton_2->isChecked())
    //if(MousePressed)
            {
                QPainter painter(this);
                QPen pen(Qt::green);
                painter.setPen(pen);
                painter.drawLine(InitialX, InitialY, FinalX, FinalY);
        }
//rectangle
                if(ui->radioButton_3->isChecked()){
                QPainter rect(this);
                QPen poo(Qt::red);
                rect.setPen(poo);
                rect.drawRect(InitialX, InitialY, FinalX, FinalY);
                }
//cricle
                if(ui->radioButton_4->isChecked()){
                QPainter circle(this);
                QPen sil(Qt::yellow);
                circle.setPen(sil);
                circle.drawEllipse(InitialX, InitialY, FinalX, FinalY);
            }
}


//scribble
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void MainWindow::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));


    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}


void MainWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}



void MainWindow::on_pushButton_clicked()
{
   ui->lineEdit->setText("shalini");

}


