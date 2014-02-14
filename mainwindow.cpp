#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
//	listWidget(new QListWidget),
	ui(new Ui::MainWindow),
	nRow(0)
{
//	QHBoxLayout *layout = new QHBoxLayout();
//	layout->addWidget(listWidget);

//	setStyleSheet("* { background-color:rgb(199,147,88); padding: 7px ; color:rgb(255,255,255)}");
//	setCentralWidget(listWidget);

	ui->setupUi(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::FillTree(const QDomNode& dom, QStandardItemModel* model) {
	if(!dom.isNull()){
		std::string aux = dom.nodeName().toStdString();
		if(dom.isText()) {
			QStandardItem* item = 0;
			aux = dom.parentNode().nodeName().toStdString();
			if(aux=="name") {
				std::cout<<dom.nodeValue().toStdString()<<std::endl;
				item = new QStandardItem(dom.nodeValue());
				item->setEditable(false);
				model->setItem(nRow,item);
				++nRow;
			}
			if(aux=="value") {
				std::cout<<"\t"<<dom.nodeValue().toStdString()<<std::endl;
				QStandardItem *subItem = new QStandardItem(dom.nodeValue());
				subItem->setCheckable(true);
				subItem->setEditable(false);
			//	model->appendRow(subItem);
				model->setItem(nRow,1,subItem);
				++nRow;
			}
		} else {
			FillTree(dom.firstChild(), model);
			FillTree(dom.nextSibling(),model);
		}
	//	++nRow;
	}
}
void MainWindow::SetModel(QStandardItemModel *mod) {
	ui->treeView->setModel(mod);
}
