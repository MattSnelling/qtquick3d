#ifndef QQMLOBJECTLISTMODEL_H
#define QQMLOBJECTLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QByteArray>
#include <QtCore/QChar>
#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QMetaMethod>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringBuilder>
#include <QtCore/QVariant>
#include <QtCore/QVector>

#define STATIC_LOCAL(type, name, arguments) static type & name = *new type arguments
#define STATIC_LOCAL_NOARG(type, name) static type & name = *new type

template<typename T>
QList<T> qListFromVariant(const QVariantList & list)
{
	QList<T> ret;
	ret.reserve(list.size());
	for (QVariantList::const_iterator it = list.constBegin(); it != list.constEnd(); it++)
	{
		const QVariant & var = (QVariant)(*it);
		ret.append(var.value<T>());
	}
	return ret;
}

template<typename T>
QVariantList qListToVariant(const QList<T> & list)
{
	QVariantList ret;
	ret.reserve(list.size());
	for (typename QList<T>::const_iterator it = list.constBegin(); it != list.constEnd(); it++)
	{
		const T & val = static_cast<T>(*it);
		ret.append(QVariant::fromValue(val));
	}
	return ret;
}

// custom foreach for QList, which uses no copy and check pointer non-null
#define FOREACH_PTR_IN_QLIST(_type_, _var_, _list_) \
	for (typename QList<_type_ *>::const_iterator it = _list_.begin(); it != _list_.end(); it++) \
		for (_type_ * _var_ = static_cast<_type_ *>(*it); _var_ != Q_NULLPTR; _var_ = Q_NULLPTR)

class QQmlObjectListModelBase : public QAbstractListModel
{ // abstract Qt base class
	Q_OBJECT
	Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
	explicit QQmlObjectListModelBase(QObject * parent) :
		QAbstractListModel(parent) {}
	virtual ~QQmlObjectListModelBase() override {}

public slots: // virtual methods API for QML
	virtual int size(void) const = 0;
	virtual int count(void) const = 0;
	virtual bool isEmpty(void) const = 0;
	virtual bool contains(QObject * item) const = 0;
	virtual int indexOf(QObject * item) const = 0;
	virtual int roleForName(const QByteArray & name) const = 0;
	virtual void clear(void) = 0;
	virtual void append(QObject * item) = 0;
	virtual void prepend(QObject * item) = 0;
	virtual void insert(int idx, QObject * item) = 0;
	virtual void move(int idx, int pos) = 0;
	virtual void remove(QObject * item) = 0;
	virtual void remove(int idx) = 0;
	virtual QObject * get(int idx) const = 0;
	virtual QObject * get(const QString & uid) const = 0;
	virtual QObject * getFirst(void) const = 0;
	virtual QObject * getLast(void) const = 0;
	virtual QVariantList toVarArray(void) const = 0;

protected slots: // internal callback
	virtual void onItemPropertyChanged(void) = 0;

signals: // notifier
	void countChanged(void);
	void itemAdded(QObject * item);
};

template<class ItemType>
class QQmlObjectListModel : public QQmlObjectListModelBase
{
public:
	explicit QQmlObjectListModel(QObject * parent, const QByteArray & displayRole = QByteArray(), const QByteArray & uidRole = QByteArray()) :
		QQmlObjectListModelBase(parent),
		m_count(0),
		m_uidRoleName(uidRole),
		m_dispRoleName(displayRole),
		m_metaObj(ItemType::staticMetaObject)
	{
		STATIC_LOCAL_NOARG(QSet<QByteArray>, roleNamesBlacklist);
		if (roleNamesBlacklist.isEmpty())
		{
			roleNamesBlacklist << QByteArrayLiteral("id")
							   << QByteArrayLiteral("index")
							   << QByteArrayLiteral("class")
							   << QByteArrayLiteral("model")
							   << QByteArrayLiteral("modelData");
		}
		static const char * HANDLER = "onItemPropertyChanged()";
		m_handler = metaObject()->method(metaObject()->indexOfMethod(HANDLER));
		if (!displayRole.isEmpty())
		{
			m_roles.insert(Qt::DisplayRole, QByteArrayLiteral("display"));
		}
		m_roles.insert(baseRole(), QByteArrayLiteral("qtObject"));
		const int len = m_metaObj.propertyCount();
		for (int propertyIdx = 0, role = (baseRole() + 1); propertyIdx < len; propertyIdx++, role++)
		{
			QMetaProperty metaProp = m_metaObj.property(propertyIdx);
			const QByteArray propName = QByteArray(metaProp.name());
			if (!roleNamesBlacklist.contains(propName))
			{
				m_roles.insert(role, propName);
				if (metaProp.hasNotifySignal())
				{
					m_signalIdxToRole.insert(metaProp.notifySignalIndex(), role);
				}
			}
			else
			{
				STATIC_LOCAL(const QByteArray, CLASS_NAME, (QByteArrayLiteral("QQmlObjectListModel<") % m_metaObj.className() % '>'));
				qWarning() << "Can't have" << propName << "as a role name in" << qPrintable(CLASS_NAME);
			}
		}
	}

