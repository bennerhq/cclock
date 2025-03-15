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
#include <QTextStream>
#include <QString>
#include <iostream>
#include "h/ConfigYAML.h"
#include "h/ConfigDefault.h"

YAML::Node config;

enum class NodeType {
    Null,
    String,
    Bool,
    Double,
    Scalar,
    Sequence,
    Map,
    Undefined
};
static const char* NodeTypeStr[] = {
    "Null",         // NodeType::Null
    "String",       // NodeType::String
    "true | false", // NodeType::Bool
    "Number",       // NodeType::Double
    "Scalar",       // NodeType::Scalar
    "Sequence",     // NodeType::Sequence
    "Map",          // NodeType::Map
    "Undefined"     // NodeType::Undefined
};

NodeType config_node_type(const YAML::Node& node) {
    switch (node.Type()) {
        case YAML::NodeType::Null:
            return NodeType::Null;

        case YAML::NodeType::Scalar:
            try {
                node.as<double>();
                return NodeType::Double;
            } catch (...) {
                try {
                    node.as<bool>();
                    return NodeType::Bool;
                } catch (...) {
                    try {
                        node.as<std::string>();
                        return NodeType::String;
                    } catch (...) {
                        // ...
                    }
                }
            }
            return NodeType::Scalar;

        case YAML::NodeType::Sequence:
            return NodeType::Sequence;

        case YAML::NodeType::Map:
            return NodeType::Map;

        case YAML::NodeType::Undefined:
        default:
            return NodeType::Undefined;
    }
}

YAML::Node config_merge(const YAML::Node& default_config, const YAML::Node& config) {
    YAML::Node merged_config = default_config;
    for (const auto& entry : config) {
        const std::string& key = entry.first.as<std::string>();
        if (default_config[key]) {
            if (default_config[key].IsMap() && config[key].IsMap()) {
                merged_config[key] = config_merge(default_config[key], config[key]);
            } else {
                NodeType left = config_node_type(default_config[key]);
                NodeType right = config_node_type(config[key]);
                if (left != right) {
                    std::cout
                        << "*** Error: Incompatible types for key "
                        << "'" << key << "' in yaml config file.\n"
                        << "           "
                        << "Must be of type " << NodeTypeStr[static_cast<int>(left)]
                        << " but is of type " << NodeTypeStr[static_cast<int>(right)]
                        << std::endl;
                }
                else {
                    merged_config[key] = config[key]; // Overwrite
                }
            }
        } else {
            merged_config[key] = config[key]; // New key value pair
        }
    }
    return merged_config;
}

bool config_load(const QString& yaml_filename) {
    bool res = false;
    try {
        QFileInfo fileInfo(yaml_filename);
        if (fileInfo.isFile()) {
            config = YAML::LoadFile(yaml_filename.toStdString());
            res = true;
        }
    } catch (const std::exception& e) {
        // ...
    }

    config = config_merge(default_config, config);
    return res;
}

bool config_save_yaml(const QString& yaml_filename, YAML::Node& config) {
    try {
        QFile file(yaml_filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << QString::fromStdString(YAML::Dump(config));
            file.close();

            return true;
        } else {
            return false;
        }
    } catch (const std::exception& e) {
        return false;
    }
}

bool config_save(const QString& yaml_filename) {
    return config_save_yaml(yaml_filename, config);
}

bool config_save_default(const QString& yaml_filename) {
    return config_save_yaml(yaml_filename, default_config);
}

QColor config_qcolor(const YAML::Node& node) {
    std::string color = node.as<std::string>();

    if (color == "transparent" || color == "none" || color == "null" || color == "") {
        return QColor();
    }

    return QColor(color.c_str());
}
