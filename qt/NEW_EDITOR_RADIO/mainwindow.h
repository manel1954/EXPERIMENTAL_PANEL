#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Variables para usar
    QString modo;
    QString memorias;

private slots:


    void on_lineEdit_id_editingFinished();

    void on_lineEdit_callsign_editingFinished();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_Timeout_editingFinished();

    void on_lineEdit_Display_editingFinished();

    void on_lineEdit_Duplex_editingFinished();

    void on_lineEdit_PorNextion_editingFinished();

    //void on_pushButton_NextionAbrir_clicked();

    //void on_pushButton_NextionCerrar_clicked();

    void on_lineEdit_RFModeHang_editingFinished();

    void on_pushButton_geany_clicked();

    void on_radioButton_DMR_pressed();

    void on_comboBox_Display_currentIndexChanged(int index);

    void on_lineEdit_TipoDisplay_editingFinished();

    //void on_lineEdit_NombreMemoria_editingFinished();

    void on_lineEdit_RXF_editingFinished();

    void on_lineEdit_TXF_editingFinished();

    void on_lineEdit_RemoteAddress_editingFinished();

    void on_lineEdit_UARTPort_editingFinished();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_lineEdit_TypeOled_editingFinished();

    void on_lineEdit_RemotePort_editingFinished();

    void on_lineEdit_Type_editingFinished();

    void on_lineEdit_Options_editingFinished();

    void on_lineEdit_Password_editingFinished();

    void on_lineEdit_Slot1_editingFinished();

    void on_lineEdit_Slot2_editingFinished();

    void on_lineEdit_Jitter_editingFinished();

    void on_lineEdit_TXInvert_2_editingFinished();

    void on_lineEdit_Latitude_editingFinished();

    void on_lineEdit_Longitude_editingFinished();

    void on_lineEdit_Location_editingFinished();

    void on_lineEdit_URL_editingFinished();

    void on_lineEdit_CW_Id_editingFinished();

    void on_lineEdit_TXInvert_editingFinished();

    void on_lineEdit_RXInvert_editingFinished();

    void on_lineEdit_RXOffset_editingFinished();

    void on_lineEdit_TXOffset_editingFinished();

    void on_lineEdit_RXLevel_editingFinished();

    void on_lineEdit_TXLevel_editingFinished();

    void on_lineEdit_RXDCOffset_editingFinished();

    void on_lineEdit_TXDCOffset_editingFinished();

    void on_comboBox_Layout_currentIndexChanged(int index);

    void on_lineEdit_Layout_editingFinished();

    void on_comboBox_Reflector_currentIndexChanged(int index);

    void on_lineEdit_Rotate_editingFinished();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_lineEdit_DisplayLevel_editingFinished();

    void on_lineEdit_FileLevel_editingFinished();

    void on_pushButton_DmrDisable_clicked();
    void on_pushButton_DmrEnable_clicked();

    void on_pushButton_FusionDisable_clicked();
    void on_pushButton_FusionEnable_clicked();


    void on_pushButton_CwDisable_clicked();
    void on_pushButton_CwEnable_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
