#pragma once

#include "../ModelObject.h"
#include "../PoolOperators.h"
#include "../WireGrid.h"
#include "../grid/GridSurface.h"
#include "common/Event.h"
#include "common/WatchSequence.h"
#include <editor/model/ModelRoot.h>

namespace MaximCompiler {
    class Runtime;
    class Transaction;
}

namespace AxiomModel {

    class Node;

    class Control;

    class Connection;

    class NodeSurface : public ModelObject {
        using InternalChildCollection = FindChildrenWatchSequence<ModelRoot::NodeCollection>;
        using InternalConnectionCollection = FindChildrenWatchSequence<ModelRoot::ConnectionCollection>;

    public:
        using ChildCollection = AxiomCommon::RefWatchSequence<InternalChildCollection>;
        using ConnectionCollection = AxiomCommon::RefWatchSequence<InternalConnectionCollection>;

        AxiomCommon::Event<const QString &> nameChanged;
        AxiomCommon::Event<const QPointF &> panChanged;
        AxiomCommon::Event<float> zoomChanged;

        NodeSurface(const QUuid &uuid, const QUuid &parentUuid, QPointF pan, float zoom, AxiomModel::ModelRoot *root);

        ChildCollection nodes();

        ConnectionCollection connections();

        GridSurface &grid() { return _grid; }

        const GridSurface &grid() const { return _grid; }

        WireGrid &wireGrid() { return _wireGrid; }

        const WireGrid &wireGrid() const { return _wireGrid; }

        virtual QString name() = 0;

        virtual bool canExposeControl() const = 0;

        virtual bool canHavePortals() const = 0;

        QPointF pan() const { return _pan; }

        void setPan(QPointF pan);

        float zoom() const { return _zoom; }

        void setZoom(float zoom);

        AxiomCommon::BoxedSequence<ModelObject *> getCopyItems();

        virtual uint64_t getRuntimeId() = 0;

        virtual void attachRuntime(MaximCompiler::Runtime *runtime, MaximCompiler::Transaction *transaction);

        void updateRuntimePointers(MaximCompiler::Runtime *runtime, void *surfacePtr);

        void build(MaximCompiler::Transaction *transaction) override;

        void doRuntimeUpdate() override;

        void remove() override;

    private:
        InternalChildCollection _nodes;
        InternalConnectionCollection _connections;
        GridSurface _grid;
        WireGrid _wireGrid;
        QPointF _pan;
        float _zoom;

        MaximCompiler::Runtime *_runtime = nullptr;

        void nodeAdded(Node *node) const;
    };
}
