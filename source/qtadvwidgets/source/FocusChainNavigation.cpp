#include <qtadvwidgets/FocusChainNavigation.h>

#include <QKeyEvent>

bool DefaultFocusChainNavigation::focusPrevious(QKeyEvent* event) const {
  return event->key() == Qt::Key_Left;
}
bool DefaultFocusChainNavigation::focusNext(QKeyEvent* event) const {
  return event->key() == Qt::Key_Right;
}