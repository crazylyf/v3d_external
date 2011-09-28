#include "NeuronContextMenu.h"

NeuronContextMenu::NeuronContextMenu(QWidget *parent) :
    QMenu(parent)
{
    neuronTitleAction = new QAction("(no neuron specified)", this);
    neuronTitleAction->setEnabled(false);

    showOnlyThisNeuronAction = new NeuronQAction(
            "View only this neuron in empty space",
            this);
    showOnlyThisNeuronAction->setIcon(QIcon(":/icons/neuronwobg.svg"));

    showOnlyThisNeuronWithBackgroundAction = new NeuronQAction(
            "View only this neuron with background",
            this);
    showOnlyThisNeuronWithBackgroundAction->setIcon(QIcon(":/icons/neuronwbg.svg"));

    showOnlyThisNeuronWithReferenceAction = new NeuronQAction(
            "View only this neuron with reference",
            this);
    showOnlyThisNeuronWithReferenceAction->setIcon(QIcon(":/icons/neuronwref.svg"));

    showOnlyThisNeuronWithBackgroundAndReferenceAction = new NeuronQAction(
            "View only this neuron with background and reference",
            this);
    showOnlyThisNeuronWithBackgroundAndReferenceAction->setIcon(QIcon(":/icons/neuronwbgref.svg"));

    addAction(neuronTitleAction);
    addAction(showOnlyThisNeuronAction);
    addAction(showOnlyThisNeuronWithBackgroundAction);
    addAction(showOnlyThisNeuronWithReferenceAction);
    addAction(showOnlyThisNeuronWithBackgroundAndReferenceAction);
}

QAction* NeuronContextMenu::exec(const QPoint& pos, int neuronIndex)
{
    neuronTitleAction->setText(QString("Neuron fragment %1").arg(neuronIndex));
    QAction* act = QMenu::exec(pos, NULL);
    NeuronQAction* nact = dynamic_cast<NeuronQAction*>(act);
    if (nact)
        nact->triggerWithIndex(neuronIndex);
    return act;
}

void NeuronContextMenu::connectActions(const NeuronSelectionModel& neuronSelectionModel)
{
    connect(showOnlyThisNeuronAction, SIGNAL(triggeredWithIndex(int)),
            &neuronSelectionModel, SLOT(showExactlyOneNeuronInEmptySpace(int)));
    connect(showOnlyThisNeuronWithBackgroundAction, SIGNAL(triggeredWithIndex(int)),
            &neuronSelectionModel, SLOT(showExactlyOneNeuronWithBackground(int)));
    connect(showOnlyThisNeuronWithReferenceAction, SIGNAL(triggeredWithIndex(int)),
            &neuronSelectionModel, SLOT(showExactlyOneNeuronWithReference(int)));
    connect(showOnlyThisNeuronWithBackgroundAndReferenceAction, SIGNAL(triggeredWithIndex(int)),
            &neuronSelectionModel, SLOT(showExactlyOneNeuronWithBackgroundAndReference(int)));
}



