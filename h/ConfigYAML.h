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

void config_load(const QString& yaml_filename);
bool config_save(const QString& yaml_filename);

int config_get_int(const QString& key);
bool config_get_bool(const QString& key);
QString config_get_str(const QString& key);
QColor config_get_qcolor(const QString& key);

#endif // CONFIG_UTILS_H
