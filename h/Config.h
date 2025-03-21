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
#include "h/ClockPainter.h"

bool config_load(const QString& yaml_filename);
bool config_save(const QString& yaml_filename);
bool config_save_default(const QString& yaml_filename);

QString config_get_string(const QString& key);
bool config_get_bool(const QString& key);
int config_get_int(const QString& key);
QColor config_get_color(const QString& key);
ClockPainter* config_get_image(const QString& key);

void config_set_int(const QString& key, int value);

#endif // CONFIG_UTILS_H
