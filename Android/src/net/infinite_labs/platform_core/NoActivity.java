package net.infinite_labs.platform_core;

import android.app.Activity;
import android.os.Bundle;

public class NoActivity extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }
}
