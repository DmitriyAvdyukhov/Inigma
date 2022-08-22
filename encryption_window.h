#pragma once

#include "create_new_key.h"
#include "encryption.h"
#include "encryption_file_txt.h"
#include "encryption_message.h"

#include <fstream>
#include <string>
#include <memory>
#include <QWizard>

namespace Ui {
  class EncryptionWindow;
}

class EncryptionWindow : public QWizard
{
  Q_OBJECT

public:
  explicit EncryptionWindow(QWidget *parent = nullptr);
  ~EncryptionWindow();

private slots:
  void on_encrypt_file_stateChanged(int arg1);

  void on_encrypt_message_stateChanged(int arg1);

  void on_line_file_name_textChanged(const QString &arg1);

  void on_area_message_textChanged();

  void on_button_insert_file_clicked();

  void on_name_file_key_textChanged(const QString &arg1);

  void on_button_insert_key_clicked();

  void on_text_isert_key_textChanged();

  void on_button_encript_message_clicked();

  void on_button_save_message_in_file_clicked();

  void on_button_ok_insert_key_clicked();

  void on_button_cancel_insert_key_clicked();

  void on_button_add_new_key_clicked();

  void on_button_encrypt_file_clicked();

  void on_button_copy_clicked(); 

private:
  Ui::EncryptionWindow *ui;
  std::unique_ptr<encryption::Encryption> encrypt_ = nullptr;
  std::unique_ptr<CreateNewKey> window_create_new_cey_ = nullptr;
  void StartWindowInsertKey();
};


