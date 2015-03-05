package org.freestick;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;



public class JoystickNatvieActivity extends NativeActivity
{
    static
    {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("FreeStick"); // Load native library at runtime
        System.loadLibrary("native-activity");

    }

}

