#ifndef INFORMATION_H
#define INFORMATION_H
#include <QString>
struct Shop
{
//    replaced shop_id by qint32
    Shop() = default;
    explicit Shop(QString shop_name_, QString url_, QString open_, QString close_):
             shop_name(shop_name_), url(url_), open(open_), close(close_){};
    int shop_id;
    QString shop_name;
    QString url;
    QString open;
    QString close;

};

struct Item
{
    Item() = default;
    explicit Item(QString item_id_, int shop_id_, QString name_, QString desc_, double price_):
        item_id(item_id_),shop_id(shop_id_), name(name_), desc(desc_), price(price_){};
    QString item_id;
    int shop_id;
    QString name;
    QString desc;
    double price;
};

#endif // INFORMATION_H
