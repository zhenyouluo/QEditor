#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QFrame>

struct TexturesData
{
    QBrush* brush;
};

class TexturesArray : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int selectedColumn READ selectedColumn)
    Q_PROPERTY(int selectedRow READ selectedRow)

public:
    TexturesArray(int rows, int cols, QWidget* parent = 0);
    ~TexturesArray();

    QString cellContent(int row, int col) const;

    int selectedColumn() const { return selCol; }
    int selectedRow() const    { return selRow; }

    virtual void setCurrent(int row, int col);
    virtual void setSelected(int row, int col);

    QSize sizeHint() const;

    virtual void setCellBrush(int row, int col, const QBrush&);

    QBrush cellBrush(int row, int col);

    inline int cellWidth() const  { return cellw; }
    inline int cellHeight() const { return cellh; }
    inline int rowAt(int y) const { return y / cellh; }

    inline int columnAt(int x) const
    {
        if(isRightToLeft())
            return (ncols - (x / cellw) - 1);

        return (x / cellw);
    }

    inline int rowY(int row) const { return cellh * row; }

    inline int columnX(int column) const
    {
        if(isRightToLeft())
            return cellw * (ncols - column - 1);

        return cellw * column;
    }

    inline int numRows() const { return nrows; }
    inline int numCols() const { return ncols; }

    void setRows(const int count) { nrows = count; }
    void setCols(const int count) { ncols = count; }

    inline QSize TextureSize() const   { return textureSize; }
    inline QSize TextureMargin() const { return textureMargin; }

    void setTextureSize(const QSize size)
    {
        textureSize = size;

        cellw = textureSize.width();
        cellh = textureSize.height();
    }

    void setTextureMargin(const QSize margins)    { textureMargin = margins; }

    void addToolTip(const QString& text) { toolTipArray.append(text); }
    void clearToolTip()                  { toolTipArray.clear(); }

    inline QRect cellRect() const { return QRect(0, 0, cellw, cellh); }
    inline QSize gridSize() const { return QSize(ncols * cellw, nrows * cellh); }

    QRect cellGeometry(int row, int column)
    {
        QRect r;

        if(row >= 0 && row < nrows && column >= 0 && column < ncols)
            r.setRect(columnX(column) + textureMargin.width() * column, rowY(row) + textureMargin.height() * row, cellw, cellh);

        return r;
    }

    inline void updateCell(int row, int column) { update(cellGeometry(row, column)); }

signals:
    void selected(int row, int col);

protected:
    virtual void paintCell(QPainter*, int row, int col, const QRect&);
    virtual void paintCellContents(QPainter*, int row, int col, const QRect&);

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    void paintEvent(QPaintEvent*);

    bool event(QEvent*);

private:
    Q_DISABLE_COPY(TexturesArray)

    int nrows;
    int ncols;
    int cellw;
    int cellh;
    int curRow;
    int curCol;
    int selRow;
    int selCol;

    QSize textureSize;
    QSize textureMargin;

    QVector<QString> toolTipArray;

    TexturesData* d;
};

class TextureWell : public TexturesArray
{
public:
    TextureWell(QWidget* parent, int r, int c, QVector<QPair<QImage, QString>> vals, QSize textureIconSize, QSize textureIconMargin)
    : TexturesArray(r, c, parent)
    , mousePressed(false)
    , oldCurrent(-1, -1)
    {
        setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

        setTextureSize(textureIconSize);
        setTextureMargin(textureIconMargin);

        for(int i = 0; i < vals.count(); ++i)
        {
            values.append(vals.at(i).first);

            addToolTip(vals.at(i).second);
        }
    }

protected:
    void paintCellContents(QPainter*, int row, int col, const QRect&);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    QVector<QImage> values;

    bool mousePressed;

    QPoint pressPos;
    QPoint oldCurrent;
};

#endif // TABLEVIEW_H