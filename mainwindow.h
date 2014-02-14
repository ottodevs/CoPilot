#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <iostream>

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QtDebug>
#include <QIODevice>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void FillTree(const QDomNode& dom, QStandardItemModel* model);
//	QListWidget *listWidget;
	void SetModel(QStandardItemModel *mod);
private:
	Ui::MainWindow *ui;
	int nRow;	//just indexing
};

#endif // MAINWINDOW_H
