package ch.hsr.mge.rzi.calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText textField = (EditText) findViewById(R.id.textField);

        View.OnClickListener simpleInput = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textField.getText().append(((Button)v).getText());
            }
        };

        // Numbers
        ((Button) findViewById(R.id.oneButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.twoButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.threeButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.fourButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.fiveButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.sixButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.sevenButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.eightButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.nineButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.zeroButton)).setOnClickListener(simpleInput);

        ((Button) findViewById(R.id.decimalButton)).setOnClickListener(simpleInput);

        // Operators
        ((Button) findViewById(R.id.plusButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.minusButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.multiplyButton)).setOnClickListener(simpleInput);
        ((Button) findViewById(R.id.divideButton)).setOnClickListener(simpleInput);

        // Reset
        ((Button) findViewById(R.id.resetButton)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textField.getText().clear();
            }
        });

        // Equals
        ((Button) findViewById(R.id.resultButton)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textField.getText().clear();
                textField.getText().insert(0, "42");
            }
        });
    }
}
