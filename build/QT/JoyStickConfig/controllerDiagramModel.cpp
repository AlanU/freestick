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

float ControllerDiagramModel::centerButton() const
{
    return m_centerButton;
}

void ControllerDiagramModel::setcenterButton(float value)
{
    m_centerButton = value;
    emit centerButtonChanged(value);
}

float ControllerDiagramModel::startButton() const
{
    return m_startButton;
}

void ControllerDiagramModel::setstartButton(float value)
{
    m_startButton = value;
    emit startButtonChanged(value);
}

float ControllerDiagramModel::selectButton() const
{
    return m_selectButton;
}

void ControllerDiagramModel::setl1Button(float value)
{
    m_l1Button = value;
    emit l1ButtonChanged(value);
}

float ControllerDiagramModel::l1Button() const
{
    return m_l1Button;
}
void ControllerDiagramModel::setl2Button(float value)
{
    m_l2Button = value;
    emit l2ButtonChanged(value);
}

float ControllerDiagramModel::l2Button() const
{
    return m_l2Button;
}

void ControllerDiagramModel::setr1Button(float value)
{
    m_r1Button = value;
    emit r1ButtonChanged(value);
}

float ControllerDiagramModel::r1Button() const
{
    return m_r1Button;
}
void ControllerDiagramModel::setr2Button(float value)
{
    m_r2Button = value;
    emit r2ButtonChanged(value);
}

float ControllerDiagramModel::r2Button() const
{
    return m_r2Button;
}


void ControllerDiagramModel::setselectButton(float value)
{
    m_selectButton = value;
    emit selectButtonChanged(value);
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

float ControllerDiagramModel::leftTrigger() const
{
    return m_leftTrigger;
}

void  ControllerDiagramModel::setleftTrigger(float value)
{
    m_leftTrigger = value;
    emit leftTriggerChanged(value);
}

float ControllerDiagramModel::rightTrigger() const
{
    return m_rightTrigger;
}

void ControllerDiagramModel::setrightTrigger(float value)
{
    m_rightTrigger = value;
    emit rightTriggerChanged(value);
}

bool ControllerDiagramModel::hasControl(FSDeviceInput inputToLookFor)
{
   if(!m_manager.expired())
   {
       return m_manager.lock()->doesDeviceHaveDeviceInput(m_joystickId,inputToLookFor);
   }
   return false;
}

bool ControllerDiagramModel::hasTriggers()
{
  return hasControl(Trigger1) && hasControl(Trigger2);
}

bool ControllerDiagramModel::hasStart()
{
    return hasControl(ButtonStart);
}

bool ControllerDiagramModel::hasCenter()
{
    return hasControl(ButtonCenter);
}

bool ControllerDiagramModel::hasAxis1()
{
    return hasControl(XAxis);
}

bool ControllerDiagramModel::hasAxis2()
{
     return hasControl(XAxis2);
}

bool ControllerDiagramModel::hasBackShoulder()
{
     return hasControl(LeftShoulder2) && hasControl(RightShoulder2);
}

bool ControllerDiagramModel::hasFrontShoulder()
{
     return hasControl(LeftShoulder) && hasControl(RightShoulder);
}

bool ControllerDiagramModel::hasYXButtons()
{
     return hasControl(ButtonY) && hasControl(ButtonX);
}

bool ControllerDiagramModel::hasAxis1Button()
{
     return hasControl(Axis1Button);
}

bool ControllerDiagramModel::hasAxis2Button()
{
     return hasControl(Axis2Button);
}

void ControllerDiagramModel::updateControllerValues(FSDeviceInputEvent & event,bool pressed)
{
    if(m_joystickId == event.getDeviceID())
    {
        //TODO support presser sentive buttons
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
        case FSDeviceInput::ButtonCenter:
                setcenterButton(digitalButtonValue);
            break;
        case FSDeviceInput::ButtonStart:
                setstartButton(digitalButtonValue);
            break;
        case FSDeviceInput::ButtonSelect:
                setselectButton(digitalButtonValue);
            break;
         case FSDeviceInput::LeftShoulder:
                setl1Button(digitalButtonValue);
            break;
        case FSDeviceInput::LeftShoulder2:
               setl2Button(digitalButtonValue);
           break;
        case FSDeviceInput::RightShoulder:
               setr1Button(digitalButtonValue);
           break;
       case FSDeviceInput::RightShoulder2:
              setr2Button(digitalButtonValue);
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
         case FSDeviceInput::Trigger1:
            setleftTrigger(event.getNewInputValue());
            break;
         case FSDeviceInput::Trigger2:
             setrightTrigger(event.getNewInputValue());
            break;
        default:
            break;
        }

    }
}
