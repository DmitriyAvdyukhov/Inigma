#include "window_decryption.h"
#include "ui_window_decryption.h"

WindowDecryption::WindowDecryption(QWidget *parent) :
  QWizard(parent),
  ui(new Ui::WindowDecryption)
{
  ui->setupUi(this);
  ui->area_name_file->hide();
  ui->label_insert_name_fale_or_message->hide();
  ui->textEdit_message->hide();
  ui->textEdit_your_file_or_message_for_decrypt->setEnabled(false);
  ui->textEdit_key_for_decrypt->setEnabled(false);
}

WindowDecryption::~WindowDecryption()
{
  delete ui;
}

void WindowDecryption::on_checkBox_file_stateChanged(int arg1)
{
    if(arg1)
      {
        decrypt_ = std::make_unique<encryption::EncryptionFileTxt>();
        ui->checkBox_message->setEnabled(false);
        ui->label_message->setEnabled(false);
        ui->label_insert_name_fale_or_message->show();
        ui->label_insert_name_fale_or_message->setText("Вставте файл который Вы хотите расшифровать");
        ui->area_name_file->show();
        ui->textEdit_message->hide();
        ui->label_your_file_or_message_for_decrypt->setText("Вы хотите расшифровать файл:");
      }
    else
      {
        decrypt_ = nullptr;
        ui->checkBox_message->setEnabled(true);
        ui->label_message->setEnabled(true);
      }
}


void WindowDecryption::on_checkBox_message_stateChanged(int arg1)
{
  if(arg1)
    {
      decrypt_ = std::make_unique<encryption::EncryptionMessage>();
      ui->checkBox_file->setEnabled(false);
      ui->label_file->setEnabled(false);
      ui->label_insert_name_fale_or_message->show();
      ui->label_insert_name_fale_or_message->setText("Вставте зашифрованное сообщение");
      ui->textEdit_message->show();
      ui->area_name_file->hide();
      ui->label_your_file_or_message_for_decrypt->setText("Вы хотите расшифровать седующие сообщение");
    }
  else
    {
      decrypt_ = nullptr;
      ui->checkBox_file->setEnabled(true);
      ui->label_file->setEnabled(true);
    }
}


void WindowDecryption::on_textEdit_message_textChanged()
{
  QString str = ui->textEdit_message->toPlainText();
  std::string  data = str.toStdString();
  decrypt_->SetData(data);
  ui->textEdit_your_file_or_message_for_decrypt->setText(
        QString::fromLocal8Bit(decrypt_->GetData()));
}


void WindowDecryption::on_area_name_file_textChanged(const QString &arg1)
{
  QString str = arg1;
  std::string  name_file = str.toStdString();
  name_file.erase(0, 8);
  name_file.erase(name_file.find('\n'));
  decrypt_->SetData(name_file);
  ui->textEdit_your_file_or_message_for_decrypt->setText(
        QString::fromLocal8Bit(decrypt_->GetData()));

}


void WindowDecryption::on_button_insert_file_clicked()
{
  ui->label_key->setText("Перетащите в поле ниже файл с ключом");
  ui->name_file_key->setEnabled(true);
  ui->text_isert_key->hide();
  ui->button_insert_key->hide();
  ui->button_insert_file->hide();
}


void WindowDecryption::on_name_file_key_textChanged(const QString &arg1)
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
      decrypt_->SetKey(str);
      ui->button_ok_insert_key->setEnabled(true);
      ui->name_file_key->setEnabled(false);
    }
  ui->label_key_for_decrypt->setText("Ключом из файла:");
  ui->textEdit_key_for_decrypt->setText(QString::fromLocal8Bit(name_file));
}


void WindowDecryption::on_button_insert_key_clicked()
{
  ui->label_key->setText("Введите Ваш ключ в поле ниже");
  ui->text_isert_key->setEnabled(true);
  ui->text_isert_key->show();
  ui->name_file_key->hide();
  ui->button_insert_key->hide();
  ui->button_insert_file->hide();
}


void WindowDecryption::on_text_isert_key_textChanged()
{
  decrypt_->SetKey(ui->text_isert_key->toPlainText().toStdString());
  ui->button_ok_insert_key->setEnabled(true);
  ui->label_key_for_decrypt->setText("Ключом:");
  ui->textEdit_key_for_decrypt->setText(ui->text_isert_key->toPlainText());
}


void WindowDecryption::on_button_decrypt_clicked()
{
  if(decrypt_->GetType() == encryption::Type::FILE)
    {
      decrypt_->DecryptionData();
    }
  else
    {
      ui->textEdit_result->setText(QString::fromLocal8Bit(decrypt_->DecryptionData(decrypt_->GetData())));
    }
}