	~QQmlObjectListModel() override
	{
		clear();
	}

	bool setData(const QModelIndex & index, const QVariant & value, int role) override
	{
		bool ret = false;
		ItemType * item = at(index.row());
		const QByteArray rolename = (role != Qt::DisplayRole ? m_roles.value(role, emptyBA()) : m_dispRoleName);
		if (item != Q_NULLPTR && role != baseRole() && !rolename.isEmpty())
		{
			ret = item->setProperty(rolename, value);
		}

		return ret;
	}

	QVariant data(const QModelIndex & index, int role) const override
	{
		QVariant ret;
		ItemType * item = at(index.row());
		const QByteArray rolename = (role != Qt::DisplayRole ? m_roles.value(role, emptyBA()) : m_dispRoleName);
		if (item != Q_NULLPTR && !rolename.isEmpty())
		{
			ret.setValue(role != baseRole() ? item->property(rolename) : QVariant::fromValue(static_cast<QObject *>(item)));
		}
		return ret;
	}

	QHash<int, QByteArray> roleNames(void) const override
	{
		return m_roles;
	}

	typedef typename QList<ItemType *>::iterator iterator;
	iterator begin(void) const
	{
		return m_items.begin();
	}

	iterator end(void) const
	{
		return m_items.end();
	}

	typedef typename QList<ItemType *>::const_iterator const_iterator;
	const_iterator constBegin(void) const
	{
		return m_items.constBegin();
	}

	const_iterator constEnd(void) const
	{
		return m_items.constEnd();
	}

public: // C++ API
	ItemType * at(int idx) const
	{
		ItemType * ret = Q_NULLPTR;
		if (idx >= 0 && idx < m_items.size())
		{
			ret = m_items.value(idx);
		}
		return ret;
	}

	ItemType * getByUid(const QString & uid) const
	{
		return m_indexByUid.value(uid, Q_NULLPTR);
	}

	int roleForName(const QByteArray & name) const override
	{
		return m_roles.key(name, -1);
	}

	int count(void) const override
	{
		return m_count;
	}

	int size(void) const override
	{
		return m_count;
	}

	bool isEmpty(void) const override
	{
		return m_items.isEmpty();
	}

	bool contains(ItemType * item) const
	{
		return m_items.contains(item);
	}

	int indexOf(ItemType * item) const
	{
		return m_items.indexOf(item);
	}

	int locate(const ItemType * item) const
	{
		int index = -1;
		for (int i = 0; i < count(); i++)
		{
			if (at(i) == item)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void clear(void) override
	{
		if (!m_items.isEmpty())
		{
			beginRemoveRows(noParent(), 0, m_items.count() - 1);
			FOREACH_PTR_IN_QLIST(ItemType, item, m_items)
			{
				dereferenceItem(item);
			}
			m_items.clear();
			endRemoveRows();
			updateCounter();
		}
	}

	void clearWithoutDereference()
	{
		if (!m_items.isEmpty())
		{
			beginRemoveRows(noParent(), 0, m_items.count() - 1);
			m_items.clear();
			endRemoveRows();
			updateCounter();
		}
	}

	void append(ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			const int pos = m_items.count();
			beginInsertRows(noParent(), pos, pos);
			m_items.append(item);
			referenceItem(item);
			emit itemAdded(item);
			endInsertRows();
			updateCounter();
		}
	}

	void prepend(ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			beginInsertRows(noParent(), 0, 0);
			m_items.prepend(item);
			referenceItem(item);
			emit itemAdded(item);
			endInsertRows();
			updateCounter();
		}
	}

