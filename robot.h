#ifndef ROBOT_H
#define ROBOT_H

#include <QDebug>
#include <QtMath>

#include "geometry.h"

class Robot {
  Qt::GlobalColor _color;
  QPointF _p;
  QPointF _v;
  QPointF _a;
  qreal _maxA;
  geometry::Border _getSmallBorder(geometry::Border* border);

 public:
  Robot();
  Robot(const QPointF& position);
  Robot(const QPointF& position, const QPointF& velocity);
  Robot(const QPointF& position, const QPointF& velocity, qreal maxA);
  Robot(const QPointF& position, const QPointF& velocity, qreal maxA,
        Qt::GlobalColor color);
  ~Robot();
  void move();
  void setP(qreal x, qreal y);
  void setV(qreal x, qreal y);
  void setA(qreal x, qreal y);
  void setA(const QPointF& a);
  void setMaxA(qreal a);
  void chaseRobot(const Robot& r);
  void avoidRobot(const Robot& r);
  void avoidBorder(geometry::Border* border);
  bool getBack(geometry::Border* border);
  QPointF p() const;
  QPointF v() const;
  QPointF a() const;
  qreal maxA() const;
  Qt::GlobalColor color() const;
};

#endif  // ROBOT_H
