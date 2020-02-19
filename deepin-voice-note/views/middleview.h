#ifndef MIDDLEVIEW_H
#define MIDDLEVIEW_H
#include "middleviewdelegate.h"
#include "middleviewsortfiltermodel.h"

#include "common/vnoteforlder.h"
#include "db/vnotefolderoper.h"
#include "dialog/vnotemessagedialog.h"

#include <DListView>
#include <DMenu>
#include <DPushButton>

DWIDGET_USE_NAMESPACE
class MiddleView : public DListView
{
    Q_OBJECT
public:
    MiddleView(QWidget *parent = nullptr);
    qint64 getFolderId(const QModelIndex &index);

    void sortView(LeftViewSortFilterModel::OperaType Type = LeftViewSortFilterModel::none, Qt::SortOrder order = Qt::AscendingOrder);
    void setCreateTimeFilter(const QDateTime &begin, const QDateTime &end, QList<qint64> *whilteList = nullptr);
    void setUpdateTimeFilter(const QDateTime &begin, const QDateTime &end, QList<qint64> *whilteList = nullptr);
    void setFolderNameFilter(const QRegExp &searchKey, QList<qint64> *whilteList = nullptr);
    void clearFilter();
    void removeFromWhiteList(qint64 id);
    void setFolderEnable(bool enable);

    int loadNoteFolder();
    int getFolderCount();

public slots:
    void handleAddFolder();
    void handleRenameItem(bool);
    void handleDeleteItem(bool);
    void handleFolderRename(VNoteFolder *data);

signals:
    void sigFolderAdd(VNoteFolder *data);
    void sigFolderDel(VNoteFolder *data);
    void sigFolderUpdate(VNoteFolder *data);

private:
    void initMenuAction();
    void initConnection();
    void initDelegate();
    void initModel();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    DMenu *m_contextMenu;
    QAction *m_renameAction;
    QAction *m_delAction;

    QStandardItemModel *m_pDataModel;
    LeftViewSortFilterModel *m_pSortFilterModel;
    LeftViewDelegate *m_pItemDelegate;

    QRegExp m_searchKey;
    VNoteMessageDialog *m_delDialog {nullptr};
};

#endif // MIDDLEVIEW_H