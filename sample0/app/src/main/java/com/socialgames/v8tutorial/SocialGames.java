package com.socialgames.v8tutorial;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class SocialGames extends Activity {


    TextView tv = null;

    static {
        System.loadLibrary("socialgames");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        View main = getLayoutInflater().inflate(R.layout.layout, null);
        this.setContentView(main);

        tv = findViewById(R.id.version);
        tv.setText("");

        InitializeV8();
    }

    /**
     * called from native.
     * @param version a string containing v8 compilation version.
     */
    public void setVersion( String version ) {
        tv.setText(version);
    }

    public native void InitializeV8();
}


