#ifndef QPROPERTYMANAGER_H
#define QPROPERTYMANAGER_H

#include "qttreepropertybrowser.h"

typedef QPair<QVariant, QString> PropertyType;
typedef QPair<QString, QList<PropertyType> > PropertyGroup;

class QtVariantEditorFactory;
class QtVariantPropertyManager;

class QT_QTPROPERTYBROWSER_EXPORT PropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    PropertyBrowser(QWidget * parent = 0);
    ~PropertyBrowser();

    void initProperties(QList<PropertyGroup> listPropertyGroup);

signals:
    void propertyValueChanged(QString propertyName, const QVariant &val);

private slots:
    void slot_valueChanged(QtProperty *property, const QVariant &val);

private:
    QList<PropertyGroup> m_listPropertyGroup;
    QtVariantEditorFactory * m_variantFactory;
    QtVariantPropertyManager * m_variantManager;
};

#endif // QPROPERTYMANAGER_H
