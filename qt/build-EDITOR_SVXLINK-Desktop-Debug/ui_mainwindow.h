/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_indicativo;
    QLabel *label_indicativo;
    QLabel *label_icono_svxlink;
    QLabel *label_editor_svxlink;
    QPushButton *pushButton_guardar;
    QPushButton *pushButton_abrir_module;
    QLabel *label_by_ea3eiz;
    QPushButton *pushButton_SALIR;
    QLineEdit *lineEdit_indicativo1;
    QLabel *label_editor_svxlink_2;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_password_proxy;
    QLineEdit *lineEdit_ip_proxy;
    QLabel *label_password_2;
    QLabel *label_ip_proxy;
    QPushButton *pushButton_proxy_on;
    QPushButton *pushButton_proxy_off;
    QLineEdit *lineEdit_sisop_name;
    QLineEdit *lineEdit_location;
    QLabel *label_location;
    QLabel *label_sisopname;
    QLineEdit *lineEdit_autocon_echolink;
    QComboBox *comboBox;
    QPushButton *pushButton_id_conferencia;
    QLabel *label_editor_svxlink_3;
    QLabel *label_rx;
    QLabel *label_tx;
    QLineEdit *lineEdit_puente_rx;
    QLabel *label_port_proxy;
    QLineEdit *lineEdit_port_proxy;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_on_pasw_proxy;
    QPushButton *pushButton_off_pasw_proxy_2;
    QLabel *label_password_3;
    QLineEdit *lineEdit_conexiones;
    QLineEdit *lineEdit_puente;
    QLabel *label_location_2;
    QPushButton *pushButton_off;
    QPushButton *pushButton_on;
    QLabel *label_status_ini;
    QPushButton *pushButton_on_2;
    QPushButton *pushButton_off_2;
    QLabel *label_editor_svxlink_4;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_proxy;
    QLabel *label_password_4;
    QLineEdit *lineEdit_password_proxy_propio;
    QLabel *label_ip_proxy_propio;
    QLineEdit *lineEdit_ip_proxy_propio;
    QLineEdit *lineEdit_port_proxy_propio;
    QLabel *label_port_proxy_2;
    QLabel *label_editor_svxlink_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_off_pasw_proxy_propio;
    QPushButton *pushButton_on_pasw_proxy_propio;
    QPushButton *pushButton_instalar_proxy;
    QLabel *label_proxy_instalado;
    QPushButton *pushButton_7;
    QLabel *label_status_soundcard;
    QLabel *label_status_proxy;
    QGroupBox *groupBox;
    QLabel *label_alsa_tx_3;
    QLabel *label_transistor;
    QPushButton *pushButton_beep_off;
    QPushButton *pushButton_beep_on;
    QPushButton *pushButton;
    QLabel *label_baliza_2;
    QLabel *label_baliza_4;
    QLineEdit *lineEdit_ptt_port;
    QLineEdit *lineEdit_tono;
    QLabel *label_baliza;
    QComboBox *comboBox_PTT_TYPE;
    QPushButton *pushButton_souncard;
    QLabel *label_alsa_rx;
    QLabel *label_alsa_tx;
    QPushButton *pushButton_vox;
    QLabel *label_PTT_TYPE;
    QLineEdit *lineEdit_numero_tono;
    QLineEdit *lineEdit_beep;
    QPushButton *pushButton_abrir_svxlink;
    QPushButton *pushButton_transistor;
    QLineEdit *lineEdit_ptt_type;
    QLineEdit *lineEdit_alsa_rx;
    QPushButton *pushButton_AUDIO_TX;
    QComboBox *comboBox_AUDIO_RX;
    QPushButton *pushButton_PTT_PORT;
    QPushButton *pushButton_AUDIO_RX;
    QLineEdit *lineEdit_alsa_tx;
    QPushButton *pushButton_tonos;
    QLabel *label_soundcard;
    QComboBox *comboBox_AUDIO_TX;
    QPushButton *pushButton_PTT_TYPE;
    QLineEdit *lineEdit_baliza;
    QLabel *label_alsa_tx_2;
    QComboBox *comboBox_PTT_PORT;
    QLabel *label;
    QPushButton *pushButton_svxlinkAbrir;
    QPushButton *pushButton_svxlinkCerrar;
    QFrame *line_lila_2;
    QFrame *line_lila_3;
    QFrame *line_violeta_horizontal_2;
    QFrame *line_violeta_horizontal_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(628, 488);
        MainWindow->setMaximumSize(QSize(1620, 1281));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ICONO_SVXLINK_OFF.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #000;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit_indicativo = new QLineEdit(centralWidget);
        lineEdit_indicativo->setObjectName(QString::fromUtf8("lineEdit_indicativo"));
        lineEdit_indicativo->setGeometry(QRect(143, 12, 158, 30));
        lineEdit_indicativo->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_indicativo->setMaxLength(32767);
        lineEdit_indicativo->setCursorPosition(0);
        lineEdit_indicativo->setAlignment(Qt::AlignCenter);
        label_indicativo = new QLabel(centralWidget);
        label_indicativo->setObjectName(QString::fromUtf8("label_indicativo"));
        label_indicativo->setGeometry(QRect(11, 12, 130, 30));
        QFont font;
        label_indicativo->setFont(font);
        label_indicativo->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_indicativo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_icono_svxlink = new QLabel(centralWidget);
        label_icono_svxlink->setObjectName(QString::fromUtf8("label_icono_svxlink"));
        label_icono_svxlink->setGeometry(QRect(40, 1830, 31, 31));
        label_icono_svxlink->setPixmap(QPixmap(QString::fromUtf8(":/ICONO_SVXLINK_OFF.png")));
        label_icono_svxlink->setScaledContents(true);
        label_editor_svxlink = new QLabel(centralWidget);
        label_editor_svxlink->setObjectName(QString::fromUtf8("label_editor_svxlink"));
        label_editor_svxlink->setGeometry(QRect(20, 1200, 248, 27));
        label_editor_svxlink->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_editor_svxlink->setAlignment(Qt::AlignCenter);
        pushButton_guardar = new QPushButton(centralWidget);
        pushButton_guardar->setObjectName(QString::fromUtf8("pushButton_guardar"));
        pushButton_guardar->setGeometry(QRect(11, 450, 606, 30));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_guardar->setFont(font1);
        pushButton_guardar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_guardar->setFocusPolicy(Qt::NoFocus);
        pushButton_guardar->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 0);\n"
"color:#fff;\n"
"border-radius:3px;\n"
""));
        pushButton_abrir_module = new QPushButton(centralWidget);
        pushButton_abrir_module->setObjectName(QString::fromUtf8("pushButton_abrir_module"));
        pushButton_abrir_module->setGeometry(QRect(11, 189, 606, 28));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        pushButton_abrir_module->setFont(font2);
        pushButton_abrir_module->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_abrir_module->setFocusPolicy(Qt::NoFocus);
        pushButton_abrir_module->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(255, 170, 0);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_by_ea3eiz = new QLabel(centralWidget);
        label_by_ea3eiz->setObjectName(QString::fromUtf8("label_by_ea3eiz"));
        label_by_ea3eiz->setGeometry(QRect(12, 544, 111, 24));
        QFont font3;
        font3.setPointSize(12);
        label_by_ea3eiz->setFont(font3);
        label_by_ea3eiz->setStyleSheet(QString::fromUtf8("color: rgb(221, 221, 221);\n"
"background:transparent;"));
        label_by_ea3eiz->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_SALIR = new QPushButton(centralWidget);
        pushButton_SALIR->setObjectName(QString::fromUtf8("pushButton_SALIR"));
        pushButton_SALIR->setGeometry(QRect(500, 1360, 91, 32));
        pushButton_SALIR->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_SALIR->setFocusPolicy(Qt::NoFocus);
        pushButton_SALIR->setStyleSheet(QString::fromUtf8(""));
        lineEdit_indicativo1 = new QLineEdit(centralWidget);
        lineEdit_indicativo1->setObjectName(QString::fromUtf8("lineEdit_indicativo1"));
        lineEdit_indicativo1->setGeometry(QRect(190, 1830, 241, 26));
        lineEdit_indicativo1->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_indicativo1->setMaxLength(32767);
        lineEdit_indicativo1->setCursorPosition(0);
        lineEdit_indicativo1->setAlignment(Qt::AlignCenter);
        label_editor_svxlink_2 = new QLabel(centralWidget);
        label_editor_svxlink_2->setObjectName(QString::fromUtf8("label_editor_svxlink_2"));
        label_editor_svxlink_2->setGeometry(QRect(210, 1830, 191, 21));
        label_editor_svxlink_2->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_editor_svxlink_2->setAlignment(Qt::AlignCenter);
        label_password = new QLabel(centralWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(310, 12, 94, 30));
        label_password->setFont(font);
        label_password->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_password->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_password = new QLineEdit(centralWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(406, 12, 210, 30));
