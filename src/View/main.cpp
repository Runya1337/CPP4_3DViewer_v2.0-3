#include <QApplication>

#include "../Controller/controller.h"
#include "viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  Viewer w(&controller, nullptr);
  w.show();
  return a.exec();
}
