#include "care_center.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Care_Center w;

    QIcon icon(":/images/AcerCareCenter.ico");
    // Set the application icon
    a.setWindowIcon(icon);

    w.show();
    return a.exec();
}
