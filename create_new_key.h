#pragma once

#include <QtWidgets>
#include <string>
#include <fstream>

namespace Ui {
  class CreateNewKey;
}

class CreateNewKey : public QWizard
{
  Q_OBJECT

public:
  explicit CreateNewKey(QWidget *parent = nullptr);
  ~CreateNewKey();
  void dumpEvent(QMouseEvent* pe);

  std::string GetKey() const;
private slots:
  void on_checkBox_auto_create_stateChanged(int arg1);
  void on_checkBox_yourself_stateChanged(int arg1);
  void on_area_create_yourself_textChanged();
  void on_save_key_button_clicked();

protected:
  virtual void mouseMoveEvent(QMouseEvent *event);

private:
  Ui::CreateNewKey *ui;
  std::string key_;

  void CutString();
  void Start();
  int RandomBetween(int low, int high, int seed);
};


