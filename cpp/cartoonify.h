#pragma once

#include <lenna/plugins/editplugin.h>
#include "widget.h"

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtGui/QIcon>

namespace lenna {
namespace plugin {
namespace cartoonify {

class Cartoonify : public EditPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.cartoonify" FILE "cartoonify.json")
  Q_INTERFACES(lenna::plugin::EditPlugin)

 public:
  Cartoonify();
  ~Cartoonify();
  std::string getName();
  std::string getTitle();
  std::string getVersion();
  std::string getAuthor();
  std::string getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  void edit(std::shared_ptr<LennaImage> image);

  std::shared_ptr<Plugin> getInstance(QString uid);

 private:
  Widget *widget;
};
}
}
}