	void insert(int idx, ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			beginInsertRows(noParent(), idx, idx);
			m_items.insert(idx, item);
			referenceItem(item);
			emit itemAdded(item);
			endInsertRows();
			updateCounter();
		}
	}

	void append(const QList<ItemType *> & itemList)
	{
		if (!itemList.isEmpty())
		{
			const int pos = m_items.count();
			beginInsertRows(noParent(), pos, pos + itemList.count() - 1);
			m_items.reserve(m_items.count() + itemList.count());
			m_items.append(itemList);
			FOREACH_PTR_IN_QLIST(ItemType, item, itemList)
			{
				referenceItem(item);
				emit itemAdded(item);
			}
			endInsertRows();
			updateCounter();
		}
	}

	void prepend(const QList<ItemType *> & itemList)
	{
		if (!itemList.isEmpty())
		{
			beginInsertRows(noParent(), 0, itemList.count() - 1);
			m_items.reserve(m_items.count() + itemList.count());
			int offset = 0;
			FOREACH_PTR_IN_QLIST(ItemType, item, itemList)
			{
				m_items.insert(offset, item);
				referenceItem(item);
				emit itemAdded(item);
				offset++;
			}
			endInsertRows();
			updateCounter();
		}
	}

	void insert(int idx, const QList<ItemType *> & itemList)
	{
		if (!itemList.isEmpty())
		{
			beginInsertRows(noParent(), idx, idx + itemList.count() - 1);
			m_items.reserve(m_items.count() + itemList.count());
			int offset = 0;
			FOREACH_PTR_IN_QLIST(ItemType, item, itemList)
			{
				m_items.insert(idx + offset, item);
				referenceItem(item);
				emit itemAdded(item);
				offset++;
			}
			endInsertRows();
			updateCounter();
		}
	}

	void move(int idx, int pos) override
	{
		if (idx != pos)
		{
			const int lowest = qMin(idx, pos);
			const int highest = qMax(idx, pos);
			beginMoveRows(noParent(), highest, highest, noParent(), lowest);
			m_items.move(highest, lowest);
			endMoveRows();
		}
	}

	void remove(ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			const int idx = m_items.indexOf(item);
			remove(idx);
		}
	}

	void remove(int idx) override
	{
		if (idx >= 0 && idx < m_items.size())
		{
			beginRemoveRows(noParent(), idx, idx);
			ItemType * item = m_items.takeAt(idx);
			dereferenceItem(item);
			endRemoveRows();
			updateCounter();
		}
	}

	ItemType * first(void) const
	{
		return m_items.first();
	}

	ItemType * last(void) const
	{
		return m_items.last();
	}

	const QList<ItemType *> & toList(void) const
	{
		return m_items;
	}

public: // QML slots implementation
	void append(QObject * item) override
	{
		append(qobject_cast<ItemType *>(item));
	}
	void prepend(QObject * item) override
	{
		prepend(qobject_cast<ItemType *>(item));
	}

	void insert(int idx, QObject * item) override
	{
		insert(idx, qobject_cast<ItemType *>(item));
	}

	void remove(QObject * item) override
	{
		remove(qobject_cast<ItemType *>(item));
	}

	bool contains(QObject * item) const override
	{
		return contains(qobject_cast<ItemType *>(item));
	}

	int indexOf(QObject * item) const override
	{
		return indexOf(qobject_cast<ItemType *>(item));
	}

	int indexOf(const QString & uid) const
	{
		return indexOf(get(uid));
	}

	QObject * get(int idx) const override
	{
		return static_cast<QObject *>(at(idx));
	}

	QObject * get(const QString & uid) const override
	{
		return static_cast<QObject *>(getByUid(uid));
	}

	QObject * getFirst(void) const override
	{
		return static_cast<QObject *>(first());
	}

	QObject * getLast(void) const override
	{
		return static_cast<QObject *>(last());
	}

	QVariantList toVarArray(void) const override
	{
		return qListToVariant<ItemType *>(m_items);
	}

