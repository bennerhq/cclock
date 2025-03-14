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
#include <string>
#include <filesystem>
#include <cstdlib>

#include <QCommandLineParser>
#include <QApplication>
#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QFileInfo>

#include "h/ConfigYAML.h"
#include "h/ClockWidget.h"
#include "h/ClockWindow.h"

QString find_config_file(char* arg_path) {
    // Find the name of the script
    QFileInfo fileInfo0(arg_path);
    QString script_name = fileInfo0.fileName() + ".yaml";

    // Check for a config file in the user's home directory
    QString home_config_path = QString(getenv("HOME")) + "/." + script_name + ".yaml";
    QFileInfo fileInfo1(home_config_path);
    if (fileInfo1.isFile()) {
        return home_config_path;
    }  

    // Check for a config file is places where the script is run from
    QString local_config_path = QCoreApplication::applicationDirPath() + "/" + script_name;
    QFileInfo fileInfo2(local_config_path);
    if (fileInfo2.isFile()) {
        return local_config_path;
    }

    // If no config file is found, return a default sceipt name
    return script_name;
}

int main(int argc, char *argv[]) {
    ::setenv("QT_QPA_PLATFORM", "xcb", 1);

    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Analog Clock");
    parser.addHelpOption();

    QCommandLineOption configLoad(QStringList() << "c" << "config", "Path to the configuration file.", "config");
    parser.addOption(configLoad);

    QCommandLineOption configSave(QStringList() << "d" << "default", "Save default configuration to a file.", "config");
    parser.addOption(configSave);

    QCommandLineOption configShow(QStringList() << "s" << "show", "Show configuration.");
    parser.addOption(configShow);

    parser.addPositionalArgument("config", "Path to the configuration file.");
    parser.process(app);

    if (parser.isSet(configSave)) {
        QString config_path = parser.value(configSave);
        bool res = config_save(config_path);
        std::cout
            << (res ? "Saved" : "Can't save") 
            << " config file: " << config_path.toStdString() 
            << std::endl;
    }

    QString config_path;
    if (parser.isSet(configLoad)) {
        config_path = parser.value(configLoad);
    } else if (parser.positionalArguments().size() > 0) {
        config_path = parser.positionalArguments().at(0);
    } else {
        config_path = find_config_file(argv[0]);
    }
    config_load(config_path);

    if (parser.isSet(configShow)) {
        std::cout << "Config file: " << config_path.toStdString() << std::endl;
    }

    ClockWindow win;
    win.show();

    return app.exec();
}
