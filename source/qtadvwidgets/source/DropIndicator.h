#pragma once

#include <qtadvwidgets/Global.h>

class QPainter;
class QRect;
class QBrush;

class DropIndicator {
 public:
  void draw(DropIndicatorPosition position, QRect const& rect,
            QBrush const& brush, QPainter* painter) const;
};
