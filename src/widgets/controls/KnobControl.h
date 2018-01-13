#pragma once

#include <QtWidgets/QGraphicsObject>

namespace AxiomModel {
    class NodeValueControl;
}

namespace AxiomGui {

    class NodeItem;

    class KnobControl : public QGraphicsObject {
    Q_OBJECT
    public:
        AxiomModel::NodeValueControl *control;
        NodeItem *parent;

        KnobControl(AxiomModel::NodeValueControl *control, NodeItem *parent);

        QRectF boundingRect() const override;

        QRectF aspectBoundingRect() const;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    private slots:

        void setPos(QPoint newPos);

        void setSize(QSize newSize);

        void remove();

        void triggerGeometryChange();

        void valueChanged(float newVal);

    private:
        bool isDragging;
        float beforeDragVal;
        QPointF dragMouseStart;
    };

}
