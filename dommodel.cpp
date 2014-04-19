#include "dommodel.h"

DomItem *DomItem::child(int idx) {
	if(childItems.contains(idx)) return childItems[idx];
	if(idx>=0 && idx<domNode.childNodes().count()) {
		QDomNode childNode = domNode.childNodes().item(idx);
		DomItem *childItem = new DomItem(childNode, idx, this);
		childItems[idx] = childItem;
		return childItem;
	}
	return 0;
}
DomItem::~DomItem() {
	QHash<int,DomItem*>::iterator itr;
	for (itr=childItems.begin();itr!=childItems.end();++itr)
		delete itr.value();
}

QVariant DomModel::data(const QModelIndex &index, int role) const {
	if(!index.isValid()) return QVariant();
	if(role!=Qt::DisplayRole) return QVariant();

	DomItem *item = static_cast<DomItem*>(index.internalPointer());
	QDomNode node = item->node();
	QStringList attributes;
	QDomNamedNodeMap attributeMap = node.attributes();
	switch (index.column()) {
	case 0:	return node.nodeName();
	case 1:	for (int idx=0;idx<attributeMap.count();++idx) {
				QDomNode attribute=attributeMap.item(idx);
				attributes<<attribute.nodeName()+"=\""
							+attribute.nodeValue()+"\"";
			}
		return attributes.join(' ');
	case 2:	return node.nodeValue().split("\n").join(' ');
	default:return QVariant();
	}
}
Qt::ItemFlags DomModel::flags(const QModelIndex &index) const {
	if(!index.isValid()) return 0;
	return QAbstractItemModel::flags(index);
}
QVariant DomModel::headerData(int section, Qt::Orientation orientation,
							  int role) const {
	if(orientation==Qt::Horizontal && role==Qt::DisplayRole) {
		switch(section) {
		case 0:	return tr("Name");
		case 1:	return tr("Attributes");
		case 2:	return tr("Value");
		default:return QVariant();
		}
	}
	return QVariant();
}
QModelIndex DomModel::index(int row, int column,
							const QModelIndex &parent) const {
	if(!hasIndex(row, column, parent)) return QModelIndex();

	DomItem *parentItem=(!parent.isValid() ? rootItem
					: static_cast<DomItem*>(parent.internalPointer()));
	DomItem *childItem = parentItem->child(row);
	return (childItem ? createIndex(row, column, childItem) : QModelIndex());
}
int DomModel::rowCount(const QModelIndex &parent) const {
	if(parent.column()>0) return 0;

	DomItem *parentItem=(!parent.isValid() ? rootItem
					: static_cast<DomItem*>(parent.internalPointer()));
	return parentItem->node().childNodes().count();
}
QModelIndex DomModel::parent(const QModelIndex &child) const {
	if(!child.isValid()) return QModelIndex();

	DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
	DomItem *parentItem = childItem->parent();
	if (!parentItem || parentItem == rootItem) return QModelIndex();
	return createIndex(parentItem->row(), 0, parentItem);
}

