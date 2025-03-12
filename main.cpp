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

#include <QCommandLineParser>
#include <QApplication>

#include "h/yamlConfig.h"
#include "h/ClockWidget.h"
#include "h/ClockWindow.h"

namespace fs = std::filesystem;

// ----------------------------------------------------------------------------
// Main entry point
//
std::string find_config_file(char* exec_filename) {
    // Find the name of the script
    std::string script_name = std::string(exec_filename) + ".yaml";

    // Check for a config file in the user's home directory
    std::string home_config_path = std::string(getenv("HOME")) + "/." + script_name;
    if (fs::exists(home_config_path)) {
        return home_config_path;
    }  

    // Check for a config file with the same name as the script
    auto current_path = fs::current_path();
    std::string local_config_path = current_path.string() + "/" + script_name;
    if (fs::exists(local_config_path)) {
        return local_config_path;
    }

    // If no config file is found, return a default name
    return script_name;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Analog Clock");
    parser.addHelpOption();
    QCommandLineOption configOption(QStringList() << "c" << "config", "Path to the configuration file.", "config");
    parser.addOption(configOption);
    parser.addPositionalArgument("config", "Path to the configuration file.");
    parser.process(app);

    std::string config_path;
    if (parser.isSet(configOption)) {
        config_path = parser.value(configOption).toStdString();
    } else if (parser.positionalArguments().size() > 0) {
        config_path = parser.positionalArguments().at(0).toStdString();
    } else {
        config_path = find_config_file(argv[0]);
    }

    std::cout << "Config file: " << config_path.c_str() << std::endl;
    
    config_load(config_path);

    ClockWindow win;
    win.show();

    return app.exec();
}
