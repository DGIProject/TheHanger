#include "thehanger.h"
#include "ui_thehanger.h"
#include "QDir"
#include "QMessageBox"
#include "QSettings"
#include "QTextStream"
#include "QDebug"
#include "QDateTime"

TheHanger::TheHanger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheHanger)
{
    ui->setupUi(this);
    ui->secretWord->hide();
    ui->windowHanger->hide();
    ui->windowHome->show();

    if(!QFileInfo("settings.ini").exists())
    {
        QSettings settings("settings.ini", QSettings::IniFormat);

        settings.setValue("level", "easy");
    }

    TheHanger::loadListUsers();
}

TheHanger::~TheHanger()
{
    delete ui;
}

void TheHanger::loadListUsers()
{
    ui->listUsersComboBox->clear();

    QDir dir("users/");
    QStringList filters("*.ini" );
    dir.setNameFilters(filters);
    QStringList list(dir.entryList());

    QStringList listName;

    for(int x = 0; x < list.count(); x++)
    {
        QFileInfo fileInfo = list.value(x);

        listName.append(fileInfo.baseName());
    }

    ui->listUsersComboBox->addItems(listName);
}

void TheHanger::refreshScore()
{
    if(ui->nameUserLineEdit->text() == "")
    {
        if(ui->listUsersComboBox->currentText() != "")
        {
            QString nameFileUser = "users/" + ui->listUsersComboBox->currentText() + ".ini";

            QSettings settings(nameFileUser, QSettings::IniFormat);

            ui->playerName->setText(QString(settings.value("user").toString()));

            QString lastScore = "score_" + settings.value("numberofparts").toString();

            ui->lastScore->setText(QString(settings.value(lastScore).toString()));
            ui->numberOfParts->setText(QString(settings.value("numberofparts").toString()));
            ui->date->setText(QString(settings.value("date").toString()));
        }
    }
    else
    {
        ui->playerName->setText(ui->nameUserLineEdit->text());
        ui->lastScore->setText("Unknow");
        ui->numberOfParts->setText("0");
        ui->date->setText("None");
    }
}

void TheHanger::on_nameUserLineEdit_textChanged()
{
    TheHanger::refreshScore();
}

void TheHanger::on_listUsersComboBox_currentIndexChanged()
{
    TheHanger::refreshScore();
}

void TheHanger::on_buttonPlay_clicked()
{
    QString username;

    if(ui->nameUserLineEdit->text() == "")
    {
        if(ui->listUsersComboBox->currentText() == "")
        {
            QMessageBox::critical(this,"Error","You must select a player.");
        }
        else
        {
            TheHanger::start(ui->listUsersComboBox->currentText());
        }
    }
    else
    {
        QFileInfo fileInfo = "users/" + ui->nameUserLineEdit->text() + ".ini";

        if(!fileInfo.exists())
        {
            QString nameFileUser = "users/" + ui->nameUserLineEdit->text() + ".ini";

            QSettings fileUser(nameFileUser, QSettings::IniFormat);

            fileUser.setValue("user", ui->nameUserLineEdit->text());
            fileUser.setValue("numberofparts", 0);
            fileUser.setValue("date", "None");

            TheHanger::loadListUsers();
        }

        TheHanger::start(ui->nameUserLineEdit->text());

        ui->nameUserLineEdit->clear();
    }
}

void TheHanger::start(QString username)
{
    ui->username->setText(username);
    ui->numberOfStrokes->setText("0");
    ui->writtenLetters->setText("");
    ui->numberScore->setText("0");
    ui->numberImg->setText("0");

    ui->img1->hide();
    ui->img2->hide();
    ui->img3->hide();
    ui->img4->hide();
    ui->img5->hide();
    ui->img6->hide();
    ui->img7->hide();
    ui->img8->hide();
    ui->img9->hide();
    ui->img10->hide();
    ui->img11->hide();

    ui->keyA->setEnabled(true);
    ui->keyB->setEnabled(true);
    ui->keyC->setEnabled(true);
    ui->keyD->setEnabled(true);
    ui->keyE->setEnabled(true);
    ui->keyF->setEnabled(true);
    ui->keyG->setEnabled(true);
    ui->keyH->setEnabled(true);
    ui->keyI->setEnabled(true);
    ui->keyJ->setEnabled(true);
    ui->keyK->setEnabled(true);
    ui->keyL->setEnabled(true);
    ui->keyM->setEnabled(true);
    ui->keyN->setEnabled(true);
    ui->keyO->setEnabled(true);
    ui->keyP->setEnabled(true);
    ui->keyQ->setEnabled(true);
    ui->keyR->setEnabled(true);
    ui->keyS->setEnabled(true);
    ui->keyT->setEnabled(true);
    ui->keyU->setEnabled(true);
    ui->keyV->setEnabled(true);
    ui->keyW->setEnabled(true);
    ui->keyX->setEnabled(true);
    ui->keyY->setEnabled(true);
    ui->keyZ->setEnabled(true);

    ui->buttonReplay->setEnabled(false);
    ui->windowPlay->setEnabled(true);

    ui->windowHome->hide();
    ui->windowHanger->show();

    QString secretWord = TheHanger::randomWord();

    if (secretWord == "ERROR")
    {
        QMessageBox::critical(this,"Error","Please reset the game.");
    }
    else
    {
        ui->secretWord->setText(secretWord);

        long sizeWord = secretWord.size();
        int *foundLetter = new int[sizeWord];

        if (foundLetter == NULL)
            exit(0);

        QString starWord;

        for (int i = 0 ; i < sizeWord ; i++)
        {
            foundLetter[i] = 0;
            starWord += "*";
        }

        ui->starWord->setText(starWord);
    }
}

