#include "robot.h"

Robot::Robot()
    : _p(QPoint(0.0, 0.0)), _v(QPointF(0.0, 0.0)), _a(QPointF(0.0, 0.0)) {}

Robot::Robot(const QPointF& position)
    : _p(position), _v(QPointF(0.0, 0.0)), _a(QPointF(0.0, 0.0)), _maxA(2) {}

Robot::Robot(const QPointF& position, const QPointF& velocity)
    : _p(position), _v(velocity), _a(QPointF(0.0, 0.0)), _maxA(2) {}

Robot::Robot(const QPointF& position, const QPointF& velocity, qreal maxA)
    : _p(position), _v(velocity), _a(QPointF(0.0, 0.0)), _maxA(maxA) {}

Robot::~Robot() {}

void Robot::move() {
  /* Update _p by _v and _a
   * s = vt + 1/2 * at^2 = v + 1/2 * a (t = 1)
   * In both x deriction and y deriction.
   */
  auto dx = _v.x() + 0.5 * _a.x();
  auto dy = _v.y() + 0.5 * _a.y();
  setP(_p.x() + dx, _p.y() + dy);

  /* Update _v by _a
   * v = v0 + at = v0 + a (t = 1)
   */
  setV(_v.x() + _a.x(), _v.y() + _a.y());
}

void Robot::chaseRobot(const Robot& r) {
  auto direction = geometry::getDirection(_p, r.p());
  auto dv = QLineF(0.0, 0.0, _v.x() - r.v().x(), _v.y() - r.v().y());
  qreal t = direction.length() / dv.length();
  dv.setLength(dv.length() * t);
  auto a = QLineF(0.0, 0.0, direction.x2() - dv.x2(), direction.y2() - dv.y2());
  a.setLength(_maxA);
  setA(a.p2());
}

void Robot::avoidRobot(const Robot& r) {
  auto direction = geometry::getDirection(r.p(), _p);
  auto dv = QLineF(0.0, 0.0, _v.x() - r.v().x(), _v.y() - r.v().y());
  qreal t = direction.length() / dv.length();
  dv.setLength(dv.length() * t);
  auto a = QLineF(0.0, 0.0, direction.x2() - dv.x2(), direction.y2() - dv.y2());
  a.setLength(_maxA);
  setA(a.p2());
}

void Robot::avoidBorder(geometry::Border* border) {
  /* avoid witch side? */
  int is2top = 0;
  int is2left = 0;
  if (_v.y() < 0) is2top = 1;
  if (_v.y() > 0) is2top = -1;
  if (_v.x() < 0) is2left = 1;
  if (_v.x() > 0) is2left = -1;

  /* time to reach side */
  qreal sy = 0.0;
  qreal sx = 0.0;
}

void Robot::setP(qreal x, qreal y) {
  _p.setX(x);
  _p.setY(y);
}

void Robot::setV(qreal x, qreal y) {
  _v.setX(x);
  _v.setY(y);
}

void Robot::setA(qreal x, qreal y) {
  _a.setX(x);
  _a.setY(y);
}

void Robot::setA(const QPointF& a) { _a = a; }

void Robot::setMaxA(qreal a) { _maxA = a; }

QPointF Robot::p() const { return _p; }

QPointF Robot::v() const { return _v; }

QPointF Robot::a() const { return _a; }

qreal Robot::maxA() const { return _maxA; }
