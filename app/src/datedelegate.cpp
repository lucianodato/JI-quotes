#include "datedelegate.h"

DateDelegate::DateDelegate(QObject * parent):
    QStyledItemDelegate(parent)
{

}

QString DateDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    if (value.toDate().isValid()) {
        return value.toDate().toString(tr("M-d-yy"));
    }
    return QStyledItemDelegate::displayText(value, locale);
}
