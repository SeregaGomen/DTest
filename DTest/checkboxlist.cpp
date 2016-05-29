#include <QtGui>

#include <QStylePainter>
#include <QAbstractItemView>

#include "checkboxlist.h"

//min-width:10em;
CheckBoxList::CheckBoxList(QWidget *widget) : QComboBox(widget)
{
    // set delegate items view
    view()->setItemDelegate(new CheckBoxListDelegate(this));
    //view()->setStyleSheet("  padding: 15px; ");
    // Enable editing on items view
    view()->setEditTriggers(QAbstractItemView::CurrentChanged);

    // set "CheckBoxList::eventFilter" as event filter for items view
    view()->viewport()->installEventFilter(this);

    // it just cool to have it as defualt ;)
    view()->setAlternatingRowColors(true);
}


bool CheckBoxList::eventFilter(QObject *object, QEvent *event)
{
    // don't close items view after we release the mouse button
    // by simple eating MouseButtonRelease in viewport of items view
    if(event->type() == QEvent::MouseButtonRelease && object==view()->viewport())
        return true;
    return QComboBox::eventFilter(object,event);
}

void CheckBoxList::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox opt;

    painter.setPen(palette().color(QPalette::Text));
    initStyleOption(&opt);

    opt.currentText.clear();
    for (int i = 0; i < count(); i++)
        if (this->itemData(i) == true)
        {
            if (opt.currentText.length())
                opt.currentText += ';';
            opt.currentText += itemText(i);
        }
    m_DisplayText = opt.currentText;
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    // draw the icon and text
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);

}

void CheckBoxList::setDisplayText(QString text)
{
    m_DisplayText = text;
}

QString CheckBoxList::getDisplayText() const
{
    return m_DisplayText;
}
