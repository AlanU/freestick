#include "controllerDiagramModel.h"

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

float ControllerDiagramModel::upDpad() const
{
    return m_upDpad;
}

void ControllerDiagramModel::setupDpad(float value)
{
    m_upDpad = value;
    emit upDpadChanged(value);
}

float ControllerDiagramModel::downDpad() const
{
    return m_downDpad;
}

void ControllerDiagramModel::setdownDpad(float value)
{
    m_downDpad = value;
    emit downDpadChanged(value);
}

float ControllerDiagramModel::leftDpad() const
{
    return m_leftDpad;
}

void ControllerDiagramModel::setleftDpad(float value)
{
    m_leftDpad = value;
    emit leftDpadChanged(value);
}

float ControllerDiagramModel::rightDpad() const
{
    return m_rightDpad;
}

void ControllerDiagramModel::setrightDpad(float value)
{
    m_rightDpad = value;
    emit rightDpadChanged(value);
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

float ControllerDiagramModel::axisButton() const
{
    return m_axisButton;
}

void ControllerDiagramModel::setaxisButton(float value)
{
    m_axisButton = value;
    emit axisButtonChanged(value);
}

float ControllerDiagramModel::xAxis() const
{
    return m_xAxis;
}

void  ControllerDiagramModel::setxAxis(float value)
{
    m_xAxis = value;
    emit xAxisChanged(value);
}

float ControllerDiagramModel::yAxis() const
{
    return m_yAxis;
}

void  ControllerDiagramModel::setyAxis(float value)
{
    m_yAxis = value;
    emit yAxisChanged(value);
}

float ControllerDiagramModel::axis2Button() const
{
    return m_axis2Button;
}

void ControllerDiagramModel::setaxis2Button(float value)
{
    m_axis2Button = value;
    emit axis2ButtonChanged(value);
}

float ControllerDiagramModel::xAxis2() const
{
    return m_xAxis2;
}

void  ControllerDiagramModel::setxAxis2(float value)
{
    m_xAxis2 = value;
    emit xAxis2Changed(value);
}

float ControllerDiagramModel::yAxis2() const
{
    return m_yAxis2;
}

void  ControllerDiagramModel::setyAxis2(float value)
{
    m_yAxis2 = value;
    emit yAxis2Changed(value);
}

void ControllerDiagramModel::updateControllerValues(FSDeviceInputEvent & event,bool pressed)
{
    if(m_joystickId == event.getDeviceID())
    {
        float digitalButtonValue = pressed ? 1 : 0;
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
        case FSDeviceInput::Axis1Button:
                setaxisButton(event.getNewInputValue());
            break;
        case FSDeviceInput::Axis2Button:
                setaxis2Button(event.getNewInputValue());
            break;
        case FSDeviceInput::DPadUp:
                setupDpad(digitalButtonValue);
            break;
        case FSDeviceInput::DPadDown:
                setdownDpad(digitalButtonValue);
            break;
        case FSDeviceInput::DPadLeft:
                setleftDpad(digitalButtonValue);
            break;
        case FSDeviceInput::DPadRight:
                setrightDpad(digitalButtonValue);
            break;
        default:
            break;
        }
    }

}

void ControllerDiagramModel::onButtonDown(FSDeviceInputEvent event)
{
   updateControllerValues(event,true);
}

void ControllerDiagramModel::onButtonUp(FSDeviceInputEvent event)
{
    updateControllerValues(event,false);
}

void ControllerDiagramModel::onStickMove(FSDeviceInputEvent event)
{
    if(m_joystickId == event.getDeviceID())
    {
        switch (event.getInputType()) {
        case FSDeviceInput::XAxis:
            setxAxis(event.getNewInputValue());
            break;
        case FSDeviceInput::YAxis:
            setyAxis(event.getNewInputValue());
            break;
        case FSDeviceInput::XAxis2:
            setxAxis2(event.getNewInputValue());
            break;
        case FSDeviceInput::YAxis2:
            setyAxis2(event.getNewInputValue());
            break;
        default:
            break;
        }

    }
}
