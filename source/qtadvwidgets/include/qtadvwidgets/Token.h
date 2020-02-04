#pragma once

#include <qtadvwidgets/BaseToken.h>
#include <qtadvwidgets/Global.h>
#include <qtadvwidgets/qtadvwidgets_api.h>

#include <QString>
#include <memory>

class QMimeData;

class AbstractTokenDragDropHandler;
class RemoveButton;
class Token;

class QTADVWIDGETS_API Token : public BaseToken {
  Q_OBJECT

 public:
  Token(AbstractTokenDragDropHandler* dragDropHandler = nullptr,
        QWidget* parent = nullptr);

  Token(QString const& text, AbstractTokenDragDropHandler* dragDropHandler,
        QWidget* parent = nullptr);
  ~Token();

  bool removable() const;
  void setRemovable(bool enable);

 signals:
  void removeClicked();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void focusInEvent(QFocusEvent* event) override;
  void focusOutEvent(QFocusEvent* event) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragLeaveEvent(QDragLeaveEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;

 private:
  QPixmap toPixmap();

  bool shouldStartDrag(QPoint const& mousePos) const;
  void startDrag(QPoint const& mousePos);
  bool acceptsDrag(QDropEvent* event) const;
  void acceptDrag(QDragMoveEvent* event);
  void finishDrag(QDropEvent* event);

  enum class DropIndicator { None, Before, After };

  void showDropIndicator(QPoint const& mousePos);
  void resetDropIndicator();

  void drawDropIndicator(QPainter* painter);

  int dragStartDistance() const;
  TokenDropHint dropHint(QPoint const& mousePos) const;

 private:
  AbstractTokenDragDropHandler* _dragDropHandler;
  RemoveButton* _button;

  bool _removable;

  // drag members
  QPoint _mousePressedAt;
  DropIndicator _dropIndicator;
};

Q_DECLARE_METATYPE(Token*);
