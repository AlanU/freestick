/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
 **************************************************************************/

package org.freestick;

import android.hardware.input.InputManager;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class FreestickDeviceManager implements InputManager.InputDeviceListener {

    static {
        // System.loadLibrary("gnustl_shared");
        // System.loadLibrary("FreeStick"); // Load native library at runtime
    }

    public native void gamepadWasAdded(int deviceid);

    public native void gamepadWasRemoved(int deviceid);

    public native boolean gamepadDeviceUpdate(int deviceid, int code, int type, float value,
            int min, int max);

    public native void updateJoystickConnectedStatus();

    public FreestickDeviceManager() {
        Log.w("FreeStick Device", "Was Created");
    }

    @Override
    public void onInputDeviceAdded(int deviceid) {
        Log.w("FreeStick Device", "gamepadWasAdded " + deviceid);

        gamepadWasAdded(deviceid);
    }

    @Override
    public void onInputDeviceRemoved(int deviceId) {
        Log.w("FreeStick Device", "onInputDeviceRemoved");

        gamepadWasRemoved(deviceId);
    }

    @Override
    public void onInputDeviceChanged(int deviceId) {
        Log.w("FreeStick", "onInputDeviceChanged");

    }

    // taken from google's example
    // http://developer.android.com/training/game-controllers/controller-input.html
    private static float getCenteredAxis(MotionEvent event, InputDevice device, int axis,
            int historyPos) {
        final InputDevice.MotionRange range = device.getMotionRange(axis, event.getSource());

        // A joystick at rest does not always report an absolute position of
        // (0,0). Use the getFlat() method to determine the range of values
        // bounding the joystick axis center.
        if (range != null) {
            float flat = range.getFlat();
            if (flat == 0.0f) {
                flat = 0.004f;
            }
            final float value = historyPos < 0 ? event.getAxisValue(axis) : event
                    .getHistoricalAxisValue(axis, historyPos);

            // Ignore axis values that are within the 'flat' region of the
            // joystick axis center.
            if (Math.abs(value) > flat) {
                return value;
            }
        }
        return 0;
    }

    private boolean processAxisEvent(MotionEvent event, int hIndex, int motion_axis) {
        Log.w("FreeStick", "processAxisEvent" + motion_axis);

        InputDevice eventDevice = event.getDevice();
        if (motion_axis == MotionEvent.AXIS_X || motion_axis == MotionEvent.AXIS_Y
                || motion_axis == MotionEvent.AXIS_Z || motion_axis == MotionEvent.AXIS_RZ) {
            float axis = FreestickDeviceManager.getCenteredAxis(event, eventDevice, motion_axis,
                    hIndex);
            // if (axis != 0) {
            gamepadDeviceUpdate(event.getDeviceId(), motion_axis, 3, axis, -1, 1);
            // }
        } else {
            final float value = hIndex < 0 ? event.getAxisValue(motion_axis) : event
                    .getHistoricalAxisValue(motion_axis, hIndex);

            gamepadDeviceUpdate(event.getDeviceId(), motion_axis, 3, value, -1, 1);

        }
        return true;
    }

    public boolean handelMotionEvent(MotionEvent event) {
        boolean handed = false;
        if (((event.getSource() & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
                || ((event.getSource() & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK)
                || ((event.getSource() & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD)
                && (event.getAction() == MotionEvent.ACTION_MOVE))
        // if (((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) != 0)
        {
            Log.w("FreeStick", "handelMotionEvent : " + event.toString());
            InputDevice eventDevice = event.getDevice();
            final int historySize = event.getHistorySize();
            final int pointerCount = event.getPointerCount();
            for (int hIndex = 0; hIndex < historySize; hIndex++) {
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_X) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_Z) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_RZ) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_Y) || handed;

                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_RTRIGGER) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_THROTTLE) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_GAS) || handed;

                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_LTRIGGER) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_BRAKE) || handed;

                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_HAT_X) || handed;
                handed = this.processAxisEvent(event, hIndex, MotionEvent.AXIS_HAT_Y) || handed;

            }

            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_X) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_Z) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_RZ) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_Y) || handed;

            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_RTRIGGER) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_THROTTLE) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_GAS) || handed;

            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_LTRIGGER) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_BRAKE) || handed;

            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_HAT_X) || handed;
            handed = this.processAxisEvent(event, -1, MotionEvent.AXIS_HAT_Y) || handed;

        }
        return handed;

    }

    public boolean handelButtonEvent(KeyEvent event) {
        if (event.getAction() == KeyEvent.ACTION_UP || event.getAction() == KeyEvent.ACTION_DOWN) {
            Log.w("FreeStick", "handelButtonEvent : " + event.toString());
            float value = event.getAction();
            int code = event.getKeyCode();
            Log.w("FreeStick", "calling gamepadDeviceUpdate");
            boolean handled = gamepadDeviceUpdate(event.getDeviceId(), code, 2, value, 0, 1);
            Log.w("FreeStick", "Back From calling gamepadDeviceUpdate");
            if (handled) {
                return true;
            }

        }
        return false;
    }

    public void checkForNewJoysticks(InputManager inputManger) {

        updateJoystickConnectedStatus();

    }

    /*
     * c++ for handelButtonEvent void ProcessInputEvent(AInputEvent * event) {
     * int32_t type = AInputEvent_getType(event); if(type ==
     * AINPUT_EVENT_TYPE_KEY) { int32_t action = AKeyEvent_getAction(event);
     * if(action == AKEY_EVENT_ACTION_UP || action == AKEY_EVENT_ACTION_DOWN) {
     * float value = (float) action; int code = AKeyEvent_getKeyCode(event);
     * int32_t deviceID = AInputEvent_getDeviceId(event);
     * JNIBridge::updateValue(deviceID, code, 0, value,0,1); } } }
     */

}
