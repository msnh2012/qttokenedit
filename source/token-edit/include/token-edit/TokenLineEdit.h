#pragma once

#include <QtWidgets/QLineEdit>

#include <token-edit/TokenDropTarget.h>
#include <token-edit/token-edit-api.h>

namespace mjendruk {

class TOKEN_EDIT_API TokenLineEdit : public TokenDropTarget<QLineEdit> {
  Q_OBJECT
 public:
  explicit TokenLineEdit(AbstractTokenDragDropHandler* handler,
                         QWidget* parent = nullptr);

 signals:
  void backspaceAtBeginning();

 protected:
  void keyPressEvent(QKeyEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

  QSize sizeHint() const override;

 private:
  void onTextChanged(QString const& text);

 private:
  int _widthHint;
};

}  // namespace mjendruk
