#include "xmlcreator.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>



XMLCreator::XMLCreator(const Marketplace* db, QWidget *parent) : QMainWindow(parent), wgt(new QWidget(this)),
                                          w(new QWidget),
                                          pcmdOK(new QPushButton("OK")),
                                          pcmdCancel(new QPushButton("Cancel")),
                                          pcmdShops (new QPushButton("Open Shops")),
                                          pnameEdit(new QLineEdit), ppassEdit(new QLineEdit),
                                          pdb(db), text(new QPlainTextEdit),
                                          pnameLbl(new QLabel("User Name:")),
                                          ppassLbl(new QLabel("Password:")),
                                          p_grid(new QGridLayout), phbxH(new QHBoxLayout),
                                          pvbxl(new QVBoxLayout)


{
  connect(pcmdCancel, SIGNAL(clicked()), this, SLOT(Quit()));
  CreateAuthWindow();
  SetCenter();
  CheckConnection();
}


void XMLCreator::CreateAuthWindow()
{


        ppassEdit->setEchoMode(QLineEdit::EchoMode::Password);

        p_grid->setContentsMargins(5, 5, 5, 5);
        p_grid->addWidget(pnameLbl, 0, 0);
        p_grid->addWidget(ppassLbl, 1, 0);
        p_grid->addWidget(pnameEdit, 0, 1);
        p_grid->addWidget(ppassEdit, 1, 1);

        phbxH->addWidget(pcmdOK);
        phbxH->addWidget(pcmdCancel);
        p_grid->addLayout(phbxH, 2, 1);
        wgt->setLayout(p_grid);
        setCentralWidget(wgt);
        setWindowTitle("MYSQL Server");
        resize(140,140);
}


void XMLCreator::SetCenter()
{
//  auto indx = QGuiApplication::screens().size();
  move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());
}

void XMLCreator::CheckConnection()
{
    connect(pcmdOK,  SIGNAL(clicked()), this, SLOT(GetClicked()));
    connect(this,    SIGNAL(Authentification(QString,QString)), pdb,
                     SLOT(CreateConnection(QString,QString)));
}


void XMLCreator::GetClicked()
{
    if(pcmdOK == sender())
        emit Authentification(pnameEdit->text(), ppassEdit->text());

    if(pcmdShops == sender())
        emit ButtonSignal();
}


void XMLCreator::GetStatus(bool status)
{
    if(status)
    {
       model.setQuery("select stores.shop_id, stores.url, stores.shop_name, offers.item_id,"
                      " offers.name, offers.description, offers.price,"
                      " stores.open, stores.close"
                      " from stores JOIN offers ON"
                      " stores.shop_id = offers.shop_id");
       if(model.lastError().isValid())
       {
           QMessageBox::information(this,"Error",
                        model.lastError().text(),QMessageBox::Critical);
       }

       CreateTableView();
    }
}


  void XMLCreator::CreateTableView()
  {
      connect(pcmdShops, SIGNAL(clicked()), this, SLOT(GetClicked()));
      connect(this, SIGNAL(ButtonSignal()), pdb, SLOT(ShopButtonClicked()));


      w = new QWidget;
      pvbxl->setSpacing(5);
      pvbxl->addWidget(&view);
      pvbxl->addWidget(pcmdShops);

      view.setModel(&model);
      w->setLayout(pvbxl);
      setCentralWidget(w);
      SetCenter();
      resize(920, 750);
  }


  void XMLCreator::GetXmlFile(QString xml)
  {
    model.setQuery("select stores.shop_id, stores.url, stores.shop_name, offers.item_id,"
                  " offers.name, offers.description, offers.price,"
                  " stores.open, stores.close"
                  " from stores JOIN offers ON"
                  " stores.shop_id = offers.shop_id where stores.open < NOW()"
                  " AND stores.close > NOW() OR stores.close = '00:00:00'"
                  " ORDER BY offers.shop_id, offers.name");

    if(model.lastError().isValid())
    {
        QMessageBox::information(QApplication::activeWindow(),"Error",
                    model.lastError().text(),QMessageBox::Ok);
    }

    view.update();
    text->setPlainText(xml);
    text->resize(450, 1000);
    text->show();
  }


void XMLCreator::Quit()
{
   QApplication::quit();
}
