#include <QListWidgetItem>
#include "UserListWidget.h"

/**
 * 构造方法。
 * @param parent    父窗口
 */
UserListWidget::UserListWidget(QWidget* parent) : QListWidget(parent)
{
}

/**
 * 添加一个列表项。
 * @param itemText      列表项显示的文字
 * @param iconFilePath  列表项显示的图标的文件路径
 * @param isColorful    为 true 表示彩色，为 false 表示灰色
 */
void UserListWidget::addItem(const QString& itemText, const QString& iconFilePath, bool isColorful)
{
    QListWidgetItem* item = NULL;

    // 创建彩色图标
    QIcon normalIcon(iconFilePath);

    // 创建灰色图标
    QSize size = normalIcon.actualSize(size, QIcon::Disabled, QIcon::Off);
    QPixmap pixmap = normalIcon.pixmap(size, QIcon::Disabled, QIcon::Off);
    QIcon grayIcon(pixmap);

    // 创建列表项
    if (isColorful)
    {
       item = new QListWidgetItem(normalIcon, itemText);
    }
    else
    {
       item = new QListWidgetItem(grayIcon, itemText);
    }

    // 将列表项加入到列表控件中
    QListWidget::addItem(item);

    // 保存图标
    m_normalIcons.append(normalIcon);
    m_grayIcons.append(grayIcon);
}

/**
 * 改变列表项的颜色(在彩色、灰色之间转换)。
 * @param itemText      列表项显示的文字
 * @param isColorful    为 true 表示彩色，为 false 表示灰色
 */
void UserListWidget::changeItemColor(const QString& itemText, bool isColorful)
{
    // 查找列表项
    QList<QListWidgetItem*> itemList = this->findItems(itemText, Qt::MatchFixedString);
    if (itemList.isEmpty())
    {
        return;
    }

    // 取得列表项的索引
    QListWidgetItem* item = itemList.at(0);
    int index = this->row(item);

    // 删除列表项
    delete item;

    // 重新创建列表项
    if (isColorful)
    {
        item = new QListWidgetItem(m_normalIcons[index], itemText);
    }
    else
    {
        item = new QListWidgetItem(m_grayIcons[index], itemText);
    }

   // 将列表项加入到列表控件中
    this->insertItem(index, item);
}

/**
 * 删除所有保存的图标和列表项。
 */
void UserListWidget::clear()
{
    const int itemCount = this->count();
    for (int i = itemCount - 1; i >= 0; i--)
    {
        delete this->item(i);
    }
    m_normalIcons.clear();
    m_grayIcons.clear();
    QListWidget::clear();
}
