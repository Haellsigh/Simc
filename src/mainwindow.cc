#include "mainwindow.hh"
#include "system/invertedpendulum.hh"

#include <QDoubleSpinBox>

namespace simc {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  ui.setupUi(this);

  refreshSystem();
}

void MainWindow::refreshSystem()
{
  system::InvertedPendulum ip;
  auto                     variables = ip.get_variable_descriptions();

  for (auto variable : variables) {
    auto label = new QLabel();
    label->setText(QString::fromStdString(variable.name()));
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    label->setToolTip(QString::fromStdString(variable.description()));

    auto edit = new QDoubleSpinBox();
    edit->setToolTip(QString::fromStdString(variable.description()));
    edit->setSuffix(QString::fromStdString(" " + variable.unit()));
    edit->setMinimum(variable.minimum());
    edit->setMaximum(variable.maximum());
    edit->setDecimals(variable.digits());
    edit->setValue(variable.initial_value());

    switch (variable.type()) {
      case Variable::Parameter:
        ui.formSystemParameters->addRow(label, edit);
        break;
      case Variable::State:
        ui.formSystemInitialState->addRow(label, edit);
        break;
      default:
        break;
    }
  }
}

}  // namespace simc
