#include "inigma256.h"
#include "./ui_inigma256.h"

Inigma256::Inigma256(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Inigma256)
{
  ui->setupUi(this);
}

Inigma256::~Inigma256()
{
  delete ui;
}


void Inigma256::on_create_kye_button_clicked()
{
  window_create_new_cey_ = std::make_unique<CreateNewKey>();
  window_create_new_cey_->show();
}


void Inigma256::on_action_create_new_key_triggered()
{
    on_create_kye_button_clicked();
}


void Inigma256::on_exit_button_clicked()
{
    close();
}


void Inigma256::on_encryption_button_clicked()
{
    window_incryption_ = std::make_unique<EncryptionWindow>();
    window_incryption_->show();
}


void Inigma256::on_decryption_button_clicked()
{
    window_decryption_ = std::make_unique<WindowDecryption>();
    window_decryption_ -> show();
}