#if QT_CONFIG(statustip)
        lineEdit_password->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
        lineEdit_password->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:12px;\n"
"border-radius:3px;"));
        lineEdit_password->setMaxLength(32767);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setCursorPosition(8);
        lineEdit_password->setAlignment(Qt::AlignCenter);
        lineEdit_password_proxy = new QLineEdit(centralWidget);
        lineEdit_password_proxy->setObjectName(QString::fromUtf8("lineEdit_password_proxy"));
        lineEdit_password_proxy->setGeometry(QRect(480, 116, 137, 30));
#if QT_CONFIG(statustip)
        lineEdit_password_proxy->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
        lineEdit_password_proxy->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:12px;\n"
"border-radius:3px;"));
        lineEdit_password_proxy->setMaxLength(32767);
        lineEdit_password_proxy->setEchoMode(QLineEdit::Password);
        lineEdit_password_proxy->setCursorPosition(8);
        lineEdit_password_proxy->setAlignment(Qt::AlignCenter);
        lineEdit_ip_proxy = new QLineEdit(centralWidget);
        lineEdit_ip_proxy->setObjectName(QString::fromUtf8("lineEdit_ip_proxy"));
        lineEdit_ip_proxy->setGeometry(QRect(142, 116, 158, 30));
        lineEdit_ip_proxy->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"border-radius:3px;"));
        lineEdit_ip_proxy->setMaxLength(32767);
        lineEdit_ip_proxy->setCursorPosition(0);
        lineEdit_ip_proxy->setAlignment(Qt::AlignCenter);
        label_password_2 = new QLabel(centralWidget);
        label_password_2->setObjectName(QString::fromUtf8("label_password_2"));
        label_password_2->setGeometry(QRect(309, 116, 169, 30));
        label_password_2->setFont(font);
        label_password_2->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_password_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_ip_proxy = new QLabel(centralWidget);
        label_ip_proxy->setObjectName(QString::fromUtf8("label_ip_proxy"));
        label_ip_proxy->setGeometry(QRect(13, 116, 127, 30));
        label_ip_proxy->setFont(font);
        label_ip_proxy->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_ip_proxy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_proxy_on = new QPushButton(centralWidget);
        pushButton_proxy_on->setObjectName(QString::fromUtf8("pushButton_proxy_on"));
        pushButton_proxy_on->setGeometry(QRect(210, 1830, 171, 31));
        pushButton_proxy_on->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_proxy_on->setFocusPolicy(Qt::NoFocus);
        pushButton_proxy_off = new QPushButton(centralWidget);
        pushButton_proxy_off->setObjectName(QString::fromUtf8("pushButton_proxy_off"));
        pushButton_proxy_off->setGeometry(QRect(30, 1830, 171, 31));
        pushButton_proxy_off->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_proxy_off->setFocusPolicy(Qt::NoFocus);
        lineEdit_sisop_name = new QLineEdit(centralWidget);
        lineEdit_sisop_name->setObjectName(QString::fromUtf8("lineEdit_sisop_name"));
        lineEdit_sisop_name->setGeometry(QRect(143, 47, 158, 30));
        lineEdit_sisop_name->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_sisop_name->setMaxLength(32767);
        lineEdit_sisop_name->setCursorPosition(0);
        lineEdit_sisop_name->setAlignment(Qt::AlignCenter);
        lineEdit_location = new QLineEdit(centralWidget);
        lineEdit_location->setObjectName(QString::fromUtf8("lineEdit_location"));
        lineEdit_location->setGeometry(QRect(406, 47, 210, 30));
        lineEdit_location->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_location->setMaxLength(32767);
        lineEdit_location->setCursorPosition(20);
        lineEdit_location->setAlignment(Qt::AlignCenter);
        label_location = new QLabel(centralWidget);
        label_location->setObjectName(QString::fromUtf8("label_location"));
        label_location->setGeometry(QRect(310, 47, 94, 30));
        label_location->setFont(font);
        label_location->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_location->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_sisopname = new QLabel(centralWidget);
        label_sisopname->setObjectName(QString::fromUtf8("label_sisopname"));
        label_sisopname->setGeometry(QRect(11, 47, 130, 30));
        label_sisopname->setFont(font);
        label_sisopname->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_sisopname->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_autocon_echolink = new QLineEdit(centralWidget);
        lineEdit_autocon_echolink->setObjectName(QString::fromUtf8("lineEdit_autocon_echolink"));
        lineEdit_autocon_echolink->setGeometry(QRect(406, 83, 210, 28));
        lineEdit_autocon_echolink->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_autocon_echolink->setMaxLength(32767);
        lineEdit_autocon_echolink->setCursorPosition(0);
        lineEdit_autocon_echolink->setAlignment(Qt::AlignCenter);
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(11, 83, 606, 28));
        comboBox->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_id_conferencia = new QPushButton(centralWidget);
        pushButton_id_conferencia->setObjectName(QString::fromUtf8("pushButton_id_conferencia"));
        pushButton_id_conferencia->setGeometry(QRect(11, 83, 391, 28));
        pushButton_id_conferencia->setFont(font2);
        pushButton_id_conferencia->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_id_conferencia->setFocusPolicy(Qt::NoFocus);
        pushButton_id_conferencia->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(97, 160, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_editor_svxlink_3 = new QLabel(centralWidget);
        label_editor_svxlink_3->setObjectName(QString::fromUtf8("label_editor_svxlink_3"));
        label_editor_svxlink_3->setGeometry(QRect(210, 1830, 191, 21));
        label_editor_svxlink_3->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_editor_svxlink_3->setAlignment(Qt::AlignCenter);
        label_rx = new QLabel(centralWidget);
        label_rx->setObjectName(QString::fromUtf8("label_rx"));
        label_rx->setGeometry(QRect(90, 1830, 391, 28));
        label_rx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_tx = new QLabel(centralWidget);
        label_tx->setObjectName(QString::fromUtf8("label_tx"));
        label_tx->setGeometry(QRect(90, 1830, 391, 28));
        label_tx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_puente_rx = new QLineEdit(centralWidget);
        lineEdit_puente_rx->setObjectName(QString::fromUtf8("lineEdit_puente_rx"));
        lineEdit_puente_rx->setGeometry(QRect(160, 1830, 241, 26));
        lineEdit_puente_rx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_puente_rx->setMaxLength(32767);
        lineEdit_puente_rx->setCursorPosition(0);
        lineEdit_puente_rx->setAlignment(Qt::AlignCenter);
        label_port_proxy = new QLabel(centralWidget);
        label_port_proxy->setObjectName(QString::fromUtf8("label_port_proxy"));
        label_port_proxy->setGeometry(QRect(13, 152, 127, 30));
        label_port_proxy->setFont(font);
        label_port_proxy->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_port_proxy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_port_proxy = new QLineEdit(centralWidget);
        lineEdit_port_proxy->setObjectName(QString::fromUtf8("lineEdit_port_proxy"));
        lineEdit_port_proxy->setGeometry(QRect(142, 152, 158, 30));
        lineEdit_port_proxy->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_port_proxy->setMaxLength(32767);
        lineEdit_port_proxy->setCursorPosition(0);
        lineEdit_port_proxy->setAlignment(Qt::AlignCenter);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(560, 20, 16, 22));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 0);"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(560, 20, 16, 22));
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_3->setFocusPolicy(Qt::NoFocus);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        pushButton_on_pasw_proxy = new QPushButton(centralWidget);
        pushButton_on_pasw_proxy->setObjectName(QString::fromUtf8("pushButton_on_pasw_proxy"));
        pushButton_on_pasw_proxy->setGeometry(QRect(599, 120, 16, 22));
        pushButton_on_pasw_proxy->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_on_pasw_proxy->setFocusPolicy(Qt::NoFocus);
        pushButton_on_pasw_proxy->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        pushButton_off_pasw_proxy_2 = new QPushButton(centralWidget);
        pushButton_off_pasw_proxy_2->setObjectName(QString::fromUtf8("pushButton_off_pasw_proxy_2"));
        pushButton_off_pasw_proxy_2->setGeometry(QRect(599, 120, 16, 22));
        pushButton_off_pasw_proxy_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_off_pasw_proxy_2->setFocusPolicy(Qt::NoFocus);
        pushButton_off_pasw_proxy_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 0);"));
        label_password_3 = new QLabel(centralWidget);
        label_password_3->setObjectName(QString::fromUtf8("label_password_3"));
        label_password_3->setGeometry(QRect(309, 152, 169, 30));
        label_password_3->setFont(font);
        label_password_3->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_password_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_conexiones = new QLineEdit(centralWidget);
        lineEdit_conexiones->setObjectName(QString::fromUtf8("lineEdit_conexiones"));
        lineEdit_conexiones->setGeometry(QRect(480, 152, 137, 30));
        lineEdit_conexiones->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_conexiones->setAlignment(Qt::AlignCenter);
        lineEdit_puente = new QLineEdit(centralWidget);
        lineEdit_puente->setObjectName(QString::fromUtf8("lineEdit_puente"));
        lineEdit_puente->setGeometry(QRect(40, 1830, 551, 32));
        label_location_2 = new QLabel(centralWidget);
        label_location_2->setObjectName(QString::fromUtf8("label_location_2"));
        label_location_2->setGeometry(QRect(392, 1170, 188, 30));
        label_location_2->setFont(font);
        label_location_2->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_location_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_off = new QPushButton(centralWidget);
        pushButton_off->setObjectName(QString::fromUtf8("pushButton_off"));
        pushButton_off->setGeometry(QRect(599, 16, 16, 22));
        pushButton_off->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_off->setFocusPolicy(Qt::NoFocus);
        pushButton_off->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 0);"));
        pushButton_on = new QPushButton(centralWidget);
        pushButton_on->setObjectName(QString::fromUtf8("pushButton_on"));
        pushButton_on->setGeometry(QRect(599, 16, 16, 22));
        pushButton_on->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_on->setFocusPolicy(Qt::NoFocus);
        pushButton_on->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        label_status_ini = new QLabel(centralWidget);
        label_status_ini->setObjectName(QString::fromUtf8("label_status_ini"));
        label_status_ini->setGeometry(QRect(40, 1830, 82, 24));
        pushButton_on_2 = new QPushButton(centralWidget);
        pushButton_on_2->setObjectName(QString::fromUtf8("pushButton_on_2"));
        pushButton_on_2->setGeometry(QRect(11, 888, 38, 38));
        pushButton_on_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_on_2->setFocusPolicy(Qt::NoFocus);
        pushButton_on_2->setStyleSheet(QString::fromUtf8("border-image: url(:/ICONO_SVXLINK_ON.png);"));
        pushButton_off_2 = new QPushButton(centralWidget);
        pushButton_off_2->setObjectName(QString::fromUtf8("pushButton_off_2"));
        pushButton_off_2->setGeometry(QRect(11, 888, 38, 38));
        pushButton_off_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_off_2->setFocusPolicy(Qt::NoFocus);
        pushButton_off_2->setStyleSheet(QString::fromUtf8("border-image: url(:/ICONO_SVXLINK_OFF.png);"));
        label_editor_svxlink_4 = new QLabel(centralWidget);
        label_editor_svxlink_4->setObjectName(QString::fromUtf8("label_editor_svxlink_4"));
        label_editor_svxlink_4->setGeometry(QRect(342, 1200, 248, 27));
        label_editor_svxlink_4->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_editor_svxlink_4->setAlignment(Qt::AlignCenter);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 1300, 551, 32));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setFocusPolicy(Qt::NoFocus);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 127);\n"
