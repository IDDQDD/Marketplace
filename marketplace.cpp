#include "marketplace.h"
#include <iostream>
#include <QRegularExpression>
#include <QString>
#include <QPair>
#include <QSqlError>
#include <QSqlRecord>
#include <QMetaType>
#include <QFile>
#include <QApplication>
#include <QMessageBox>


Marketplace::Marketplace(QWidget* parent): QWidget(parent),
                                           query(db = QSqlDatabase::addDatabase(("QMYSQL")))
{

//CreateXmlFile();
}

 void Marketplace::CreateConnection(const QString& name, const QString& password,
                                    const QString& host)
{

        connect(this, SIGNAL(ConnectionStatus(bool)), sender(), SLOT(GetStatus(bool)));
         db.setUserName(name);
         db.setHostName(host);
         db.setPassword(password);
         db.setDatabaseName("mysql");
         if(!db.open())
         {
            QMessageBox::warning(QApplication::activeWindow(),"Error",
                         db.lastError().text(),QMessageBox::Ok);
         } else {

             query.exec("CREATE DATABASE IF NOT EXISTS marketplace");
             query.exec("USE marketplace");
             if(db.tables().empty())CreateDatabase();

             emit ConnectionStatus(true);

}

}

 void Marketplace::CreateDatabase()
 {

     CreateStoresTable();
     CreateOffresTable();

 }


 void Marketplace::addStore(Shop shop)
 {
     query.prepare("INSERT INTO stores (shop_id, shop_name, url, open, close)"
                   "VALUES(?, ?, ?, ?, ?)");

     query.addBindValue(0);
     query.addBindValue(shop.shop_name);
     query.addBindValue(shop.url);
     query.addBindValue(shop.open + ":00");
     query.addBindValue(shop.close + ":00");

     if(!query.exec()){
         QMessageBox::information(QApplication::activeWindow(),"Error",
                                                query.lastError().text(),QMessageBox::Ok);
     }
 }


 void Marketplace::CreateStoresTable()
 {

     query.prepare("CREATE TABLE IF NOT EXISTS stores ("
                   "shop_id INTEGER NOT NULL AUTO_INCREMENT,"
                   "shop_name VARCHAR(30),"
                   "url  VARCHAR(30),"
                   "open TIME,"
                   "close TIME,"
                   "CONSTRAINT pk_stores PRIMARY KEY(shop_id) )");
     if(!query.exec())
        {
          QMessageBox::information(QApplication::activeWindow(),"Error",
                    query.lastError().text(),QMessageBox::Ok);
        }

     addStore(Shop("Dviglo",    "www.dviglo.by",         "03:00", "20:00"));
     addStore(Shop("Vlap-auto", "www.vlap.by",           "00:00",  "17:00"));
     addStore(Shop("Grach",     "www.grach.by",          "01:00",  "12:00"));
     addStore(Shop("Vior",      "www.vior.by",           "00:00",  "00:00"));
     addStore(Shop("Shate-m",   "www.shatem.by",         "16:00",  "22:00"));
     addStore(Shop("Armtek",    "www.armtek.by",         "01:00",  "19:00"));
     addStore(Shop("Forward",   "www.forward-motors.by", "09:00",  "18:00"));
     addStore(Shop("L-autp",    "www.l-auto.by",         "04:30",  "5:30"));
     addStore(Shop("Motexauto", "www.motex.by",          "15:00",  "16:30"));
     addStore(Shop("Sviat",     "www.sviat.by",          "02:00",  "17:00"));


 }

