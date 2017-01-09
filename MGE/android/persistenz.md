## Persistenz

Zwei unterschiedliche Arten von Daten: **View-Daten Persitenz** (aktuelle Eingabewerte/Checkboxen) und **App-Daten Persistenz** (Domain-Klassen)

### View-Daten Persistieren

* Im Bundle-Object von ``onCreate`` und ``onSaveInstanceState``
* Geht nur mit Views, die eine ID haben
* Vorsicht: onSaveInstance wird nicht immer ausgeführt (bsp. kill, Back-Button)

```java
public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
       // Restore state...
       mCurrentScore = savedInstanceState.getInt(STATE_SCORE);
    }
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        // Save state...
       savedInstanceState.putInt(STATE_SCORE, mCurrentScore);
       super.onSaveInstanceState(outState);
    }
}
```

### App-Daten Persistieren
App-Daten immer in onPause sichern, da `onSaveInstanceState` nicht immer ausgeführt(bsp. kill, Back-Button)

#### Shared Preferences

```java
SharedPreferences settings = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
SharedPreferences.Editor editor = settings.edit();
editor.putBoolean("disabled", false);
// Nur boolean, float, int, long, String, Set möglich
boolean isDisabled = settings.getBoolean("disabled", false); // False als default
editor.commit();
```
#### SQLite

```java
public class DBHelper extends SQLiteOpenHelper {
    private static final int DATABASE_VERSION = 2;
    DBHelper(Context context) {
       super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
       db.execSQL("CREATE TABLE ...;");
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // schema update!
    }
}

DBHelper helper = new DBHelper(this);
SQLiteDatabase db = helper.getReadableDatabase();
db.execSQL("SELECT * FROM ...;");
```
#### Files
```java
// Auf interner / privater speicher schreiben (Methode openFileOutput auf Context (Activity extends Context))
FileOutputStream fos = openFileOutput(FILENAME, Context.MODE_PRIVATE);
fos.write("File Content".getBytes());
fos.close();
// Auf "shared" Storage (Braucht permission in manifest!)
File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
File file = new File(path, "HSR_Cat.png");
```


#### Cloud
firebase.google.com, realm.io usw. Nicht imer Verfügbar - braucht zwischenspeicher.
