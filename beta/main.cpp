#include <QApplication>
#include "betascene.h"
#include "skplot2d.h"
#include "skviewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SKViewer viewer("Beta data viewer");

    BetaScene scene(&viewer);

    viewer.resize(900, 600);
    scene.resize(1000, 700);

    viewer.show();
    scene.show();

    return app.exec();
}
