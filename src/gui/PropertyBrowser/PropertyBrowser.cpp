#include "PropertyBrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include <QDate>
#include <QLocale>

PropertyBrowser::PropertyBrowser(QWidget *parent)
    :QtTreePropertyBrowser(parent)
{
    m_variantManager = new QtVariantPropertyManager();
    m_variantFactory = new QtVariantEditorFactory();
    setFactoryForManager(m_variantManager, m_variantFactory);
    setPropertiesWithoutValueMarked(true);
    setRootIsDecorated(false);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slot_valueChanged(QtProperty *, const QVariant &)));
}

PropertyBrowser::~PropertyBrowser()
{
    delete m_variantManager;
    delete m_variantFactory;
}

void PropertyBrowser::initProperties(QList<PropertyGroup> listPropertyGroup)
{
    clear();
    m_listPropertyGroup = listPropertyGroup;
    foreach (PropertyGroup group, m_listPropertyGroup)
    {
        QtProperty *topItem = m_variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), group.first);
        foreach (PropertyType property, group.second)
        {
            QtVariantProperty *item = m_variantManager->addProperty(property.first.type(), property.second);
            item->setValue(property.first);
            topItem->addSubProperty(item);
        }
        addProperty(topItem);
    }
}

void PropertyBrowser::slot_valueChanged(QtProperty *property, const QVariant &val)
{
    foreach (PropertyGroup group, m_listPropertyGroup)
    {
        foreach (PropertyType shapeProperty, group.second)
        {
            if(shapeProperty.second == property->propertyName())
            {
                emit propertyValueChanged(property->propertyName(), val);
            }
        }
    }
}
