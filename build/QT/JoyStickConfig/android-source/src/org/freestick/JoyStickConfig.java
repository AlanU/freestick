package org.freestick;


import android.hardware.input.InputManager;
import android.util.Log;
import android.content.Context;
import android.os.Bundle;
public class JoyStickConfig extends org.qtproject.qt5.android.bindings.QtActivity
{
   private InputManager m_inputManager;
   static FreestickDeviceManager m_deviceManager;
   public JoyStickConfig()
   {


   }

  public void onCreate(Bundle savedInstanceState)
  {
      m_inputManager = (InputManager)getSystemService(Context.INPUT_SERVICE);


        m_deviceManager = new FreestickDeviceManager();

      super.onCreate(savedInstanceState);
  }

  protected void onResume()
  {
      if(m_inputManager == null)
      {
          Log.w("FreeStick", "m_inputManager was null");

      }

      if(m_deviceManager != null)
        {
             m_inputManager.registerInputDeviceListener(m_deviceManager, null);
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
