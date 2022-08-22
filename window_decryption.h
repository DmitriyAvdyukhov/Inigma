#pragma once

#include "encryption.h"
#include "encryption_file_txt.h"
#include "encryption_message.h"
#include <QWizard>

namespace Ui {
  class WindowDecryption;
}

class WindowDecryption : public QWizard
{
  Q_OBJECT

public:
  explicit WindowDecryption(QWidget *parent = nullptr);
  ~WindowDecryption();

private slots:
  void on_checkBox_file_stateChanged(int arg1);

  void on_checkBox_message_stateChanged(int arg1);

  void on_textEdit_message_textChanged();

  void on_area_name_file_textChanged(const QString &arg1);

  void on_button_insert_file_clicked();

  void on_name_file_key_textChanged(const QString &arg1);

  void on_button_insert_key_clicked();

  void on_text_isert_key_textChanged();

  void on_button_decrypt_clicked();

private:
  Ui::WindowDecryption *ui;
  std::unique_ptr<encryption::Encryption> decrypt_ = nullptr;
};


