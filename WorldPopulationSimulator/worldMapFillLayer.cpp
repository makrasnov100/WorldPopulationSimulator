#include "worldMapFillLayer.h"

//[Constructors]
worldMapFillLayer::worldMapFillLayer()
{
    continentName = "Other";
    fillOpacity = 0.0;
    landArea = 10.0;
    fillMultiplier = 1.0;
    qCritical("Error: DO NOT DECLARE A FILL LAYER W/O ANY IMAGE - Loaded default values");
};

worldMapFillLayer::worldMapFillLayer(std::string continent,
                                     double area,
                                     double fillMultiplier,
                                     double initOpacity)
{
    continentName = continent;
    setPixmap(continentName);
    fillOpacity = initOpacity;
    this->fillMultiplier = fillMultiplier;
    landArea = area;
}

//Updates the opacity for current fill layer
//@param: running - tells wether animation is running
//@param: population - amount of people on the continent
//@param: population - amount of people on the continent
void worldMapFillLayer::calculateState(bool running, double population)
{
    if(!running)
        fillOpacity = 0.0;

    fillOpacity = std::fmin(1, (population/landArea) * fillMultiplier);

    //DEBUG CODE
    //std::cout << std::showpoint << std::fixed << std::setprecision(4) << fillOpacity
    //          << population << "/" << landArea << " * " << fillMultiplier << std::endl;
    //std::cout << "FillOpacity updated: " << std::showpoint << std::fixed << std::setprecision(4) << fillOpacity << std::endl;
}

//Paints the layer on the map
void worldMapFillLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //DEBUG CODE
    //std::cout << "Repainted with fill opacity: " << std::showpoint
    //          << std::fixed << std::setprecision(4)<< fillOpacity << std::endl;

    painter->setOpacity(fillOpacity);
    painter->drawPixmap(0,0,1510,744, fillImage);
}

//Loads in the needed image
//@param: landName - if not given a parameter will return full overlay
void worldMapFillLayer::setPixmap(std::string landName)
{
    //Locate file in directory
    std::string location;
    if(landName == "Other")
    {
        location = "://Resources/WorldMapFilled.png";
        qInfo("Warning: the entrire map fill layer was loaded.");
    }
    else //FIXME add checks to see if files actually there
    {
        location = "://Resources/" + landName + ".png";
    }

    //Convert found image to a pix map and store w/ correct resolution
    QString strLocation = QString::fromUtf8(location.c_str());
    fillImage = QPixmap(strLocation);
    fillImage = fillImage.scaled(1510, 744, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}


QRectF worldMapFillLayer::boundingRect() const
{
    return QRect(0,0,1510,744);
}

//[ACCESSOR(S)/MUTATOR(S)]
QPixmap worldMapFillLayer::getFillImage()
{
    return fillImage;
}
