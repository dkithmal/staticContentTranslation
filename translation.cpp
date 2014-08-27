#include "translation.h"
#include "ui_translation.h"

Translation::Translation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Translation)
{
    ui->setupUi(this);
}

Translation::~Translation()
{
    delete ui;
}


void Translation::widgetConfigFileSelectClicked()
{
    widgetConfigFilePath=QFileDialog::getOpenFileName(this, tr("Select WidgetConfig File"),"D:/dk work/Motarola");
    ui->lEWidgetConfigFilePath->setText(widgetConfigFilePath);

}

void Translation::googleTranlatingFileSavePathSelectClicked()
{
    googleTranlatingFileSavePath=QFileDialog::getExistingDirectory(this, tr("Select Directry to save Google tranlating File"),"D:/dk work/Motarola");
    ui->lEgoogletranlatedfileSavePath->setText(googleTranlatingFileSavePath);

}

void Translation::googleTranlatingFileSelectClicked()
{
    googleTranlatingFileSelectPath=QFileDialog::getOpenFileName(this, tr("Select Google Tranlating file"),"D:/dk work/Motarola");
    ui->lEGoogleTranlatingFilePath->setText(googleTranlatingFileSelectPath);

}


void Translation::googleTranlatedFileSelectClicked()
{
    googleTranlatedFilePath=QFileDialog::getOpenFileName(this, tr("Select Google Translated File"),"D:/dk work/Motarola");
    ui->lEGoogleTranlatedFilePath->setText(googleTranlatedFilePath);

}

void Translation::staticTranlationFileSavePathSelectClicked()
{
    staticTranlationFileSavePath=QFileDialog::getExistingDirectory(this, tr("Select Directry to save Static Translated file"),"D:/dk work/Motarola");
    ui->lEStaticTranlationFileSavePath->setText(staticTranlationFileSavePath);


}


void Translation::googleTranlatingFileGenarateClicked()
{
    if(widgetConfigFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select WidgetConfig File");
        return;
    }

    if(googleTranlatingFileSavePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select directry to save googleTranslatingFile");
        return;

    }

    QFile widgetConfigFile(widgetConfigFilePath);

    if(!widgetConfigFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
        QFile googleTranlatingFile(googleTranlatingFileSavePath+"/"+"googleTranlatingFile.txt");
        if(!googleTranlatingFile.open(QFile::ReadWrite| QIODevice::Text))
        {
            qDebug()<<"error";

        }
        else
        {


            QTextStream googletranlateFileGenarate(&googleTranlatingFile);



            QDomDocument document;

            document.setContent(&widgetConfigFile);
            QDomElement root= document.firstChildElement();


            QDomNodeList columns = root.elementsByTagName("Column");

            for(int j=0;j<columns.count();j++)
            {
                 if(translatingWordList.contains(columns.at(j).toElement().attribute("name")))
                 {

                 }
                 else
                 {
                     googletranlateFileGenarate<<columns.at(j).toElement().attribute("name")<<"\n";
                     translatingWordList.append(columns.at(j).toElement().attribute("name"));

                 }



            }

            googleTranlatingFile.close();
            widgetConfigFile.close();
            QMessageBox::information(this,"Success","Google Tranlating File Created");
        }
    }



}

void Translation::staticTranlationFileGranarateClicked()
{

    if(googleTranlatingFileSelectPath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please select priviously genarated google Tranlating file");
        return;
    }

    if(googleTranlatedFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please select google Tranlated file");
        return;

    }
    if(staticTranlationFileSavePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select Directry to save static Tranlation File");
        return;
    }


    QFile googleTranslatingFile(googleTranlatingFileSelectPath);
    QFile googleTranslatedFile(googleTranlatedFilePath);
    QFile staticTrnlationFile(staticTranlationFileSavePath+"/staticTranlated.txt");

    if(!(googleTranslatingFile.open(QFile::ReadOnly| QIODevice::Text)&&googleTranslatedFile.open(QFile::ReadOnly| QIODevice::Text)&&staticTrnlationFile.open(QFile::ReadWrite| QIODevice::Text)))
    {
        qDebug()<<"error";

    }
    else
    {QStringList tranlatingContent;
     QStringList translatedContent;

     QTextStream in(&googleTranslatingFile);
     while(!in.atEnd())
     {

         QString line = in.readLine();
         tranlatingContent.append(line);


     }

     QTextStream in2(&googleTranslatedFile);
     while(!in2.atEnd())
     {

         QString line = in2.readLine();
         translatedContent.append(line);


     }


     QTextStream staticTranlationFileGenarate(&staticTrnlationFile);
     staticTranlationFileGenarate.setCodec("UTF-8");

     for(int x=0;x<tranlatingContent.size();x++)
     {
         staticTranlationFileGenarate<<tranlatingContent.at(x)<<"\t"<<translatedContent.at(x)<<"\n";

     }



        staticTrnlationFile.close();
        googleTranslatingFile.close();
        googleTranslatedFile.close();
        QMessageBox::information(this,"Success","Static Tranlation File Created");

    }


}
