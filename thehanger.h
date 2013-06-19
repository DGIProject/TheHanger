#ifndef THEHANGER_H
#define THEHANGER_H

#include <QMainWindow>
#include "QDir"
#include "QMessageBox"
#include "QSettings"
#include "QTextStream"
#include "QDebug"
#include "QDateTime"

namespace Ui {
class TheHanger;
}

class TheHanger : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TheHanger(QWidget *parent = 0);
    ~TheHanger();

private slots:
    void loadListUsers();
    void refreshScore();
    void on_nameUserLineEdit_textChanged();
    void on_listUsersComboBox_currentIndexChanged();
    
    void on_buttonPlay_clicked();
    void start(QString username);
    QString randomWord();
    void findLetter(QString letter);
    void showHanger();
    void win();
    void saveScore();

    void on_keyA_clicked();
    void on_keyB_clicked();
    void on_keyC_clicked();
    void on_keyD_clicked();
    void on_keyE_clicked();
    void on_keyF_clicked();
    void on_keyG_clicked();
    void on_keyH_clicked();
    void on_keyI_clicked();
    void on_keyJ_clicked();
    void on_keyK_clicked();
    void on_keyL_clicked();
    void on_keyM_clicked();
    void on_keyN_clicked();
    void on_keyO_clicked();
    void on_keyP_clicked();
    void on_keyQ_clicked();
    void on_keyR_clicked();
    void on_keyS_clicked();
    void on_keyT_clicked();
    void on_keyU_clicked();
    void on_keyV_clicked();
    void on_keyW_clicked();
    void on_keyX_clicked();
    void on_keyY_clicked();
    void on_keyZ_clicked();

    void on_buttonReplay_clicked();
    void on_buttonBack_clicked();

private:
    Ui::TheHanger *ui;
};

#endif // THEHANGER_H
