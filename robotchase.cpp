#include "robotchase.h"

RobotChase::RobotChase(QWidget *parent) : QMainWindow(parent) {
  resize(1000, 1000);
  _border = new geometry::Border(50, 950, 50, 950);
  _addRobot(300, 300, 1, 0);
  _addRobot(600, 300, 0, 1);
  _addRobot(450, 600, 0, -1);
  _initTimer();
}

RobotChase::~RobotChase() {
  delete _timer;
  delete _border;
  _clearRobotList();
}

void RobotChase::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPen pen;

  pen.setColor(Qt::blue);
  pen.setWidth(5);
  painter.setPen(pen);
  painter.drawPoint(_robotList.at(0)->p());
  painter.drawPoint(_robotList.at(1)->p());
  painter.drawPoint(_robotList.at(2)->p());
}

void RobotChase::_addRobot(qreal x = 0.0, qreal y = 0.0, qreal vx = 0.0,
                           qreal vy = 0.0) {
  Robot *r = new Robot(QPointF(x, y));
  r->setV(vx, vy);
  _robotList.append(r);
}

void RobotChase::_clearRobotList() {
  for (auto it = _robotList.begin(); it != _robotList.end(); it++) {
    delete (*it);
  }
  _robotList.clear();
}

void RobotChase::_timeOutEvent() {
  auto r0 = _robotList.at(0);
  auto r1 = _robotList.at(1);
  auto r2 = _robotList.at(2);

  if (((_run_time++) / 5) % 4 == 0) {
    r0->chaseRobot(*r1);
    r1->chaseRobot(*r2);
    r2->chaseRobot(*r0);
  } else {
    r0->avoidRobot(*r2);
    r1->avoidRobot(*r0);
    r2->avoidRobot(*r1);
  }

  switch (((_run_time++) / 50) % 4) {
    case 0: {
      r0->chaseRobot(*r1);
      r1->chaseRobot(*r2);
      r2->chaseRobot(*r0);
      break;
    }
    case 1: {
      r0->avoidRobot(*r2);
      r1->avoidRobot(*r0);
      r2->avoidRobot(*r1);
      break;
    }
    case 2: {
      r0->chaseRobot(*r1);
      r1->avoidRobot(*r0);
      r2->chaseRobot(*r0);
      break;
    }
    case 3: {
      r0->avoidRobot(*r2);
      r1->chaseRobot(*r2);
      r2->avoidRobot(*r1);
      break;
    }
    default:
      break;
  }

  r0->move();
  r1->move();
  r2->move();

  this->update();
}

void RobotChase::_initTimer() {
  _run_time = 0;
  _timer = new QTimer(this);
  _timer->setInterval(40);
  connect(_timer, SIGNAL(timeout()), this, SLOT(_timeOutEvent()));
  _timer->start();
}
