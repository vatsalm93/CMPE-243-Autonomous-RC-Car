package com.example.techsavvy;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
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
import com.google.android.gms.maps.model.MarkerOptions;



public class MapsActivity extends AppCompatActivity implements OnMapReadyCallback, GoogleMap.OnMapLongClickListener {

    private Toolbar toolbar;
    private DrawerLayout drawerLayout;
    private NavigationView navigationView;
    private GoogleMap mMap;
    private ActionBar actionbar;
    ToggleButton toggleStart;


    double srcLat, srcLng, dstLat, dstLng;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);

        toolbar=(Toolbar) findViewById(R.id.toolBar);
        setSupportActionBar(toolbar);

        actionbar = this.getSupportActionBar();

        actionbar.setDisplayHomeAsUpEnabled(true);
        actionbar.setHomeAsUpIndicator(R.drawable.ic_menu);

        toggleStart = (ToggleButton) findViewById(R.id.mapButton);

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
        srcLat = intent.getDoubleExtra("latitude", 37.3352);
        srcLng = intent.getDoubleExtra("longitude", -121.8811);

        if(srcLat == 0.00 || srcLng == 0.00){
            srcLat = 37.3352;
            srcLng = -121.8811;
        }

        //Create Obj Location
        LatLng sourceLocation = new LatLng(srcLat , srcLng);

        //Round value to 2-decimal to test accuracy of GPS location
        //https://stackoverflow.com/questions/5945867/how-to-round-the-double-value-to-2-decimal-points
        /*double lat2Dec = (Math.round(srcLat * 100.0))/100.0;
        double long2Dec = (Math.round(srcLng * 100.0))/100.0;*/

        //Convert to string for logging the values
        String latitudeStr = String.valueOf(srcLat);
        String longitudeStr = String.valueOf(srcLng);
        String markerDisplay = "Lat: " + latitudeStr + "   Long: " + longitudeStr;
        Toast.makeText(this, markerDisplay, Toast.LENGTH_LONG).show();

        // Add a marker and move the camera
        mMap.addMarker(new MarkerOptions().position(sourceLocation).title(markerDisplay));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(sourceLocation, 15));
    }

    @Override
    public void onMapLongClick(LatLng latLng) {
        //Clear Map to remove previous markers
        mMap.clear();
        dstLat = latLng.latitude;
        dstLng = latLng.longitude;

        //Round value to 2-decimal to test accuracy of GPS location
        //https://stackoverflow.com/questions/5945867/how-to-round-the-double-value-to-2-decimal-points
        double lat2Dec = (Math.round(dstLat * 1000000.0))/1000000.0;
        double long2Dec = (Math.round(dstLng * 1000000.0))/1000000.0;

        //Convert to string for logging the values
        String latitudeStr = String.valueOf(dstLat);
        String longitudeStr = String.valueOf(dstLng);
        String toastDisplay = "Dest - Lat: " + latitudeStr + "   Long: " + longitudeStr;
        Toast.makeText(this, toastDisplay, Toast.LENGTH_LONG).show();

        // Add source marker
        LatLng Source = new LatLng(srcLat , srcLng);
        mMap.addMarker(new MarkerOptions().position(Source).title("Source"));

        //Add destination marker.. Make it Green color
        latitudeStr = String.valueOf(lat2Dec);
        longitudeStr = String.valueOf(long2Dec);
        String markerDisplay = "Dest - Lat: " + latitudeStr + "   Long: " + longitudeStr;
        mMap.addMarker(new MarkerOptions().position(latLng).title(markerDisplay).icon(BitmapDescriptorFactory
                .defaultMarker(BitmapDescriptorFactory.HUE_GREEN)));
    }

    public void startButton2OnClick(View view) {
        Toast.makeText(this, "Button pressed", Toast.LENGTH_LONG).show();

        //Intent intent = new Intent(getApplicationContext(), Bluetooth.class);

        //Send location to Maps
        /*intent.putExtra("latitude_destination", dstLat);
        intent.putExtra("longitude_destination", dstLng);*/

        Bluetooth.dstLat = dstLat;
        Bluetooth.dstLng = dstLng;
        Bluetooth.flagStartButtonPressed = true;
    }

    public void onToggleClicked(View view) {
        // Is the toggle on?
        boolean on = ((ToggleButton) view).isChecked();
        if (on) {
            Bluetooth.cmdStartStop = "S1";
            Toast.makeText(this, "Button pressed", Toast.LENGTH_LONG).show();

            //Intent intent = new Intent(getApplicationContext(), Bluetooth.class);

            //Send location to Maps
        /*intent.putExtra("latitude_destination", dstLat);
        intent.putExtra("longitude_destination", dstLng);*/

            Bluetooth.dstLat = dstLat;
            Bluetooth.dstLng = dstLng;
            Bluetooth.flagStartButtonPressed = true;
        } else {
            Bluetooth.cmdStartStop = "S0";
        }
    }
}

