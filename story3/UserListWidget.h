#pragma once

#include <QListWidget>
#include <QVector>
#include <QIcon>

class UserListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit UserListWidget(QWidget* parent = 0);
    void addItem(const QString&, const QString&, bool);
    void changeItemColor(const QString&, bool);
    void clear();

private:
    QVector<QIcon> m_normalIcons;   // 正常图标集合
    QVector<QIcon> m_grayIcons;     // 灰度图标集合
};
