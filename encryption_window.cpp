#include "encryption_window.h"
#include "ui_encryption_window.h"

EncryptionWindow::EncryptionWindow(QWidget *parent) :
  QWizard(parent),
  ui(new Ui::EncryptionWindow)
{
  ui->setupUi(this);
  ui->area_message->hide();
  ui->label_area_message->hide();

  ui->label_line_file_name->hide();
  ui->line_file_name->hide();

  ui->name_file_key->show();
  ui->text_isert_key->show();

  ui->button_ok_insert_key->setEnabled(false);
}

EncryptionWindow::~EncryptionWindow()
{
  delete ui;
}

void EncryptionWindow::on_encrypt_file_stateChanged(int arg1)
{
  if(arg1)
    {
      ui->encrypt_message->setEnabled(false);
      ui->label_line_file_name->show();
      ui->line_file_name->show();
      ui->label_your_message->setText("Вы хотите зашифровать файл:");
      ui->button_encript_message->hide();
      ui->button_save_message_in_file->hide();
      ui->button_encrypt_file->show();
      encrypt_ = std::make_unique<encryption::EncryptionFileTxt>();
    }
  else
    {
      ui->encrypt_message->setEnabled(true);
      ui->label_line_file_name->hide();
      ui->line_file_name->hide();
    }
}


void EncryptionWindow::on_encrypt_message_stateChanged(int arg1)
{
  if(arg1)
    {
      ui->encrypt_file->setEnabled(false);
      ui->area_message->show();
      ui->label_area_message->show();
      ui->button_encript_message->show();
      ui->button_save_message_in_file->show();
      ui->button_encrypt_file->hide();
      ui->button_copy->show();
      encrypt_ = std::make_unique<encryption::EncryptionMessage>();
    }
  else
    {
      ui->encrypt_file->setEnabled(true);
      ui->area_message->hide();
      ui->label_area_message->hide();
    }
}


void EncryptionWindow::on_line_file_name_textChanged(const QString &arg1)
{
  QString str = arg1;
  std::string  name_file = str.toStdString();
  name_file.erase(0, 8);
  name_file.erase(name_file.find('\n'));
  encrypt_->SetData(name_file);
  ui->line_file_name->setEnabled(false);
  ui->your_secret_message->setText(
        QString::fromLocal8Bit(encrypt_->GetData()));
  ui->your_secret_message->setEnabled(false);
  ui->button_encript_message->hide();
  ui->button_save_message_in_file->hide();
  ui->label_your_message->show();
}


void EncryptionWindow::on_area_message_textChanged()
{
  QString str = ui->area_message->toPlainText();
  std::string  data = str.toStdString();
  encrypt_->SetData(data);
  ui->your_secret_message->setText(
        QString::fromLocal8Bit(encrypt_->GetData()));
  ui->label_your_message->setText("Вы хотите зашифровать сообщение:");
  ui->your_secret_message->setEnabled(false);
}


void EncryptionWindow::on_button_insert_file_clicked()
{
  ui->label_key->setText("Перетащите в поле ниже файл с ключом");
  ui->name_file_key->setEnabled(true);
  ui->text_isert_key->hide();
  ui->button_insert_key->hide();
  ui->button_add_new_key->hide();
  ui->button_insert_file->hide();

}


void EncryptionWindow::on_name_file_key_textChanged(const QString &arg1)
{
  std::string  name_file = arg1.toStdString();
  name_file.erase(0, 8);
  name_file.erase(name_file.find('\n'));
  std::ifstream file(name_file);
  if(file)
    {
      std::string str;
      while (file)
        {
          std::string tmp;
          std::getline(file, tmp);
          str += tmp;
        }
      if(str.size() > 256)
        {
          str.erase(256);
        }
      encrypt_->SetKey(str);
      ui->button_ok_insert_key->setEnabled(true);
      ui->name_file_key->setEnabled(false);
    }
}


void EncryptionWindow::on_button_insert_key_clicked()
{
  ui->label_key->setText("Введите Ваш ключ в поле ниже");
  ui->text_isert_key->setEnabled(true);
  ui->text_isert_key->show();
  ui->name_file_key->hide();
  ui->button_insert_key->hide();
  ui->button_add_new_key->hide();
  ui->button_insert_file->hide();
}


