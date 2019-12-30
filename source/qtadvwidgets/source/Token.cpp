#include <qtadvwidgets/RemoveButton.h>
#include <qtadvwidgets/Token.h>
#include <qtadvwidgets/TokenChainElement.h>

#include <QBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QToolButton>
#include <cmath>

Token::Token(QString const& text, QWidget* parent) : Token{text, {}, parent} {}

Token::Token(QString const& text, QVariant const& userData, QWidget* parent)
    : QWidget{parent},
      _text{text},
      _userData{userData},
      _chainElement{std::make_unique<TokenChainElement>(this)},
      _hovered{false} {
  setCursor(Qt::ArrowCursor);
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  setFocusPolicy(Qt::ClickFocus);

  _button = new RemoveButton{palette().color(QPalette::ButtonText),
                             contentHeight(), this};

  connect(_button, &RemoveButton::clicked, this, &Token::removeClicked);
}

Token::~Token() = default;

QString const& Token::text() const { return _text; }

void Token::setText(QString const& text) {
  _text = text;
  update();
}

QVariant const& Token::userData() const { return _userData; }

void Token::setUserData(QVariant const& data) { _userData = data; }

QSize Token::sizeHint() const {
  auto const margins =
      QSize{horizontalTextMargin() + margin(), margin() + margin()};
  auto const buttonWidth = _button->sizeHint().width();

  return textSize() + margins + QSize{buttonWidth + spacing(), 0};
}

QSize Token::minimumSizeHint() const {
  auto const margins =
      QSize{horizontalTextMargin() + margin(), margin() + margin()};

  auto const buttonWidth = _button->sizeHint().width();

  auto const minimalTextWidth =
      fontMetrics().averageCharWidth() * std::min(5, _text.size());

  return margins + QSize{minimalTextWidth + buttonWidth + spacing(), 0};
}

TokenChainElement* Token::chainElement() const { return _chainElement.get(); }

int Token::contentHeight() const { return fontMetrics().height(); }

int Token::horizontalTextMargin() const { return margin() * 2; }

int Token::margin() const { return std::lround(contentHeight() / 6.0); }

int Token::spacing() const { return std::lround(contentHeight() * 0.25); }

QSize Token::textSize() const {
  return fontMetrics().size(Qt::TextSingleLine, _text);
}

void Token::paintEvent(QPaintEvent* event) {
  auto const clippingRect = QRectF{event->rect()};

  auto rect = QRectF{QPointF{0.0, 0.0}, QSizeF{size()}};

  auto const rounding = contentHeight() / 8.0;

  auto path = QPainterPath{};
  path.addRoundedRect(rect, rounding, rounding);

  auto painter = QPainter{this};

  auto palette = this->palette();

  painter.save();

  auto const brushRole = hasFocus() ? QPalette::Highlight : QPalette::Button;
  
  auto brush = palette.brush(brushRole);
  
  if (_hovered) {
    auto color = brush.color();
    brush.setColor(color.lighter(102));
  }
  
  painter.setBrush(brush);
  painter.setPen(Qt::NoPen);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setClipRect(clippingRect);
  painter.drawPath(path);

  painter.restore();

  auto const penRole =
      hasFocus() ? QPalette::HighlightedText : QPalette::ButtonText;
  painter.setPen(palette.color(penRole));

  auto const textPosition = QPointF(horizontalTextMargin(), margin());
  auto const textSize =
      QSizeF{QSize{elidedTextSize().width(), contentHeight()}};

  painter.drawText(QRectF{textPosition, textSize},
                   Qt::TextSingleLine | Qt::AlignLeft, _elidedText);

  QWidget::paintEvent(event);
}

void Token::leaveEvent(QEvent* event) {
  _hovered = false;
  update();
}

void Token::enterEvent(QEvent* event) {
  _hovered = true;
  update();
}

void Token::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  updateElidedText(event->size());
  updateButtonPosition(event->size());
}

void Token::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Backspace) {
    emit removeClicked();
    event->accept();
    return;
  }

  QWidget::keyPressEvent(event);
}

void Token::focusInEvent(QFocusEvent* event) {
  emit focused();

  _button->setColor(palette().color(QPalette::HighlightedText));
  QWidget::focusInEvent(event);
}

void Token::focusOutEvent(QFocusEvent* event) {
  _button->setColor(palette().color(QPalette::ButtonText));

  QWidget::focusOutEvent(event);
}

void Token::updateElidedText(QSize size) {
  auto availableWidth = size.width() - (horizontalTextMargin() + spacing() +
                                        _button->sizeHint().width() + margin());

  _elidedText = fontMetrics().elidedText(_text, Qt::ElideRight, availableWidth);
}

void Token::updateButtonPosition(QSize size) {
  auto const x = size.width() - _button->sizeHint().width() - margin();
  auto const y = margin();
  _button->move(x, y);
}

QSize Token::elidedTextSize() const {
  return fontMetrics().size(Qt::TextSingleLine, _elidedText);
}

QString Token::elidedText() const { return _elidedText; }