"selection-background-color: rgb(170, 0, 255);"));
        groupBox_proxy = new QGroupBox(centralWidget);
        groupBox_proxy->setObjectName(QString::fromUtf8("groupBox_proxy"));
        groupBox_proxy->setGeometry(QRect(20, 1400, 571, 401));
        groupBox_proxy->setCursor(QCursor(Qt::PointingHandCursor));
        groupBox_proxy->setStyleSheet(QString::fromUtf8(""));
        label_password_4 = new QLabel(groupBox_proxy);
        label_password_4->setObjectName(QString::fromUtf8("label_password_4"));
        label_password_4->setGeometry(QRect(10, 220, 553, 30));
        label_password_4->setFont(font);
        label_password_4->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_password_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_password_proxy_propio = new QLineEdit(groupBox_proxy);
        lineEdit_password_proxy_propio->setObjectName(QString::fromUtf8("lineEdit_password_proxy_propio"));
        lineEdit_password_proxy_propio->setGeometry(QRect(220, 222, 341, 26));
        QFont font4;
        font4.setPointSize(13);
        lineEdit_password_proxy_propio->setFont(font4);
#if QT_CONFIG(statustip)
        lineEdit_password_proxy_propio->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
        lineEdit_password_proxy_propio->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"border-radius:3px;"));
        lineEdit_password_proxy_propio->setMaxLength(32767);
        lineEdit_password_proxy_propio->setEchoMode(QLineEdit::Password);
        lineEdit_password_proxy_propio->setCursorPosition(8);
        lineEdit_password_proxy_propio->setAlignment(Qt::AlignCenter);
        label_ip_proxy_propio = new QLabel(groupBox_proxy);
        label_ip_proxy_propio->setObjectName(QString::fromUtf8("label_ip_proxy_propio"));
        label_ip_proxy_propio->setGeometry(QRect(10, 170, 271, 30));
        label_ip_proxy_propio->setFont(font);
        label_ip_proxy_propio->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_ip_proxy_propio->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_ip_proxy_propio = new QLineEdit(groupBox_proxy);
        lineEdit_ip_proxy_propio->setObjectName(QString::fromUtf8("lineEdit_ip_proxy_propio"));
        lineEdit_ip_proxy_propio->setGeometry(QRect(139, 172, 140, 26));
        lineEdit_ip_proxy_propio->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_ip_proxy_propio->setMaxLength(32767);
        lineEdit_ip_proxy_propio->setCursorPosition(0);
        lineEdit_ip_proxy_propio->setAlignment(Qt::AlignCenter);
        lineEdit_port_proxy_propio = new QLineEdit(groupBox_proxy);
        lineEdit_port_proxy_propio->setObjectName(QString::fromUtf8("lineEdit_port_proxy_propio"));
        lineEdit_port_proxy_propio->setGeometry(QRect(460, 172, 101, 26));
        lineEdit_port_proxy_propio->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_port_proxy_propio->setMaxLength(32767);
        lineEdit_port_proxy_propio->setCursorPosition(0);
        lineEdit_port_proxy_propio->setAlignment(Qt::AlignCenter);
        label_port_proxy_2 = new QLabel(groupBox_proxy);
        label_port_proxy_2->setObjectName(QString::fromUtf8("label_port_proxy_2"));
        label_port_proxy_2->setGeometry(QRect(290, 170, 273, 30));
        label_port_proxy_2->setFont(font);
        label_port_proxy_2->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_port_proxy_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_editor_svxlink_5 = new QLabel(groupBox_proxy);
        label_editor_svxlink_5->setObjectName(QString::fromUtf8("label_editor_svxlink_5"));
        label_editor_svxlink_5->setGeometry(QRect(10, 130, 551, 27));
        label_editor_svxlink_5->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_editor_svxlink_5->setAlignment(Qt::AlignCenter);
        pushButton_6 = new QPushButton(groupBox_proxy);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(450, 340, 109, 32));
        pushButton_off_pasw_proxy_propio = new QPushButton(groupBox_proxy);
        pushButton_off_pasw_proxy_propio->setObjectName(QString::fromUtf8("pushButton_off_pasw_proxy_propio"));
        pushButton_off_pasw_proxy_propio->setGeometry(QRect(542, 224, 16, 22));
        pushButton_off_pasw_proxy_propio->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_off_pasw_proxy_propio->setFocusPolicy(Qt::NoFocus);
        pushButton_off_pasw_proxy_propio->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 0);"));
        pushButton_on_pasw_proxy_propio = new QPushButton(groupBox_proxy);
        pushButton_on_pasw_proxy_propio->setObjectName(QString::fromUtf8("pushButton_on_pasw_proxy_propio"));
        pushButton_on_pasw_proxy_propio->setGeometry(QRect(542, 224, 16, 22));
        pushButton_on_pasw_proxy_propio->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_on_pasw_proxy_propio->setFocusPolicy(Qt::NoFocus);
        pushButton_on_pasw_proxy_propio->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        pushButton_instalar_proxy = new QPushButton(groupBox_proxy);
        pushButton_instalar_proxy->setObjectName(QString::fromUtf8("pushButton_instalar_proxy"));
        pushButton_instalar_proxy->setGeometry(QRect(10, 70, 551, 32));
        pushButton_instalar_proxy->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(170, 0, 255);"));
        label_proxy_instalado = new QLabel(groupBox_proxy);
        label_proxy_instalado->setObjectName(QString::fromUtf8("label_proxy_instalado"));
        label_proxy_instalado->setGeometry(QRect(10, 70, 551, 32));
        label_proxy_instalado->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 127);\n"
