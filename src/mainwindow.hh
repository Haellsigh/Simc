#pragma once

#include "ui_mainwindow.h"

namespace simc {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private:
  void refreshSystem();

 private:
  Ui::MainWindow ui;
};

}  // namespace simc
