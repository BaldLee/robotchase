#include "robotchase.h"

RobotChase::RobotChase(QWidget *parent) : QMainWindow(parent) {
  resize(1000, 1000);
  _border = new geometry::Border(200, 800, 200, 800);
  _addRobot(300, 300, 1, 0, 1.0, Qt::blue);
  _addRobot(600, 300, 0, 1, 1.0, Qt::red);
  _addRobot(450, 600, 0, -1, 1.0, Qt::green);
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
  pen.setColor(Qt::black);
  pen.setWidth(3);
  painter.setPen(pen);
  painter.drawLine(
      QLineF(_border->left, _border->top, _border->right, _border->top));
  painter.drawLine(
      QLineF(_border->left, _border->buttom, _border->right, _border->buttom));
  painter.drawLine(
      QLineF(_border->left, _border->top, _border->left, _border->buttom));
  painter.drawLine(
      QLineF(_border->right, _border->top, _border->right, _border->buttom));
  //  painter.drawPoint(_robotList.at(0)->p());
  //  painter.drawPoint(_robotList.at(1)->p());
  //  painter.drawPoint(_robotList.at(2)->p());
  paintRobotList(painter, _robotList);
}

void RobotChase::_addRobot(qreal x, qreal y, qreal vx, qreal vy, qreal maxA,
                           Qt::GlobalColor color) {
  Robot *r = new Robot(QPointF(x, y), QPointF(vx, vy), maxA, color);
  _robotList.append(r);
}

void RobotChase::paintRobotList(QPainter &painter,
                                const QList<Robot *> &rlist) {
  QPen pen;
  pen.setWidth(5);
  for (auto it = rlist.begin(); it != rlist.end(); it++) {
    Robot *rp = *it;
    pen.setColor(rp->color());
    painter.setPen(pen);
    painter.drawPoint(rp->p());
  }
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

  //  if (((_run_time++) / 5) % 4 == 0) {
  //    r0->chaseRobot(*r1);
  //    r1->chaseRobot(*r2);
  //    r2->chaseRobot(*r0);
  //  } else {
  //    r0->avoidRobot(*r2);
  //    r1->avoidRobot(*r0);
  //    r2->avoidRobot(*r1);
  //  }

  switch (((_run_time++) / 2) % 4) {
    case 0: {
      r0->chaseRobot(*r1);
      r1->avoidRobot(*r0);
      r2->avoidBorder(_border);
      break;
    }
    case 1: {
      r0->avoidBorder(_border);
      r1->chaseRobot(*r2);
      r2->avoidRobot(*r1);
      break;
    }
    case 2: {
      r0->avoidRobot(*r2);
      r1->avoidBorder(_border);
      r2->chaseRobot(*r0);
      break;
    }
    case 3: {
      r0->avoidBorder(_border);
      r1->avoidBorder(_border);
      r2->avoidBorder(_border);
      break;
    }
    default:
      break;
  }

  r0->getBack(_border);
  r1->getBack(_border);
  r2->getBack(_border);
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
