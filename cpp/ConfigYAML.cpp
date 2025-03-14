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

#include <yaml-cpp/yaml.h>

#include <QFileInfo>
#include <QDebug>

#include "h/ConfigYAML.h"

YAML::Node config;

YAML::Node default_config = YAML::Load(R"(
    colors:
        background: '#00FFFFFF'
        dial: '#00FFFFFF'

        date_background: '#000000'
        date: '#FFFFFF'
        date_font: 'Courier New'

        hour_mark: '#000000'
        minute_mark: '#000000'

        second_hand: '#FF0000'
        hour_hand: '#000000'
        minute_hand: '#000000'
        middle_dot: '#000000'

    window:
        frameless: true
        always_on_top: true
        tool: true
        x: -200
        y: -200
        width: 200
        height: 200
)");

YAML::Node merge_configs(const YAML::Node& default_config, const YAML::Node& config) {
    YAML::Node merged_config = default_config;
    for (const auto& entry : config) {
        const std::string& key = entry.first.as<std::string>();
        if (default_config[key]) {
            if (default_config[key].IsMap() && config[key].IsMap()) {
                merged_config[key] = merge_configs(default_config[key], config[key]);
            } else {
                merged_config[key] = config[key]; // Overwrite
            }
        } else {
            merged_config[key] = config[key]; // New key value pair
        }
    }
    return merged_config;
}

void config_load(const QString& yaml_filename) {
    try {
        QFileInfo fileInfo(yaml_filename);
        if (fileInfo.isFile()) {
            config = YAML::LoadFile(yaml_filename.toStdString());
        } else {
            qDebug() << "Configuration file not found: " << yaml_filename << ". Using default settings.";
        }
    } catch (const std::exception& e) {
        qDebug() << "An unexpected error occurred: " << e.what() << ". Using default settings.";
    }

    config = merge_configs(default_config, config);
}

bool config_save(const QString& yaml_filename) {
    try {
        QFile file(yaml_filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << QString::fromStdString(YAML::Dump(default_config));
            file.close();

            return true;
        } else {
            return false;
        }
    } catch (const std::exception& e) {
        return false;
    }
}

template <typename T>
T get_value(const QString& key) {
    QString s = key;
    QStringList tokens = s.split('.');
    YAML::Node current = YAML::Clone(config);

    for (const QString& token : tokens) {
        std::string token_std = token.toStdString();
        if (!current || !current[token_std]) {
            qDebug() << "*** ERROR: Key not found: " << key;
            exit(1);
        }
        current = current[token_std];
    }

    return current.as<T>();
}

int config_get_int(const QString& key) {
    return get_value<int>(key);
}

bool config_get_bool(const QString& key) {
    return get_value<bool>(key);
}

QString config_get_str(const QString& key) {
    return get_value<std::string>(key).c_str();
}

QColor config_get_qcolor(const QString& key) {
    QString value = config_get_str(key);

    if (value == "" || value == "none" || value == "transparent") {
        return QColor(0, 0, 0, 0);
    }

    return QColor(value);
}
