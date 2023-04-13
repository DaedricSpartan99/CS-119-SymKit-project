#include <QApplication>
#include "alphascene.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    AlphaScene scene;

    scene.show();

    return app.exec();
}
