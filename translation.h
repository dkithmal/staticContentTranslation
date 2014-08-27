#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>

namespace Ui {
class Translation;
}

class Translation : public QDialog
{
    Q_OBJECT
    
public:
    explicit Translation(QWidget *parent = 0);
    ~Translation();
    
private:
    Ui::Translation *ui;
    QString widgetConfigFilePath;
    QString googleTranlatingFileSavePath;
    QString googleTranlatingFileSelectPath;
    QString googleTranlatedFilePath;
    QString staticTranlationFileSavePath;
    QStringList translatingWordList;

private slots:
    void widgetConfigFileSelectClicked();
    void googleTranlatingFileSavePathSelectClicked();
    void googleTranlatingFileSelectClicked();
    void googleTranlatedFileSelectClicked();
    void staticTranlationFileSavePathSelectClicked();
    void googleTranlatingFileGenarateClicked();
    void staticTranlationFileGranarateClicked();

};

#endif // TRANSLATION_H
