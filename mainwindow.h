#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow(QWidget *parent = 0);

protected:
   void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
   void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;


private slots:
   void on_pushButton_clicked();
private:
   void drawLineTo(const QPoint &endPoint);
   void resizeImage(QImage *image, const QSize &newSize);

   bool modified;
   bool scribbling;
   bool line;
   int myPenWidth;
   QColor myPenColor;

   QImage image;
   QPoint lastPoint;

  int  InitialX;
  int  InitialY;
  int  FinalX ;
  int  FinalY ;
  bool MousePressed;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
