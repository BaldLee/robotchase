#include "robot.h"

Robot::Robot()
    : _name("default"),
      _color(Qt::blue),
      _p(QPoint(0.0, 0.0)),
      _v(QPointF(0.0, 0.0)),
      _a(QPointF(0.0, 0.0)) {}

Robot::Robot(const QPointF& position)
    : _name("default"),
      _color(Qt::blue),
      _p(position),
      _v(QPointF(0.0, 0.0)),
      _a(QPointF(0.0, 0.0)),
      _maxA(2) {}

Robot::Robot(const QPointF& position, const QPointF& velocity)
    : _name("default"),
      _color(Qt::blue),
      _p(position),
      _v(velocity),
      _a(QPointF(0.0, 0.0)),
      _maxA(2) {}

Robot::Robot(const QPointF& position, const QPointF& velocity, qreal maxA)
    : _name("default"),
      _color(Qt::blue),
      _p(position),
      _v(velocity),
      _a(QPointF(0.0, 0.0)),
      _maxA(maxA) {}

Robot::Robot(const QPointF& position, const QPointF& velocity, qreal maxA,
             Qt::GlobalColor color)
    : _name("default"),
      _color(color),
      _p(position),
      _v(velocity),
      _a(QPointF(0.0, 0.0)),
      _maxA(maxA) {}
Robot::Robot(const QPointF& position, const QPointF& velocity, qreal maxA,
             Qt::GlobalColor color, QString name)
    : _name(name),
      _color(color),
      _p(position),
      _v(velocity),
      _a(QPointF(0.0, 0.0)),
      _maxA(maxA) {}
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
  auto newV = QLineF(0.0, 0.0, _v.x() + _a.x(), _v.y() + _a.y());
  if (newV.length() > 10) newV.setLength(10);
  setV(newV.x2(), newV.y2());
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

geometry::Border Robot::_getSmallBorder(geometry::Border* _border) {
  auto centerX = (_border->left + _border->right) / 2;
  auto centerY = (_border->top + _border->buttom) / 2;
  return geometry::Border(centerY - (centerY - _border->top) * 0.8,
                          centerY + (_border->buttom - centerY) * 0.8,
                          centerX - (centerX - _border->left) * 0.8,
                          centerX + (_border->right - centerX) * 0.8);
}

void Robot::avoidBorder(geometry::Border* _border) {
  auto border = _getSmallBorder(_border);
  /* time to reach side */
  qreal tx = 0.0;
  qreal ty = 0.0;
  if (_v.y() < 0) {
    ty = (border.top - _p.y()) / _v.y();
  } else if (_v.y() > 0) {
    ty = (_p.y() - border.buttom) / _v.y();
  }
  if (_v.x() < 0) {
    ty = (border.left - _p.x()) / _v.x();
  } else if (_v.x() > 0) {
    ty = (_p.x() - border.right) / _v.x();
  }
  QLineF newA(0.0, 0.0, tx, ty);
  newA.setLength(_maxA);
  setA(newA.p2());
}

bool Robot::getBack(geometry::Border* _border) {
  auto border = _getSmallBorder(_border);
  bool isTopOut = _p.y() <= border.top;
  bool isButtomOut = _p.y() >= border.buttom;
  bool isLeftOut = _p.x() <= border.left;
  bool isRightOut = _p.x() >= border.right;
  qreal sx = 0.0, sy = 0.0;
  if (isTopOut) {
    sy = border.top - _p.y();
  }
  if (isButtomOut) {
    sy = border.buttom - _p.y();
  }
  if (isLeftOut) {
    sx = border.left - _p.x();
  }
  if (isRightOut) {
    sx = border.right - _p.x();
  }

  if (isTopOut || isButtomOut || isLeftOut || isRightOut) {
    auto newA = QLineF(0.0, 0.0, sx, sy);
    newA.setLength(_maxA);
    setA(newA.p2());
  }

  return isTopOut || isButtomOut || isLeftOut || isRightOut;
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

QString Robot::name() const { return _name; }

Qt::GlobalColor Robot::color() const { return _color; }
