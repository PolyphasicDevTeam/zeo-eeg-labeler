#ifndef ZEOPICDATA_H
#define ZEOPICDATA_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QFileDialog>
#include <QLineEdit>
#include <QLinkedList>
#include <QColor>
#include <QMessageBox>
#include <QRadioButton>
#include <QSlider>
#include <QLCDNumber>



#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <filesystem>





class pixelerkennung : public QWidget
{
    QPushButton *buttonBeenden,
    *buttonLaden, *buttonDialog,
    *buttonLabel, *buttonStats,
    *buttonCheck, *buttonFinallabel,
    *buttonPicCheck;

    QLabel *labelPic, *labelText;

    QPixmap *pixmapBild;
    QLineEdit *editText, *editDirection,
    *editName, *editDay, *editDate, *editSchedule,
    *editCoreNumber;

    QImage pic;

    QRadioButton *radioAdaptedState,
    *radioManuell;

    QSlider *sliderCheck;

    QLCDNumber *lcdCheck;

    QVector <QColor> colorList;
    QVector <QString> blockList;

    unsigned short remCounter;
    unsigned short lightCounter;
    unsigned short deepCounter;
    unsigned short awakeCounter;
    unsigned short totalCounter;

    double manuellCheck;

    const QColor AWAKE {255, 0, 0};
    const QColor LIGHT {102, 178, 255};
    const QColor DEEP {0, 0, 204};
    const QColor REM {0, 153, 0};

    const QString stringAwake = "Awake";
    const QString stringLight = "Light";
    const QString stringDeep = "Deep";
    const QString stringRem = "Rem";


    Q_OBJECT
public:
    pixelerkennung();


public slots:
    void showBild();
    void showStats();
    void chooseBild();
    void label();
    void labelCheck();


};

#endif // ZEOPICDATA_H
