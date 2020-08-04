#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QDate>

class DateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};

#endif // DATEDELEGATE_H
