#ifndef DOMMODEL_H
#define DOMMODEL_H

#include <QAbstractItemModel>
#include <QtXml/QDomNode>
#include <QtDebug>
#include <stdio.h>
#include <iostream>

#include "hs/concepts.h"

class DomItem {
public:
	DomItem(QDomNode &node, int row, DomItem *parent = 0) :
		domNode(node),parentItem(parent),rowNumber(row) { }
	~DomItem();
	DomItem *child(int idx);
	QDomNode node() const { return domNode; }
	DomItem *parent() { return parentItem; }
	int row() { return rowNumber; }
private:
	QHash<int,DomItem*> childItems;
	QDomNode domNode;
	DomItem *parentItem;
	int rowNumber;
};

class DomModel : public QAbstractItemModel {	Q_OBJECT
public:
	DomModel(QDomDocument document, QObject *parent) :
		QAbstractItemModel(parent),domDocument(document) {
		rootItem = new DomItem(domDocument, 0);
	}
	~DomModel() { delete rootItem; }
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
						int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
					  const QModelIndex &parent = QModelIndex()) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const {
		return 3;
	}
	QModelIndex parent(const QModelIndex &child) const;

	void Fill(std::map<std::string,Card>& cards, bool tokens=false);
private:
	void FillNode(const QDomNode& node,
				  std::map<std::string,Card>& cards, bool tokens=false);
	QDomDocument domDocument;
	DomItem *rootItem;
};

#endif // DOMMODEL_H
