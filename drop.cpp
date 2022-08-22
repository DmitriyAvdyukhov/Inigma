#include "drop.h"

Drop::Drop(QWidget* parent) : QLineEdit(parent)
{
  setAcceptDrops(true);
}
void Drop::dragEnterEvent(QDragEnterEvent* pe)
{
  if(pe->mimeData()->hasFormat("text/uri-list"))
    {
      pe->accept(rect());
      pe->acceptProposedAction();
    }
}

void Drop::dropEvent(QDropEvent* pe)
{
  QList<QUrl>url_list = pe->mimeData()->urls();
  QString str;
  foreach(QUrl url, url_list)
    {
      str += url.toString() + "\n";
    }
  setText(str);
}

void Drop::clear()
{
  setText("");
}
