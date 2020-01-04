/**
 * 
 */

#pragma once

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#define UI_SINGLETON_INSTANCE_CHECK { if (instanceExists()) qFatal("Cannot create another instance of this class. This is a singleton!"); }
#define UI_SINGLETON \
    public Q_SLOTS: \
        void aboutToBeDestroyed() override \
		{ \
			QObject::disconnect(m_instanceConnection); \
			p_instance = nullptr; \
		} \
	private:

namespace UI {

    /*
     * This template creates a singleton class that can be registed with the QML engine.
     * The engine takes care of deleting this class so there's no memory leak, however
     * it is responsibility of this template to clean-up the pointer to the instance.
    */

    template <class T>
    class Singleton
    {
    public:
        static T & instance(QObject * pParent = nullptr)
        {
            if (!p_instance)
            {
				Q_ASSERT(pParent);
                p_instance = new T(pParent);
				m_instanceConnection = QObject::connect(p_instance, &T::destroyed, p_instance, &T::aboutToBeDestroyed);
				Q_ASSERT(m_instanceConnection);
            }

            return *p_instance;
        }

        static bool instanceExists()
        {
            return p_instance != nullptr;
        }

        static void setSingletonInstance(T * pInstance)
        {
            UI_SINGLETON_INSTANCE_CHECK
            p_instance = pInstance;
        }

    protected:

		virtual ~Singleton() 
		{ 
			QObject::disconnect(m_instanceConnection);
			p_instance = nullptr; 
		}

        virtual void aboutToBeDestroyed() = 0;

    protected:
        static T * p_instance;
		static QMetaObject::Connection m_instanceConnection;
    };

    template <typename T>
    T * Singleton<T>::p_instance = nullptr;

	template <typename T>
	QMetaObject::Connection Singleton<T>::m_instanceConnection;

} // namespace UI
