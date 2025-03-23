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
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QRegularExpression>
#include <QImage>
#include <QDebug>
#include "h/Config.h"
#include "h/ConfigYAML.h"

YAML::Node config;
std::unordered_map<QString, QString> config_map;

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

    config = config_merge("", default_config, config);
    return res;
}

bool config_save_yaml(const QString& yaml_filename, YAML::Node& config, bool overwrite) {
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
            out << QString::fromStdString(YAML::Dump(config));
            file.close();

            return true;
        }

        return false;
    } catch (const std::exception& e) {
        return false;
    }
}

bool config_save(const QString& yaml_filename, bool overwrite) {
    return config_save_yaml(yaml_filename, config, overwrite);
}

bool config_save_default(const QString& yaml_filename, bool overwrite) {
    return config_save_yaml(yaml_filename, default_config, overwrite);
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
        std::cout << "*** Error: " << key.toStdString() << " is not of type int: " << str.toStdString() << std::endl;
        return 0;
    }

    return value;
}

QColor config_get_color(const QString& key) {
    return QColor(config_get_string(key));
}

ClockPainter* config_get_image(const QString& key) {
    QString svg_str = config_get_string(key);

    if (svg_str.startsWith("$:")) {
        svg_str.remove(0, 2);
        if (svg_str.endsWith(".svg")) {
            QFile file(svg_str);
            if (file.open(QIODevice::ReadOnly)) {
                svg_str = file.readAll();
                file.close();
            }
            else {
                std::cout << "*** Error: Can't open file " << svg_str.toStdString() << std::endl;
                return nullptr;
            }
        }
        else {
            QImage* image = new QImage(svg_str);
            if (image->isNull()) {
                std::cout << "*** Error: Can't read image: " << svg_str.toStdString() << std::endl;

                delete image;
                return nullptr;
            }
            return new BitmapClockPainter(image);
        }
    }
    else if (svg_str.startsWith("data:image/")) {
        QString base64Data = svg_str;
        if (base64Data.startsWith("data:image/")) {
            int commaIndex = base64Data.indexOf(',');
            if (commaIndex != -1) {
                base64Data = base64Data.mid(commaIndex + 1);
            }
        }

        QByteArray byteArray = QByteArray::fromBase64(base64Data.toUtf8());
        QImage* image = new QImage();
        if (!image->loadFromData(byteArray)) {
            std::cout << "*** Error: Can't create image from base64 image" << std::endl;

            delete image;
            return nullptr;
        }
        return new BitmapClockPainter(image);
    }

    svg_str = config_get_replace(svg_str);
    if (svg_str == "") {
        return nullptr;
    } 

    QSvgRenderer* renderer = new QSvgRenderer();
    try {
        QByteArray svg_byte = svg_str.toUtf8();
        renderer->load(svg_byte);
        return new SvgClockPainter(renderer);
    } catch (...) {
        delete renderer;
        return nullptr;
    }
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
