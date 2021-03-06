/*
 * Copyright (C) 2012, 2013 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <TestUtil.h>

#include <QQmlProperty>

TestUtil::TestUtil(QObject *parent)
    : QObject(parent)
{
}

TestUtil::~TestUtil()
{
}

bool
TestUtil::isInstanceOf(QObject *obj, QString name)
{
    if (!obj) return false;
    bool result = obj->inherits(name.toUtf8());
    if (!result)
    {
        const QMetaObject *metaObject = obj->metaObject();
        while (!result && metaObject)
        {
            const QString className = metaObject->className();
            const QString qmlName = className.left(className.indexOf("_QMLTYPE_"));
            result = qmlName == name;
            metaObject = metaObject->superClass();
        }
    }
    return result;
}

bool TestUtil::objectHasPropertyOfType(QObject *qmlObject, const QString &propertyName,
                                       const QString &expectedPropertyTypeName)
{
    if (!qmlObject) return false;

    QQmlProperty property(qmlObject, propertyName);

    if (!property.isValid()) return false;
    if (!property.isProperty()) return false;
    return QString(property.propertyTypeName()) == expectedPropertyTypeName;

}
