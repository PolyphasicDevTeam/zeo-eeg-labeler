#include "zeopicdata.h"

std::ostream &operator << (std::ostream &os, const QColor &color)
{
    return os << color.red() << ", " << color.green() << ", " << color.blue();
}


pixelerkennung::pixelerkennung()
{
    setFixedSize(1290, 722);
    setWindowTitle("Labeling-0.5");

    deepCounter = 0;
    lightCounter = 0;
    remCounter = 0;
    awakeCounter = 0;
    totalCounter = 0;

    manuellCheck = 0;


    buttonBeenden = new (QPushButton)(this);
    buttonBeenden->setText("Close");
    buttonBeenden->setGeometry(1240,0,50,50);
    buttonBeenden->setToolTip("This will end the program");
    QObject::connect(buttonBeenden,SIGNAL(released()),this,SLOT(close()));

    buttonLaden = new (QPushButton)(this);
    buttonLaden->setText("Load");
    buttonLaden->setGeometry(1190,50,50,50);
    buttonLaden->setToolTip("This will load and show the pic in the text");
    QObject::connect(buttonLaden,SIGNAL(released()),this,SLOT(showBild()));

    buttonDialog = new (QPushButton)(this);
    buttonDialog->setText("Search");
    buttonDialog->setGeometry(1190,0,50,50);
    buttonDialog->setToolTip("This will let you select a pic.\n After it it's getting loaded automatically");
    QObject::connect(buttonDialog,SIGNAL(released()),this,SLOT(chooseBild()));


    buttonLabel = new (QPushButton)(this);
    buttonLabel->setText("Get data");
    buttonLabel->setGeometry(1240,50,50,50);
    buttonLabel->setToolTip("This will load the data from the currently loaded pic.");
    QObject::connect(buttonLabel,SIGNAL(released()),this,SLOT(showStats()));

    buttonStats = new (QPushButton)(this);
    buttonStats->setText("Save");
    buttonStats->setGeometry(1190,100,100,50);
    buttonStats->setToolTip("This will create a .txt file with the data, from the current pic");
    QObject::connect(buttonStats,SIGNAL(released()),this,SLOT(label()));

    buttonPicCheck = new (QPushButton)(this);
    buttonPicCheck->setText("Check");
    buttonPicCheck->setGeometry(1190,670,100,50);
    buttonPicCheck->setToolTip("You can check and if needed manually set the line, to get the data of pics, which are not automatically supported");
    QObject::connect(buttonPicCheck,SIGNAL(released()),this, SLOT(labelCheck()));




    radioAdaptedState = new (QRadioButton)(this);
    radioAdaptedState->setText("Adapted?");
    radioAdaptedState->setGeometry(1115,500,100,50);
    radioAdaptedState->setToolTip("Activate it, if you are adapted");

    radioManuell = new (QRadioButton)(this);
    radioManuell->setText("Manuell ?");
    radioManuell->setGeometry(1210,605,100,50);
    radioManuell->setToolTip("Activate this, if you wanna get the data manuell");





    editText = new (QLineEdit)(this);
    editText->setText("Full Pic Path");
    editText->setGeometry(1115,150,174,50);
    editText->setToolTip("Example :\n"
                         "C:/User/Pic/Cat.png");

    editDirection = new (QLineEdit)(this);
    editDirection->setText("Full-Save-Path");
    editDirection->setGeometry(1115,200,174,50);
    editDirection->setToolTip("Example :\n"
                           "C:/User/Files/");

    editName = new (QLineEdit)(this);
    editName->setText("User-Name");
    editName->setGeometry(1115,250,174,50);
    editName->setToolTip("Example :\n"
                         "Yinsei");

    editDay = new (QLineEdit)(this);
    editDay->setText("Day x");
    editDay->setGeometry(1115,300,174,50);
    editDay->setToolTip("Example :\n"
                        "1");

    editDate = new (QLineEdit)(this);
    editDate->setText("Date x");
    editDate->setGeometry(1115,350,174,50);
    editDate->setToolTip("Example :\n"
                         "12/12/2012");

    editSchedule = new (QLineEdit)(this);
    editSchedule->setText("Schedule");
    editSchedule->setGeometry(1115,400,174,50);
    editSchedule->setToolTip("Example :\n"
                             "Uberman");

    editCoreNumber = new (QLineEdit)(this);
    editCoreNumber->setText("Core number x");
    editCoreNumber->setGeometry(1115,450,174,50);
    editCoreNumber->setToolTip("Example :\n"
                               "2");


    lcdCheck = new (QLCDNumber)(this);
    lcdCheck->setDecMode();
    lcdCheck->setGeometry(1115,540,174,50);



    sliderCheck = new (QSlider)(this);
    sliderCheck->sliderPosition();
    sliderCheck->setGeometry(1140,595,25,125);
    sliderCheck->setToolTip("Slide this, to manually detect the data, if it doesn't work automatically");
    sliderCheck->setTickInterval(5);
    sliderCheck->setMinimum(0);
    sliderCheck->setMaximum(1920);
    QObject::connect(sliderCheck,SIGNAL(valueChanged(int)), lcdCheck,SLOT(display(int)));





    labelPic = new (QLabel)(this);
    labelPic->setGeometry(0,0,1115,1200);




}

void pixelerkennung::showBild()
{

    if(pic.load(editText->text()))
    {
        labelPic->setPixmap(QPixmap::fromImage(pic));
    }

    else
    {
        QMessageBox::critical(this, "Pic load error \n", "The pic loader doesn't worked. \n"
                                                         "Error code : showPic");
    }
}

