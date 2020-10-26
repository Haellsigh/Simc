#include <QApplication>
#include "mainwindow.hh"

int main(int argc, char* argv[])
{
  QApplication     a(argc, argv);
  simc::MainWindow w;
  w.show();

  return a.exec();
}
