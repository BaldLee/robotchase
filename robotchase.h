#ifndef ROBOTCHASE_H
#define ROBOTCHASE_H

#include <QDebug>
#include <QList>
#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QThread>
#include <QTimer>
#include <QtMath>
#include <chrono>

#include "geometry.h"
#include "robot.h"

class RobotChase : public QMainWindow {
  Q_OBJECT
  QTimer *_timer;
  int _run_time;
  QList<Robot *> _robotList;
  geometry::Border *_border;
  void _initTimer();
  void _addRobot(qreal x, qreal y, qreal vx, qreal vy);
  void _clearRobotList();
 private slots:
  void _timeOutEvent();

 public:
  RobotChase(QWidget *parent = nullptr);
  ~RobotChase();
  void paintEvent(QPaintEvent *event = 0);
};
#endif  // ROBOTCHASE_H