"color:#000;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;\n"
""));
        label_proxy_instalado->setAlignment(Qt::AlignCenter);
        label_password_4->raise();
        lineEdit_password_proxy_propio->raise();
        label_ip_proxy_propio->raise();
        lineEdit_ip_proxy_propio->raise();
        label_port_proxy_2->raise();
        lineEdit_port_proxy_propio->raise();
        label_editor_svxlink_5->raise();
        pushButton_6->raise();
        pushButton_off_pasw_proxy_propio->raise();
        pushButton_on_pasw_proxy_propio->raise();
        pushButton_instalar_proxy->raise();
        label_proxy_instalado->raise();
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(30, 1830, 551, 32));
        pushButton_7->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color:#55aa7f;\n"
"color:#e8e8e8;\n"
"selection-background-color: rgb(170, 0, 255);"));
        label_status_soundcard = new QLabel(centralWidget);
        label_status_soundcard->setObjectName(QString::fromUtf8("label_status_soundcard"));
        label_status_soundcard->setGeometry(QRect(70, 1830, 82, 24));
        label_status_proxy = new QLabel(centralWidget);
        label_status_proxy->setObjectName(QString::fromUtf8("label_status_proxy"));
        label_status_proxy->setGeometry(QRect(90, 1830, 82, 24));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 217, 620, 231));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: #000;"));
        label_alsa_tx_3 = new QLabel(groupBox);
        label_alsa_tx_3->setObjectName(QString::fromUtf8("label_alsa_tx_3"));
        label_alsa_tx_3->setGeometry(QRect(290, 104, 141, 28));
        label_alsa_tx_3->setFont(font);
        label_alsa_tx_3->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_alsa_tx_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_transistor = new QLabel(groupBox);
        label_transistor->setObjectName(QString::fromUtf8("label_transistor"));
        label_transistor->setGeometry(QRect(11, 169, 606, 28));
        label_transistor->setStyleSheet(QString::fromUtf8("color: #ff0;\n"
"border:2px solid #f00;\n"
"border-radius:3px;"));
        label_transistor->setAlignment(Qt::AlignCenter);
        pushButton_beep_off = new QPushButton(groupBox);
        pushButton_beep_off->setObjectName(QString::fromUtf8("pushButton_beep_off"));
        pushButton_beep_off->setGeometry(QRect(292, 137, 324, 28));
        pushButton_beep_off->setFont(font2);
        pushButton_beep_off->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_beep_off->setFocusPolicy(Qt::NoFocus);
        pushButton_beep_off->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        pushButton_beep_on = new QPushButton(groupBox);
        pushButton_beep_on->setObjectName(QString::fromUtf8("pushButton_beep_on"));
        pushButton_beep_on->setGeometry(QRect(292, 137, 324, 28));
        pushButton_beep_on->setFont(font2);
        pushButton_beep_on->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_beep_on->setFocusPolicy(Qt::NoFocus);
        pushButton_beep_on->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(433, 7, 184, 28));
        pushButton->setFont(font2);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_baliza_2 = new QLabel(groupBox);
        label_baliza_2->setObjectName(QString::fromUtf8("label_baliza_2"));
        label_baliza_2->setGeometry(QRect(290, 7, 90, 28));
        label_baliza_2->setFont(font);
        label_baliza_2->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_baliza_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_baliza_4 = new QLabel(groupBox);
        label_baliza_4->setObjectName(QString::fromUtf8("label_baliza_4"));
        label_baliza_4->setGeometry(QRect(435, 370, 128, 30));
        label_baliza_4->setFont(font);
        label_baliza_4->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_baliza_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_ptt_port = new QLineEdit(groupBox);
        lineEdit_ptt_port->setObjectName(QString::fromUtf8("lineEdit_ptt_port"));
        lineEdit_ptt_port->setGeometry(QRect(433, 71, 184, 28));
        lineEdit_ptt_port->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_ptt_port->setMaxLength(32767);
        lineEdit_ptt_port->setCursorPosition(0);
        lineEdit_ptt_port->setAlignment(Qt::AlignCenter);
        lineEdit_tono = new QLineEdit(groupBox);
        lineEdit_tono->setObjectName(QString::fromUtf8("lineEdit_tono"));
        lineEdit_tono->setGeometry(QRect(159, 104, 123, 28));
        lineEdit_tono->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_tono->setMaxLength(32767);
        lineEdit_tono->setCursorPosition(0);
        lineEdit_tono->setAlignment(Qt::AlignCenter);
        label_baliza = new QLabel(groupBox);
        label_baliza->setObjectName(QString::fromUtf8("label_baliza"));
        label_baliza->setGeometry(QRect(11, 7, 196, 28));
        label_baliza->setFont(font);
        label_baliza->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_baliza->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBox_PTT_TYPE = new QComboBox(groupBox);
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->addItem(QString());
        comboBox_PTT_TYPE->setObjectName(QString::fromUtf8("comboBox_PTT_TYPE"));
        comboBox_PTT_TYPE->setGeometry(QRect(11, 72, 271, 29));
        comboBox_PTT_TYPE->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_PTT_TYPE->setFocusPolicy(Qt::NoFocus);
        comboBox_PTT_TYPE->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_souncard = new QPushButton(groupBox);
        pushButton_souncard->setObjectName(QString::fromUtf8("pushButton_souncard"));
        pushButton_souncard->setGeometry(QRect(11, 200, 371, 28));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(false);
        font5.setWeight(50);
        pushButton_souncard->setFont(font5);
        pushButton_souncard->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_souncard->setFocusPolicy(Qt::NoFocus);
        pushButton_souncard->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_alsa_rx = new QLabel(groupBox);
        label_alsa_rx->setObjectName(QString::fromUtf8("label_alsa_rx"));
        label_alsa_rx->setGeometry(QRect(157, 490, 128, 30));
        label_alsa_rx->setFont(font);
        label_alsa_rx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_alsa_rx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_alsa_tx = new QLabel(groupBox);
        label_alsa_tx->setObjectName(QString::fromUtf8("label_alsa_tx"));
        label_alsa_tx->setGeometry(QRect(460, 420, 128, 30));
        label_alsa_tx->setFont(font);
        label_alsa_tx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_alsa_tx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_vox = new QPushButton(groupBox);
        pushButton_vox->setObjectName(QString::fromUtf8("pushButton_vox"));
        pushButton_vox->setGeometry(QRect(11, 137, 272, 28));
        pushButton_vox->setFont(font2);
        pushButton_vox->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_vox->setFocusPolicy(Qt::NoFocus);
        pushButton_vox->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_PTT_TYPE = new QLabel(groupBox);
        label_PTT_TYPE->setObjectName(QString::fromUtf8("label_PTT_TYPE"));
        label_PTT_TYPE->setGeometry(QRect(157, 380, 128, 30));
        label_PTT_TYPE->setFont(font);
        label_PTT_TYPE->setStyleSheet(QString::fromUtf8("background:#ccc;\n"
"color:#000;\n"
"border:1px solid #000;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_PTT_TYPE->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_numero_tono = new QLineEdit(groupBox);
        lineEdit_numero_tono->setObjectName(QString::fromUtf8("lineEdit_numero_tono"));
        lineEdit_numero_tono->setGeometry(QRect(382, 7, 41, 28));
        lineEdit_numero_tono->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_numero_tono->setMaxLength(32767);
        lineEdit_numero_tono->setCursorPosition(0);
        lineEdit_numero_tono->setAlignment(Qt::AlignCenter);
        lineEdit_beep = new QLineEdit(groupBox);
        lineEdit_beep->setObjectName(QString::fromUtf8("lineEdit_beep"));
        lineEdit_beep->setGeometry(QRect(433, 104, 184, 28));
        lineEdit_beep->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_beep->setMaxLength(32767);
        lineEdit_beep->setCursorPosition(0);
        lineEdit_beep->setAlignment(Qt::AlignCenter);
        pushButton_abrir_svxlink = new QPushButton(groupBox);
        pushButton_abrir_svxlink->setObjectName(QString::fromUtf8("pushButton_abrir_svxlink"));
        pushButton_abrir_svxlink->setGeometry(QRect(390, 200, 228, 28));
        pushButton_abrir_svxlink->setFont(font2);
        pushButton_abrir_svxlink->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_abrir_svxlink->setFocusPolicy(Qt::NoFocus);
        pushButton_abrir_svxlink->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(255, 170, 0);\n"
"color:#000;\n"
"border-radius:3px;"));
        pushButton_transistor = new QPushButton(groupBox);
        pushButton_transistor->setObjectName(QString::fromUtf8("pushButton_transistor"));
        pushButton_transistor->setGeometry(QRect(11, 200, 371, 28));
        pushButton_transistor->setFont(font5);
        pushButton_transistor->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_transistor->setFocusPolicy(Qt::NoFocus);
        pushButton_transistor->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        lineEdit_ptt_type = new QLineEdit(groupBox);
        lineEdit_ptt_type->setObjectName(QString::fromUtf8("lineEdit_ptt_type"));
        lineEdit_ptt_type->setGeometry(QRect(159, 71, 123, 28));
        lineEdit_ptt_type->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_ptt_type->setMaxLength(32767);
        lineEdit_ptt_type->setCursorPosition(0);
        lineEdit_ptt_type->setAlignment(Qt::AlignCenter);
        lineEdit_alsa_rx = new QLineEdit(groupBox);
        lineEdit_alsa_rx->setObjectName(QString::fromUtf8("lineEdit_alsa_rx"));
        lineEdit_alsa_rx->setGeometry(QRect(159, 39, 123, 28));
        lineEdit_alsa_rx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_alsa_rx->setMaxLength(32767);
        lineEdit_alsa_rx->setCursorPosition(13);
        lineEdit_alsa_rx->setAlignment(Qt::AlignCenter);
        pushButton_AUDIO_TX = new QPushButton(groupBox);
        pushButton_AUDIO_TX->setObjectName(QString::fromUtf8("pushButton_AUDIO_TX"));
        pushButton_AUDIO_TX->setGeometry(QRect(290, 39, 140, 28));
        pushButton_AUDIO_TX->setFont(font2);
        pushButton_AUDIO_TX->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_AUDIO_TX->setFocusPolicy(Qt::NoFocus);
        pushButton_AUDIO_TX->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        comboBox_AUDIO_RX = new QComboBox(groupBox);
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->addItem(QString());
        comboBox_AUDIO_RX->setObjectName(QString::fromUtf8("comboBox_AUDIO_RX"));
        comboBox_AUDIO_RX->setGeometry(QRect(11, 39, 271, 29));
        comboBox_AUDIO_RX->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_AUDIO_RX->setFocusPolicy(Qt::NoFocus);
        comboBox_AUDIO_RX->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_PTT_PORT = new QPushButton(groupBox);
        pushButton_PTT_PORT->setObjectName(QString::fromUtf8("pushButton_PTT_PORT"));
        pushButton_PTT_PORT->setGeometry(QRect(290, 71, 140, 28));
        pushButton_PTT_PORT->setFont(font2);
        pushButton_PTT_PORT->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_PTT_PORT->setFocusPolicy(Qt::NoFocus);
        pushButton_PTT_PORT->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        pushButton_AUDIO_RX = new QPushButton(groupBox);
        pushButton_AUDIO_RX->setObjectName(QString::fromUtf8("pushButton_AUDIO_RX"));
        pushButton_AUDIO_RX->setGeometry(QRect(11, 39, 144, 28));
        pushButton_AUDIO_RX->setFont(font2);
        pushButton_AUDIO_RX->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_AUDIO_RX->setFocusPolicy(Qt::NoFocus);
        pushButton_AUDIO_RX->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        lineEdit_alsa_tx = new QLineEdit(groupBox);
        lineEdit_alsa_tx->setObjectName(QString::fromUtf8("lineEdit_alsa_tx"));
        lineEdit_alsa_tx->setGeometry(QRect(433, 39, 184, 28));
        lineEdit_alsa_tx->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_alsa_tx->setMaxLength(32767);
        lineEdit_alsa_tx->setCursorPosition(13);
        lineEdit_alsa_tx->setAlignment(Qt::AlignCenter);
        pushButton_tonos = new QPushButton(groupBox);
        pushButton_tonos->setObjectName(QString::fromUtf8("pushButton_tonos"));
        pushButton_tonos->setGeometry(QRect(11, 137, 272, 28));
        pushButton_tonos->setFont(font2);
        pushButton_tonos->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_tonos->setFocusPolicy(Qt::NoFocus);
        pushButton_tonos->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        label_soundcard = new QLabel(groupBox);
        label_soundcard->setObjectName(QString::fromUtf8("label_soundcard"));
        label_soundcard->setGeometry(QRect(11, 169, 606, 28));
        label_soundcard->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"border:2px solid  rgb(0, 170, 0);\n"