void Marketplace::CreateOffresTable()
{
    query.prepare("CREATE TABLE IF NOT EXISTS offers ("
                  "item_id VARCHAR(20),"
                  "shop_id INTEGER,"
                  "name VARCHAR(30),"
                  "description VARCHAR(100),"
                  "price DOUBLE,"
                  "CONSTRAINT pk_offers  PRIMARY KEY (shop_id, item_id),"
                  "CONSTRAINT fk_shop_id FOREIGN KEY (shop_id)"
                  "REFERENCES stores (shop_id) )");

    if(!query.exec())
    {
        QMessageBox::information(QApplication::activeWindow(),"Error",
                  query.lastError().text(),QMessageBox::Ok);
    }
    addOffer(Item("47670RPW",             3, "Narva h7",
             "<p>New generation car lamps</p>",               23.97));
    addOffer(Item("64193NBIHCB",          3, "Osram Night Breaker h4",
             "<p>New from OSRAM</p>",                         40.67));
    addOffer(Item("62531/5",              9, "Wolf Vital Tech 5w-40 5L",
             "<p>Semi-synthetic engine oil</p>",               60.20));
    addOffer(Item("64210",                3, "Osram h4",
             "<p>Incandescent lamp with h4 socket</p>",        9.80));
    addOffer(Item("GX3309",               1, "Mobil 3309 1L",
             "<p>Automatic transmission oil</p>",              24.50));
    addOffer(Item("GX3309",               9, "Mobil 3309 1L",
             "<p>Automatic transmission oil</p>",              23.99));
    addOffer(Item("47670RPW",             8, "Narva h7",
             "<p>New generation car lamps</p>",                23.97));
    addOffer(Item("12345",                5, "Mobil FS 5w-50 4L",
             "<p>Ester based engine oil</p>",                  109.04));
    addOffer(Item("63123",                7, "Bosch Aerotwin 550/600",
             "<p>Wiper blades</p>",                            58.29));
    addOffer(Item("63120",                7, "Bosch Aerotwin 500/500",
             "<p>Wiper blades</p>",                            33.09));
    addOffer(Item("1023R",                1, "Renault RN0720 5L",
             "<p>Synthetic engine oil>",                       77.07));
    addOffer(Item("213678",               5, "Total quartz ineo ECS 5w-30 5L",
             "<p>Synthetic engine oil</p>",                    88.63));
    addOffer(Item("60102356",             1, "Fuchs Titan supersyn 5w-40 5L",
             "<p>Synthetic engine oil</p>",                    73.50));
    addOffer(Item("47670RPW",             6, "Narva h7",
             "<p>New generation car lamps</p>",                24.97));
    addOffer(Item("ENIISINT5W305L",       6, "Eni i-Sint 5w-30 5L",
             "<p>Hydrocracked engine oil</p>",                 69.91));
    addOffer(Item("LN3523",               3, "Lavr LV-40 650ML",
             "<p>Hydrocracked engine oil</p>",                 23.97));
    addOffer(Item("0364070020",           3, "Ate plastilube 70ml",
             "<p>Brake grease</p>",                            26.00));
    addOffer(Item("PFG110",               1, "TRW brake paste",
             "<p>Brake grease</p>",                            12.20));
    addOffer(Item("PFB401",               6, "TRW brake fluid 1L",
             "<p>Brake fluid, DOT 4</p>",                      26.15));
    addOffer(Item("P99G1215L",            4, "Hepu g12 1.5l",
             "<p>Monoethylene glycol based antifreeze</p>",  24.80));
    addOffer(Item("XTC5L",                5, "Comma X-tech 5w-30 5L",
             "<p>Oil with ACEA A5 / B5 approval</p>",        63.97));
    addOffer(Item("SHELLHELIXULTRAECTC3", 4, "Shell helix ultra ECT c3 4L",
             "<p>Fully synthetic motor oil;</p>",            112.50));
    addOffer(Item("6421001b",             8, "Osram h7(блистер)",
             "<p>Car lamp in blister</p>",                   11.00));

}


