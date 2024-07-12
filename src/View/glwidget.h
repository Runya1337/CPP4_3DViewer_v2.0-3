#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "../Controller/controller.h"

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget *parent = nullptr);
  void setControll(s21::Controller *control) { controller_ = control; };
  void setFileName(QString str) {
    file_ = str;
    controller_->GetData().ClearData();
    controller_->GetData().GetAllVertex().clear();
    controller_->GetData().GetAllConnections().clear();
    controller_->ParseFile(file_.toStdString());
    controller_->SetCentre(&controller_->GetData());
    countVertexes = controller_->GetData().GetAllVertex().size();
    countLines = controller_->GetData().GetAllConnections().size();
  }
  double moveX_ = 0, moveY_ = 0, moveZ_ = 0;
  double rotationX_ = 0, rotationY_ = 0.3, rotationZ_ = 0;
  double size_ = 1, sizeP_ = 1, sizeL_ = 2;
  int countVertexes = 0;
  int countLines = 0;
  int typeP = 3;
  int typeL = 3;
  int typeProect = 1;
  QColor colorWidget;
  QColor colorLines;
  QColor colorVertices;

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void drawGL();
  void positionGL();
  void vertexesType();
  void lineType();
  void proectionType();
  s21::Controller *controller_;
  QString file_;
};

#endif  // GLWIDGET_H
