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

extern YAML::Node config;

bool config_load(const QString& yaml_filename);
bool config_save(const QString& yaml_filename);
bool config_save_default(const QString& yaml_filename);

QColor config_qcolor(const YAML::Node& node);

#endif // CONFIG_UTILS_H