QString TheHanger::randomWord()
{
    int MAX = 0;
    char caractere = 0;
    QString nameDicoFile;

    QSettings settings("settings.ini", QSettings::IniFormat);

    if(QString(settings.value("level").toString()) == "easy")
    {
        nameDicoFile = "dico/easy.dico";
    }
    else if(QString(settings.value("level").toString()) == "medium")
    {
        nameDicoFile = "dico/medium.dico";
    }
    else if(QString(settings.value("level").toString()) == "hard")
    {
        nameDicoFile = "dico/hard.dico";
    }

    QFile dicoFile(nameDicoFile);

    if (!dicoFile.open(QIODevice::ReadOnly))
        return ("ERROR");

    QTextStream file(&dicoFile);

    while (!file.atEnd())
    {
        file >> caractere;

        if (caractere == '\n')
            MAX++;
    }

    file.seek(0);

    int ligneAleat = rand() % MAX;
    int t = 0;

    while (t != ligneAleat)
    {
        file >> caractere;
        if (caractere == '\n')
            t++;
    }

    QString word;
    file >> word;

    return word;
}

void TheHanger::findLetter(QString letter)
{
    QString secretWord = ui->secretWord->text();
    QString starWord = ui->starWord->text();

    QString word;

    bool goodLetter = false;

    QString listWrittenLetters = ui->writtenLetters->text() + " " + letter;
    ui->writtenLetters->setText(listWrittenLetters);

    int numberOfStrokes = ui->numberOfStrokes->text().toInt() + 1;
    ui->numberOfStrokes->setText(QString::number(numberOfStrokes));

    for (int i = 0 ; secretWord[i] != '\0' ; i++)
    {
        word = secretWord[i];

        if (word == letter)
        {
            starWord.replace(i, 1, letter);
            ui->starWord->setText(starWord);

            goodLetter = true;
        }
    }

    if(goodLetter)
    {
        int score = ui->numberScore->text().toInt() + 80;
        ui->numberScore->setText(QString::number(score));
    }
    else
    {
        int score = ui->numberScore->text().toInt() - 20;
        ui->numberScore->setText(QString::number(score));

        TheHanger::showHanger();
    }

    TheHanger::win();
}

void TheHanger::showHanger()
{
    int mistakes = ui->numberImg->text().toInt() + 1;
    ui->numberImg->setText(QString::number(mistakes));

    if(mistakes == 1)
    {
        ui->img1->show();
    }
    else if(mistakes == 2)
    {
        ui->img2->show();
    }
    else if(mistakes == 3)
    {
        ui->img3->show();
    }
    else if(mistakes == 4)
    {
        ui->img4->show();
    }
    else if(mistakes == 5)
    {
        ui->img5->show();
    }
    else if(mistakes == 6)
    {
        ui->img6->show();
    }
    else if(mistakes == 7)
    {
        ui->img7->show();
    }
    else if(mistakes == 8)
    {
        ui->img8->show();
    }
    else if(mistakes == 9)
    {
        ui->img9->show();
    }
    else if(mistakes == 10)
    {
        ui->img10->show();
    }
    else
    {
        ui->img11->show();

        QMessageBox::information(this,"Information","You lost.");

        ui->windowPlay->setEnabled(false);
        ui->buttonReplay->setEnabled(true);

        TheHanger::saveScore();
    }
}

void TheHanger::win()
{
    if(!ui->starWord->text().contains("*", Qt::CaseInsensitive))
    {
        QMessageBox::information(this,"Information","You won.");

        ui->windowPlay->setEnabled(false);
        ui->buttonReplay->setEnabled(true);

        TheHanger::saveScore();
    }
}

void TheHanger::saveScore()
{
    QString nameFileUser = "users/" + ui->username->text() + ".ini";

    QSettings fileUser(nameFileUser, QSettings::IniFormat);

    int numberOfParts = fileUser.value("numberofparts").toInt() + 1;
    fileUser.setValue("numberofparts", QString::number(numberOfParts));

    QString nameScore = "score_" + QString::number(numberOfParts);
    fileUser.setValue(nameScore, ui->numberScore->text());

    fileUser.setValue("date", QDateTime::currentDateTime);
}

