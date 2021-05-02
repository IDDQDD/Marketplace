#ifndef XMLCREATOR_H
#define XMLCREATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QSqlQueryModel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QGridLayout>
#include "marketplace.h"

class XMLCreator : public QMainWindow
{
    Q_OBJECT
public:
    explicit XMLCreator(const Marketplace* db, QWidget *parent = nullptr);

signals:
    void Authentification(const QString& name, const QString& pass,
                          const QString& host);
    void ButtonSignal();

public slots:
    void GetClicked();
    void GetStatus(bool status);
    void GetXmlFile(QString xml);
    void Quit();

private:
    void SetCenter();
    void CreateAuthWindow();
    void CheckConnection();
    void CreateTableView();

private:
    QWidget* wgt;

    QPushButton* pcmdOK;
    QPushButton* pcmdCancel;
    QPushButton* pcmdShops;

    QLineEdit*  pnameEdit;
    QLineEdit* ppassEdit;
    QLineEdit* phostEdit;


    const Marketplace* pdb;

    QPlainTextEdit* text;
    QTableView view;
    QSqlQueryModel model;


    QLabel* pnameLbl;
    QLabel* ppassLbl;
    QLabel* phostLbl;

    QGridLayout* p_grid;
    QHBoxLayout* phbxH;
    QVBoxLayout* pvbxl;
};

#endif // XMLCREATOR_H
