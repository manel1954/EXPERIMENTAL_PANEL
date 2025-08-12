#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "iostream"
#include "QTextEdit"
#include "QLineEdit"
#include "QObject"
#include "QLabel"
#include "QString"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include "QInputDialog"
#include "QTextCodec"
#include "QTimer"

#include "QSettings"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    system("sudo killall qt_menu_superior &");


    //Variables para usar
    modo = "/home/pi/MMDVMHost/MMDVM.ini";
    //memorias = "/home/pi/.local/memorias.ini";


// Buscar numero de linea Options
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[DMR Network]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("Options=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    // En el constructor de tu clase, por ejemplo MainWindow
                QFile file4("/home/pi/A108/DMR_IPSC2.txt");
                if (file4.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file4);
                while (!in.atEnd()) {
                QString line = in.readLine().trimmed();
                // Saltar líneas vacías o comentarios
                if (line.isEmpty() || line.startsWith("#")) continue;
                // Dividir por espacios o tabulaciones
                QStringList columns = line.split(QRegExp("\\s+"));
                if (columns.size() >= 2) {
                // Mostrar columna 1 en comboBox_2
                // Almacenar la línea completa como dato oculto
                ui->comboBox_2->addItem(columns[0], line);
                }
                }
                file4.close();
    }
                // Conectar signal al slot para mostrar columnas 3 y 5 en etiquetas

                 ui->progressBar->setVisible(false);

                 connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
                 [=](int index){
                     if (index >= 0) {
                         QString line = ui->comboBox_2->itemData(index).toString();
                         QStringList columns = line.split(QRegExp("\\s+"));
                         if (columns.size() >= 2) {
                             ui->label_hosts_2->setText(columns[2]);
                             QString memo = ui->label_hosts_2->text();


                             QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                             QString sed = "sed -i '" + numLineaStr + "c";
                             QString ipsc2 = sed + "Options=" + memo + "' " + modo;
                             ui->lineEdit_puente->setText(ipsc2);
                             system(ui->lineEdit_puente->text().toStdString().c_str());



                             int duration = 3000; // 3 segundos en milisegundos
                             int interval = 100;  // cada cuánto actualizar la barra
                             int steps = duration / interval;
                             int* counter = new int(0);  // usar puntero si estás dentro de una lambda

                             // Mostrar la barra de progreso y reiniciarla
                             ui->progressBar->setValue(0);
                             ui->progressBar->setVisible(true);
                             QTimer* timer = new QTimer(this);
                             connect(timer, &QTimer::timeout, this, [=]() mutable {
                                 (*counter)++;
                                 int progress = (*counter) * 100 / steps;
                                 ui->progressBar->setValue(progress);

                                 if (*counter >= steps) {
                                     timer->stop();
                                     ui->progressBar->setVisible(false);
                                     delete counter;
                                     timer->deleteLater();
                                     //qDebug() << "Progreso terminado tras 5 segundos";
                                     // Aquí puedes volver a hacer visible el botón o lo que necesites


                                     // Presenta el fichero MMDVMhost
                                     QFile file(modo);
                                     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                                         QMessageBox::information(nullptr, "info", file.errorString());
                                         return;
                                     }
                                     QTextStream in(&file);
                                     QString line;
                                     bool inGeneralSection = false;

                                     //UARTPort
                                     while (!in.atEnd()) {
                                         line = in.readLine().trimmed();

                                         // Detecta la sección [Network]
                                         if (line.startsWith('[')) {
                                             if (line == "[DMR Network]") {
                                                 inGeneralSection = true;
                                             } else {
                                                 inGeneralSection = false;
                                             }
                                         }

                                         if (inGeneralSection && line.startsWith("Options=")) {
                                             QString ipsc2 = line.section('=', 1);  // Extrae el valor después del '='
                                             ui->lineEdit_Options->setText(ipsc2);
                                             break;  // Ya lo encontramos, salimos del bucle
                                         }
                                     }
                                     ui->lineEdit_Options->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
                                 }
                             });
                             timer->start(interval);
                         } else {
                             ui->label_hosts_2->clear();
                         }
                     }
                 });










                 // Buscar numero de linea UARTPort
                     QFile file10(modo);
                     if (!file10.open(QIODevice::ReadOnly | QIODevice::Text)) {
                         QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file10.errorString());
                         return;
                     }
                     QTextStream in10(&file10);
                     QString line10;
                     int lineNumber10 = 0;
                     int numero_linea10 = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
                     bool inGeneral10 = false;

                     while (!in10.atEnd()) {
                         line10 = in10.readLine();
                         lineNumber10++;
                         if (line10.trimmed() == "[Modem]") {
                             inGeneral10 = true;
                         } else if (line10.trimmed().startsWith('[') && inGeneral10) {
                             // Salimos de la sección [General]
                             inGeneral10 = false;
                         }
                         if (inGeneral10 && line10.trimmed().startsWith("UARTPort=")) {
                             numero_linea10 = lineNumber10;
                             break;  // Ya lo encontramos, no hace falta seguir
                         }
                     }
                     file10.close();

                     // En el constructor de tu clase, por ejemplo MainWindow
                                 QFile file11("/home/pi/A108/DMR_PORT_MODEM.txt");
                                 if (file11.open(QIODevice::ReadOnly | QIODevice::Text)) {
                                 QTextStream in11(&file11);
                                 while (!in11.atEnd()) {
                                 QString line11 = in11.readLine().trimmed();
                                 // Saltar líneas vacías o comentarios
                                 if (line10.isEmpty() || line11.startsWith("#")) continue;
                                 // Dividir por espacios o tabulaciones
                                 QStringList columns = line11.split(QRegExp("\\s+"));
                                 if (columns.size() >= 2) {
                                 // Mostrar columna 1 en comboBox_2
                                 // Almacenar la línea completa como dato oculto
                                 ui->comboBox_3->addItem(columns[0], line11);
                                 }
                                 }
                                 file11.close();
                     }
                                 // Conectar signal al slot para mostrar columnas 3 y 5 en etiquetas

                                  ui->progressBar->setVisible(false);

                                  connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged),
                                  [=](int index){
                                      if (index >= 0) {
                                          QString line11 = ui->comboBox_3->itemData(index).toString();
                                          QStringList columns = line11.split(QRegExp("\\s+"));
                                          if (columns.size() >= 2) {
                                              ui->label_hosts_2->setText(columns[2]);
                                              QString memo = ui->label_hosts_2->text();


                                              QString numLineaStr = QString::number(numero_linea10);  // convertir int a QString
                                              QString sed = "sed -i '" + numLineaStr + "c";
                                              QString ipsc2 = sed + "UARTPort=" + memo + "' " + modo;
                                              ui->lineEdit_puente->setText(ipsc2);
                                              system(ui->lineEdit_puente->text().toStdString().c_str());



                                              int duration = 3000; // 3 segundos en milisegundos
                                              int interval = 100;  // cada cuánto actualizar la barra
                                              int steps = duration / interval;
                                              int* counter = new int(0);  // usar puntero si estás dentro de una lambda

                                              // Mostrar la barra de progreso y reiniciarla
                                              ui->progressBar->setValue(0);
                                              ui->progressBar->setVisible(true);
                                              QTimer* timer = new QTimer(this);
                                              connect(timer, &QTimer::timeout, this, [=]() mutable {
                                                  (*counter)++;
                                                  int progress = (*counter) * 100 / steps;
                                                  ui->progressBar->setValue(progress);

                                                  if (*counter >= steps) {
                                                      timer->stop();
                                                      ui->progressBar->setVisible(false);
                                                      delete counter;
                                                      timer->deleteLater();
                                                      //qDebug() << "Progreso terminado tras 5 segundos";
                                                      // Aquí puedes volver a hacer visible el botón o lo que necesites


                                                      // Presenta el fichero MMDVMhost
                                                      QFile file(modo);
                                                      if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                                                          QMessageBox::information(nullptr, "info", file.errorString());
                                                          return;
                                                      }
                                                      QTextStream in(&file);
                                                      QString line;
                                                      bool inGeneralSection = false;

                                                      //UARTPort
                                                      while (!in.atEnd()) {
                                                          line = in.readLine().trimmed();

                                                          // Detecta la sección [Network]
                                                          if (line.startsWith('[')) {
                                                              if (line == "[Modem]") {
                                                                  inGeneralSection = true;
                                                              } else {
                                                                  inGeneralSection = false;
                                                              }
                                                          }

                                                          if (inGeneralSection && line.startsWith("UARTPort=")) {
                                                              QString UARTPort = line.section('=', 1);  // Extrae el valor después del '='
                                                              ui->lineEdit_UARTPort->setText(UARTPort);
                                                              break;  // Ya lo encontramos, salimos del bucle
                                                          }
                                                      }
                                                      ui->lineEdit_UARTPort->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
                                                  }
                                              });
                                              timer->start(interval);
                                          } else {
                                              ui->label_hosts_2->clear();
                                          }
                                      }
                                  });


    // la linea siguiente oculta toda la barra superior del formulario
     setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

    // POSICION DEL FORMULARIO EN LA PANTALLA
    int px  = (7);
    int py = (63);
    this->move(   QPoint(px,py)  );


    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();

        // Detecta la sección [Network]
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Callsign=")) {
            QString callsign = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_callsign->setText(callsign);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Id
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Id=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_id->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Port Nextion
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Nextion]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Port=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_PorNextion->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

 // **************************************************************************************
 // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
    file.close();
    // Presenta el fichero MMDVMhost
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
// ***************************************************************************************

    //Timeout
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Timeout=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Timeout->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Duplex
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Duplex=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Duplex->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //RFModeHang
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("RFModeHang=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_RFModeHang->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Display
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Display=")) {
            QString display = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TipoDisplay->setText(display);
            ui->lineEdit_Display->setText(display);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //RXFrequency
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("RXFrequency=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_RXF->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //TXFrequency
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("TXFrequency=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TXF->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //Latitude
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Latitude=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Latitude->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Longitude
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Longitude=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Longitude->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //Location
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Location=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Location->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //URL
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("URL=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_URL->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //DisplayLevel
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Log]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("DisplayLevel=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_DisplayLevel->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //FileLevel
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith('[')) {
                if (line == "[Log]") {
                    inGeneralSection = true;
                } else {
                    inGeneralSection = false;
                }
            }
            if (inGeneralSection && line.startsWith("FileLevel=")) {
                QString id = line.section('=', 1);  // Extrae el valor después del '='
                ui->lineEdit_FileLevel->setText(id);
                break;  // Ya lo encontramos, salimos del bucle
            }
        }

        //CW Id
            while (!in.atEnd()) {
                line = in.readLine().trimmed();
                if (line.startsWith('[')) {
                    if (line == "[CW Id]") {
                        inGeneralSection = true;
                    } else {
                        inGeneralSection = false;
                    }
                }
                if (inGeneralSection && line.startsWith("Enable=")) {
                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                    ui->lineEdit_CW_Id->setText(id);
                    break;  // Ya lo encontramos, salimos del bucle
                }
            }

            //UARTPort
                while (!in.atEnd()) {
                    line = in.readLine().trimmed();
                    if (line.startsWith('[')) {
                        if (line == "[Modem]") {
                            inGeneralSection = true;
                        } else {
                            inGeneralSection = false;
                        }
                    }
                    if (inGeneralSection && line.startsWith("UARTPort=")) {
                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                        ui->lineEdit_UARTPort->setText(id);
                        break;  // Ya lo encontramos, salimos del bucle
                    }
                }

                //TXInvert
                    while (!in.atEnd()) {
                        line = in.readLine().trimmed();
                        if (line.startsWith('[')) {
                            if (line == "[Modem]") {
                                inGeneralSection = true;
                            } else {
                                inGeneralSection = false;
                            }
                        }
                        if (inGeneralSection && line.startsWith("TXInvert=")) {
                            QString id = line.section('=', 1);  // Extrae el valor después del '='
                            ui->lineEdit_TXInvert->setText(id);
                            break;  // Ya lo encontramos, salimos del bucle
                        }
                    }

                    //RXInvert
                        while (!in.atEnd()) {
                            line = in.readLine().trimmed();
                            if (line.startsWith('[')) {
                                if (line == "[Modem]") {
                                    inGeneralSection = true;
                                } else {
                                    inGeneralSection = false;
                                }
                            }
                            if (inGeneralSection && line.startsWith("RXInvert=")) {
                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                ui->lineEdit_RXInvert->setText(id);
                                break;  // Ya lo encontramos, salimos del bucle
                            }
                        }

                        //RXOffset
                            while (!in.atEnd()) {
                                line = in.readLine().trimmed();
                                if (line.startsWith('[')) {
                                    if (line == "[Modem]") {
                                        inGeneralSection = true;
                                    } else {
                                        inGeneralSection = false;
                                    }
                                }
                                if (inGeneralSection && line.startsWith("RXOffset=")) {
                                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                                    ui->lineEdit_RXOffset->setText(id);
                                    break;  // Ya lo encontramos, salimos del bucle
                                }
                            }

                            //TXOffset
                                while (!in.atEnd()) {
                                    line = in.readLine().trimmed();
                                    if (line.startsWith('[')) {
                                        if (line == "[Modem]") {
                                            inGeneralSection = true;
                                        } else {
                                            inGeneralSection = false;
                                        }
                                    }
                                    if (inGeneralSection && line.startsWith("TXOffset=")) {
                                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                                        ui->lineEdit_TXOffset->setText(id);
                                        break;  // Ya lo encontramos, salimos del bucle
                                    }
                                }

                                //RXLevel
                                    while (!in.atEnd()) {
                                        line = in.readLine().trimmed();
                                        if (line.startsWith('[')) {
                                            if (line == "[Modem]") {
                                                inGeneralSection = true;
                                            } else {
                                                inGeneralSection = false;
                                            }
                                        }
                                        if (inGeneralSection && line.startsWith("RXLevel=")) {
                                            QString id = line.section('=', 1);  // Extrae el valor después del '='
                                            ui->lineEdit_RXLevel->setText(id);
                                            break;  // Ya lo encontramos, salimos del bucle
                                        }
                                    }

                                    //TXLevel
                                        while (!in.atEnd()) {
                                            line = in.readLine().trimmed();
                                            if (line.startsWith('[')) {
                                                if (line == "[Modem]") {
                                                    inGeneralSection = true;
                                                } else {
                                                    inGeneralSection = false;
                                                }
                                            }
                                            if (inGeneralSection && line.startsWith("TXLevel=")) {
                                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                ui->lineEdit_TXLevel->setText(id);
                                                break;  // Ya lo encontramos, salimos del bucle
                                            }
                                        }

                                        //RXDCOffset
                                            while (!in.atEnd()) {
                                                line = in.readLine().trimmed();
                                                if (line.startsWith('[')) {
                                                    if (line == "[Modem]") {
                                                        inGeneralSection = true;
                                                    } else {
                                                        inGeneralSection = false;
                                                    }
                                                }
                                                if (inGeneralSection && line.startsWith("RXDCOffset=")) {
                                                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                    ui->lineEdit_RXDCOffset->setText(id);
                                                    break;  // Ya lo encontramos, salimos del bucle
                                                }
                                            }
                                            //TXDCOffset
                                                while (!in.atEnd()) {
                                                    line = in.readLine().trimmed();
                                                    if (line.startsWith('[')) {
                                                        if (line == "[Modem]") {
                                                            inGeneralSection = true;
                                                        } else {
                                                            inGeneralSection = false;
                                                        }
                                                    }
                                                    if (inGeneralSection && line.startsWith("TXDCOffset=")) {
                                                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                        ui->lineEdit_TXDCOffset->setText(id);
                                                        break;  // Ya lo encontramos, salimos del bucle
                                                    }
                                                }
                                                //Type
                                                while (!in.atEnd()) {
                                                line = in.readLine().trimmed();
                                                if (line.startsWith('[')) {
                                                if (line == "[DMR Network]") {
                                                inGeneralSection = true;
                                                } else {
                                                inGeneralSection = false;
                                                }
                                                }
                                                if (inGeneralSection && line.startsWith("Type=")) {
                                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                ui->lineEdit_Type->setText(id);
                                                break;  // Ya lo encontramos, salimos del bucle
                                                }
                                                }

             //RemoteAddress
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("RemoteAddress=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_RemoteAddress->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //RemotePort
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("RemotePort=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_RemotePort->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Password
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Password=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Password->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Jitter
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Jitter=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Jitter->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Slot1
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Slot1=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Slot1->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }


             //Slot2
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Slot2=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Slot2->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }


             //Options
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Options=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Options->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }
    // **************************************************************************************
    // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
       file.close();
       // Presenta el fichero MMDVMhost
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           QMessageBox::information(nullptr, "info", file.errorString());
           return;
       }
   // ***************************************************************************************

       // [DMR] Enable 1 ó 0
       bool inDMRSection = false;
       QString linea;
       while (!in.atEnd()) {
       linea = in.readLine().trimmed();
       // Detectar comienzo o fin de sección
       if (linea.startsWith('[')) {
       inDMRSection = (linea == "[DMR]");
       }
       // Cuando estamos en [DMR] y encontramos Enable=
       if (inDMRSection && linea.startsWith("Enable=")) {
       QString value = linea.section('=', 1).trimmed(); // Extrae el valor
       if (value == "1") {
       // Mostrar botón para desactivar, ocultar botón de activar
       ui->pushButton_DmrEnable->setVisible(false);
       ui->pushButton_DmrDisable->setVisible(true);
       }
       else if (value == "0") {
       // Mostrar botón para activar, ocultar botón de desactivar
       ui->pushButton_DmrEnable->setVisible(true);
       ui->pushButton_DmrDisable->setVisible(false);
       }
       break; // Ya encontramos la línea, salimos
       }
}

       // [System Fusion] Enable 1 ó 0
       bool inFUSIONSection = false;
       QString lineaa;
       while (!in.atEnd()) {
       lineaa = in.readLine().trimmed();

       // Detectar comienzo o fin de sección
       if (lineaa.startsWith('[')) {
       inFUSIONSection = (lineaa == "[System Fusion]");
       }

       // Cuando estamos en [DMR] y encontramos Enable=
       if (inFUSIONSection && lineaa.startsWith("Enable=")) {
       QString value = lineaa.section('=', 1).trimmed(); // Extrae el valor

       if (value == "1") {
       // Mostrar botón para desactivar, ocultar botón de activar
       ui->pushButton_FusionEnable->setVisible(false);
       ui->pushButton_FusionDisable->setVisible(true);
       }
       else if (value == "0") {
       // Mostrar botón para activar, ocultar botón de desactivar
       ui->pushButton_FusionEnable->setVisible(true);
       ui->pushButton_FusionDisable->setVisible(false);
       }

       break; // Ya encontramos la línea, salimos
       }
}

       // **************************************************************************************
       // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
          file.close();
          // Presenta el fichero MMDVMhost
          if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
              QMessageBox::information(nullptr, "info", file.errorString());
              return;
          }
      // ***************************************************************************************




       // [CW Id] Enable 1 ó 0
       bool inCWSection = false;
       QString lineaac;
       while (!in.atEnd()) {
       lineaac = in.readLine().trimmed();

       // Detectar comienzo o fin de sección
       if (lineaac.startsWith('[')) {
       inCWSection = (lineaac == "[CW Id]");
       }

       // Cuando estamos en [DMR] y encontramos Enable=
       if (inCWSection && lineaac.startsWith("Enable=")) {
       QString value = lineaac.section('=', 1).trimmed(); // Extrae el valor

       if (value == "1") {
       // Mostrar botón para desactivar, ocultar botón de activar
       ui->pushButton_CwEnable->setVisible(false);
       ui->pushButton_CwDisable->setVisible(true);
       }
       else if (value == "0") {
       // Mostrar botón para activar, ocultar botón de desactivar
       ui->pushButton_CwEnable->setVisible(true);
       ui->pushButton_CwDisable->setVisible(false);
       }

       break; // Ya encontramos la línea, salimos
       }
}
            // **************************************************************************************
            // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
               file.close();
               // Presenta el fichero MMDVMhost
               if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                   QMessageBox::information(nullptr, "info", file.errorString());
                   return;
               }
           // ***************************************************************************************
            //Type OLED
            while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith('[')) {
            if (line == "[OLED]") {
            inGeneralSection = true;
            } else {
            inGeneralSection = false;
            }
            }
            if (inGeneralSection && line.startsWith("Type=")) {
            QString type = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TypeOled->setText(type);
            break;  // Ya lo encontramos, salimos del bucle
            }
            }

            // **************************************************************************************
            // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
               file.close();
               // Presenta el fichero MMDVMhost
               if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                   QMessageBox::information(nullptr, "info", file.errorString());
                   return;
               }
           // ***************************************************************************************

            // ScreenLayout
            while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith('[')) {
            if (line == "[Nextion]") {
            inGeneralSection = true;
            } else {
            inGeneralSection = false;
            }
            }
            if (inGeneralSection && line.startsWith("ScreenLayout=")) {
            QString type = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Layout->setText(type);
            break;  // Ya lo encontramos, salimos del bucle
            }
            }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_id_editingFinished()
{
    QString nuevoId = ui->lineEdit_id->text();
    nuevoId = nuevoId.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Id=" + nuevoId;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Id=")) {
            lineas << "Id=" + nuevoId;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }

    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_id->setText(nuevoId);
    ui->lineEdit_id->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_callsign_editingFinished()
{
    QString nuevoCallsign = ui->lineEdit_callsign->text();
    nuevoCallsign = nuevoCallsign.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Callsign=" + nuevoCallsign;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Callsign=")) {
            lineas << "Callsign=" + nuevoCallsign;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_callsign->setText(nuevoCallsign);
    ui->lineEdit_callsign->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_clicked()
{
    //system("cd /home/pi/A108/qt; ./qt_new_menu_alto &");
    close();
}

void MainWindow::on_comboBox_currentIndexChanged(int /*index*/)
{

            QFile file1(modo);
            if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
                return;
            }
            QTextStream in1(&file1);
            QString line1;
            int lineNumber = 0;
            int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
            bool inGeneral = false;

            while (!in1.atEnd()) {
                line1 = in1.readLine();
                lineNumber++;
                if (line1.trimmed() == "[Nextion]") {
                    inGeneral = true;
                } else if (line1.trimmed().startsWith('[') && inGeneral) {
                    // Salimos de la sección [General]
                    inGeneral = false;
                }
                if (inGeneral && line1.trimmed().startsWith("Port=")) {
                    numero_linea = lineNumber;
                    break;  // Ya lo encontramos, no hace falta seguir
                }
            }
            file1.close();

            //extrae número de item del comboBox
            QString sistema;

            if (ui->comboBox->currentIndex() == 1) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=modem' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }

            if (ui->comboBox->currentIndex() == 2) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/ttyUSB0' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }

            if (ui->comboBox->currentIndex() == 3) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/ttyUSB1' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }

            if (ui->comboBox->currentIndex() == 4) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/rfcomm1' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }

            if (ui->comboBox->currentIndex() == 5) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/rfcomm2' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }

            if (ui->comboBox->currentIndex() == 6) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/virtual1' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }
            if (ui->comboBox->currentIndex() == 7) {
                QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
                QString sed = "sed -i '" + numLineaStr + "c Port=/dev/virtual2' ";
                QString port = sed + modo;
                ui->lineEdit_puente->setText(port);
                system(ui->lineEdit_puente->text().toStdString().c_str());
            }



    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Nextion]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Port=")) {
            QString portnextion = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_PorNextion->setText(portnextion);
            ui->lineEdit_PorNextion->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

}