void TheHanger::on_keyA_clicked()
{
    ui->keyA->setEnabled(false);

    TheHanger::findLetter(ui->keyA->text());
}

void TheHanger::on_keyB_clicked()
{
    ui->keyB->setEnabled(false);

    TheHanger::findLetter(ui->keyB->text());
}

void TheHanger::on_keyC_clicked()
{
    ui->keyC->setEnabled(false);

    TheHanger::findLetter(ui->keyC->text());
}

void TheHanger::on_keyD_clicked()
{
    ui->keyD->setEnabled(false);

    TheHanger::findLetter(ui->keyD->text());
}

void TheHanger::on_keyE_clicked()
{
    ui->keyE->setEnabled(false);

    TheHanger::findLetter(ui->keyE->text());
}

void TheHanger::on_keyF_clicked()
{
    ui->keyF->setEnabled(false);

    TheHanger::findLetter(ui->keyF->text());
}

void TheHanger::on_keyG_clicked()
{
    ui->keyG->setEnabled(false);

    TheHanger::findLetter(ui->keyG->text());
}

void TheHanger::on_keyH_clicked()
{
    ui->keyH->setEnabled(false);

    TheHanger::findLetter(ui->keyH->text());
}

void TheHanger::on_keyI_clicked()
{
    ui->keyI->setEnabled(false);

    TheHanger::findLetter(ui->keyI->text());
}

void TheHanger::on_keyJ_clicked()
{
    ui->keyJ->setEnabled(false);

    TheHanger::findLetter(ui->keyJ->text());
}

void TheHanger::on_keyK_clicked()
{
    ui->keyK->setEnabled(false);

    TheHanger::findLetter(ui->keyK->text());
}

void TheHanger::on_keyL_clicked()
{
    ui->keyL->setEnabled(false);

    TheHanger::findLetter(ui->keyL->text());
}

void TheHanger::on_keyM_clicked()
{
    ui->keyM->setEnabled(false);

    TheHanger::findLetter(ui->keyM->text());
}

void TheHanger::on_keyN_clicked()
{
    ui->keyN->setEnabled(false);

    TheHanger::findLetter(ui->keyN->text());
}

void TheHanger::on_keyO_clicked()
{
    ui->keyO->setEnabled(false);

    TheHanger::findLetter(ui->keyO->text());
}

void TheHanger::on_keyP_clicked()
{
    ui->keyP->setEnabled(false);

    TheHanger::findLetter(ui->keyP->text());
}

void TheHanger::on_keyQ_clicked()
{
    ui->keyQ->setEnabled(false);

    TheHanger::findLetter(ui->keyQ->text());
}

void TheHanger::on_keyR_clicked()
{
    ui->keyR->setEnabled(false);

    TheHanger::findLetter(ui->keyR->text());
}

void TheHanger::on_keyS_clicked()
{
    ui->keyS->setEnabled(false);

    TheHanger::findLetter(ui->keyS->text());
}

void TheHanger::on_keyT_clicked()
{
    ui->keyT->setEnabled(false);

    TheHanger::findLetter(ui->keyT->text());
}

void TheHanger::on_keyU_clicked()
{
    ui->keyU->setEnabled(false);

    TheHanger::findLetter(ui->keyU->text());
}

void TheHanger::on_keyV_clicked()
{
    ui->keyV->setEnabled(false);

    TheHanger::findLetter(ui->keyV->text());
}

void TheHanger::on_keyW_clicked()
{
    ui->keyW->setEnabled(false);

    TheHanger::findLetter(ui->keyW->text());
}

void TheHanger::on_keyX_clicked()
{
    ui->keyX->setEnabled(false);

    TheHanger::findLetter(ui->keyX->text());
}

void TheHanger::on_keyY_clicked()
{
    ui->keyY->setEnabled(false);

    TheHanger::findLetter(ui->keyY->text());
}

void TheHanger::on_keyZ_clicked()
{
    ui->keyZ->setEnabled(false);

    TheHanger::findLetter(ui->keyZ->text());
}

void TheHanger::on_buttonReplay_clicked()
{
    TheHanger::start(ui->username->text());
}

void TheHanger::on_buttonBack_clicked()
{
    if(ui->starWord->text().contains("*", Qt::CaseInsensitive))
    {
        int question = QMessageBox::question(this,"Question","Are you sure to quit this part ?", QMessageBox::Yes | QMessageBox::No);

        if(question == QMessageBox::Yes)
        {
            ui->windowHanger->hide();
            ui->windowHome->show();

            TheHanger::refreshScore();
        }
    }
    else
    {
        ui->windowHanger->hide();
        ui->windowHome->show();

        TheHanger::refreshScore();
    }
}
