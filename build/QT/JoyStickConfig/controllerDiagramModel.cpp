#include "controllerDiagramModel.h"
#include "qmlControllerModel.h"

ControllerDiagramModel::ControllerDiagramModel():BaseDeviceModel()
{

}

int  ControllerDiagramModel::joystickID()
{
    return m_joystickId;
}

void  ControllerDiagramModel::setJoystickID(unsigned int newID)
{
    m_joystickId = newID;
    updateModel(newID);
    emit joystickIDChanged(newID);
}

void ControllerDiagramModel::updateModel(unsigned int joystickID)
{
    if(!m_manager.expired() && m_manager.lock()->getDevice(joystickID))
    {
        beginResetModel();
        //Reset properties
        endResetModel();
    }
}

float ControllerDiagramModel::aButton() const
{
    return m_aButton;
}

void ControllerDiagramModel::setaButton(float value)
{
    m_aButton = value;
    emit aButtonChanged(value);
}

float ControllerDiagramModel::bButton() const
{
    return m_bButton;
}

void ControllerDiagramModel::setbButton(float value)
{
    m_bButton = value;
    emit bButtonChanged(value);
}

float ControllerDiagramModel::xButton() const
{
    return m_xButton;
}

void ControllerDiagramModel::setxButton(float value)
{
    m_xButton = value;
    emit xButtonChanged(value);
}

float ControllerDiagramModel::yButton() const
{
    return m_yButton;
}

void ControllerDiagramModel::setyButton(float value)
{
    m_yButton = value;
    emit yButtonChanged(value);
}


void ControllerDiagramModel::updateControllerValues(FSDeviceInputEvent & event)
{
    if(m_joystickId == event.getDeviceID())
    {
        switch (event.getInputType()) {
        case FSDeviceInput::ButtonA:
                setaButton(event.getNewInputValue());
            break;
        case FSDeviceInput::ButtonB:
                setbButton(event.getNewInputValue());
            break;
        case FSDeviceInput::ButtonX:
                setxButton(event.getNewInputValue());
            break;
        case FSDeviceInput::ButtonY:
                setyButton(event.getNewInputValue());
            break;
        default:
            break;
        }
    }

}

void ControllerDiagramModel::onButtonDown(FSDeviceInputEvent event)
{
   updateControllerValues(event);
}

void ControllerDiagramModel::onButtonUp(FSDeviceInputEvent event)
{
    updateControllerValues(event);
}

void ControllerDiagramModel::onStickMove(FSDeviceInputEvent /*event*/)
{

}
