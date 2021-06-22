/**
    This file is part of program Lenna
    Copyright (C) 2013-2016 FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cartoonify.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::cartoonify;

Cartoonify::Cartoonify() { widget = 0; }

Cartoonify::~Cartoonify() {
  if (this->widget) delete this->widget;
}

std::string Cartoonify::getName() { return std::string("cartoonify"); }

std::string Cartoonify::getTitle() { return tr("Cartoonify").toStdString(); }

std::string Cartoonify::getVersion() { return std::string("0.1"); }

std::string Cartoonify::getAuthor() { return std::string("chriamue"); }

std::string Cartoonify::getDescription() { return tr("gives images cartoon style").toStdString(); }

QIcon Cartoonify::getIcon() { return QIcon(":/plugins/cartoonify/cartoonify"); }

QWidget *Cartoonify::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void Cartoonify::edit(std::shared_ptr<LennaImage> img) {
  int size = widget->getRadius();
  cv::blur(img->getImage(), img->getImage(), cv::Size(size, size));
}

std::shared_ptr<Plugin> Cartoonify::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Cartoonify());
  plugin->setUID(uid);
  return plugin;
}
