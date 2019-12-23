#pragma once

#include <qtadvwidgets/qtadvwidgets_api.h>

#include <QWidget>

class QTADVWIDGETS_API RoundRemoveButton : public QWidget {
  Q_OBJECT

 public:
  RoundRemoveButton(int diameter, QWidget *parent = nullptr);

  QSize sizeHint() const override;
  
 signals:
  void clicked();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void enterEvent(QEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  
private:
  void initSize();
  void initButtonShapePath();

private:
  bool _pressed;
  bool _hovered;
  int _diameter;
  QSize _size;
  QPainterPath _path;
};