void pixelerkennung::chooseBild()
{
    QString search;
    search = QFileDialog::getOpenFileName(this,"Open pic",QDir::cleanPath("C:/"),"Pics (*.jpg *.png)" );
    if(!search.isEmpty())
    {
        editText->setText(search);
        showBild();
        search.clear();
    }
    else
    {
        QMessageBox::critical(this, "Choose-Pic error. \n", "There is no pic loaded. \n"
                                                            "Error code : choosePic.");
    }

}

void pixelerkennung::showStats()
{
    if(!pic.isNull() && colorList.empty())
    {
        const unsigned short Y = 700;
        QColor temp;

        if(radioManuell->isChecked())
        {
            for(unsigned short x = 0; x < pic.width(); x++)
            {
                temp = pic.pixel(x, static_cast<int>(lcdCheck->value()));
                colorList.push_back(temp);
            }
        }

        else if(pic.width() == 1024 && pic.height() == 1024)
        {
            for(unsigned short x = 0; x < pic.width(); x++)
            {
                temp = pic.pixelColor(x,400);
                colorList.push_back(temp);
            }
        }

        else
        {
            for(unsigned short x = 0; x < pic.width(); x++)
            {
                temp = pic.pixelColor(x,Y);
                colorList.push_back(temp);
            }
        }

    }
    else
    {
        QMessageBox::critical(this, "Show-Stats-Error \n",
                              "The pic is not loaded, or the list is already filled \n"
                              "Error code : showStats.");
    }
}

void pixelerkennung::label()
{

    if(!colorList.empty() && !editDirection->text().isEmpty() && !editName->text().isEmpty())
    {
        std::string path = editDirection->displayText().toStdString() + editName->displayText().toStdString() + ".txt";
        std::string pathTimes = editDirection->displayText().toStdString() + editName->displayText().toStdString() + "_Times.txt";

        if(std::experimental::filesystem::exists(editDirection->displayText().toStdString()))
        {

            QColor temp;
            std::ofstream outputTotalTime(pathTimes);
            std::ofstream outputState(path, std::ios::app);

            for(int i = 0; i < colorList.size(); )
            {
                temp = colorList.at(i);
                if(temp == AWAKE)
                {
                    while(temp == AWAKE)
                    {
                        ++i;
                        temp = colorList.at(i);
                    }
                    temp = colorList.at(i);
                    awakeCounter += 5;
                    blockList.push_back("Awake ");
                }

                else if(temp == LIGHT)
                {
                    while(temp == LIGHT)
                    {
                        ++i;
                        temp = colorList.at(i);
                    }
                    temp = colorList.at(i);
                    lightCounter += 5;
                    blockList.push_back("Light ");
                }

                else if(temp == REM)
                {
                    while(temp == REM)
                    {
                        ++i;
                        temp = colorList.at(i);
                    }
                    temp = colorList.at(i);
                    remCounter += 5;
                    blockList.push_back("Rem ");
                }

                else if(temp == DEEP)
                {
                    while(temp == DEEP)
                    {
                        ++i;
                        temp = colorList.at(i);
                    }
                    temp = colorList.at(i);
                    deepCounter += 5;
                    blockList.push_back("Deep ");
                }

                else
                {
                    ++i;
                }
            }

            totalCounter = awakeCounter + remCounter + lightCounter + deepCounter;

            outputTotalTime << "Awake : " << awakeCounter << '.' << std::endl;
            outputTotalTime << "Rem : " << remCounter << '.' << std::endl;
            outputTotalTime << "Light : " << lightCounter << '.' << std::endl;
            outputTotalTime << "Deep : "  << deepCounter << '.' << std::endl;
            outputTotalTime << "Total : " << totalCounter << '.' << std::endl;
            outputTotalTime << std::endl;



            outputState << editName->text().toStdString() + ',';
            outputState << editSchedule->text().toStdString() + ',';
            outputState << editDate->text().toStdString() + ',';
            outputState << editDay->text().toStdString() + ',';
            if(radioAdaptedState->isChecked())
            {
                outputState << "True,";
            }
            else
            {
                outputState << "False,";
            }
            outputState << "Zeo,";
            outputState << editCoreNumber->text().toStdString() + ',';

            for(int i = 0; i < blockList.size(); i++)
            {
                outputState << blockList.at(i).toStdString();
            }
            outputState << std::endl;


            //Reset everything after the labeling
            awakeCounter = 0;
            remCounter = 0;
            lightCounter = 0;
            deepCounter = 0;
            totalCounter = 0;

            blockList.clear();
            colorList.clear();

            path.clear();
            pathTimes.clear();
        }
        else
        {
            QMessageBox::critical(this,"Path error. \n",
                                       "The path doesn't exist. \n"
                                       "Error code : label.");
        }

    }
    else
    {
        QMessageBox::critical(this, "Label error. \n",
                                    "Case 1: The 'Get data' button wasn't pressed. \n"
                                    "Case 2: The path or username is empty. \n"
                              "Error code : label.");
    }



}

void pixelerkennung::labelCheck()
{

    if(!pic.isNull())
    {
        QVector<QColor> reset;
        manuellCheck = lcdCheck->value();

        QColor setColur = Qt::red;
        for(unsigned short x = 0; x < pic.width(); x++)
        {
            reset.push_back(pic.pixelColor(x,static_cast<int>(manuellCheck)));
            pic.setPixelColor(x, static_cast<int>(manuellCheck), setColur);
        }
        labelPic->setPixmap(QPixmap::fromImage(pic));


        for(unsigned short x = 0; x < reset.size(); x++)
        {
            pic.setPixelColor(x, static_cast<int>(manuellCheck), reset.at(x));
        }


        reset.clear();
    }
    else
    {
        QMessageBox::critical(this, "Check error. \n",
                              "The pic is not loaded. \n"
                              "Error code : label-check");
    }

}
