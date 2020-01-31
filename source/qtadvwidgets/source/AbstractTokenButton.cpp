#include <qtadvwidgets/AbstractTokenButton.h>

#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QStyle>

AbstractTokenButton::AbstractTokenButton(QWidget* parent)
    : AbstractTokenButton{QPalette::Text, parent} {}

AbstractTokenButton::AbstractTokenButton(QPalette::ColorRole colorRole,
                                         QWidget* parent)
    : QAbstractButton{parent},
      _colorRole{colorRole} {
  setCheckable(false);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setCursor(Qt::PointingHandCursor);
  setFocusPolicy(Qt::ClickFocus);
}

QSize AbstractTokenButton::sizeHint() const {
  auto extent = this->extent();
  return QSize{extent, extent};
}

QPalette::ColorRole AbstractTokenButton::colorRole() const {
  return _colorRole;
}

void AbstractTokenButton::setColorRole(QPalette::ColorRole role) {
  if (_colorRole == role) {
    return;
  }

  _colorRole = role;
  update();
}

void AbstractTokenButton::draw(QPainter* painter) const {
  painter->setBrush(palette().color(_colorRole));
  painter->setPen(Qt::NoPen);

  painter->drawPath(_path);
}

void AbstractTokenButton::paintEvent(QPaintEvent* event) {
  auto const clippingRect = QRectF{event->rect()};

  auto painter = QPainter{this};
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setClipRect(clippingRect);

  draw(&painter);
}

void AbstractTokenButton::setPath(QPainterPath const& path) { _path = path; }

int AbstractTokenButton::extent() const { 
  return fontMetrics().height();
}