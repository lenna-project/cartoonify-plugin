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
#include "base64.h"

#include <QtGui/QPainter>

#include <lenna_cartoonify_plugin.hpp>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::cartoonify;

Cartoonify::Cartoonify() { widget = 0; }

Cartoonify::~Cartoonify()
{
  if (this->widget)
    delete this->widget;
}

std::string Cartoonify::getName() { return std::string(lenna_plugin_name()); }

std::string Cartoonify::getTitle() { return std::string(lenna_plugin_title()); }

std::string Cartoonify::getVersion() { return std::string(lenna_plugin_version()); }

std::string Cartoonify::getAuthor() { return std::string(lenna_plugin_author()); }

std::string Cartoonify::getDescription() { return std::string(lenna_plugin_description()); }

QIcon Cartoonify::getIcon() { return QIcon(":/plugins/cartoonify/cartoonify"); }

QWidget *Cartoonify::getWidget()
{
  if (!this->widget)
  {
    this->widget = new Widget();
  }
  return this->widget;
}

void Cartoonify::edit(std::shared_ptr<LennaImage> img)
{
  std::vector<uchar> buf;
  cv::imencode(".png", img->getImage(), buf);
  auto *enc_msg = reinterpret_cast<unsigned char *>(buf.data());
  std::string encoded = base64_encode(enc_msg, buf.size());
  std::string processed(lenna_plugin_process_base64(encoded.c_str()));
  std::string dec_png = base64_decode(processed);
  std::vector<uchar> data(dec_png.begin(), dec_png.end());
  cv::Mat processed_img = cv::imdecode(cv::Mat(data), 1);
  img->setMat(processed_img);
}

std::shared_ptr<Plugin> Cartoonify::getInstance(QString uid)
{
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Cartoonify());
  plugin->setUID(uid);
  return plugin;
}
