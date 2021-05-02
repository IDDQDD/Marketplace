#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDomDocument>
#include <vector>
#include <QWidget>
#include "information.h"
#include "xmlbuilder.h"



class Marketplace : public QWidget
{
     Q_OBJECT
public:
    Marketplace(QWidget* parent = nullptr);

signals:

    void ConnectionStatus(bool status);
    void SendXmlFile(QString);

public slots:

    void CreateConnection(const QString& name,const QString& password,
                          const QString& host);
    void ShopButtonClicked();

private:
    //replaced by unordered_map
    using OFFERS = std::map<Shop, std::vector<Item>>;

private:
    void CreateDatabase();
    void CreateStoresTable();
    void addStore(const Shop shop);

    void CreateOffresTable();
    void addOffer(const Item item);




    void CreateXmlFile();
    OFFERS GetValuesFromQuery();
    QString ParseDescription(QString desc);
    void FillXml(OFFERS stores_of);
//    void addValues(QString open, QString close);

private:
    QSqlDatabase db;
    QSqlQuery query;
    XMLBuilder xml;


};

#endif // MARKETPLACE_H
