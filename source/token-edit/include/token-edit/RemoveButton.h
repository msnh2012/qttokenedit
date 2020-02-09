#pragma once

#include <token-edit/AbstractTokenButton.h>
#include <token-edit/token-edit-api.h>

namespace mjendruk {

class TOKEN_EDIT_API RemoveButton : public AbstractTokenButton {
  Q_OBJECT

 public:
  RemoveButton(QWidget* parent = nullptr);
  RemoveButton(QPalette::ColorRole colorRole, QWidget* parent = nullptr);

 private:
  QPainterPath createPath(int extent) const;
};

}  // namespace mjendruk