void MainWindow::on_lineEdit_Timeout_editingFinished()
{
    QString nuevoTimeout = ui->lineEdit_Timeout->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Timeout=" + nuevoTimeout;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Timeout=")) {
            lineas << "Timeout=" + nuevoTimeout;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Timeout->setText(nuevoTimeout);
    ui->lineEdit_Timeout->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Display_editingFinished()
{
    QString nuevoDisplay = ui->lineEdit_Display->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Display=" + nuevoDisplay;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Display=")) {
            lineas << "Display=" + nuevoDisplay;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Display->setText(nuevoDisplay);
    ui->lineEdit_Display->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Duplex_editingFinished()
{
    QString nuevoDuplex = ui->lineEdit_Duplex->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Duplex=" + nuevoDuplex;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Duplex=")) {
            lineas << "Duplex=" + nuevoDuplex;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Duplex->setText(nuevoDuplex);
    ui->lineEdit_Duplex->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_PorNextion_editingFinished()
{
    QString nuevoPortNextion = ui->lineEdit_PorNextion->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Port=" + nuevoPortNextion;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Nextion]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Port=")) {
            lineas << "Port=" + nuevoPortNextion;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_PorNextion->setText(nuevoPortNextion);
    ui->lineEdit_PorNextion->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RFModeHang_editingFinished()
{
    QString nuevoRFModeHang = ui->lineEdit_RFModeHang->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RFModeHang=" + nuevoRFModeHang;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("RFModeHang=")) {
            lineas << "RFModeHang=" + nuevoRFModeHang;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RFModeHang->setText(nuevoRFModeHang);
    ui->lineEdit_RFModeHang->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_geany_clicked()
{
    system("geany /home/pi/MMDVMHost/MMDVM.ini &");
}

void MainWindow::on_radioButton_DMR_pressed()
{
    QString nuevodmr = "1";
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Enable=" + nuevodmr;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Enable=")) {
            lineas << "Enable=" + nuevodmr;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
//    ui->lineEdit_RFModeHang->setText(nuevodmr);
//    ui->lineEdit_RFModeHang->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");


    QString nuevodstar = "0";
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file1.errorString());
        return;
    }
    QStringList lineas1;
    QTextStream in1(&file1);
    QString linea1;
    bool DStar = false;
    bool dstarenable = false;
    while (!in1.atEnd()) {
        linea1 = in1.readLine();
        // Verifica si se cambia de sección
        if (linea1.trimmed().startsWith('[')) {
            if (DStar && !dstarenable) {
                lineas1 << "Enable=" + nuevodstar;
                dstarenable = true;
            }
            DStar = (linea1.trimmed() == "[D-Star]");
        }
        if (DStar && linea1.trimmed().startsWith("Enable=")) {
            lineas1 << "Enable=" + nuevodstar;
            dstarenable = true;
        } else {
            lineas1 << linea1;
        }
    }
    file1.close();
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file1.errorString());
        return;
    }
    QTextStream out1(&file1);
    for (const QString &l : lineas1) {
        out1 << l << "\n";
    }
    file1.close();

    ui->radioButton_DMR->setChecked(true);
}

