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

    public native void gamepadDeviceUpdate(int deviceid, int code, int type, float value, int min,
            int max);

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

    public void handelMotionEvent(MotionEvent event) {
        if (((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) != 0)
                && (event.getAction() == MotionEvent.ACTION_MOVE)) {
            Log.w("FreeStick", "handelMotionEvent" + event.toString());
            final int pointerCount = event.getPointerCount();
            // Log.w("FreeStick","At time :" + event.getEventTime());
            for (int p = 0; p < pointerCount; p++) {
                // Log.w("FreeStick","  pointer " + event.getPointerId(p) +":"+
                // "(" + event.getX(p) +"," + event.getY(p) + ")" );
            }
            // gamepadDeviceUpdate(event.getDeviceId(),code,1,value,-1,1);
        }

    }

    public boolean handelButtonEvent(KeyEvent event) {
        if (event.getAction() == KeyEvent.ACTION_UP || event.getAction() == KeyEvent.ACTION_DOWN) {
            Log.w("FreeStick", "handelButtonEvent" + event.toString());
            float value = event.getAction();
            int code = event.getKeyCode();
            Log.w("FreeStick", "calling gamepadDeviceUpdate");
            gamepadDeviceUpdate(event.getDeviceId(), code, 0, value, 0, 1);
            Log.w("FreeStick", "Back From calling gamepadDeviceUpdate");
            if (code != KeyEvent.KEYCODE_BACK) {
                return true;
            }

        }
        return false;
    }

    public void checkForNewJoysticks(InputManager inputManger) {
        if (inputManger != null) {
            int[] ids = InputDevice.getDeviceIds();// inputManger.getInputDeviceIds();
            Log.w("FreeStick", "checkForNewJoysticks lengthe" + ids.length);

            for (int i = 0; i < ids.length; i++) {
                Log.w("FreeStick", "java found device id " + ids[i] + " at " + i);
                InputDevice currentDevice = InputDevice.getDevice(ids[i]); // inputManger.getInputDevice(ids[i]);
                int sources = currentDevice.getSources();

                if (((sources & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
                        || ((sources & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK)
                        || ((sources & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD)
                        && !((sources & InputDevice.SOURCE_KEYBOARD) == InputDevice.SOURCE_KEYBOARD)) {
                    if (!currentDevice.isVirtual()) {
                        this.onInputDeviceAdded(ids[i]);
                        Log.w("FreeStick", "device on resume " + currentDevice.toString());
                    }

                }
            }
        }

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
