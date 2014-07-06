#include "mainwindow.h"
#include <QApplication>

#include "hs/concepts.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow window;
	window.resize(640,480);
	window.show();
	window.openFile();

/*	QString filename("W:/CoPilot/CoPilot/resources/test.xml");
	int errorLine, errorColumn;
	QString errorMsg;
	QFile modelFile(filename);
	QDomDocument document;
//	QDomProcessingInstruction xmlProcessingInstruction =
//		document.createProcessingInstruction("xml","version=\"1.0\"");
//	document.appendChild(xmlProcessingInstruction);
//	QDomElement root = document.createElement("MyRoot");
//	document.appendChild(root);
	if(!document.setContent(&modelFile, &errorMsg,
							&errorLine, &errorColumn)) {
		QString error("Syntax error line %1, column %2:\n%3");
		error = error.arg(errorLine)
					.arg(errorColumn)
					.arg(errorMsg);
		QMessageBox msgBox;
		msgBox.setText(error);
		msgBox.exec();
	}

//	std::list<QString> result;
//	QDomElement rootElement = document.documentElement();
//	for(QDomNode node=rootElement.firstChild();!node.isNull();
//	node=node.nextSibling()) {
//		QDomElement element = node.toElement();
//		if(!element.isNull()) {
//			result.push_back(element.tagName());
//			qDebug()<<"Filling list with "<<result.back();
//		}
//	}
	qDebug()<<"Creating windows";

	MainWindow w;
//	w.FillList(result);	//document.documentElement().firstChild()
	QStandardItemModel *model = new QStandardItemModel();
	w.FillTree(document.firstChild(), model);
	w.SetModel(model);
	w.show();

//to search for widget:
//	QListWidget *listWidget = w.findChild<QListWidget*>("listWidget");
//	Q_ASSERT(listWidget);
*/
	Card::Print();

    return a.exec();
}
