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

#include <QColor>

void config_load(const std::string& yaml_filename);

int config_get_int(const std::string& key);
bool config_get_bool(const std::string& key);
std::string config_get_str(const std::string& key);
QColor config_get_qcolor(const std::string& key);

#endif // CONFIG_UTILS_H
