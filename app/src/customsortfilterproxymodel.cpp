#include "customsortfilterproxymodel.h"

CustomSortFilterProxyModel::CustomSortFilterProxyModel()
{
}

bool CustomSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, DbManager::quotes::content, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, DbManager::quotes::author, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, DbManager::quotes::topicIndex, sourceParent);
    QModelIndex index3 = sourceModel()->index(sourceRow, DbManager::quotes::created, sourceParent);

    return (sourceModel()->data(index0).toString().contains(filterRegExp())
            || sourceModel()->data(index1).toString().contains(filterRegExp())
            || sourceModel()->data(index2).toString().contains(filterRegExp())
            || sourceModel()->data(index3).toString().contains(filterRegExp()));
}
