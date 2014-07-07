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
import android.view.InputDevice;
import android.view.InputDevice.MotionRange;
import android.view.KeyEvent;
import android.util.Log;
import android.content.Context;
import android.os.Bundle;
import android.view.MotionEvent;
public class JoyStickConfig extends org.qtproject.qt5.android.bindings.QtActivity
{
   private static InputManager m_inputManager;
   static FreestickDeviceManager m_deviceManager;
   public JoyStickConfig()
   {


   }

  public void onCreate(Bundle savedInstanceState)
  {
    m_inputManager = (InputManager)getSystemService(Context.INPUT_SERVICE);
    m_deviceManager = new FreestickDeviceManager();
    m_inputManager.registerInputDeviceListener(m_deviceManager, null);

    super.onCreate(savedInstanceState);
  }

   public boolean dispatchGenericMotionEvent(MotionEvent event)
   {

       m_deviceManager.handelMotionEvent(event);

        return super.dispatchGenericMotionEvent(event);
   }

  public boolean dispatchKeyEvent(KeyEvent event)
  {
     m_deviceManager.handelButtonEvent(event);
     return super.dispatchKeyEvent(event);
  }

  protected void onResume()
  {
       Log.w("FreeStick", "onResume");
      if(m_inputManager == null)
      {
          Log.w("FreeStick", "m_inputManager was null");

      }

      if(m_deviceManager != null)
        {
             Log.w("FreeStick", "registring device manager");
            // m_inputManager.registerInputDeviceListener(m_deviceManager, null);
             /*int[] ids = m_inputManager.getInputDeviceIds();
             for (int i = 0; i < ids.length; i++) {
                 InputDevice currentDevice = m_inputManager.getInputDevice(ids[i]);
             if((currentDevice.getSources() & InputDevice.SOURCE_GAMEPAD) != 0)
             {m_deviceManager.onInputDeviceAdded(ids[i]);}

             if((currentDevice.getSources() & InputDevice.SOURCE_JOYSTICK) != 0 )
                    {m_deviceManager.onInputDeviceAdded(ids[i]);}
             }*/
        }

      super.onResume();
  }

  protected void onPause()
  {
      if(m_deviceManager != null)
        {
          m_inputManager.unregisterInputDeviceListener(m_deviceManager);
        }
       super.onPause();

  }


}
