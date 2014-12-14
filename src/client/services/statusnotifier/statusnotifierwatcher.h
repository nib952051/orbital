/*
 * Copyright 2014 Giulio Camuffo <giuliocamuffo@gmail.com>
 *
 * This file is part of Orbital
 *
 * Orbital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Orbital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Orbital.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This file was originally generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp org.kde.StatusNotifierWatcher.xml -a statusnotifierwatcher -c StatusNotifierWatcher
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 */

#ifndef STATUSNOTIFIERWATCHER_H_1417865964
#define STATUSNOTIFIERWATCHER_H_1417865964

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface org.kde.StatusNotifierWatcher
 */
class StatusNotifierWatcher: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.kde.StatusNotifierWatcher\">\n"
"    <method name=\"RegisterStatusNotifierItem\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"service\"/>\n"
"    </method>\n"
"    <method name=\"RegisterStatusNotifierHost\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"service\"/>\n"
"    </method>\n"
"    <property access=\"read\" type=\"as\" name=\"RegisteredStatusNotifierItems\">\n"
"      <annotation value=\"QStringList\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
"      <annotation value=\"QStringList\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\"/>\n"
"    </property>\n"
"    <property access=\"read\" type=\"b\" name=\"IsStatusNotifierHostRegistered\"/>\n"
"    <property access=\"read\" type=\"i\" name=\"ProtocolVersion\"/>\n"
"    <signal name=\"StatusNotifierItemRegistered\">\n"
"      <arg type=\"s\"/>\n"
"    </signal>\n"
"    <signal name=\"StatusNotifierItemUnregistered\">\n"
"      <arg type=\"s\"/>\n"
"    </signal>\n"
"    <signal name=\"StatusNotifierHostRegistered\"/>\n"
"    <signal name=\"StatusNotifierHostUnregistered\"/>\n"
"  </interface>\n"
        "")
public:
    StatusNotifierWatcher(QObject *parent);
    virtual ~StatusNotifierWatcher();

public: // PROPERTIES
    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ isStatusNotifierHostRegistered)
    bool isStatusNotifierHostRegistered() const;

    Q_PROPERTY(int ProtocolVersion READ protocolVersion)
    int protocolVersion() const;

    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ registeredStatusNotifierItems)
    QStringList registeredStatusNotifierItems() const;

public Q_SLOTS: // METHODS
    void RegisterStatusNotifierHost(const QString &service);
    void RegisterStatusNotifierItem(const QString &service);
Q_SIGNALS: // SIGNALS
    void StatusNotifierHostRegistered();
    void StatusNotifierHostUnregistered();
    void StatusNotifierItemRegistered(const QString &in0);
    void StatusNotifierItemUnregistered(const QString &in0);

    void newItem(const QString &service);
};

#endif