#include "BatteryManager.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //attempts to make icons work
    QGuiApplication::setDesktopFileName("Acer Battery Manager");
    QCoreApplication::setApplicationName("Acer Battery Manager");

    QCoreApplication::setApplicationVersion("1.1");

    // Set up command-line parser
    QCommandLineParser parser;
    parser.setApplicationDescription("Change Acer specific battery settings");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption logOption("enable-logging", "Enable detailed logging output.");
    parser.addOption(logOption);

    // Process the command-line arguments
    parser.process(app);

    // Enable logging if argument sets it
    if (parser.isSet(logOption)) {
        QLoggingCategory::setFilterRules("*.debug=true\n*.warning=true\n*.critical=true\nqt.*.debug=false");
    }

    BatteryManager window;
    window.show();
    return app.exec();
}
