
#include <qttokenedit/DarkStyle.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  auto application = QApplication{argc, argv};
//  application.setStyle(new DarkStyle{});

  application.setStyle(QStyleFactory::create("Fusion"));
#ifdef Q_OS_WIN
  auto font = application.font();
  font.setFamily("Segoe UI");
  application.setFont(font);
#endif

  auto mainWindow = MainWindow{};
  mainWindow.show();

  return application.exec();
}