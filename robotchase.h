#ifndef ROBOTCHASE_H
#define ROBOTCHASE_H

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
  void _addRobot(qreal x = 0.0, qreal y = 0.0, qreal vx = 0.0, qreal vy = 0.0,
                 qreal maxA = 1.0, Qt::GlobalColor color = Qt::blue);
  void _clearRobotList();
  void paintRobotList(QPainter &painter, const QList<Robot *> &rlist);
 private slots:
  void _timeOutEvent();

 public:
  RobotChase(QWidget *parent = nullptr);
  ~RobotChase();
  void paintEvent(QPaintEvent *event = 0);
};
#endif  // ROBOTCHASE_H
