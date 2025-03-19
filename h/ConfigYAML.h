// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 43):
//
// Github Co-pilot & <jens@bennerhq.com> wrote this file.  As long as you 
// retain this notice you can do whatever you want with this stuff. If we meet 
// some day, and you think this stuff is worth it, you can buy me a beer in 
// return.   
//
// /benner
// ----------------------------------------------------------------------------

#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H

#include <string>
#include <yaml-cpp/yaml.h>
#include <QColor>
#include <QSvgRenderer>
#include "h/ClockPainter.h"

extern YAML::Node config;

bool config_load(const QString& yaml_filename);
bool config_save(const QString& yaml_filename);
bool config_save_default(const QString& yaml_filename);

QString config_get_string(const YAML::Node& node);
int config_get_int(const YAML::Node& node);
QColor config_get_color(const YAML::Node& node);
ClockPainter* config_get_image(YAML::Node config);

#endif // CONFIG_UTILS_H