"border-radius:3px;"));
        label_soundcard->setAlignment(Qt::AlignCenter);
        comboBox_AUDIO_TX = new QComboBox(groupBox);
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->addItem(QString());
        comboBox_AUDIO_TX->setObjectName(QString::fromUtf8("comboBox_AUDIO_TX"));
        comboBox_AUDIO_TX->setGeometry(QRect(290, 39, 328, 29));
        comboBox_AUDIO_TX->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_AUDIO_TX->setFocusPolicy(Qt::NoFocus);
        comboBox_AUDIO_TX->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_PTT_TYPE = new QPushButton(groupBox);
        pushButton_PTT_TYPE->setObjectName(QString::fromUtf8("pushButton_PTT_TYPE"));
        pushButton_PTT_TYPE->setGeometry(QRect(11, 72, 144, 28));
        pushButton_PTT_TYPE->setFont(font2);
        pushButton_PTT_TYPE->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_PTT_TYPE->setFocusPolicy(Qt::NoFocus);
        pushButton_PTT_TYPE->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 255);\n"
"color:#000;\n"
"border-radius:3px;"));
        lineEdit_baliza = new QLineEdit(groupBox);
        lineEdit_baliza->setObjectName(QString::fromUtf8("lineEdit_baliza"));
        lineEdit_baliza->setGeometry(QRect(209, 7, 74, 28));
        lineEdit_baliza->setStyleSheet(QString::fromUtf8("background:#272727;\n"
"color:#e8e8e8;\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        lineEdit_baliza->setAlignment(Qt::AlignCenter);
        label_alsa_tx_2 = new QLabel(groupBox);
        label_alsa_tx_2->setObjectName(QString::fromUtf8("label_alsa_tx_2"));
        label_alsa_tx_2->setGeometry(QRect(11, 104, 144, 28));
        label_alsa_tx_2->setFont(font);
        label_alsa_tx_2->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 66, 68);\n"
"color: rgb(223, 223, 223);\n"
"border:1px solid #fff;\n"
"font-size:15px;\n"
"border-radius:3px;"));
        label_alsa_tx_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBox_PTT_PORT = new QComboBox(groupBox);
        comboBox_PTT_PORT->addItem(QString());
        comboBox_PTT_PORT->addItem(QString());
        comboBox_PTT_PORT->addItem(QString());
        comboBox_PTT_PORT->addItem(QString());
        comboBox_PTT_PORT->setObjectName(QString::fromUtf8("comboBox_PTT_PORT"));
        comboBox_PTT_PORT->setGeometry(QRect(290, 71, 328, 29));
        comboBox_PTT_PORT->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_PTT_PORT->setFocusPolicy(Qt::NoFocus);
        comboBox_PTT_PORT->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_alsa_tx->raise();
        pushButton->raise();
        label_soundcard->raise();
        pushButton_tonos->raise();
        lineEdit_alsa_rx->raise();
        pushButton_PTT_PORT->raise();
        pushButton_beep_on->raise();
        label_alsa_rx->raise();
        label_alsa_tx_3->raise();
        label_PTT_TYPE->raise();
        lineEdit_alsa_tx->raise();
        label_baliza_4->raise();
        lineEdit_beep->raise();
        pushButton_AUDIO_RX->raise();
        pushButton_beep_off->raise();
        label_baliza_2->raise();
        label_alsa_tx_2->raise();
        lineEdit_ptt_port->raise();
        pushButton_vox->raise();
        pushButton_PTT_TYPE->raise();
        pushButton_souncard->raise();
        comboBox_AUDIO_RX->raise();
        pushButton_transistor->raise();
        pushButton_AUDIO_TX->raise();
        lineEdit_ptt_type->raise();
        label_transistor->raise();
        pushButton_abrir_svxlink->raise();
        lineEdit_numero_tono->raise();
        label_baliza->raise();
        lineEdit_baliza->raise();
        comboBox_AUDIO_TX->raise();
        comboBox_PTT_PORT->raise();
        comboBox_PTT_TYPE->raise();
        lineEdit_tono->raise();
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 1100, 82, 24));
        pushButton_svxlinkAbrir = new QPushButton(centralWidget);
        pushButton_svxlinkAbrir->setObjectName(QString::fromUtf8("pushButton_svxlinkAbrir"));
        pushButton_svxlinkAbrir->setGeometry(QRect(110, 540, 331, 28));
        pushButton_svxlinkAbrir->setFont(font5);
        pushButton_svxlinkAbrir->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_svxlinkAbrir->setFocusPolicy(Qt::NoFocus);
        pushButton_svxlinkAbrir->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(255, 85, 127);\n"