void DomModel::Fill(std::map<std::string,Card>& cards, bool tokens) {
	FillNode(rootItem->node(),cards,tokens);
}
void DomModel::FillNode(const QDomNode& node,std::map<std::string,Card>& cards, bool tokens) {
	QDomNode domNode=node.firstChild();
	int level=0; ++level;
	std::map<std::string,Card>::iterator current=cards.end();
	while(!(domNode.isNull())) {
		if(domNode.isElement()) {
			QDomElement domElem=domNode.toElement();
			if(!(domElem.isNull())) {
				std::cout<<domElem.tagName().toStdString()<<"("
						<<domElem.isElement()<<")"<<std::endl;
			//	qDebug()<<__FUNCTION__<<""<<domElem.tagName()<<domElem.text();
			//	std::cout<<domElem.tagName().toStdString()<<"="
			//			<<domElem.text().toStdString()<<std::endl;
				QDomNamedNodeMap nodeMap=domElem.attributes();
				for(int idx=0;idx<nodeMap.length();++idx) {
					QDomAttr domAttr=nodeMap.item(idx).toAttr();
					std::cout<<"lvl="<<level<<" "<<domAttr.name().toStdString()<<"=\""
							<<domAttr.value().toStdString()<<"\""<<std::endl;
				}

				if(domElem.tagName()=="card") {
					current=cards.end();
					Card tmp_card;
				for(int idx=0;idx<nodeMap.length();++idx) {
					QDomAttr domAttr=nodeMap.item(idx).toAttr();
					if(domAttr.name().toStdString()=="name") {
						current=cards.insert(std::make_pair(
						domAttr.value().toStdString(),Card())).first;
					} else
					if(domAttr.name().toStdString()=="type") {
						if(domAttr.value().toStdString()=="spell") {
							tmp_card.type=Card::spell;
						} else if(domAttr.value().toStdString()=="minion") {
							tmp_card.type=Card::creature;
						} else if(domAttr.value().toStdString()=="weapon") {
							tmp_card.type=Card::weapon;
						}
					} else
					if(domAttr.name().toStdString()=="rarity") {
						if(domAttr.value().toStdString()=="common") {
							tmp_card.rarity=Card::common;
						} else if(domAttr.value().toStdString()=="rare") {
							tmp_card.rarity=Card::rare;
						} else if(domAttr.value().toStdString()=="epic") {
							tmp_card.rarity=Card::epic;
						} else if(domAttr.value().toStdString()=="legendary") {
							tmp_card.rarity=Card::legendary;
						}
					} else
					if(domAttr.name().toStdString()=="set") {
						if(domAttr.value().toStdString()=="basic") {
							tmp_card.set=Card::basic;
						} else if(domAttr.value().toStdString()=="expert") {
							tmp_card.set=Card::expert;
						} else if(domAttr.value().toStdString()=="dream") {
							tmp_card.set=Card::dream;
						} else if(domAttr.value().toStdString()=="promotion:basic") {
							tmp_card.set=Card::promotion_basic;
						} else if(domAttr.value().toStdString()=="promotion:expert") {
							tmp_card.set=Card::promotion_expert;
						} else if(domAttr.value().toStdString()=="missions") {
							tmp_card.set=Card::missions;
						} else if(domAttr.value().toStdString()=="legacy") {
							tmp_card.set=Card::legacy;
						}
					} else
					if(domAttr.name().toStdString()=="class") {
						if(domAttr.value().toStdString()=="neutral") {
							tmp_card.card_class=Hero::none;
						} else if(domAttr.value().toStdString()=="Druid") {
							tmp_card.card_class=Hero::druid;
						} else if(domAttr.value().toStdString()=="Hunter") {
							tmp_card.card_class=Hero::hunter;
						} else if(domAttr.value().toStdString()=="Mage") {
							tmp_card.card_class=Hero::mage;
						} else if(domAttr.value().toStdString()=="Paladin") {
							tmp_card.card_class=Hero::paladin;
						} else if(domAttr.value().toStdString()=="Priest") {
							tmp_card.card_class=Hero::priest;
						} else if(domAttr.value().toStdString()=="Rogue") {
							tmp_card.card_class=Hero::rogue;
						} else if(domAttr.value().toStdString()=="Shaman") {
							tmp_card.card_class=Hero::shaman;
						} else if(domAttr.value().toStdString()=="Warlock") {
							tmp_card.card_class=Hero::warlock;
						} else if(domAttr.value().toStdString()=="Warrior") {
							tmp_card.card_class=Hero::warrior;
						}
					}
				}
					if(current!=cards.end()) {
						current->second=tmp_card;
					}
				}
			}
		}
		if(domNode.isText()) {
			QDomText domText=domNode.toText();
			if(!domText.isNull()) {
				std::cout<<"\tlvl="<<level<<" "<<domText.data().toStdString()<<std::endl;
			}
		}
		FillNode(domNode,cards,tokens);
		domNode=domNode.nextSibling();
	}
}
