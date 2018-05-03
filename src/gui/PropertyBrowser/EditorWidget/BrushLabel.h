#ifndef BRUSHLABEL_H
#define BRUSHLABEL_H

#include <QLabel>

class BrushLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BrushLabel(QWidget *parent = nullptr, QBrush brush = QBrush());

    QBrush brush() const;
    void setBrush(const QBrush &brush);

signals:
    void pressed();

public slots:

protected:
    virtual void paintEvent(QPaintEvent * pEvent);
    virtual void mousePressEvent(QMouseEvent *pEvent);

private:
    QBrush m_brush;
};

#endif // BRUSHLABEL_H