void MainWindow::on_comboBox_Display_currentIndexChanged(int /*index*/)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[General]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("Display=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBo
    QString sistema;
    if (ui->comboBox_Display->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Display=Nextion' ";
        QString Display = sed + modo;
        ui->lineEdit_puente->setText(Display);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox_Display->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Display=OLED' ";
        QString Display = sed + modo;
        ui->lineEdit_puente->setText(Display);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "General", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Display
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Display=")) {
            QString display = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TipoDisplay->setText(display);
            ui->lineEdit_Display->setText(display);
            ui->lineEdit_Display->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
}

void MainWindow::on_lineEdit_TipoDisplay_editingFinished()
{
    QString nuevoDisplay = ui->lineEdit_TipoDisplay->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Display=" + nuevoDisplay;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Display=")) {
            lineas << "Display=" + nuevoDisplay;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Display->setText(nuevoDisplay);
    ui->lineEdit_TipoDisplay->setText(nuevoDisplay);
    ui->lineEdit_TipoDisplay->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}
























void MainWindow::on_lineEdit_RXF_editingFinished()
{
    QString nuevoRFX = ui->lineEdit_RXF->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RXFrequency=" + nuevoRFX;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RXFrequency=")) {
            lineas << "RXFrequency=" + nuevoRFX;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RXF->setText(nuevoRFX);
    ui->lineEdit_RXF->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXF_editingFinished()
{
    QString nuevoTFX = ui->lineEdit_TXF->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "TXFrequency=" + nuevoTFX;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("TXFrequency=")) {
            lineas << "TXFrequency=" + nuevoTFX;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXF->setText(nuevoTFX);
    ui->lineEdit_TXF->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
}

void MainWindow::on_lineEdit_RemoteAddress_editingFinished()
{
    QString nuevoAddress = ui->lineEdit_RemoteAddress->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RemoteAddress=" + nuevoAddress;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RemoteAddress=")) {
            lineas << "RemoteAddress=" + nuevoAddress;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RemoteAddress->setText(nuevoAddress);
    ui->lineEdit_RemoteAddress->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}


