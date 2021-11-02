#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QLineF>
#include <QPointF>
#include <QtMath>

namespace geometry {
QLineF getDirection(const QPointF& p1, const QPointF& p2);
class Border {
 public:
  qreal top;
  qreal buttom;
  qreal left;
  qreal right;
  Border();
  Border(qreal t, qreal b, qreal l, qreal r);
};
}  // namespace geometry

#endif  // GEOMETRY_H
