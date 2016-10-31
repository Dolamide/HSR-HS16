# Hintergrundtasks

Problem: Lang laufende Tasks blockieren den UI-Thread (bsp. Download).
Der Main/UI-Thread koordiniert Events, zeichnet GUI (Event-Loop - siehe Grundlagen)

```java
public void onClick(View v) {

Runnable runnable = new Runnable() {
   @Override
   public void run() {
       // Hier kann nicht auf UI zugegriffen werden!
       final Bitmap bitmap = download("http://slow.hsr.ch/hsr_cat.bmp");

       // command wird im UI-Thread ausgeführt
       Runnable command = new Runnable() {
           @Override
           public void run() {
               imageView.setImageBitmap(bitmap);
           }
       };
       imageView.post(command);
   }
};
Thread thread = new Thread(runnable);
thread.start();
}
```

## AsyncTask
Schönere Variante als oben!

```java
class DownloadBitmapTask extends AsyncTask<String, Integer, Bitmap> {
    @Override
    protected void onPreExecute() {
        // Wird im UI-Thread ausgeführt
        super.onPreExecute();
    }
    @Override
    protected Bitmap doInBackground(String... params) {
        // Background Task
        publishProgress(10);
        return download(params[0]);
    }
    @Override
    protected void onPostExecute(Bitmap bitmap) {
        // Wird im UI-Thread ausgeführt
        imageView.setImageBitmap(bitmap);
    }
    @Override
    protected void onProgressUpdate(Integer... values) {
        // Wird im UI-Thread ausgeführt
       progressBar.setProgress(values[0]);
    }
}

new DownloadBitmapTask().execute("http://slow.hsr.ch/hsr_cat.bmp");
// Evtl aufruf wie folgt, da sonst ClassCastException
new DownloadBitmapTask().execute(new String[]{"http://slow.hsr.ch/hsr_cat.bmp"});

```

## Services

Services dienen dazu, Aufgaben im Hintergrund auszuführen, deren Abarbeitung das UI zu lange blockieren würde wie Abspielen von Musik oder Laden von Daten über das Netzwerk.

Services laufen im UI-Thread - laufen aber weiter, wenn die App gewechselt wird.

Services werden im UI gestartet (einmalige Aufgabe, `startService(intent)`) oder gebunden (längere Zeitdauer, `bindService(intent, ...)`)

Vorsicht: Services sind keine eigenen Threads und müssen in der Manifest-Datei deklariert werden:

```xml
<application>
   <service
       android:name=".ExampleService"
       android:exported="false" />
        <!-- Dieser Service steht nur der eigenen App zur Verfügung -->
</application>
```

```java
// Service starten
Intent intent = new Intent(this, SimpleService.class);
startService(intent);
// Service stoppen
stopSelf();
```

!!! todo

    Bei Zeit/Notwendigkeit für Prüfung:

    * IntentService

### Bound Services
Beim Aufruf von `bindService()` erhält der Client ein Interface, um mit dem Service zu kommunizieren.

Nachdem alle Clients unbindService() aufgerufen haben, wird der Service beendet

!!! todo

    Einfaches Code-Sample aus den Übugen

### Datenrückgabe

* Variante Broadcast: Service verschickt und die Activity stellt einen Broadcast Receiver zur Verfügung, der Intent empfängt.
* Variante `PendingIntent` (nicht prüfungsrelveant)

### AsyncTask vs. Service

Mit dem AsyncTask kann eine Aufgabe *vom Main-Thread* entkopppelt werde

Ein Service entkopelt *von Context*

## Broadcasts
Das System verschickt Meldungen wie SMS empfangen, System wurde gebootet, Akku schwach, Power Connected usw. per Broadcast. Broadcast Receiver können registriert werden, um bestimmte Meldungenzu erhalten. Zudem können auch Apps Meldungen per Broadcast verschicken.

Können statisch in der Manifast...

```xml
<receiver android:name=".TimeChangedReceiver">
   <intent-filter>
       <action android:name="android.intent.action.TIME_SET" />
   </intent-filter>
</receiver>
```

... oder dynamisch in Java registriert werden.

```java
// Muss von BroadcastReceiver ableiten...
private class MyBroadcastReceiver extends BroadcastReceiver {
   public MyBroadcastReceiver(MainActivity activity) {
   }

   @Override
   public void onReceive(Context context, Intent intent) {
   }
}

// Anmelden
LocalBroadcastManager lbm = LocalBroadcastManager.getInstance(getApplicationContext());
IntentFilter filter = new IntentFilter(Intent.ACTION_BOOT_COMPLETED);

MyBroadcastReceiver receiver = new MyBroadcastReceiver(this);
lbm.registerReceiver(receiver, filter);

//Abmelden
LocalBroadcastManager lbm = LocalBroadcastManager.getInstance(this);
lbm.unregisterReceiver(receiver);
```

Statisch wird der Receiver wird bei jeder Meldung neu instanziert und ist somit an keine Activity gebunden.

Weiteres:

* Namensgebung der Action ist global, bei eigenen Actions Name mit eigenem Namespace verwenden
* Senden von eigenem Broadcast: `sendBroadcast(intent)`
* Beim Intent können unter Extras zusätzliche Daten hinterlegt werden
* LocalBroadcastManager um im selben Prozess zu senden

## Content Provider

Ein Content Provider stellt Daten prozessübergreifend zur Verfügung und stellt in der Regel Daten zur Verfügung, die in einer Datenbank abgelegt sind. Die Schnittstelle ähnelt stark der SQL-Syntax.

Bsp. Android stellt Daten über Content-Provider zur Verfügung: Kalender, Kontakte, ...


```java
Cursor cursor = getContentResolver().query(
       UserDictionary.Words.CONTENT_URI,
       mProjection,
       mSelectionClause,
       mSelectionArgs,
       mSortOrder);

int index = cursor.getColumnIndex(UserDictionary.Words.WORD);
while (cursor.moveToNext()) {
String word = cursor.getString(index);
}
```
