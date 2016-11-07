## Persistenz

Zwei unterschiedliche Arten von Daten:

* Zustandsdaten der Views (aktuelle Eingabewerte, Checkboxes, etc.)
* Anwendungsdaten unserer Domain-Klassen

### View-Daten Persistieren

* Im Bundle-Object von ``onCreate`` und ``onSaveInstanceState``
* Geht nur mit Views, die eine ID haben

```java
public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);

       // Restore state...
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        // Save state...
       savedInstanceState.putInt(STATE_SCORE, mCurrentScore);
       savedInstanceState.putInt(STATE_LEVEL, mCurrentLevel);

       super.onSaveInstanceState(outState);
    }
}
```

Vorsicht: onSaveInstance wird nicht immer ausgeführt (bsp. kill, Back-Button)

### App-Daten Persistieren

#### Shared Preferences

```java
SharedPreferences settings = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
SharedPreferences.Editor editor = settings.edit();
editor.putBoolean("disabled", false);

// Nur boolean, float, int, long, String, Set möglich
boolean isDisabled = settings.getBoolean("disabled", false); // False als default

editor.commit();
```

Listener kann registriert werden...

#### Files
```java
// Auf interner / privater speicher schreiben
FileOutputStream fos = openFileOutput(FILENAME, Context.MODE_PRIVATE);
fos.write("File Content".getBytes());
fos.close();

// Auf "shared" Storage
// Braucht permission in manifest!
File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
File file = new File(path, "HSR_Cat.png");
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

#### Cloud

* firebase.google.com
* realm.io
* ...
