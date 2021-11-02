#include "geometry.h"

namespace geometry {
QLineF getDirection(const QPointF& p1, const QPointF& p2) {
  return QLineF(QPointF(0.0, 0.0), QPointF(p2.x() - p1.x(), p2.y() - p1.y()));
}

Border::Border() : top(50), buttom(950), left(50), right(950) {}

Border::Border(qreal t, qreal b, qreal l, qreal r)
    : top(t), buttom(b), left(l), right(r) {}
}  // namespace geometry
