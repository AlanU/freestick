package org.freestick;
import android.hardware.input.InputManager;
import android.util.Log;
public class FreestickDeviceManager implements InputManager.InputDeviceListener{

    static
    {
        System.loadLibrary("gnustl_shared");
       // System.loadLibrary("FreeStick"); // Load native library at runtime
     }
     public native void gamepadWasAdded(int deviceid);

     public native void gamepadWasRemoved(int deviceid);

     public FreestickDeviceManager()
     {
        Log.w("FreeStick", "Was Created");
         gamepadWasAdded(0);
         Log.w("FreeStick", "gamepadWasAdded");
     }

     public void onInputDeviceAdded(int deviceid)
     {
       gamepadWasAdded(deviceid);
     }

     public void onInputDeviceRemoved(int deviceId)
     {

       gamepadWasRemoved(deviceId);
     }

     public void onInputDeviceChanged(int deviceId)
     {

     }





}
