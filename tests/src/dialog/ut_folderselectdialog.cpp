/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author:     zhangteng <zhangteng@uniontech.com>
* Maintainer: zhangteng <zhangteng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ut_folderselectdialog.h"
#include "folderselectdialog.h"
#include "leftview.h"
#include "leftviewdelegate.h"
#include "leftviewsortfilter.h"
#include "common/vnoteforlder.h"

#include <QStandardItemModel>

ut_folderselectdialog_test::ut_folderselectdialog_test()
{
}

TEST_F(ut_folderselectdialog_test, setNoteContext)
{
    LeftView leftview;
    FolderSelectDialog folderselectdialog(leftview.m_pDataModel);
    folderselectdialog.setNoteContextInfo("test", 1);
    folderselectdialog.getSelectIndex();
}

TEST_F(ut_folderselectdialog_test, clearSelection)
{
    LeftView leftview;
    FolderSelectDialog folderselectdialog(leftview.m_pDataModel);
    folderselectdialog.clearSelection();
}

TEST_F(ut_folderselectdialog_test, hideEvent)
{
    LeftView leftview;
    FolderSelectDialog folderselectdialog(leftview.m_pDataModel);
    QHideEvent *event = new QHideEvent();
    folderselectdialog.hideEvent(event);
}

TEST_F(ut_folderselectdialog_test, refreshTextColor)
{
    QStandardItemModel dataModel;
    FolderSelectDialog folderselectdialog(&dataModel);
    folderselectdialog.refreshTextColor(true);
    folderselectdialog.refreshTextColor(false);
}

TEST_F(ut_folderselectdialog_test, setFolderBlack)
{
    VNoteFolder *folder1 = new VNoteFolder;
    LeftView leftview;
    leftview.addFolder(folder1);
    FolderSelectDialog folderselectdialog(leftview.m_pDataModel);
    QList<VNoteFolder *> blackList;
    blackList.push_back(folder1);
    folderselectdialog.setFolderBlack(blackList);
}