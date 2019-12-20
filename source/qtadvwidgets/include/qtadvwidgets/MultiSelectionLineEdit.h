#pragma once

#include <qtadvwidgets/qtadvwidgets_api.h>

#include <QLineEdit>

class QTADVWIDGETS_API MultiSelectionLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  using QLineEdit::QLineEdit;

 signals:
  void backspaceAtBeginning();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
};