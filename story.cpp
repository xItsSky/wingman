#include "story.h"
#include "ui_story.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QFontDatabase>
#include <QThread>
#include <QTimer>


void Story::firstScene(){
    this->centralWidget()->setStyleSheet("QWidget#storyBackground {background-image: url(':images/Images/Plan de travail 1.jpg')}");
    this->displayText("Il etait une fois, dans une contree eloigne, a une epoque que le temps a effacer de la memoire des hommes...");
    this->clearMapTimer();
    this->createTimer(1,"un jeune garçon du nom de Sahri.",true);
    this->createTimer(2,"Nul ne savait d’ou il venait ni qui il avait pour parents.",true);
    this->createTimer(3,"Certains racontait même qu’il était le fils des étoiles et de la lune.",true);
}

void Story::secondScene(){
    this->centralWidget()->setStyleSheet("QWidget#storyBackground {background-image: url(':images/Images/desert.png')}");
    this->displayText("Un jour, alors que tout était calme, le jeune Sahri rencontra un homme tout de blanc vêtu. ");
    this->clearMapTimer();
    this->createTimer(1,"A ses côtés se tenait une jeune fille, dont le visage était masqué par une épaisse brume.",true);
    this->createTimer(2,"Le jeune Sahri s’arrêta alors, contempla la jeune fille si mystérieuse et sentit soudain sa poitrine se déchirer.",true);
    this->createTimer(3,"\"Qui êtes vous ?\" interrogea le jeune homme ?",true);
    this->createTimer(4,"\"Je me nomme Gaïen et voici ma fille Elëia, nous sommes les seules représentants de notre peuple disparu.\"",true);
    this->createTimer(5,"\"Et toi qui es tu ?\" rétorqua Gaïen.",true);
    this->createTimer(6,"\"Je me nomme Sahri, je suis seul sur ces terres depuis si longtemps que je ne puis me rappeler le dernier visage que j'ai pu contempler.\"",true);
    this->createTimer(7,"\"Mais pourquoi le visage de votre fille est-il couvert par la brume ?\".",true);
}

void Story::thirdScene(){
    this->centralWidget()->setStyleSheet("QWidget#storyBackground {background-image: url(':images/Images/CitySahri.jpg')}");
    this->displayText("\"Elle a été victime d'une malédiction, jadis notre peuple vivait en paix\"");
    this->clearMapTimer();
    this->createTimer(1,"Mais un jour funeste, un éclair vint déchirer les cieux",true);
    this->createTimer(2,"\"Il rebondit sur tous ceux que nous avons pu connaitre avant de s'arrêter devant le visage de ma fille et de s'évaporer en brume.\"",true);
    this->createTimer(3,"\"Qui êtes vous ?\" interrogea le jeune homme ?",true);
    this->createTimer(4,"\"Je me nomme Gaïen et voici ma fille Elëia, nous sommes les seules représentants de notre peuple disparu.\"",true);
    this->createTimer(5,"\"Et toi qui es tu ?\" rétorqua Gaïen.",true);
    this->createTimer(6,"\"Je me nomme Sahri, je suis seul sur ces terres depuis si longtemps que je ne puis me rappeler le dernier visage que j'ai pu contempler.\"",true);
    this->createTimer(7,"\"Mais pourquoi le visage de votre fille est-il couvert par la brume ?\".",true);
}

Story::Story(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Story)
{
    //Setup de l interface -- doit etre au debut
    ui->setupUi(this);

    //Initialisation de l haptique
    this->mHaptique = new GestionHaptique(this);

    //Ajout de la police specifique
    QFontDatabase::addApplicationFont(":/fonts/Font/AlfredDrake.ttf");
    QFont font = QFont("AlfredDrake",20,10);
    ui->storyLabel->setFont(font);
    ui->storyLabel->setStyleSheet("color: white; background-color: rgba(0,0,0,0.8)");
    ui->storyLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    ui->storyLabel->setWordWrap(true);

    //Lancement de la firstScene
    this->firstScene();

    //Stockage des scenes dans la map
    mapStory[0]= &Story::firstScene;
    mapStory[1]= &Story::secondScene;
    mapStory[2]= &Story::thirdScene;

    //Parametrage du spinner
    ui->spinPage->setMinimum(1);
    ui->spinPage->setMaximum(mapStory.size());
    ui->labelNbPage->setText("/" + QString::number(mapStory.size()));
    ui->labelNbPage->setStyleSheet("color: white;");
    ui->labelNbPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    ui->labelNbPage->setWordWrap(true);

}

Story::~Story()
{
    delete ui;
    if (mHaptique)
        delete mHaptique;
}


/*
 * Fonction pour l affichage du texte avec un effet de fade in
 * */
void Story::displayText(const char* chaine){
    //Effet d'apparition
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->storyLabel->setGraphicsEffect(eff);
    ui->storyLabel->setText(chaine);
    ui->storyLabel->adjustSize();
    ui->storyLabel->setAlignment(Qt::AlignCenter);
    QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
    a->setDuration(3000);
    a->setStartValue(0);
    a->setEndValue(1);
    a->start();
}

void Story::on_pushButton_clicked() //Bouton Retour
{

    if(currentPage > 0){
        currentPage--;
        (this->*mapStory[currentPage])();
    }
    else
        (this->*mapStory[0])();

    ui->spinPage->setValue(currentPage+1);

}


void Story::on_pushButton_2_clicked() //Bouton suivant
{
    if(currentPage < mapStory.size()-1){
        currentPage++;
        (this->*mapStory[currentPage])();
    }
    else
        (this->*mapStory[mapStory.size()-1])();


    ui->spinPage->setValue(currentPage+1);
}




QTimer* Story::createTimer(double nb,const char* toDisplay ){
    QTimer *m_myLongTimer = new QTimer(this);
    m_myLongTimer->setInterval(this->delayPrintText * nb);
    m_myLongTimer->setSingleShot(true);
    connect(m_myLongTimer, &QTimer::timeout, [this,toDisplay] {
       this->displayText(toDisplay);
    });
    m_myLongTimer->start();
    return m_myLongTimer;
}

QTimer* Story::createTimer(double nb,const char* toDisplay, bool addToMapTimer ){
    mapTimer[nb]=this->createTimer(nb,toDisplay);
    return mapTimer[nb];
}

//QTimer* Story::createTimer(double nb,const char* toDisplay, double additionalTime ){
//    mapTimer[nb]=this->createTimer(nb + additionalTime,toDisplay);
//}

void Story::clearMapTimer(){
    for (std::map<int, QTimer*>::iterator it = mapTimer.begin(); it != mapTimer.end(); ++it)
    {
      it->second->stop();
    }
}

void Story::on_spinPage_editingFinished()
{

}

void Story::on_spinPage_valueChanged(int arg1)
{
    if(ui->spinPage->value() <= mapStory.size() && ui->spinPage->value() > 0){
        currentPage = ui->spinPage->value() - 1;
        (this->*mapStory[currentPage])();
    }
}