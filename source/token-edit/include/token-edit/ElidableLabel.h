#pragma once

#include <QtWidgets/QWidget>

#include <token-edit/token-edit-api.h>

namespace mjendruk {

class TOKEN_EDIT_API ElidableLabel : public QWidget {
  Q_OBJECT

 public:
  ElidableLabel(QWidget* parent = nullptr);
  ElidableLabel(QString const& text, QWidget* parent = nullptr);

  QString const& text() const;
  void setText(QString const& text);

  int minVisibleCharacters() const;
  void setMinVisibleCharacters(int count);

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

  QPalette::ColorRole textColorRole() const;
  void setTextColorRole(QPalette::ColorRole role);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void updateTextSize();
  void updateMinimumTextSize();

  QString elidedText() const;

 private:
  QString _text;
  int _minVisibleCharacters;
  QPalette::ColorRole _colorRole;

  QSize _textSize;
  QSize _minTextSize;
};

}  // namespace mjendruk