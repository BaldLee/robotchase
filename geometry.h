#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QLineF>
#include <QPointF>
#include <QtMath>

namespace geometry {
QLineF getDirection(const QPointF& p1, const QPointF& p2);
}  // namespace geometry

#endif  // GEOMETRY_H
