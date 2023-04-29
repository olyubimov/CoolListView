
#ifndef COOLLISTMODEL_H
#define COOLLISTMODEL_H

#include "coollistitem.h"
#include <QAbstractListModel>
#include <QList>
#include "dataloader.h"

class CoolListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int chunkSize READ chunkSize WRITE setChunkSize NOTIFY chunkSizeChanged)

public:
    enum ModelRoles {
        MessageIndexRole = Qt::UserRole + 1,
        NickNameRole,
        MessageTextRole,
    };

    explicit CoolListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;

    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count() const;

    void append(const CoolListItem &item);

    void append(const QList<CoolListItem> &list);

    void prepend(const QList<CoolListItem> &list);

    void insert(const CoolListItem &item, int position);

    void remove(int position, int count = 1);

    void replace(const CoolListItem &item, int position);

    void removeUnusedFrontItems(int treshold, int count);
    void removeUnusedBackItems(int treshold, int count);


    Q_INVOKABLE bool canFetchMoreFront();
    Q_INVOKABLE void fetchMoreFront();

    int chunkSize() const;
    void setChunkSize(int newChunkSize);

signals:
    void countChanged();
    void chunkSizeChanged();

private:
    QList<CoolListItem> m_list;
    DataLoader m_dataLoader;
    int m_chunkSize;
};

#endif // COOLLISTMODEL_H
