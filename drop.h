#pragma once

#include <QtWidgets>

class Drop : public QLineEdit
{
  Q_OBJECT
public:
  Drop(QWidget* parent = nullptr);

  virtual void clear();
protected:
  virtual void dragEnterEvent(QDragEnterEvent* pe);

  virtual void dropEvent(QDropEvent* pe);  
};