"color:#000;\n"
"border-radius:5px;\n"
""));
        pushButton_svxlinkCerrar = new QPushButton(centralWidget);
        pushButton_svxlinkCerrar->setObjectName(QString::fromUtf8("pushButton_svxlinkCerrar"));
        pushButton_svxlinkCerrar->setGeometry(QRect(110, 540, 331, 28));
        pushButton_svxlinkCerrar->setFont(font5);
        pushButton_svxlinkCerrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_svxlinkCerrar->setFocusPolicy(Qt::NoFocus);
        pushButton_svxlinkCerrar->setStyleSheet(QString::fromUtf8("text-align:center;\n"
"background-color: rgb(85, 170, 0);\n"
"color:#000;\n"
"border-radius:5px;\n"
""));
        line_lila_2 = new QFrame(centralWidget);
        line_lila_2->setObjectName(QString::fromUtf8("line_lila_2"));
        line_lila_2->setGeometry(QRect(0, 0, 5, 488));
        line_lila_2->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 51, 215);\n"
"border:4px solid rgb(252, 51, 215);"));
        line_lila_2->setFrameShape(QFrame::VLine);
        line_lila_2->setFrameShadow(QFrame::Sunken);
        line_lila_3 = new QFrame(centralWidget);
        line_lila_3->setObjectName(QString::fromUtf8("line_lila_3"));
        line_lila_3->setGeometry(QRect(623, 0, 5, 488));
        line_lila_3->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 51, 215);\n"
"border:4px solid rgb(252, 51, 215);"));
        line_lila_3->setFrameShape(QFrame::VLine);
        line_lila_3->setFrameShadow(QFrame::Sunken);
        line_violeta_horizontal_2 = new QFrame(centralWidget);
        line_violeta_horizontal_2->setObjectName(QString::fromUtf8("line_violeta_horizontal_2"));
        line_violeta_horizontal_2->setGeometry(QRect(0, 483, 739, 5));
        line_violeta_horizontal_2->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 51, 215);\n"
"border:4px solid rgb(252, 51, 215);"));
        line_violeta_horizontal_2->setFrameShape(QFrame::HLine);
        line_violeta_horizontal_2->setFrameShadow(QFrame::Sunken);
        line_violeta_horizontal_3 = new QFrame(centralWidget);
        line_violeta_horizontal_3->setObjectName(QString::fromUtf8("line_violeta_horizontal_3"));
        line_violeta_horizontal_3->setGeometry(QRect(0, 0, 739, 5));
        line_violeta_horizontal_3->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 51, 215);\n"
