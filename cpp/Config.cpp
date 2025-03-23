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

#include <iostream>
#include <unordered_map>
#include <QTextStream>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QRegularExpression>
#include "h/Config.h"
#include "h/ConfigYAML.h"

YAML::Node default_config = YAML::Load(DEFAULT_CONFIG_YAML);
YAML::Node config;

std::unordered_map<QString, QString> config_map; // Fast & simple, single string, lookup to config

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
    "Boolean",      // NodeType::Bool
    "Number",       // NodeType::Double
    "Scalar",       // NodeType::Scalar
    "Sequence",     // NodeType::Sequence
    "Map",          // NodeType::Map
    "Undefined"     // NodeType::Undefined
};

NodeType config_node_type(const YAML::Node& node) {
    switch (node.Type()) {
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

        case YAML::NodeType::Null:
            return NodeType::Null;

        case YAML::NodeType::Sequence:
            return NodeType::Sequence;

        case YAML::NodeType::Map:
            return NodeType::Map;

        case YAML::NodeType::Undefined:
        default:
            return NodeType::Undefined;
    }
}

YAML::Node config_merge(QString root, const YAML::Node& default_config, const YAML::Node& config) {
    YAML::Node merged_config = default_config;
    for (const auto& entry : config) {
        const std::string& key = entry.first.as<std::string>();
        QString qkey = QString::fromStdString(key);
        qkey = (root == "" ? qkey : root + "." + qkey);

        if (default_config[key].IsMap() && config[key].IsMap()) {
            merged_config[key] = config_merge(qkey, default_config[key], config[key]);
            continue;
        }

        QString value = config[key].as<std::string>().c_str();
        if (default_config[key]) {
            NodeType left = config_node_type(default_config[key]);
            NodeType right = config_node_type(config[key]);
            if (left != right) {
                std::cout
                    << "*** Error: Incompatible types for key "
                    << "'" << key << "' in yaml config file.\n"
                    << "           "
                    << "Must be of type " << NodeTypeStr[static_cast<int>(left)]
                    << " but is of type " << NodeTypeStr[static_cast<int>(right)] << ".\n"
                    << "           Using default value: " << default_config[key]
                    << std::endl;

                value = default_config[key].as<std::string>().c_str(); // Overwrite
            }
        }

        config_map[qkey] = value;
    }
    return merged_config;
}

bool config_load(const QString& yaml_filename) {
    try {
        config = YAML::LoadFile(yaml_filename.toStdString());
        config = config_merge("", default_config, config);
        return true;
    } catch (const std::exception& e) {
        config = config_merge("", default_config, default_config);
        return false;
    }
}

bool config_save_yaml(const QString& yaml_filename, std::string yaml_config, bool overwrite) {
    try {
        if (!overwrite) {
            QFileInfo fileInfo(yaml_filename);
            if (fileInfo.isFile()) {
                return false;
            }
        }

        QFile file(yaml_filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << QString::fromStdString(yaml_config);
            file.close();

            return true;
        }

        return false;
    } catch (const std::exception& e) {
        return false;
    }
}

bool config_save(const QString& yaml_filename, bool overwrite) {
    return config_save_yaml(yaml_filename, YAML::Dump(config), overwrite);
}

bool config_save_default(const QString& yaml_filename, bool overwrite) {
    return config_save_yaml(yaml_filename,DEFAULT_CONFIG_YAML, overwrite);
}

QString config_get_replace(QString& str) {
    if (str == "transparent" || str == "none" || str == "null" || str == "") {
        return "";
    }

    QRegularExpression regex("\\$\\{([^}]+)\\}");
    QRegularExpressionMatchIterator i = regex.globalMatch(str);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString key = match.captured(1);
        QString replacement = config_map[key];

        str.replace(match.capturedStart(0), match.capturedLength(0), replacement);

        QRegularExpression regex("\\$\\{([^}]+)\\}"); // ??
        i = regex.globalMatch(str);
    }

    return str;
}

QString config_get_string(const QString& key) {
    QString value = config_map[key];
    return config_get_replace(config_map[key]);
}

bool config_get_bool(const QString& key) {
    return config_get_string(key) == "true";
}

int config_get_int(const QString& key) {
    QString str = config_get_string(key);

    bool ok;
    int value = str.toInt(&ok);
    if (!ok) {
        std::cout << "*** Error: " << key.toStdString() << " is not of type int: '" << str.toStdString() <<"'" << std::endl;
        return 0;
    }

    return value;
}

QColor config_get_color(const QString& key) {
    return QColor(config_get_string(key));
}

QString config_get_image(const QString& key) {
    QString image_str = config_get_string(key);

    if (image_str.startsWith("$:")) {
        image_str.remove(0, 2);

        QFile file(image_str);
        if (!file.open(QIODevice::ReadOnly)) {
            std::cout << "*** Error: Can't open file " << image_str.toStdString() << std::endl;
            return nullptr;
        }

        if (image_str.endsWith(".svg")) {
            image_str = file.readAll();
        }
        else {
            QByteArray imageData = file.readAll();
            image_str = "data:image/" + QFileInfo(image_str).suffix() + ";base64," + imageData.toBase64();
        }
        file.close();
    }

    image_str = config_get_replace(image_str);
    if (image_str == "") {
        return nullptr;
    }

    return image_str;
}

void config_set_int(const QString& key, int value) {
    config_map[key] = QString::number(value);

    YAML::Node* node = &config;
    QStringList keys = key.split('.');
    for (int i = 0; i < keys.size() - 1; ++i) {
        YAML::Node temp = (*node)[keys[i].toStdString()];
        node = &temp;
    }
    (*node)[keys.last().toStdString()] = value;
}
