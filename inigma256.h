#pragma once

#include <QMainWindow>
#include "create_new_key.h"
#include "encryption_window.h"
#include "window_decryption.h"

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class Inigma256; }
QT_END_NAMESPACE

class Inigma256 : public QMainWindow
{
  Q_OBJECT

public:
  Inigma256(QWidget *parent = nullptr);
  ~Inigma256();

public slots:
  void on_create_kye_button_clicked();

private slots:  

  void on_action_create_new_key_triggered();

  void on_exit_button_clicked();

  void on_encryption_button_clicked();

  void on_decryption_button_clicked();

private:
  Ui::Inigma256 *ui;
  std::unique_ptr<CreateNewKey> window_create_new_cey_ = nullptr;
  std::unique_ptr<EncryptionWindow> window_incryption_ = nullptr;
  std::unique_ptr<WindowDecryption> window_decryption_ = nullptr;
};