void MainWindow::on_lineEdit_UARTPort_editingFinished()
{
    QString nuevoUARTPort = ui->lineEdit_UARTPort->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "UARTPort=" + nuevoUARTPort;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("UARTPort=")) {
            lineas << "UARTPort=" + nuevoUARTPort;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_UARTPort->setText(nuevoUARTPort);
    ui->lineEdit_UARTPort->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_comboBox_4_currentIndexChanged(int /*index*/)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[OLED]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("Type=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBox
    QString sistema;

    if (ui->comboBox_4->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Type=3' ";
        QString port = sed + modo;
        ui->lineEdit_puente->setText(port);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }


    if (ui->comboBox_4->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Type=6' ";
        QString port = sed + modo;
        ui->lineEdit_puente->setText(port);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }


    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[OLED]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Type=")) {
            QString portnextion = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TypeOled->setText(portnextion);
            ui->lineEdit_TypeOled->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

}

void MainWindow::on_lineEdit_TypeOled_editingFinished()
{
    QString nuevoTypeOled = ui->lineEdit_TypeOled->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Type=" + nuevoTypeOled;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[OLED]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Type=")) {
            lineas << "Type=" + nuevoTypeOled;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TypeOled->setText(nuevoTypeOled);
    ui->lineEdit_TypeOled->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RemotePort_editingFinished()
{
    QString nuevoRemotePort = ui->lineEdit_RemotePort->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RemotePort=" + nuevoRemotePort;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RemotePort=")) {
            lineas << "RemotePort=" + nuevoRemotePort;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RemotePort->setText(nuevoRemotePort);
    ui->lineEdit_RemotePort->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Type_editingFinished()
{
    QString nuevoTypet = ui->lineEdit_Type->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Type=" + nuevoTypet;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Type=")) {
            lineas << "Type=" + nuevoTypet;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Type->setText(nuevoTypet);
    ui->lineEdit_Type->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Options_editingFinished()
{
    QString nuevoOptions = ui->lineEdit_Options->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Options=" + nuevoOptions;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Options=")) {
            lineas << "Options=" + nuevoOptions;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Options->setText(nuevoOptions);
    ui->lineEdit_Options->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Password_editingFinished()
{
    QString nuevoPassword = ui->lineEdit_Password->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Password=" + nuevoPassword;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Password=")) {
            lineas << "Password=" + nuevoPassword;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Password->setText(nuevoPassword);
    ui->lineEdit_Password->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Slot1_editingFinished()
{
    QString nuevoSlot1 = ui->lineEdit_Slot1->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Slot1=" + nuevoSlot1;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Slot1=")) {
            lineas << "Slot1=" + nuevoSlot1;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Slot1->setText(nuevoSlot1);
    ui->lineEdit_Slot1->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Slot2_editingFinished()
{
    QString nuevoSlot2 = ui->lineEdit_Slot2->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Slot2=" + nuevoSlot2;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Slot2=")) {
            lineas << "Slot2=" + nuevoSlot2;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Slot2->setText(nuevoSlot2);
    ui->lineEdit_Slot2->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Jitter_editingFinished()
{
    QString nuevoJitter = ui->lineEdit_Jitter->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Jitter=" + nuevoJitter;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR Network]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Jitter=")) {
            lineas << "Jitter=" + nuevoJitter;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Jitter->setText(nuevoJitter);
    ui->lineEdit_Jitter->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXInvert_2_editingFinished()
{
    QString nuevoModule = ui->lineEdit_TXInvert_2->text();
    nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Module=" + nuevoModule;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[D-Star]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Module=")) {
            lineas << "Module=" + nuevoModule;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXInvert_2->setText(nuevoModule);
    ui->lineEdit_TXInvert_2->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Latitude_editingFinished()
{
    QString nuevoLatitud = ui->lineEdit_Latitude->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Latitude=" + nuevoLatitud;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Latitude=")) {
            lineas << "Latitude=" + nuevoLatitud;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Latitude->setText(nuevoLatitud);
    ui->lineEdit_Latitude->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Longitude_editingFinished()
{
    QString nuevoLongitude = ui->lineEdit_Longitude->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Longitude=" + nuevoLongitude;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Longitude=")) {
            lineas << "Longitude=" + nuevoLongitude;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Longitude->setText(nuevoLongitude);
    ui->lineEdit_Longitude->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Location_editingFinished()
{
    QString nuevoLocation = ui->lineEdit_Location->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Location=" + nuevoLocation;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Location=")) {
            lineas << "Location=" + nuevoLocation;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Location->setText(nuevoLocation);
    ui->lineEdit_Location->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_URL_editingFinished()
{
    QString nuevoURL = ui->lineEdit_URL->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "URL=" + nuevoURL;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Info]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("URL=")) {
            lineas << "URL=" + nuevoURL;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_URL->setText(nuevoURL);
    ui->lineEdit_URL->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_CW_Id_editingFinished()
{
    QString nuevoCW = ui->lineEdit_CW_Id->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Enable=" + nuevoCW;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[CW Id]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Enable=")) {
            lineas << "Enable=" + nuevoCW;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_CW_Id->setText(nuevoCW);
    ui->lineEdit_CW_Id->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXInvert_editingFinished()
{
    QString nuevoTxinvert = ui->lineEdit_TXInvert->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "TXInvert=" + nuevoTxinvert;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("TXInvert=")) {
            lineas << "TXInvert=" + nuevoTxinvert;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXInvert->setText(nuevoTxinvert);
    ui->lineEdit_TXInvert->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RXInvert_editingFinished()
{
    QString nuevoRxinvert = ui->lineEdit_RXInvert->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RXInvert=" + nuevoRxinvert;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RXInvert=")) {
            lineas << "RXInvert=" + nuevoRxinvert;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RXInvert->setText(nuevoRxinvert);
    ui->lineEdit_RXInvert->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RXOffset_editingFinished()
{
    QString nuevoRXOffset = ui->lineEdit_RXOffset->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RXOffset=" + nuevoRXOffset;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RXOffset=")) {
            lineas << "RXOffset=" + nuevoRXOffset;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RXOffset->setText(nuevoRXOffset);
    ui->lineEdit_RXOffset->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXOffset_editingFinished()
{
    QString nuevoTXOffset = ui->lineEdit_TXOffset->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "TXOffset=" + nuevoTXOffset;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("TXOffset=")) {
            lineas << "TXOffset=" + nuevoTXOffset;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXOffset->setText(nuevoTXOffset);
    ui->lineEdit_TXOffset->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RXLevel_editingFinished()
{
    QString nuevoRXLevel = ui->lineEdit_RXLevel->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RXLevel=" + nuevoRXLevel;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RXLevel=")) {
            lineas << "RXLevel=" + nuevoRXLevel;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RXLevel->setText(nuevoRXLevel);
    ui->lineEdit_RXLevel->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXLevel_editingFinished()
{
    QString nuevoTXLevel = ui->lineEdit_TXLevel->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "TXLevel=" + nuevoTXLevel;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("TXLevel=")) {
            lineas << "TXLevel=" + nuevoTXLevel;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXLevel->setText(nuevoTXLevel);
    ui->lineEdit_TXLevel->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_RXDCOffset_editingFinished()
{
    QString nuevoRXDCOffset = ui->lineEdit_RXDCOffset->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RXDCOffset=" + nuevoRXDCOffset;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("RXDCOffset=")) {
            lineas << "RXDCOffset=" + nuevoRXDCOffset;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RXDCOffset->setText(nuevoRXDCOffset);
    ui->lineEdit_RXDCOffset->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_TXDCOffset_editingFinished()
{
    QString nuevoTXDCOffset = ui->lineEdit_TXDCOffset->text();
    //nuevoModule = nuevoModule.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "TXDCOffset=" + nuevoTXDCOffset;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Modem]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("TXDCOffset=")) {
            lineas << "TXDCOffset=" + nuevoTXDCOffset;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_TXDCOffset->setText(nuevoTXDCOffset);
    ui->lineEdit_TXDCOffset->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_comboBox_Layout_currentIndexChanged(int index)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[Nextion]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("ScreenLayout=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBo
    QString sistema;
    if (ui->comboBox_Layout->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c ScreenLayout=2' ";
        QString Layout = sed + modo;
        ui->lineEdit_puente->setText(Layout);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox_Layout->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c ScreenLayout=3' ";
        QString Display = sed + modo;
        ui->lineEdit_puente->setText(Display);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Nextion", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    // layout
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Nextion]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("ScreenLayout=")) {
            QString layout = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Layout->setText(layout);
            ui->lineEdit_Layout->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
}



void MainWindow::on_lineEdit_Layout_editingFinished()
{
    QString nuevoLayout = ui->lineEdit_Layout->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "ScreenLayout=" + nuevoLayout;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Nextion]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("ScreenLayout=")) {
            lineas << "ScreenLayout=" + nuevoLayout;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Layout->setText(nuevoLayout);
    ui->lineEdit_Layout->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_comboBox_Reflector_currentIndexChanged(int index)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "RemodeAddress=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[DMR Network]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("RemoteAddress=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBox_Reflector
    QString sistema;
    if (ui->comboBox_Reflector->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c RemoteAddress=212.237.3.141' ";
        QString address = sed + modo;
        ui->lineEdit_puente->setText(address);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox_Reflector->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c RemoteAddress=eamaster04.xreflector.es' ";
        QString address = sed + modo;
        ui->lineEdit_puente->setText(address);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "DMR Network", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    // layout
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[DMR Network]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("RemoteAddress=")) {
            QString address = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_RemoteAddress->setText(address);
            ui->lineEdit_RemoteAddress->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
}

void MainWindow::on_lineEdit_Rotate_editingFinished()
{
    QString nuevoRotate = ui->lineEdit_Rotate->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Rotate=" + nuevoRotate;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[OLED]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Rotate=")) {
            lineas << "Rotate=" + nuevoRotate;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Rotate->setText(nuevoRotate);
    ui->lineEdit_Rotate->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Rotate=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[OLED]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("Rotate=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBox_Reflector
    QString sistema;
    if (ui->comboBox_5->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Rotate=0' ";
        QString rotate = sed + modo;
        ui->lineEdit_puente->setText(rotate);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox_5->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Rotate=1' ";
        QString rotate = sed + modo;
        ui->lineEdit_puente->setText(rotate);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "OLED", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    // layout
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[OLED]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Rotate=")) {
            QString address = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Rotate->setText(address);
            ui->lineEdit_Rotate->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
}

void MainWindow::on_lineEdit_DisplayLevel_editingFinished()
{
    QString nuevodisplaylevel = ui->lineEdit_DisplayLevel->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "DisplayLevel=" + nuevodisplaylevel;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Log]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("DisplayLevel=")) {
            lineas << "DisplayLevel=" + nuevodisplaylevel;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_DisplayLevel->setText(nuevodisplaylevel);
    ui->lineEdit_DisplayLevel->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_FileLevel_editingFinished()
{
    QString nuevofilelevel = ui->lineEdit_FileLevel->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "FileLevel=" + nuevofilelevel;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Log]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("FileLevel=")) {
            lineas << "FileLevel=" + nuevofilelevel;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_FileLevel->setText(nuevofilelevel);
    ui->lineEdit_FileLevel->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}
void MainWindow::on_pushButton_DmrEnable_clicked()
{


    ui->pushButton_DmrEnable->setVisible(false);
    ui->pushButton_DmrDisable->setVisible(true);

    QFile file(modo);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QStringList lines;
        QTextStream in(&file);
        bool inDMRSection = false;

        while (!in.atEnd()) {
            QString line = in.readLine();

            if (line.trimmed() == "[DMR]") {
                inDMRSection = true;
            } else if (line.startsWith("[") && line.endsWith("]")) {
                inDMRSection = false;
            }

            if (inDMRSection && line.startsWith("Enable=")) {
                line = "Enable=1";
            }

            lines << line;
        }
        file.close();

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            return;

        QTextStream out(&file);
        for (const QString &l : lines) {
            out << l << "\n";
        }
        file.close();
}

void MainWindow::on_pushButton_DmrDisable_clicked()
{
    ui->pushButton_DmrEnable->setVisible(true);
    ui->pushButton_DmrDisable->setVisible(false);

    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);
    bool inDMRSection = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed() == "[DMR]") {
            inDMRSection = true;
        } else if (line.startsWith("[") && line.endsWith("]")) {
            inDMRSection = false;
        }

        if (inDMRSection && line.startsWith("Enable=")) {
            line = "Enable=0";
        }

        lines << line;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QString &l : lines) {
        out << l << "\n";
    }
    file.close();
}

void MainWindow::on_pushButton_FusionEnable_clicked()
{
    ui->pushButton_FusionEnable->setVisible(false);
    ui->pushButton_FusionDisable->setVisible(true);

    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);
    bool inFUSIONSection = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed() == "[System Fusion]") {
            inFUSIONSection = true;
        } else if (line.startsWith("[") && line.endsWith("]")) {
            inFUSIONSection = false;
        }

        if (inFUSIONSection && line.startsWith("Enable=")) {
            line = "Enable=1";
        }

        lines << line;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QString &l : lines) {
        out << l << "\n";
    }
    file.close();
}
void MainWindow::on_pushButton_FusionDisable_clicked()
{
    ui->pushButton_FusionEnable->setVisible(true);
    ui->pushButton_FusionDisable->setVisible(false);

    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);
    bool inFUSIONSection = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed() == "[System Fusion]") {
            inFUSIONSection = true;
        } else if (line.startsWith("[") && line.endsWith("]")) {
            inFUSIONSection = false;
        }

        if (inFUSIONSection && line.startsWith("Enable=")) {
            line = "Enable=0";
        }

        lines << line;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QString &l : lines) {
        out << l << "\n";
    }
    file.close();
}

void MainWindow::on_pushButton_CwEnable_clicked()
{
    ui->pushButton_CwEnable->setVisible(false);
    ui->pushButton_CwDisable->setVisible(true);

    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);
    bool inCwection = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed() == "[CW Id]") {
            inCwection = true;
        } else if (line.startsWith("[") && line.endsWith("]")) {
            inCwection = false;
        }

        if (inCwection && line.startsWith("Enable=")) {
            line = "Enable=1";
        }

        lines << line;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QString &l : lines) {
        out << l << "\n";
    }
    file.close();
}

void MainWindow::on_pushButton_CwDisable_clicked()
{
    ui->pushButton_CwEnable->setVisible(true);
    ui->pushButton_CwDisable->setVisible(false);

    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);
    bool inCwection = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed() == "[CW Id]") {
            inCwection = true;
        } else if (line.startsWith("[") && line.endsWith("]")) {
            inCwection = false;
        }

        if (inCwection && line.startsWith("Enable=")) {
            line = "Enable=0";
        }

        lines << line;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    for (const QString &l : lines) {
        out << l << "\n";
    }
    file.close();
}

