#include "carecenter.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Override Qt's logging rules to enable debug messages, disable for release
    QLoggingCategory::setFilterRules("*.debug=true\n*.warning=true\n*.critical=true\nqt.*.debug=false");
    //QLoggingCategory::setFilterRules("*.debug=true\nqt.*.debug=false");

    CareCenter w;
    w.show();
    return a.exec();
}
