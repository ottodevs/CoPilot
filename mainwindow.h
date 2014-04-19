#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <stdio.h>
//#include <iostream>

//#include <QObject>
#include <QMainWindow>
//#include <QMessageBox>
//#include <QHBoxLayout>
//#include <QListWidget>
//#include <QtXml/QDomDocument>
//#include <QFile>
//#include <QtDebug>
//#include <QIODevice>
//#include <QStandardItemModel>
#include <QString>

//namespace Ui {
//class MainWindow;
//}
class DomModel;
class QMenu;
class QTreeView;

class MainWindow : public QMainWindow {	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	//~MainWindow();

//	void FillTree(const QDomNode& dom, QStandardItemModel* model);
//	QListWidget *listWidget;
//	void SetModel(QStandardItemModel *mod);
public slots:
	void openFile(void);
private:
	//Ui::MainWindow *ui;
	DomModel *model;
	QMenu *fileMenu;
	QString xmlPath;
	QTreeView *view;
//	int nRow;	//just indexing
};

#endif // MAINWINDOW_H
