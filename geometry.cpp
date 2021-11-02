#include "geometry.h"

namespace geometry {
QLineF getDirection(const QPointF& p1, const QPointF& p2) {
  return QLineF(QPointF(0.0, 0.0), QPointF(p2.x() - p1.x(), p2.y() - p1.y()));
}
}  // namespace geometry