void Marketplace::addOffer(const Item item)
{
    query.prepare("INSERT INTO offers(item_id, shop_id, name, description, price)"
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(item.item_id);
    query.addBindValue(item.shop_id);
    query.addBindValue(item.name);
    query.addBindValue(item.desc);
    query.addBindValue(item.price);
    if(!query.exec())
    {
        QMessageBox::information(QApplication::activeWindow(),"Error",
                    query.lastError().text(),QMessageBox::Ok);
    }

}







//select offers.item_id, offers.name, offers.description  from stores JOIN offers ON stores.shop_id = offers.shop_id
//       where stores.open < NOW() AND stores.close > NOW() ORDER BY offers.name

//select stores.shop_id, stores.url, stores.name, offers.item_id, offers.name, offers.description, offers.price from stores JOIN offers ON stores.shop_id = offers.shop_id where stores.open < NOW() AND stores.close > NOW() OR stores.close = '00:00:00'  ORDER BY offers.name;
//mysql -u root -p  --xml -e 'select marketplace.stores.shop_id, marketplace.stores.url, marketplace.stores.name, marketplace.offers.item_id, marketplace.offers.name, marketplace.offers.description, marketplace.offers.price from marketplace.stores JOIN marketplace.offers ON marketplace.stores.shop_id = marketplace.offers.shop_id where marketplace.stores.open < NOW() AND marketplace.stores.close > NOW() OR marketplace.stores.close = "00:00:00"  ORDER BY  marketplace.offers.shop_id, marketplace.offers.name' > filez.xml


void Marketplace::CreateXmlFile()
{
    query.prepare("select stores.shop_id, stores.url, stores.shop_name, offers.item_id,"
                  " offers.name, offers.description, offers.price,"
                  " stores.open, stores.close"
                  " from stores JOIN offers ON"
                  " stores.shop_id = offers.shop_id where stores.open < NOW()"
                  " AND stores.close > NOW() OR stores.close = '00:00:00'"
                  " ORDER BY offers.shop_id, offers.name");


    if(!query.exec())
    {
        QMessageBox::information(QApplication::activeWindow(),"Error",
                    query.lastError().text(),QMessageBox::Ok);
    }

    FillXml(GetValuesFromQuery());
}


Marketplace::OFFERS Marketplace::GetValuesFromQuery()
{


    Shop shop;
    Item item;
    OFFERS stores_offers;

    auto GetValue = ([this](QString field){
                     auto idx = query.record().indexOf(field);
                     return query.record().value(idx);
});

    while (query.next())
        {

           shop.shop_name =  GetValue("shop_name").toString();
           shop.shop_id =    GetValue("shop_id").toInt();
           shop.url =        GetValue("url").toString();
           shop.open =       GetValue("open").toString();
           shop.close =      GetValue("close").toString();

           item.item_id =    GetValue("item_id").toString();
           item.name =       GetValue("name").toString();
           item.desc =       ParseDescription(GetValue("description").toString());
           item.price =      GetValue("price").toDouble();
           stores_offers[shop].push_back(item);
        };
    return stores_offers;
}


void Marketplace::FillXml(OFFERS stores_of)
{

    xml.begin("root");
for (auto& [shop, items] : stores_of)
{
              xml.begin("shop").
                 attr("id", QString::number(shop.shop_id)).add("name", shop.shop_name).
                 add("url", shop.url).
                 begin("working_time").add("open", shop.open).
                 add("close", shop.close).end().begin("offers");

  for(auto& item : items)
  {
                xml.begin("item").
                attr("id", item.item_id).
                add("name", item.name).
                add("description", item.desc).
                add("price", QString::number(item.price)).end();
  }
                xml.end().end();

}
    xml.end();
    xml.saveXML();
}



QString Marketplace::ParseDescription(QString desc)
{
//    stringview?
 return  !desc.isEmpty() ? desc.remove(QRegularExpression("<[^>]*>"))
                         : QString();
}


bool operator <(const std::pair<Shop, std::vector<Item>>& lhs, const std::pair<Shop, std::vector<Item>>& rhs)
{
    return lhs.first.shop_id < rhs.first.shop_id;
}

bool operator <(const Shop& lhs, const Shop& rhs)
{
    return lhs.shop_id < rhs.shop_id;
}


void Marketplace::ShopButtonClicked()
{
    connect(this,SIGNAL(SendXmlFile(QString)),
            sender(), SLOT(GetXmlFile(QString)));
    CreateXmlFile();
    emit SendXmlFile(xml.GetString());
}
