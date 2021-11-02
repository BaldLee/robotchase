#include <QApplication>

#include "robotchase.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  RobotChase w;
  w.show();
  return a.exec();
}