"border:4px solid rgb(252, 51, 215);"));
        line_violeta_horizontal_3->setFrameShape(QFrame::HLine);
        line_violeta_horizontal_3->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        label_indicativo->raise();
        label_icono_svxlink->raise();
        label_editor_svxlink->raise();
        lineEdit_indicativo->raise();
        pushButton_guardar->raise();
        pushButton_abrir_module->raise();
        label_by_ea3eiz->raise();
        pushButton_SALIR->raise();
        lineEdit_indicativo1->raise();
        label_editor_svxlink_2->raise();
        label_password_2->raise();
        label_ip_proxy->raise();
        pushButton_proxy_off->raise();
        lineEdit_ip_proxy->raise();
        lineEdit_password_proxy->raise();
        pushButton_proxy_on->raise();
        label_location->raise();
        label_sisopname->raise();
        lineEdit_location->raise();
        lineEdit_sisop_name->raise();
        pushButton_id_conferencia->raise();
        label_editor_svxlink_3->raise();
        label_rx->raise();
        label_tx->raise();
        lineEdit_puente_rx->raise();
        label_port_proxy->raise();
        lineEdit_port_proxy->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_on_pasw_proxy->raise();
        pushButton_off_pasw_proxy_2->raise();
        label_password->raise();
        lineEdit_password->raise();
        label_password_3->raise();
        lineEdit_conexiones->raise();
        lineEdit_puente->raise();
        label_location_2->raise();
        lineEdit_autocon_echolink->raise();
        comboBox->raise();
        pushButton_off->raise();
        pushButton_on->raise();
        label_status_ini->raise();
        pushButton_on_2->raise();
        pushButton_off_2->raise();
        label_editor_svxlink_4->raise();
        pushButton_4->raise();
        pushButton_7->raise();
        groupBox_proxy->raise();
        label_status_soundcard->raise();
        label_status_proxy->raise();
        groupBox->raise();
        label->raise();
        pushButton_svxlinkCerrar->raise();
        pushButton_svxlinkAbrir->raise();
        line_lila_3->raise();
        line_violeta_horizontal_2->raise();
        line_lila_2->raise();
        line_violeta_horizontal_3->raise();
        QWidget::setTabOrder(lineEdit_indicativo, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, lineEdit_sisop_name);
        QWidget::setTabOrder(lineEdit_sisop_name, lineEdit_location);
        QWidget::setTabOrder(lineEdit_location, lineEdit_autocon_echolink);
        QWidget::setTabOrder(lineEdit_autocon_echolink, lineEdit_ip_proxy);
        QWidget::setTabOrder(lineEdit_ip_proxy, lineEdit_password_proxy);
        QWidget::setTabOrder(lineEdit_password_proxy, lineEdit_port_proxy);
        QWidget::setTabOrder(lineEdit_port_proxy, lineEdit_puente_rx);
        QWidget::setTabOrder(lineEdit_puente_rx, lineEdit_indicativo1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EDITOR SVXLINK", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_indicativo->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Indicativo Echolink + L \303\263 R</span></p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_indicativo->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_indicativo->setText(QCoreApplication::translate("MainWindow", "CALLSIGN:", nullptr));
        label_icono_svxlink->setText(QString());
        label_editor_svxlink->setText(QCoreApplication::translate("MainWindow", "- - - - -    EDITOR", nullptr));
        pushButton_guardar->setText(QCoreApplication::translate("MainWindow", "GUARDAR Y SALIR", nullptr));
        pushButton_abrir_module->setText(QCoreApplication::translate("MainWindow", "Abrir fichero ModuleEchoLink.conf para hacer cualquier cambio", nullptr));
        label_by_ea3eiz->setText(QCoreApplication::translate("MainWindow", "by EA3EIZ", nullptr));
        pushButton_SALIR->setText(QCoreApplication::translate("MainWindow", "SALIR", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_indicativo1->setToolTip(QCoreApplication::translate("MainWindow", "Introduce tu indicativo", nullptr));
#endif // QT_CONFIG(tooltip)
        label_editor_svxlink_2->setText(QCoreApplication::translate("MainWindow", "ModuleEchoLink", nullptr));
#if QT_CONFIG(tooltip)
        label_password->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_password->setText(QCoreApplication::translate("MainWindow", "PASSWD:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_password->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Password del indicativo Echolink</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_password->setText(QCoreApplication::translate("MainWindow", "password", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_password_proxy->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Password del proxy</span></p><p><span style=\" font-size:12pt;\"><br/></span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_password_proxy->setText(QCoreApplication::translate("MainWindow", "password", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_ip_proxy->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Pon la Ip de tu raspberry</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_ip_proxy->setText(QString());
#if QT_CONFIG(tooltip)
        label_password_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_password_2->setText(QCoreApplication::translate("MainWindow", "PROXY_PASS:", nullptr));
#if QT_CONFIG(tooltip)
        label_ip_proxy->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_ip_proxy->setText(QCoreApplication::translate("MainWindow", "PROXY_SERVER:", nullptr));
        pushButton_proxy_on->setText(QCoreApplication::translate("MainWindow", "Activar Proxy", nullptr));
        pushButton_proxy_off->setText(QCoreApplication::translate("MainWindow", "Desactivar Proxy", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_sisop_name->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Informaci\303\263n en pantalla Echolink</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_sisop_name->setText(QString());
#if QT_CONFIG(tooltip)
        lineEdit_location->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Informaci\303\263n donde est\303\241 conectado</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_location->setText(QCoreApplication::translate("MainWindow", "Connect to *REM-ESP*", nullptr));
#if QT_CONFIG(tooltip)
        label_location->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_location->setText(QCoreApplication::translate("MainWindow", "LOCATION:", nullptr));
#if QT_CONFIG(tooltip)
        label_sisopname->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_sisopname->setText(QCoreApplication::translate("MainWindow", "SYSOPNAME:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_autocon_echolink->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Introduce el ID de la conferencia donde quieres conectarte</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "                 Elige una conferencia a la que conectarse", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "*ADER*", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "*REM-ESP*", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "*CZR-ESP*", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "*ECHOTEST*", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "*EALINK*", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow", "*AELD-ESP*", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("MainWindow", "*CUBANOS*", nullptr));

#if QT_CONFIG(tooltip)
        pushButton_id_conferencia->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Esoge la Id de la conferencia de una lista</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_id_conferencia->setText(QCoreApplication::translate("MainWindow", "AUTOCON_ECHOLINK_ID Conferencia", nullptr));
        label_editor_svxlink_3->setText(QCoreApplication::translate("MainWindow", "svxlink", nullptr));
        label_rx->setText(QString());
        label_tx->setText(QString());
#if QT_CONFIG(tooltip)
        lineEdit_puente_rx->setToolTip(QCoreApplication::translate("MainWindow", "Introduce tu indicativo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_port_proxy->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_port_proxy->setText(QCoreApplication::translate("MainWindow", "PROXY_PORT:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_port_proxy->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Puerto del proxy</span></p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_port_proxy->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_on_pasw_proxy->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_off_pasw_proxy_2->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
#if QT_CONFIG(tooltip)
        label_password_3->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_password_3->setText(QCoreApplication::translate("MainWindow", "MAX_CONNECTIONS:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_conexiones->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Conexiones m\303\241ximas permitidas</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_conexiones->setText(QString());
#if QT_CONFIG(tooltip)
        label_location_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_location_2->setText(QCoreApplication::translate("MainWindow", "LOCATION:", nullptr));
        pushButton_off->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_on->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        label_status_ini->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_on_2->setText(QString());
        pushButton_off_2->setText(QString());
        label_editor_svxlink_4->setText(QCoreApplication::translate("MainWindow", "SVXLINK    - - - - - ", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Instalar y Configurar tu propio proxy en esta Rapberry pi", nullptr));
        groupBox_proxy->setTitle(QString());
#if QT_CONFIG(tooltip)
        label_password_4->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_password_4->setText(QCoreApplication::translate("MainWindow", "Password para tu proxy:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_password_proxy_propio->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lineEdit_password_proxy_propio->setText(QCoreApplication::translate("MainWindow", "password", nullptr));
#if QT_CONFIG(tooltip)
        label_ip_proxy_propio->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_ip_proxy_propio->setText(QCoreApplication::translate("MainWindow", "Ip de tu raspi:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_ip_proxy_propio->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Introduce la ip de tu raspi</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_ip_proxy_propio->setText(QString());
#if QT_CONFIG(tooltip)
        lineEdit_port_proxy_propio->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Introduce puerto ej: 8100</span></p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_port_proxy_propio->setText(QString());
#if QT_CONFIG(tooltip)
        label_port_proxy_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_port_proxy_2->setText(QCoreApplication::translate("MainWindow", "Puerto para tu proxy:", nullptr));
        label_editor_svxlink_5->setText(QCoreApplication::translate("MainWindow", "- - - - -  CONFIGURA TU PROXY INSTALADO EN ESTA RASPBERRY PI  - - - - -", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "CERRAR", nullptr));
        pushButton_off_pasw_proxy_propio->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_on_pasw_proxy_propio->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
        pushButton_instalar_proxy->setText(QCoreApplication::translate("MainWindow", "INSTALAR PROXY EN ESTA RASPBERRY PI", nullptr));
        label_proxy_instalado->setText(QCoreApplication::translate("MainWindow", "YA TIENES INSTALADO EL PROXY EN ESTA RASPBERRY PI", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "PONER EN MARCHA EL PROXY RASPI \303\263 EXTERNO", nullptr));
        label_status_soundcard->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_status_proxy->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        groupBox->setTitle(QString());
#if QT_CONFIG(tooltip)
        label_alsa_tx_3->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_alsa_tx_3->setText(QCoreApplication::translate("MainWindow", "Roger Bepp :", nullptr));
        label_transistor->setText(QCoreApplication::translate("MainWindow", "SISTEMA ACTIVO: modem construido con resistencia y  transistor", nullptr));
        pushButton_beep_off->setText(QCoreApplication::translate("MainWindow", "Desactivar Roger Beep", nullptr));
        pushButton_beep_on->setText(QCoreApplication::translate("MainWindow", "Activar Roger Beep", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Alsamixer", nullptr));
#if QT_CONFIG(tooltip)
        label_baliza_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_baliza_2->setText(QCoreApplication::translate("MainWindow", "CTCSS_FQ:", nullptr));
#if QT_CONFIG(tooltip)
        label_baliza_4->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_baliza_4->setText(QCoreApplication::translate("MainWindow", "PTT_PORT:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_ptt_port->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEdit_tono->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_baliza->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_baliza->setText(QCoreApplication::translate("MainWindow", "SHORT_IDENT_INTERVAL:", nullptr));
        comboBox_PTT_TYPE->setItemText(0, QCoreApplication::translate("MainWindow", "          Elige PTT TYPE", nullptr));
        comboBox_PTT_TYPE->setItemText(1, QCoreApplication::translate("MainWindow", "SerialPin", nullptr));
        comboBox_PTT_TYPE->setItemText(2, QCoreApplication::translate("MainWindow", "GPIO", nullptr));
        comboBox_PTT_TYPE->setItemText(3, QCoreApplication::translate("MainWindow", "Hidraw", nullptr));
        comboBox_PTT_TYPE->setItemText(4, QCoreApplication::translate("MainWindow", "PTY", nullptr));
        comboBox_PTT_TYPE->setItemText(5, QCoreApplication::translate("MainWindow", "NONE", nullptr));

        pushButton_souncard->setText(QCoreApplication::translate("MainWindow", "CAMBIAR a  modem sound card o similar", nullptr));
#if QT_CONFIG(tooltip)
        label_alsa_rx->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_alsa_rx->setText(QString());
#if QT_CONFIG(tooltip)
        label_alsa_tx->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_alsa_tx->setText(QString());
        pushButton_vox->setText(QCoreApplication::translate("MainWindow", "Cambiar a VOX", nullptr));
#if QT_CONFIG(tooltip)
        label_PTT_TYPE->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_PTT_TYPE->setText(QCoreApplication::translate("MainWindow", "PTT_TYPE:", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_numero_tono->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Introduce n\303\272mero de tono</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEdit_beep->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_abrir_svxlink->setText(QCoreApplication::translate("MainWindow", "Abrir fichero svxlink.conf", nullptr));
        pushButton_transistor->setText(QCoreApplication::translate("MainWindow", "CAMBIAR a modem con resistencia y transistor", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_ptt_type->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEdit_alsa_rx->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lineEdit_alsa_rx->setText(QCoreApplication::translate("MainWindow", "alsa:plughw:0", nullptr));
        pushButton_AUDIO_TX->setText(QCoreApplication::translate("MainWindow", "AUDIO TX", nullptr));
        comboBox_AUDIO_RX->setItemText(0, QCoreApplication::translate("MainWindow", "          Elige AUDIO RX", nullptr));
        comboBox_AUDIO_RX->setItemText(1, QCoreApplication::translate("MainWindow", "alsa:default", nullptr));
        comboBox_AUDIO_RX->setItemText(2, QCoreApplication::translate("MainWindow", "alsa:plughw:0", nullptr));
        comboBox_AUDIO_RX->setItemText(3, QCoreApplication::translate("MainWindow", "alsa:plughw:1", nullptr));
        comboBox_AUDIO_RX->setItemText(4, QCoreApplication::translate("MainWindow", "alsa:hw:0", nullptr));
        comboBox_AUDIO_RX->setItemText(5, QCoreApplication::translate("MainWindow", "alsa:hw:1", nullptr));
        comboBox_AUDIO_RX->setItemText(6, QString());

#if QT_CONFIG(tooltip)
        comboBox_AUDIO_RX->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_PTT_PORT->setText(QCoreApplication::translate("MainWindow", "PTT PORT", nullptr));
        pushButton_AUDIO_RX->setText(QCoreApplication::translate("MainWindow", "AUDIO RX", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_alsa_tx->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lineEdit_alsa_tx->setText(QCoreApplication::translate("MainWindow", "alsa:plughw:1", nullptr));
        pushButton_tonos->setText(QCoreApplication::translate("MainWindow", "Cambiar a TONOS", nullptr));
        label_soundcard->setText(QCoreApplication::translate("MainWindow", "SISTEMA ACTIVO: modem Sound card o similar", nullptr));
        comboBox_AUDIO_TX->setItemText(0, QCoreApplication::translate("MainWindow", "          Elige AUDIO TX", nullptr));
        comboBox_AUDIO_TX->setItemText(1, QCoreApplication::translate("MainWindow", "alsa:default", nullptr));
        comboBox_AUDIO_TX->setItemText(2, QCoreApplication::translate("MainWindow", "alsa:plughw:0", nullptr));
        comboBox_AUDIO_TX->setItemText(3, QCoreApplication::translate("MainWindow", "alsa:plughw:1", nullptr));
        comboBox_AUDIO_TX->setItemText(4, QCoreApplication::translate("MainWindow", "alsa:hw:0", nullptr));
        comboBox_AUDIO_TX->setItemText(5, QCoreApplication::translate("MainWindow", "alsa:hw:1", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_AUDIO_TX->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_PTT_TYPE->setText(QCoreApplication::translate("MainWindow", "PTT_TYPE", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_baliza->setToolTip(QCoreApplication::translate("MainWindow", "Cada cuanto tiempo en minutos da la baliza", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_baliza->setText(QString());
#if QT_CONFIG(tooltip)
        label_alsa_tx_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_alsa_tx_2->setText(QCoreApplication::translate("MainWindow", "TONO \303\263 VOX :", nullptr));
        comboBox_PTT_PORT->setItemText(0, QCoreApplication::translate("MainWindow", "          Elige PTT PORT", nullptr));
        comboBox_PTT_PORT->setItemText(1, QCoreApplication::translate("MainWindow", "/dev/ttyUSB0", nullptr));
        comboBox_PTT_PORT->setItemText(2, QCoreApplication::translate("MainWindow", "/dev/ttyUSB1", nullptr));
        comboBox_PTT_PORT->setItemText(3, QCoreApplication::translate("MainWindow", "/dev/ttyUSB2", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_svxlinkAbrir->setText(QCoreApplication::translate("MainWindow", "ABRIR MEN\303\232 CONFIGURACI\303\223N SVXLINK", nullptr));
        pushButton_svxlinkCerrar->setText(QCoreApplication::translate("MainWindow", "CERRAR MEN\303\232 CONFIGURACI\303\223N SVXLINK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
