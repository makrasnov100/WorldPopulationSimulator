#include "mainwindow.h"
#include "worldMapFillLayer.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->worldMapView->setScene(scene);
    ui->worldMapView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //Load the requred Resources for animation to run
    QImage worldMap("://Resources/WorldMap.png");
    worldMapView = QPixmap::fromImage(worldMap);
    worldMapView = worldMapView.scaled(1510, 744, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    //Begin Time that tells how much time passed total since simulation start
    simTimer = new QTimer(this);
    connect(simTimer, SIGNAL(timeout()), this, SLOT(updatePopulation()));
    simTimer->start(100); //FIX ME - currently just adds population every second

    //Begin Timer that calls the updates of frames
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnim())); //an update tenth of a second
    timer->start(100);

    //Background for the world map
    scene->addPixmap(worldMapView);

    //Create continent overalys
    createContinentOverlays();

    //Add continent layers to scene
    addContinentsToScene();
    updateAnim();

    //Create the input/calculation storage class
    simInfo = new Sim_Helper();
}

//Central function that updates the entire map by going through each continent
void MainWindow::updateAnim()
{
    for(int i = 0; i < (int)continents.size(); i++)
    {
        continents[i]->calculateState(running, population);
        QWidget* viewport = ui->worldMapView->viewport();
        viewport->repaint();
    }
}

//Updates the population amount of each country
void MainWindow::updatePopulation()
{
    if(running)
        population++;
}

//Adds continent overlay items to storage vector
void MainWindow::createContinentOverlays()
{
    //Object creation using Overlay constructor
    worldMapFillLayer* Asia = new worldMapFillLayer("Asia", 17.21,.02,0.0);
    worldMapFillLayer* Africa = new worldMapFillLayer("Africa", 11.73,.02,0.0);
    worldMapFillLayer* Australia = new worldMapFillLayer("Australia", 3.32,.02,0.0);
    worldMapFillLayer* Europe = new worldMapFillLayer("Europe", 3.931,.02,0.0);
    worldMapFillLayer* NorthAmerica = new worldMapFillLayer("NorthAmerica", 9.54,.02,0.0);
    worldMapFillLayer* SouthAmerica = new worldMapFillLayer("SouthAmerica", 6.888,.02,0.0);
    //Pushing all continents into the storage vector
    continents.push_back(Asia);
    continents.push_back(Africa);
    continents.push_back(Australia);
    continents.push_back(Europe);
    continents.push_back(NorthAmerica);
    continents.push_back(SouthAmerica);
}

//Adds continent ovelays to scene (done once)
void MainWindow::addContinentsToScene()
{
    for(int i = 0; i < (int)continents.size(); i++)
        scene->addItem(continents[i]);
}

MainWindow::~MainWindow()
{
    //Remove overlay items (FIXME: check if unneeded)
    while(continents.size() != 0)
    {
        scene->removeItem(continents[0]);
        delete continents[0];
        continents.erase(continents.begin());
    }
    delete simInfo;
    delete ui;
}

void MainWindow::on_beginSimBtn_clicked()
{
    if(!running)
    {
        ui->beginSimBtn->setText("Pause Simulation");
        running = true;
    }
    else
    {
        ui->beginSimBtn->setText("Begin Simulation");
        running = false;
    }
}

void MainWindow::on_resetSimBtn_clicked()
{
    population = 0;
    if(running)
    {
        running=false;
        ui->beginSimBtn->setText("Begin Simulation");
    }
}

void MainWindow::on_simRuntimeInput_textEdited(const QString &arg1)
{
    simInfo->runtime = arg1.toInt();
}

void MainWindow::on_enableDisastersInput_toggled(bool checked)
{
    simInfo->enableDisaster = checked;
}

void MainWindow::on_enableMigrationInput_toggled(bool checked)
{
    simInfo->enableMigration = checked;
}

void MainWindow::on_continentFocusInput_currentTextChanged(const QString &arg1)
{
    simInfo->continentFocus = arg1.toUtf8().constData();;
}

void MainWindow::on_startDateInput_dateChanged(const QDate &date)
{
    simInfo->startDate = date;
}
