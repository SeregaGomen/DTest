#ifndef CHECKBOXLIST_H
#define CHECKBOXLIST_H

#include <QComboBox>
#include <QItemDelegate>
#include <QApplication>
#include <QCheckBox>

class CheckBoxList: public QComboBox
{
    Q_OBJECT

private:
    QString m_DisplayText;

public:
    CheckBoxList(QWidget *widget = 0);
    virtual ~CheckBoxList() {}
    bool eventFilter(QObject *object, QEvent *event);
    virtual void paintEvent(QPaintEvent *);
    void setDisplayText(QString text);
    QString getDisplayText() const;
};

// internal private delegate
class CheckBoxListDelegate : public QItemDelegate
{
public:

    CheckBoxListDelegate(QObject *parent) : QItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        //Get item data
        bool value = index.data(Qt::UserRole).toBool();
        QString text = index.data(Qt::DisplayRole).toString();
        // fill style options with item data
        const QStyle *style = QApplication::style();
        QStyleOptionButton opt;

        opt.state |= value ? QStyle::State_On : QStyle::State_Off;
        opt.state |= QStyle::State_Enabled;
        opt.text = text;
        opt.rect = option.rect;

        // draw item data as CheckBox
        style->drawControl(QStyle::CE_CheckBox,&opt,painter);
        //QMessageBox::information(0,"Info",text);
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex & ) const
    {
        // create check box as our editor
        QCheckBox *editor = new QCheckBox(parent);

        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        //set editor data
        QCheckBox *myEditor = static_cast<QCheckBox*>(editor);

        myEditor->setText(index.data(Qt::DisplayRole).toString());
        myEditor->setChecked(index.data(Qt::UserRole).toBool());
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        //get the value from the editor (CheckBox)
        QCheckBox *myEditor = static_cast<QCheckBox*>(editor);
        bool value = myEditor->isChecked();
        QMap<int,QVariant> data;

        data.insert(Qt::DisplayRole,myEditor->text());
        data.insert(Qt::UserRole,value);
        model->setItemData(index,data);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & ) const
    {
        editor->setGeometry(option.rect);
    }
};


#endif // CHECKBOXLIST_H
