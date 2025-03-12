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

#include <filesystem>
#include <yaml-cpp/yaml.h>

#include <QDebug>

#include "h/ConfigYAML.h"

namespace fs = std::filesystem;

YAML::Node config;

YAML::Node default_config = YAML::Load(R"(
    colors:
        background: '#00FFFFFF'
        dial: '#00FFFFFF'

        hour_mark: '#000000'
        minute_mark: '#000000'
        second_hand: '#FF0000'
        hour_hand: '#000000'
        minute_hand: '#000000'

        date_background: '#000000'
        date: '#FFFFFF'
        date_font: 'Courier New'

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
                // Recursively merge nested maps
                merged_config[key] = merge_configs(default_config[key], config[key]);
            } else {
                // Otherwise, overwrite with the value from config
                merged_config[key] = config[key];
            }
        } else {
            // Add the key-value pair from config to merged_config
            merged_config[key] = config[key];
        }
    }
    return merged_config;
}

void config_load(const std::string& yaml_filename) {
    try {
        if (fs::exists(yaml_filename)) {
            config = YAML::LoadFile(yaml_filename);
        } else {
            qDebug() << "Configuration file not found: " << yaml_filename.c_str() << ". Using default settings.";
        }
    } catch (const std::exception& e) {
        qDebug() << "An unexpected error occurred: " << e.what() << ". Using default settings.";
    }

    config = merge_configs(default_config, config);
}

template <typename T>
T get_value(const std::string& key) {
    std::string s = key;
    size_t pos = 0;
    YAML::Node current_config = YAML::Clone(config); // FIXME

    while (current_config && (pos = s.find(".")) != std::string::npos) {
        std::string token = s.substr(0, pos);
        if (!current_config[token]) break;

        current_config = current_config[token];
        s.erase(0, pos + 1);
    }

    if (!current_config || !current_config[s]) {
        qDebug() << "*** ERROR: Key not found: " << key.c_str();
        exit(1);
    }

    return current_config[s].as<T>();
}

int config_get_int(const std::string& key) {
    return get_value<int>(key);
}

bool config_get_bool(const std::string& key) {
    return get_value<bool>(key);
}

std::string config_get_str(const std::string& key) {
    return get_value<std::string>(key);
}

QColor config_get_qcolor(const std::string& key) {
    std::string value = config_get_str(key);

    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    if (value == "" || value == "none" || value == "transparent") {
        return QColor(0, 0, 0, 0);
    }

    return QColor(value.c_str());
}
