#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QWidget>

#include <token-edit/token-edit-api.h>

namespace mjendruk {

class FocusChainNavigation;

class TOKEN_EDIT_API FocusChainElement : public QObject {
  Q_OBJECT
 public:
  /**
   * @param defaultNavigation enables navigation using arrow keys
   */
  FocusChainElement(QWidget* widget, FocusChainNavigation* navigation,
                    QObject* parent = nullptr);

  FocusChainElement* previousElement() const;
  void setPreviousElement(FocusChainElement* element);

  FocusChainElement* nextElement() const;
  void setNextElement(FocusChainElement* element);

  QWidget* widget() const;

 signals:
  void gotFocus(QWidget* element);
  void lostFocus(QWidget* element);

 protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

 private:
  FocusChainElement* _previousElement;
  FocusChainElement* _nextElement;
  QWidget* _widget;
  FocusChainNavigation* _navigation;
};

}  // namespace mjendruk