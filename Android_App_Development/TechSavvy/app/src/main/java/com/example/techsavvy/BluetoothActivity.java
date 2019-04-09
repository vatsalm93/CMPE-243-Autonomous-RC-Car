package com.example.techsavvy;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class BluetoothActivity extends AppCompatActivity implements AdapterView.OnItemClickListener {
    ListView listView;
    TextView statusTextView ;
    Button searchButton,onOffButton;
    BluetoothAdapter bluetoothAdapter;
    public DeviceListAdapter mDeviceListAdapter;
    ListView lvNewDevices;

    ArrayList<BluetoothDevice> bluetoothDevices = new ArrayList<>();
    //ArrayList<String> addresses = new ArrayList<>();
    //ArrayAdapter arrayAdapter ;
    private static String TAG = "BluetoothActiviy";

    private final BroadcastReceiver broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            Log.i(TAG, action.toString());
            if(BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)){
                statusTextView.setText("Finished");
                searchButton.setEnabled(true);
            }else if(BluetoothDevice.ACTION_FOUND.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE );
                //String name = device.getName();
                //String address = device.getAddress();
                //String rssi = Integer.toString( intent.getShortExtra(BluetoothDevice.EXTRA_RSSI, Short.MIN_VALUE));
                //Log.i(TAG, "Name: " + name + " Address: "+ address + " RSSI:" + rssi);
//                if(!addresses.contains(address)){
//                    addresses.add(address);
//                    String deviceString = "";
//                    if(name == null || name.equals("")){
//                        deviceString = address + " - RSSI " + rssi + "dBm";
//                    }
//                    else{
//                        deviceString = name + " - RSSI " + rssi + "dBm";
//                    }
                    bluetoothDevices.add(device);
                    //arrayAdapter.notifyDataSetChanged();
                    mDeviceListAdapter = new DeviceListAdapter(context, R.layout.device_adapter_view, bluetoothDevices);
                    lvNewDevices.setAdapter(mDeviceListAdapter);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth);

        lvNewDevices = (ListView) findViewById(R.id.lvNewDevices);
        statusTextView = findViewById(R.id.textView1);
        searchButton = findViewById(R.id.searchButton);
        onOffButton = findViewById(R.id.onOffButton);
        bluetoothDevices = new ArrayList<>();
        //arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, bluetoothDevices);

        //listView.setAdapter(arrayAdapter);
        lvNewDevices.setOnItemClickListener(BluetoothActivity.this);
        int MY_PERMISSION_RESPONSE = 2;
        if (ContextCompat.checkSelfPermission(BluetoothActivity.this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(BluetoothActivity.this, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},MY_PERMISSION_RESPONSE);
        }

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);

        getApplicationContext().registerReceiver(broadcastReceiver, intentFilter);

        onOffButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(bluetoothAdapter == null)
                {
                    statusTextView.setText("Bluetooth is not available");
                }
                if (!bluetoothAdapter.isEnabled()) {
                    Intent turnOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                    startActivityForResult(turnOn, 0);
                    Toast.makeText(getApplicationContext(), "Turned on",Toast.LENGTH_LONG).show();
                    Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
                    discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION,300);
                    startActivity(discoverableIntent);

                    IntentFilter BTintent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
                    registerReceiver(broadcastReceiver,BTintent);
                }
                if (bluetoothAdapter.isEnabled())
                {
                    bluetoothAdapter.disable();
                    Toast.makeText(getApplicationContext(), "Turned off" ,Toast.LENGTH_LONG).show();
                    IntentFilter BTintent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
                    registerReceiver(broadcastReceiver,BTintent);
                }

            }
        });

        searchButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                statusTextView.setText("Searching...");
                searchButton.setEnabled(false);
                bluetoothDevices.clear();
                //addresses.clear();
                bluetoothAdapter.startDiscovery();
            }
        });
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        bluetoothAdapter.cancelDiscovery();
        Log.d(TAG,"Onclick item: You clicked on item");
        String deviceName = bluetoothDevices.get(position).getName();
        String deviceAddress = bluetoothDevices.get(position).getAddress();
        if(Build.VERSION.SDK_INT > Build.VERSION_CODES.JELLY_BEAN_MR2){
            Log.d(TAG, "Trying to pair with " + deviceName);
            bluetoothDevices.get(position).createBond();
            Toast.makeText(getApplicationContext(), "Connected to "+ deviceName,Toast.LENGTH_LONG).show();
        }

    }
}
