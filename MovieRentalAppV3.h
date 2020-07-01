#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MovieRentalAppV3.h"

class MovieRentalAppV3 : public QMainWindow
{
    Q_OBJECT

public:
    MovieRentalAppV3(QWidget *parent = Q_NULLPTR);

private:
    Ui::MovieRentalAppV3Class ui;
};
