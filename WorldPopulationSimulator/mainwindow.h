#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <vector>
#include <iostream>
#include "worldMapFillLayer.h"
#include "simdeltaoutcome.h"
#include "simulator.h"
#include "sim_helper.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void addContinentsToScene();
    void createContinentOverlays();
    QString getCurSimDate();
    //SimDeltaOutcome run_simulation();

    ~MainWindow();

public Q_SLOTS:
    void updateAnim();
    void updatePopulation();
    void simCalcFinished();

private slots:
    void on_beginSimBtn_clicked();

    void on_resetSimBtn_clicked();

    void on_simRuntimeInput_textEdited(const QString &arg1);

    void on_enableDisastersInput_toggled(bool checked);

    void on_enableMigrationInput_toggled(bool checked);

    void on_continentFocusInput_currentTextChanged(const QString &arg1);

    void on_startDateInput_dateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    QPixmap worldMapView;
    QTimer* timer;
    QTimer* simTimer;
    std::vector<worldMapFillLayer*> continents;
    Sim_Helper* simInfo;
    QFutureWatcher<SimDeltaOutcome> simWatcher;
    QFuture<SimDeltaOutcome> simResults;
    SimDeltaOutcome curSimResults;

    //temp test variables
    int population = 0;
    int day = 0;
    bool running = false; //Tells wether simulation is running
    QFont* dateFont;
    QGraphicsTextItem* shownDate;
};

#endif // MAINWINDOW_H
