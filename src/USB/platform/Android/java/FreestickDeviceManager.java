package org.freestick;
import android.app.Activity;

public class FreestickDeviceManager extends Activity
{
    static {
        System.loadLibrary("FreeStick");
    }

}