protected: // internal stuff
	static const QString & emptyStr(void)
	{
		STATIC_LOCAL(const QString, ret, QStringLiteral(""));
		return ret;
	}

	static const QByteArray & emptyBA(void)
	{
		STATIC_LOCAL(const QByteArray, ret, QByteArrayLiteral(""));
		return ret;
	}

	static const QModelIndex & noParent(void)
	{
		static const QModelIndex ret = QModelIndex();
		return ret;
	}

	static const int & baseRole(void)
	{
		static const int ret = Qt::UserRole;
		return ret;
	}

	int rowCount(const QModelIndex & parent = QModelIndex()) const override
	{
		Q_UNUSED(parent);
		return m_items.count();
	}

	void referenceItem(ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			if (item->parent() == Q_NULLPTR)
			{
				item->setParent(this);
			}

			bool ok = connect(item, &ItemType::destroyed, this, [&](QObject * pItem) { remove(qobject_cast<ItemType *>(pItem)); });
			Q_ASSERT(ok);
			Q_UNUSED(ok);

			const QList<int> signalsIdxList = m_signalIdxToRole.keys();
			auto endIt = signalsIdxList.constEnd();
			for (QList<int>::const_iterator it = signalsIdxList.constBegin(); it != endIt; ++it)
			{
				const int signalIdx = static_cast<int>(*it);
				QMetaMethod notifier = item->metaObject()->method(signalIdx);
				connect(item, notifier, this, m_handler, Qt::UniqueConnection);
			}

			if (!m_uidRoleName.isEmpty())
			{
				const QString key = m_indexByUid.key(item, emptyStr());
				if (!key.isEmpty())
				{
					m_indexByUid.remove(key);
				}
				const QString value = item->property(m_uidRoleName).toString();
				if (!value.isEmpty())
				{
					m_indexByUid.insert(value, item);
				}
			}
		}
	}
	void dereferenceItem(ItemType * item)
	{
		if (item != Q_NULLPTR)
		{
			disconnect(this, Q_NULLPTR, item, Q_NULLPTR);
			disconnect(item, Q_NULLPTR, this, Q_NULLPTR);
			if (!m_uidRoleName.isEmpty())
			{
				const QString key = m_indexByUid.key(item, emptyStr());
				if (!key.isEmpty())
				{
					m_indexByUid.remove(key);
				}
			}
			if (item->parent() == this || item->parent() == this->parent()) // If this list object or its parent owns the item then we can delete it.
			{
				item->deleteLater();
			}
			else
			{
				Q_ASSERT(false);
			}
		}
	}
	void onItemPropertyChanged(void) override
	{
		ItemType * item = qobject_cast<ItemType *>(sender());
		const int row = m_items.indexOf(item);
		const int sig = senderSignalIndex();
		const int role = m_signalIdxToRole.value(sig, -1);
		if (row >= 0 && role >= 0)
		{
			QModelIndex index = QAbstractListModel::index(row, 0, noParent());
			QVector<int> rolesList;
			rolesList.append(role);
			if (m_roles.value(role) == m_dispRoleName)
			{
				rolesList.append(Qt::DisplayRole);
			}
			emit dataChanged(index, index, rolesList);
		}
		if (!m_uidRoleName.isEmpty())
		{
			const QByteArray roleName = m_roles.value(role, emptyBA());
			if (!roleName.isEmpty() && roleName == m_uidRoleName)
			{
				const QString key = m_indexByUid.key(item, emptyStr());
				if (!key.isEmpty())
				{
					m_indexByUid.remove(key);
				}
				const QString value = item->property(m_uidRoleName).toString();
				if (!value.isEmpty())
				{
					m_indexByUid.insert(value, item);
				}
			}
		}
	}
	inline void updateCounter(void)
	{
		if (m_count != m_items.count())
		{
			m_count = m_items.count();
			emit countChanged();
		}
	}

private: // data members
	int m_count;
	QByteArray m_uidRoleName;
	QByteArray m_dispRoleName;
	QMetaObject m_metaObj;
	QMetaMethod m_handler;
	QHash<int, QByteArray> m_roles;
	QHash<int, int> m_signalIdxToRole;
	QList<ItemType *> m_items;
	QHash<QString, ItemType *> m_indexByUid;
};

#define QML_OBJMODEL_PROPERTY(type, name) \
protected: \
	Q_PROPERTY(QQmlObjectListModelBase * name READ get_##name##_ptr CONSTANT) \
private: \
	QQmlObjectListModel<type> m_##name; \
\
public: \
	QQmlObjectListModel<type> & get_##name(void) const { return const_cast<QQmlObjectListModel<type> &>(m_##name); } \
	QQmlObjectListModelBase * get_##name##_ptr(void) { return static_cast<QQmlObjectListModelBase *>(&m_##name); } \
\
private:

#endif // QQMLOBJECTLISTMODEL_H
