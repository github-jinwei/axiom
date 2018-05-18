#include "MidiControl.h"

#include "compiler/runtime/Control.h"
#include "compiler/runtime/ControlGroup.h"

using namespace AxiomModel;

MidiControl::MidiControl(const QUuid &uuid, const QUuid &parentUuid, QPoint pos, QSize size, bool selected,
                         QString name, bool showName, AxiomModel::ModelRoot *root)
    : Control(ControlType::MIDI_SCALAR, ConnectionWire::WireType::MIDI, uuid, parentUuid, pos, size, selected,
              std::move(name), showName, root) {
}

std::unique_ptr<MidiControl> MidiControl::create(const QUuid &uuid, const QUuid &parentUuid, QPoint pos, QSize size,
                                                 bool selected, QString name, bool showName,
                                                 AxiomModel::ModelRoot *root) {
    return std::make_unique<MidiControl>(uuid, parentUuid, pos, size, selected, std::move(name), showName, root);
}

std::unique_ptr<MidiControl> MidiControl::deserialize(QDataStream &stream, const QUuid &uuid, const QUuid &parentUuid,
                                                      QPoint pos, QSize size, bool selected, QString name,
                                                      bool showName, AxiomModel::ModelRoot *root) {
    return create(uuid, parentUuid, pos, size, selected, std::move(name), showName, root);
}

void MidiControl::serialize(QDataStream &stream, const QUuid &parent, bool withContext) const {
    Control::serialize(stream, parent, withContext);
}

void MidiControl::setValue(const MaximRuntime::MidiValue &value) {
    setInternalValue(value);
    restoreValue();
}

void MidiControl::doRuntimeUpdate() {
    saveValue();
}

void MidiControl::saveValue() {
    if (!runtime() || !(*runtime())->group()) return;
    setInternalValue((*runtime())->group()->getMidiValue());
}

void MidiControl::restoreValue() {
    if (!runtime() || !(*runtime())->group()) return;
    (*runtime())->group()->setMidiValue(_value);
}

void MidiControl::setInternalValue(MaximRuntime::MidiValue value) {
    if (value != _value) {
        _value = value;
        valueChanged.trigger(value);
    }
}
