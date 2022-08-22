#include "create_new_key.h"
#include "ui_create_new_key.h"

CreateNewKey::CreateNewKey(QWidget *parent) :
  QWizard(parent),
  ui(new Ui::CreateNewKey)
{
  ui->setupUi(this);
  setWindowTitle("Создание ключа шифрования для Inigma256");
  Start();
}

CreateNewKey::~CreateNewKey()
{
  delete ui;
}

void CreateNewKey::on_checkBox_auto_create_stateChanged(int arg1)
{
  if(arg1)
    {
      ui->groupBox_progress_bar->show();
      ui->label_area_auto_create->show();
      ui->checkBox_yourself->setEnabled(false);
      ui->label_area_auto_create->setEnabled(true);
      ui->label_auto_create->setEnabled(true);
      ui->label_yourself->setEnabled(false);

      ui->label_area_yourself_create->hide();
      ui->area_create_yourself->hide();

      key_.clear();
    }
  else
    {
      ui->checkBox_yourself->setEnabled(true);
      ui->label_yourself->setEnabled(true);

    }
}

void CreateNewKey::mouseMoveEvent(QMouseEvent *pe)
{
  dumpEvent(pe);
}

int CreateNewKey::RandomBetween(int low, int high, int seed)
{
  srand(seed); // Setting a base number for counting a random in qrand
  return (rand() % ((high + 1) - low) + low);
}

void CreateNewKey::on_checkBox_yourself_stateChanged(int arg1)
{
  if(arg1)
    {
      ui->groupBox_progress_bar->show();
      ui->checkBox_auto_create->setEnabled(false);
      ui->label_area_auto_create->setEnabled(false);
      ui->label_auto_create->setEnabled(false);
      ui->label_yourself->setEnabled(true);
      ui->area_create_yourself->setEnabled(true);

      ui->label_area_auto_create->hide();
      ui->label_area_yourself_create->show();
      ui->area_create_yourself->show();

      key_.clear();
    }
  else
    {
      ui->checkBox_auto_create->setEnabled(true);
      ui->label_auto_create->setEnabled(true);
    }
}

void CreateNewKey::dumpEvent(QMouseEvent* pe)
{
  QPoint pos{};

  if(pe->buttons()&Qt::LeftButton
     && pos != pe->pos())
    {
      char ch = static_cast<char>(RandomBetween(32, 254, QDateTime::currentMSecsSinceEpoch()));
      key_.push_back(ch);
      pos = pe->pos();
    }
  ui->progressBar_create_key->setValue(key_.size());
  CutString();
  ui->show_your_key->setText(QString::fromLocal8Bit(key_.c_str()));
  ui->save_key_button->setEnabled(true);
}

void CreateNewKey::on_area_create_yourself_textChanged()
{
  key_ = ui->area_create_yourself->toPlainText().toStdString();
  ui->progressBar_create_key->setValue(key_.size());
  CutString();
  ui->show_your_key->setText(QString::fromLocal8Bit(key_.c_str()));
  ui->save_key_button->setEnabled(true);
}

void CreateNewKey::CutString()
{
  const int MAX = 256;
  while(true)
    {
      auto pos = key_.find('\n');
      if(pos != std::string::npos)
        {
          key_.erase(pos, 1);
        }
      else
        {
          break;
        }
    }
  if(key_.size() > MAX)
    {
      key_.erase(MAX);
    }
}

void CreateNewKey::on_save_key_button_clicked()
{
  QString file_name = QFileDialog::getSaveFileName(this, tr("Save file"));
  std::ofstream file(file_name.toStdString());
  if(file)
    {
      file << key_;
      file.close();
    }

  QMessageBox* p_mb = new QMessageBox(QMessageBox::Information,
                                      "Сообщение",
                                      "<b> Вы сохранили ваш ключ в файл</b> <i>" + file_name
                                      + "</i>",
                                      QMessageBox::Cancel);
  p_mb->exec();

  Start();  
  ui->save_key_button->setEnabled(false);
  ui->show_your_key->clear();
}

void CreateNewKey::Start()
{
  ui->groupBox_progress_bar->hide();
  ui->progressBar_create_key->reset();
  ui->progressBar_create_key->setRange(0, 256);
  ui->progressBar_create_key->setAlignment(Qt::AlignCenter);
  ui->area_auto_create->hide();
  ui->label_area_auto_create->hide();
  ui->area_create_yourself->hide();
  ui->label_area_yourself_create->hide();
  ui->save_key_button->setEnabled(false);  
}

std::string CreateNewKey::GetKey() const
{
  return key_;
}
