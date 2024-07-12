#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget{parent} {}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(colorWidget.redF(), colorWidget.greenF(), colorWidget.blueF(),0);
  glMatrixMode(GL_MODELVIEW);
  if ( controller_->error.second == "ok") {
    // qDebug() << QString("OK: %1").arg(controller_->error.second.c_str());
    glLoadIdentity();
    proectionType();
    glTranslated(0, 0, -3);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    positionGL();
    drawGL();
    glEnd();
    update();
  } else {
      // qDebug() << QString("ERROR: %1").arg(controller_->error.second.c_str());
  }
}

void GLWidget::proectionType() {
  if (typeProect == 1) glFrustum(-1, 1, -1, 1, 1, 99999);
  else glOrtho(-1, 1, -1, 1, 1, 99999);
}

void GLWidget::positionGL() {
    if (moveX_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kMove,
        s21::Strategy::TypeCoordinate::kX, &controller_->GetData(),moveX_);
        moveX_ = 0;
    }
    if (moveY_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kMove,
        s21::Strategy::TypeCoordinate::kY, &controller_->GetData(),moveY_);
        moveY_ = 0;
    }
    if (moveZ_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kMove,
        s21::Strategy::TypeCoordinate::kZ, &controller_->GetData(),moveZ_);
        moveZ_ = 0;
    }
    if (rotationX_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kRotate,
                             s21::Strategy::TypeCoordinate::kX, &controller_->GetData(),
                             rotationX_);
    }
    if (rotationY_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kRotate,
                             s21::Strategy::TypeCoordinate::kY, &controller_->GetData(),
                             rotationY_);
    }
    if (rotationZ_ !=0) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kRotate,
                             s21::Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                             rotationZ_);
    }

    if (size_ !=1) {
        controller_->Affine(s21::Strategy::SelectionStrategy::kDistance,
                             s21::Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                             size_);
        size_ = 1;
    }
}

void GLWidget::drawGL() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetData().GetAllVertex().data());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (typeP != 1) vertexesType();
  if (typeL != 1) lineType();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::vertexesType() {
  if (typeP == 3) glEnable(GL_POINT_SMOOTH);
  else glDisable(GL_POINT_SMOOTH);
  glPointSize(sizeP_);
  glColor3f(colorVertices.redF(), colorVertices.greenF(),colorVertices.blueF());
  glDrawArrays(GL_POINTS, 0, controller_->GetData().GetAllVertex().size());
}

void GLWidget::lineType() {
  if (typeL == 2) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0x00FF);
  } else glDisable(GL_LINE_STIPPLE);
  glColor3f(colorLines.redF(), colorLines.greenF(), colorLines.blueF());
  glLineWidth(sizeL_);

  glDrawElements(
      GL_LINES, 2*controller_->GetData().GetAllConnections().size(),
              GL_UNSIGNED_INT, controller_->GetData().GetAllConnections().data());
}

void GLWidget::mousePressEvent(QMouseEvent* mouse) {
    mPos = mouse->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* mouse) {
  xRot = 1 / M_PI * (mouse->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mouse->pos().x() - mPos.x());
  update();
}
