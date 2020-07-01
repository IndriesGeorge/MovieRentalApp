#include "MovieRentalAppV3.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "Repository.h"
#include "Service.h"
#include "GUI.h"

int main(int argc, char *argv[])
{

    test_all();

    {
        QApplication a(argc, argv);
        Repository rep{ "movies_new.csv" };
        Validator val;
        Service serv{ rep,val };
        GUI gui{ serv };
        gui.show();
        return a.exec();
    }
    
}
