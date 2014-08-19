/*
The MIT License (MIT)

Copyright (c) 2014 (https://hackaday.io/project/2068-%2460-bluetooth-head-mounted-display.-)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
package com.hmdone.serialbluetooth;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Locale;
import java.util.Set;
import java.util.UUID;

import com.hmdone.serialbluetooth.R;

import android.app.ActionBar;
import android.app.FragmentTransaction;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.NavUtils;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends FragmentActivity implements
ActionBar.TabListener {
	static BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
	static BluetoothDevice mmDevice = null;
	static BluetoothSocket mmSocket = null; 
	static OutputStream mmOutputStream = null;
	static InputStream mmInputStream = null;

	/**
	 * The {@link android.support.v4.view.PagerAdapter} that will provide
	 * fragments for each of the sections. We use a
	 * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
	 * will keep every loaded fragment in memory. If this becomes too memory
	 * intensive, it may be best to switch to a
	 * {@link android.support.v4.app.FragmentStatePagerAdapter}.
	 */
	SectionsPagerAdapter mSectionsPagerAdapter;

	/**
	 * The {@link ViewPager} that will host the section contents.
	 */
	ViewPager mViewPager;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		// Set up the action bar.
		final ActionBar actionBar = getActionBar();
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

		// Create the adapter that will return a fragment for each of the three
		// primary sections of the app.
		mSectionsPagerAdapter = new SectionsPagerAdapter(
				getSupportFragmentManager());

		// Set up the ViewPager with the sections adapter.
		mViewPager = (ViewPager) findViewById(R.id.pager);
		mViewPager.setAdapter(mSectionsPagerAdapter);

		// When swiping between different sections, select the corresponding
		// tab. We can also use ActionBar.Tab#select() to do this if we have
		// a reference to the Tab.
		mViewPager
		.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
			@Override
			public void onPageSelected(int position) {
				actionBar.setSelectedNavigationItem(position);
			}
		});

		// For each of the sections in the app, add a tab to the action bar.
		for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
			// Create a tab with text corresponding to the page title defined by
			// the adapter. Also specify this Activity object, which implements
			// the TabListener interface, as the callback (listener) for when
			// this tab is selected.
			actionBar.addTab(actionBar.newTab()
					.setText(mSectionsPagerAdapter.getPageTitle(i))
					.setTabListener(this));
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onTabSelected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
		// When the given tab is selected, switch to the corresponding page in
		// the ViewPager.
		mViewPager.setCurrentItem(tab.getPosition());
	}

	@Override
	public void onTabUnselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	@Override
	public void onTabReselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	/**
	 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
	 * one of the sections/tabs/pages.
	 */
	public class SectionsPagerAdapter extends FragmentPagerAdapter {

		public SectionsPagerAdapter(FragmentManager fm) {
			super(fm);
		}

		@Override
		public Fragment getItem(int position) {
			// getItem is called to instantiate the fragment for the given page.
			// Return a DummySectionFragment (defined as a static inner class
			// below) with the page number as its lone argument.
			Fragment fragment = new DummySectionFragment();
			Bundle args = new Bundle();
			args.putInt(DummySectionFragment.ARG_SECTION_NUMBER, position + 1);
			fragment.setArguments(args);
			return fragment;
		}

		@Override
		public int getCount() {
			// Show 3 total pages.
			return 4;
		}

		@Override
		public CharSequence getPageTitle(int position) {
			Locale l = Locale.getDefault();
			switch (position) {
			case 0:
				return getString(R.string.title_section1).toUpperCase(l);
			case 1:
				return getString(R.string.title_section2).toUpperCase(l);
			case 2:
				return getString(R.string.title_section3).toUpperCase(l);
			case 3:
				return getString(R.string.title_section4).toUpperCase(l);
			}
			return null;
		}
	}

	/**
	 * A dummy fragment representing a section of the app, but that simply
	 * displays dummy text.
	 */
	public static class DummySectionFragment extends Fragment {
		/**
		 * The fragment argument representing the section number for this
		 * fragment.
		 */
		public static final String ARG_SECTION_NUMBER = "section_number";
		public DummySectionFragment() {
		}

		@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			View rootView = null;
			if(1 == getArguments().getInt(
					ARG_SECTION_NUMBER))
			{
				rootView =inflater.inflate(R.layout.tab1,
						container, false);
				Button send = (Button)rootView.findViewById(R.id.send_button);
				Button clear = (Button)rootView.findViewById(R.id.clear_button);
				clear.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View v) {
						if(null != mmOutputStream)
						{
							try {
								mmOutputStream.write("****CLR".getBytes());
								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}

					}
				});
				final EditText textbox = (EditText)rootView.findViewById(R.id.editText2);
				send.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View v) {
						if(null != mmOutputStream)
						{
							try {
								String text = textbox.getText().toString();
								if(!text.isEmpty())
								{
									String dispText = new String(text.getBytes(), "ASCII");
									mmOutputStream.write(dispText.replaceAll("[^\\p{Print}\\t\\n]", "").getBytes());
									mmOutputStream.flush();
									textbox.setText("");
								}

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}

					}
				});

			}else if(2 == getArguments().getInt(ARG_SECTION_NUMBER)){
				rootView = inflater.inflate(R.layout.tab2, container, false);
				Button connect = (Button)rootView.findViewById(R.id.connect);

				connect.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View arg0) {

						if(!mBluetoothAdapter.isEnabled())
						{
							Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
							startActivityForResult(enableBluetooth, 0);
						}
						Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
						if(pairedDevices.size() > 0)
						{
							for(BluetoothDevice device : pairedDevices)
							{
								System.out.println("DEVICE" + device.getName());
								if(device.getName().toLowerCase().contains("hc-05")) //Note, you will need to change this to match the name of your device
								{
									mmDevice = device;
									break;
								}
							}
						}else {
							System.out.println("DEVICE 0");

						}
						if(null != mmDevice)
						{
							UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID

							try {
								mmSocket = mmDevice.createInsecureRfcommSocketToServiceRecord(uuid);

								if(!mmSocket.isConnected())
									mmSocket.connect();
								mmOutputStream = mmSocket.getOutputStream();
								mmInputStream = mmSocket.getInputStream();	

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					};
				});
			}else if(3 == getArguments().getInt(ARG_SECTION_NUMBER))
			{

				rootView =inflater.inflate(R.layout.tab3,
						container, false);

				final Switch  sw1 = (Switch)rootView.findViewById(R.id.switch1);
				final Switch  sw2 = (Switch)rootView.findViewById(R.id.switch2);
				final Switch  sw3 = (Switch)rootView.findViewById(R.id.switch3);


				sw1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

					@Override
					public void onCheckedChanged(CompoundButton arg0, boolean arg1) {
						boolean checked = sw1.isChecked();
						if(null != mmOutputStream)
						{
							try {
								if(checked)
									mmOutputStream.write("****LED3".getBytes());
								else
									mmOutputStream.write("****LED6".getBytes());

								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}
					}
				});

				sw2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

					@Override
					public void onCheckedChanged(CompoundButton arg0, boolean arg1) {
						boolean checked = sw2.isChecked();
						if(null != mmOutputStream)
						{
							try {
								if(checked)
									mmOutputStream.write("****LED1".getBytes());
								else
									mmOutputStream.write("****LED4".getBytes());

								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}
					}
				});

				sw3.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

					@Override
					public void onCheckedChanged(CompoundButton arg0, boolean arg1) {
						boolean checked = sw3.isChecked();
						if(null != mmOutputStream)
						{
							try {
								if(checked)
									mmOutputStream.write("****LED2".getBytes());
								else
									mmOutputStream.write("****LED5".getBytes());

								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}
					}
				});

			}else if(4 == getArguments().getInt(ARG_SECTION_NUMBER))
			{
				rootView =inflater.inflate(R.layout.tab4,
						container, false);
				final Button button1 = (Button)rootView.findViewById(R.id.button1);
				final Button button2 = (Button)rootView.findViewById(R.id.button2);
				final Button button3 = (Button)rootView.findViewById(R.id.button3);

				button1.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View arg0) {
						if(null != mmOutputStream)
						{
							try {

								mmOutputStream.write("****SND1".getBytes());


								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}						

					}
				});

				button2.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View arg0) {
						if(null != mmOutputStream)
						{
							try {

								mmOutputStream.write("****SND2".getBytes());


								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}						

					}
				});

				button3.setOnClickListener(new OnClickListener() {

					@Override
					public void onClick(View arg0) {
						if(null != mmOutputStream)
						{
							try {

								mmOutputStream.write("****SND3".getBytes());


								mmOutputStream.flush();

							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}else {
							Log.e("TAB1", "mmOutputStream null");
						}						

					}
				});


			}
			else
			{
				rootView =inflater.inflate(R.layout.fragment_main_dummy,
						container, false);


				TextView dummyTextView = (TextView) rootView
						.findViewById(R.id.section_label);
				dummyTextView.setText(Integer.toString(getArguments().getInt(
						ARG_SECTION_NUMBER)));
			}
			return rootView;
		}
	}

}
