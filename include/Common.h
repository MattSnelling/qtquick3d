/**
 *
 */

#pragma once

#include <QtCore/QPointer>
#include "include/utilities/QQmlHelpers.h"
#include "include/utilities/QQmlObjectListModel.h"

#define QML_REFERENCE_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type * name READ get_##name##_ptr CONSTANT) \
    private: \
        type & m_##name; \
    public: \
        type & get_##name () { \
            return m_##name ; \
        } \
        const type & get_##name () const { \
            return m_##name ; \
        } \
        type * get_##name##_ptr () { \
            return &m_##name ; \
        } \
    private:

#define QML_QOBJECT_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type * name READ get_##name##_ptr CONSTANT) \
    private: \
        type m_##name; \
    public: \
        type & get_##name () { \
            return m_##name ; \
        } \
        const type & get_##name () const { \
            return m_##name ; \
        } \
        type * get_##name##_ptr () { \
            return &m_##name ; \
        } \
    private:

#define QML_POINTER_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type * name READ get_##name##_ptr WRITE set_##name NOTIFY name##Changed) \
    private: \
        QPointer< type > p_##name = nullptr; \
        type * get_##name##_ptr () const { \
            return p_##name ; \
        } \
    public: \
        QPointer< type > get_##name () const { \
            return p_##name ; \
        } \
        bool set_##name (const QPointer< type > & name) { \
            bool ret = p_##name != name; \
            if (ret) { \
                p_##name = name; \
                emit name##Changed (p_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (QPointer< type > name); \
    private:

#define QML_WRITABLE_PROPERTY_EPS(type, name, defaultValue) \
    protected: \
        Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
        type m_##name = static_cast< type >(defaultValue); \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (type name) { \
            bool ret = !(fabs(m_##name - name) <= std::numeric_limits< type >::epsilon() * fabs(m_##name)); \
            if (ret) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define QML_READONLY_PROPERTY_EPS(type, name, defaultValue) \
    protected: \
        Q_PROPERTY (type name READ get_##name NOTIFY name##Changed) \
    private: \
        type m_##name = static_cast< type >(defaultValue); \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
        bool update_##name (type name) { \
            bool ret = !(fabs(m_##name - name) <= std::numeric_limits<type>::epsilon() * fabs(m_##name)); \
            if (ret) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define LOCAL_PROPERTY(type, name, defaultValue) \
    private: \
        type m_##name = defaultValue ; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    void set_##name (type name) { \
        m_##name = name; \
    } \
    private:

#define LOCAL_PROPERTY_NODEF(type, name) \
    private: \
        type m_##name ; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    void set_##name (type name) { \
        m_##name = name; \
    } \
    private:

#define LOCAL_PROPERTY_SIG(type, name, defaultValue) \
    private: \
        type m_##name = defaultValue; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (type name) { \
            bool ret = m_##name != name; \
            if (ret) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define LOCAL_PROPERTY_SIG_EPS(type, name, defaultValue) \
    private: \
        type m_##name = defaultValue; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (type name) { \
            bool ret = !(fabs(m_##name - name) <= std::numeric_limits<type>::epsilon() * fabs(m_##name)); \
            if (ret) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define QVARIANT_INIT(name, value) QVariant name; name.setValue(value);
