package ch.hsr.mge.rzi.mailappw2;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class ComposeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_compose);

        final EditText from = (EditText) findViewById(R.id.fromEditText);
        final EditText to = (EditText) findViewById(R.id.toEditText);
        final EditText  subject = (EditText) findViewById(R.id.subjectEditText);
        final TextView message = (TextView) findViewById(R.id.messageTextView);;
        final Button send = (Button) findViewById(R.id.sendButton);

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send(from.getText().toString(),
                        to.getText().toString(),
                        subject.getText().toString(),
                        message.getText().toString());
            }
        });
    }
    private void send(String from, String to, String subject, String message) {

        Intent i = new Intent(Intent.ACTION_SEND);
        i.setType("message/rfc822");
        i.putExtra(Intent.EXTRA_EMAIL, new String[]{to});
        i.putExtra(Intent.EXTRA_SUBJECT, subject);
        i.putExtra(Intent.EXTRA_TEXT, message);
        try {
            startActivity(Intent.createChooser(i, "Send mail using ..."));
        } catch (android.content.ActivityNotFoundException ex) {
            Toast.makeText(ComposeActivity.this, "No email client found!", Toast.LENGTH_SHORT).show();
        }

    }
}
