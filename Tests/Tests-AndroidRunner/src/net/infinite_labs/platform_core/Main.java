package net.infinite_labs.platform_core;

import net.infinite_labs.platform_core.TestRunner.Outcome;
import android.app.ListActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;

public class Main extends ListActivity implements TestRunner.ResultsReceiver
{
	ArrayAdapter<Outcome> adapter;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        adapter = new ArrayAdapter<Outcome>(this, android.R.layout.simple_list_item_1);
        
        setListAdapter(adapter);
        adapter.clear();
        
        new Thread(new Runnable() {
			
			public void run() {
				new TestRunner(Main.this).run();
			}
			
		}).start();
    }

	public void testPerformed(final Outcome o) {
		runOnUiThread(new Runnable() {
			
			public void run() {
				adapter.add(o);
			}
			
		});
	}
}
