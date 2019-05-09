package com.example.techsavvy;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;



public class MapsActivity extends AppCompatActivity implements OnMapReadyCallback, GoogleMap.OnMapLongClickListener {

    private Toolbar toolbar;
    private DrawerLayout drawerLayout;
    private NavigationView navigationView;
    private GoogleMap mMap;
    private ActionBar actionbar;
    static ToggleButton toggleStart;
    static int cmdStartStop_intent = 0;
    static Marker srcMarker;
    static Marker dstMarker;
    static Marker currentMarker;
    boolean isDstSet = false;


    //double srcLat, srcLng, dstLat, dstLng;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);

        toolbar=(Toolbar) findViewById(R.id.toolBar);
        setSupportActionBar(toolbar);

        actionbar = this.getSupportActionBar();

        actionbar.setDisplayHomeAsUpEnabled(true);
        actionbar.setHomeAsUpIndicator(R.drawable.ic_menu);

        //toggleStart = (ToggleButton) findViewById(R.id.mapButton);

        navigationView = (NavigationView)findViewById(R.id.NavigationView);
        //Log.i(TAG, "Inside onCreate");

        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(MenuItem item) {
                switch(item.getItemId())
                {
                    case R.id.bt_func:
                        //Log.i(TAG, "Menu item clicked " + item.toString());
                        Intent intent2 = new Intent(getBaseContext(), Bluetooth.class);
                        startActivity(intent2);
                }
                return false;
            }
        });
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                //Log.i(TAG, "Menu item selected " + item.toString());
                drawerLayout=findViewById(R.id.drawer_layout);
                drawerLayout.openDrawer(GravityCompat.START);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }



    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        //mMap2 = googleMap;
        mMap.setOnMapLongClickListener(this);

        Intent intent = getIntent();
        //Get Longitude and Latitude Values
        Bluetooth.srcLat = intent.getDoubleExtra("latitude", 37.3352);
        Bluetooth.srcLng = intent.getDoubleExtra("longitude", -121.8811);

        if(Bluetooth.srcLat == 0.00 || Bluetooth.srcLng == 0.00){
            Bluetooth.srcLat = 37.3352;
            Bluetooth.srcLng = -121.8811;
        }

        //Create Obj Location
        LatLng sourceLocation = new LatLng(Bluetooth.srcLat , Bluetooth.srcLng);

        //Round value to 2-decimal to test accuracy of GPS location
        //https://stackoverflow.com/questions/5945867/how-to-round-the-double-value-to-2-decimal-points
        /*double lat2Dec = (Math.round(srcLat * 100.0))/100.0;
        double long2Dec = (Math.round(srcLng * 100.0))/100.0;*/

        //Convert to string for logging the values
        String latitudeStr = String.valueOf(Bluetooth.srcLat);
        String longitudeStr = String.valueOf(Bluetooth.srcLng);
        String markerDisplay = "Lat: " + latitudeStr + "   Long: " + longitudeStr;
        Toast.makeText(this, markerDisplay, Toast.LENGTH_LONG).show();

        // Add a marker and move the camera
        srcMarker = mMap.addMarker(new MarkerOptions().position(sourceLocation).title(markerDisplay));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(sourceLocation, 16));
    }

    @Override
    public void onMapLongClick(LatLng latLng) {
        //Clear Map to remove previous markers
        //mMap.clear();
        if(isDstSet)
        {
            dstMarker.remove();
        }
        else
            isDstSet = true;

        Bluetooth.dstLat = latLng.latitude;
        Bluetooth.dstLng = latLng.longitude;

        //Round value to 2-decimal to test accuracy of GPS location
        //https://stackoverflow.com/questions/5945867/how-to-round-the-double-value-to-2-decimal-points
        double lat2Dec = (Math.round(Bluetooth.dstLat * 1000000.0))/1000000.0;
        double long2Dec = (Math.round(Bluetooth.dstLng * 1000000.0))/1000000.0;

        //Convert to string for logging the values
        String latitudeStr = String.valueOf(Bluetooth.dstLat);
        String longitudeStr = String.valueOf(Bluetooth.dstLng);
        String toastDisplay = "Dest - Lat: " + latitudeStr + "   Long: " + longitudeStr;
        Toast.makeText(this, toastDisplay, Toast.LENGTH_SHORT).show();

        // Add source marker
        //LatLng Source = new LatLng(Bluetooth.srcLat , Bluetooth.srcLng);
        //LatLng currentPos = new LatLng(Bluetooth.currentLat , Bluetooth.currentLng);
        //srcMarker = mMap.addMarker(new MarkerOptions().position(Source).title("Source"));
        //dstMarker = mMap.addMarker(new MarkerOptions().position(currentPos).title("Current Position").icon(BitmapDescriptorFactory
                //.defaultMarker(BitmapDescriptorFactory.HUE_VIOLET)));


        //Add destination marker.. Make it Green color
        latitudeStr = String.valueOf(lat2Dec);
        longitudeStr = String.valueOf(long2Dec);
        String markerDisplay = "Dest - Lat: " + latitudeStr + "   Long: " + longitudeStr;
        dstMarker = mMap.addMarker(new MarkerOptions().position(latLng).title(markerDisplay).icon(BitmapDescriptorFactory
                .defaultMarker(BitmapDescriptorFactory.HUE_GREEN)));
    }

    public void startButton2OnClick(View view) {
        Toast.makeText(this, "Button pressed", Toast.LENGTH_SHORT).show();
        //Intent intent = new Intent(getApplicationContext(), Bluetooth.class);
        //if(cmdStartStop_intent == 0) {
        if(Bluetooth.cmdStartStop == false) {
            Bluetooth.cmdStartStop = true;
            //cmdStartStop_intent = 1;
            //intent.putExtra("start_stop_command", cmdStartStop_intent);
            //Bluetooth.dstLat = dstLat;
            //Bluetooth.dstLng = dstLng;
            Bluetooth.flagStartButtonPressed = true;
            Log.d("Toggle", "Start");
            //threadLiveLocation.start();
        }
        else if(Bluetooth.cmdStartStop == true)
        {
            Bluetooth.cmdStartStop = false;
            Log.d("Toggle","Stop");
            //cmdStartStop_intent = 0;
            Bluetooth.flagStartButtonPressed = true;
            //intent.putExtra("start_stop_command", cmdStartStop_intent);

        }
    }

    /*public void onToggleClicked(View view) {
        // Is the toggle on?
        boolean on = ((ToggleButton) view).isChecked();
        boolean cmdStartStop_intent;
        Intent intent = new Intent(getApplicationContext(), Bluetooth.class);
        if (on) {
            Bluetooth.cmdStartStop = true;
            cmdStartStop_intent = true;
            Toast.makeText(this, "Button pressed", Toast.LENGTH_LONG).show();

            intent.putExtra("start_stop_command", cmdStartStop_intent);




            Bluetooth.dstLat = dstLat;
            Bluetooth.dstLng = dstLng;
            Bluetooth.flagStartButtonPressed = true;
            Log.d("Toggle","Start");
        } else {
            Bluetooth.cmdStartStop = false;
            Log.d("Toggle","Stop");
            cmdStartStop_intent = false;
            intent.putExtra("start_stop_command", cmdStartStop_intent);
        }
    }*/

    /*Thread threadLiveLocation = new Thread() {
        @Override
        public void run() {
            try {
                while(true) {
                    sleep(1000);

                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    };*/


}