void EncryptionWindow::on_text_isert_key_textChanged()
{
  encrypt_->SetKey(ui->text_isert_key->toPlainText().toStdString());
  ui->button_ok_insert_key->setEnabled(true);

}


void EncryptionWindow::on_button_encript_message_clicked()
{
  ui->your_secret_message->setText(
        QString::fromLocal8Bit(encrypt_->EncryptionData(encrypt_->GetData())));
  ui->button_save_message_in_file->setEnabled(true);
  ui->button_encript_message->setEnabled(false);
  ui->label_your_message->setText("Ваше зашифрованное сообщение:");
}


void EncryptionWindow::on_button_save_message_in_file_clicked()
{
  QString file_name = QFileDialog::getSaveFileName(this, tr("Save file"));
  std::ofstream file(file_name.toStdString());
  if(file)
    {
      file << ui->your_secret_message->toPlainText().toStdString();
      file.close();
    }

  QMessageBox* p_mb = new QMessageBox(QMessageBox::Information,
                                      "Сообщение",
                                      "<b> Вы сохранили Ваше зашифрованное сообщение в файл</b> <i>" + file_name
                                      + "</i>",
                                      QMessageBox::Cancel);
  p_mb->exec();
  ui->button_save_message_in_file->setEnabled(false);
  ui->your_secret_message->setEnabled(false);
}


void EncryptionWindow::on_button_ok_insert_key_clicked()
{
  if(window_create_new_cey_ != nullptr)
    {
      QMessageBox* p_mb = new QMessageBox(QMessageBox::Information,
                                          "Сообщение",
                                          "<b> Ваш ключ успешно создан</b> <i></i>",
                                          QMessageBox::Cancel);
      p_mb->exec();
      encrypt_->SetKey(window_create_new_cey_->GetKey());
    }
  if(encrypt_->GetCharEncryption().size())
    {
      QMessageBox* p_mb = new QMessageBox(QMessageBox::Information,
                                          "Сообщение",
                                          "<b> Ваш ключ успешно добавлен</b> <i></i>",
                                          QMessageBox::Cancel);
      p_mb->exec();
    }
  else
    {
      QMessageBox* p_mb = new QMessageBox(QMessageBox::Information,
                                          "Сообщение",
                                          "<b> Не получилось добавить ключ</b> <i></i>",
                                          QMessageBox::Cancel);
      p_mb->exec();
    }
  ui->name_file_key->hide();
  ui->text_isert_key->hide();
  ui->button_ok_insert_key->hide();
  ui->button_cancel_insert_key->hide();
  ui->button_add_new_key->hide();
  ui->button_insert_file->hide();
  ui->button_insert_key->hide();
  ui->label_key->hide();
}

void EncryptionWindow::StartWindowInsertKey()
{
  ui->name_file_key->setEnabled(true);
  ui->text_isert_key->clear();
  ui->name_file_key->hide();
  ui->text_isert_key->hide();
  ui->button_ok_insert_key->setEnabled(false);
  ui->button_cancel_insert_key->show();
  ui->button_insert_file->show();
  ui->button_insert_key->show();
  ui->button_add_new_key->show();
}

void EncryptionWindow::on_button_cancel_insert_key_clicked()
{
  StartWindowInsertKey();
  encrypt_->Clear();
}


void EncryptionWindow::on_button_add_new_key_clicked()
{
  window_create_new_cey_ = std::make_unique<CreateNewKey>();
  window_create_new_cey_->show();
  ui->button_ok_insert_key->setEnabled(true);
}


void EncryptionWindow::on_button_encrypt_file_clicked()
{
  encrypt_->EncryptionData();
  ui->your_secret_message->setEnabled(true);
  ui->your_secret_message->setText(
        QString::fromLocal8Bit(encrypt_->GetData() + 'i'));
  ui->your_secret_message->setEnabled(false);
  ui->button_encrypt_file->setEnabled(false);
  ui->button_copy->hide();
  ui->label_your_message->setText("Ваш зашифрованный файл:");
}

void EncryptionWindow::on_button_copy_clicked()
{
  QClipboard* clipboard = QApplication::clipboard();
  ui->your_secret_message->setEnabled(true);
  clipboard->setText(ui->your_secret_message->toPlainText());
   ui->your_secret_message->setEnabled(false);
}

