package com.example.techsavvy;

import android.content.Intent;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }



    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        Intent intent = getIntent();
        //Get Longitude and Latitude Values
        double latitude = intent.getDoubleExtra("latitude", 37.3352);
        double longitude = intent.getDoubleExtra("longitude", -121.8811);

        //Round value to 2-decimal to test accuracy of GPS location
        //https://stackoverflow.com/questions/5945867/how-to-round-the-double-value-to-2-decimal-points
        double lat2Dec = (Math.round(latitude * 100.0))/100.0;
        double long2Dec = (Math.round(longitude * 100.0))/100.0;

        latitude = lat2Dec;
        longitude = long2Dec;

        //Convert to string for logging the values
        String latitudeStr = String.valueOf(latitude);
        String longitudeStr = String.valueOf(longitude);

        String markerDisplay = "Lat: " + latitudeStr + "   Long: " + longitudeStr;
        Toast.makeText(this, markerDisplay, Toast.LENGTH_LONG).show();

        // Add a marker in Sydney and move the camera
        LatLng SJSU = new LatLng(latitude , longitude);
        mMap.addMarker(new MarkerOptions().position(SJSU).title(markerDisplay));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(SJSU, 15));
    }
}
