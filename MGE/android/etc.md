## Weiterführende Themen

### Sensoren
* Unterstützung und Qualität von Gerät zu Gerät verschieden
* Kategorien:
    * Bewegungssensoren (Beschleunigung)
    * Umgebungssensoren (Temperatur, Beleuchtung)
    * Lagesensoren (Neigung, Kompass)

```java
public class MainActivity extends AppCompatActivity
    implements SensorEventListener { // Listener für onSensorChanged
    private Sensor lightSensor;
    private SensorManager sensorManager;
    protected void onCreate(Bundle savedInstanceState) {
        // ...
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        lightSensor = sensorManager.getSensorList(Sensor.TYPE_LIGHT).get(0); // evtl. OutOfBound!
    }
    @Override
    protected void onResume() {
        super.onResume();
        // nur Sensordaten empfangen wenn die App im Vordergrund läuft
        sensorManager.registerListener(this, lightSensor, SensorManager.SENSOR_DELAY_NORMAL);
    }
    @Override
    protected void onPause() {
        super.onPause();
        // nur Sensordaten empfangen wenn die App im Vordergrund läuft
        sensorManager.unregisterListener(this);
    }
    @Override
    public void onSensorChanged(SensorEvent event) {
        // Event values enthält je nach sensor unterschiedliche Werte
        textView.setText(String.format("Helligkeit: %.0f", event.values[0]));
    }
}
```

### Dependency- und View Injection
Problem: Enge Koplung (Bsp. Library Service) - wird zudem mehrfach instantiiert.

* `+` keine statischen Methoden mehr
* `+` zentrale Konfiguration in Modul und Komponente
* `+` Einfache Testbarkeit: Modul oder Applikation austauschen
* `-` Nicht weniger Schreibaufwand bei kleinen Projekten
* `-` Gute Tests sind sehr Wichtig → Bei einer Fehlkonfiguration drohen NullPointerException

#### Dependency-Injection mit Dagger
Modul
: Ein Modul instanziert unsere Klassen (z.B. LibraryService) die wir injecten wollen

Komponente
: Eine Komponente fasst Module zusammen und ist zuständig für die Injection

Klasse lässt sich über die Komponenten ihre Abhängigkeiten injecten.

```java
@Module
public class LibraryServiceModule {
   @Provides
   @Singleton
   public LibraryService getLibraryService() {
       return new LibraryService();
   }
}
@Singleton
@Component(modules = {LibraryServiceModule.class})
public interface GadgeothekComponent {
    // Für jede Klasse, in die wir den LibraryService injizieren wollen
   void inject(GadgeothekActivity activity);
}
public class Application extends android.app.Application {
   GadgeothekComponent component;
   public void onCreate() {
       // In der Application erstellen wir die Komponente
       component = DaggerGadgeothekComponent.builder().build();
   }
   public GadgeothekComponent getComponent() {  return component;  }
}
public class GadgeothekActivity extends AppCompatActivity {

   // Mit @Inject annotierte Felder werden von der Komponente gesetzt
   @Inject
   LibraryService libraryService;

   @Override
   protected void onCreate(Bundle savedInstanceState) {
   // ...
  // Mit @Inject annotierte Felder mit der Komponente injecten
   ((Application) getApplication()).getComponent().inject(this);
   }
}
```

#### View-Injection mit Butter Knife
```java
class ExampleActivity extends Activity {
   @Bind(R.id.username) EditText username;
   @Bind(R.id.password) EditText password;

   @BindString(R.string.login_error)
   String loginErrorMessage;

   @OnClick(R.id.submit)
   void submit() {
      // ...
   }

   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.simple_activity);
      ButterKnife.bind(this);
      // ...
   }
}
```

### Data Binding
* `-` Aufpassen, dass nicht zu viel Logik ins XML wandert
* `-` Android generiert noch mehr zusätzlichen Code
* `-` Code schwieriger zu lesen und zu debuggen
* `-` Data Binding ist eine Extra Library und ist nicht der Default

In der View können Variablen, die zu "Binden" sind angegeben werden:
```xml
<layout xmlns:android="http://schemas.android.com/apk/res/android">
   <data><variable name="user" type="ch.hsr.mge.databindingdemo.User"/></data>
   <RelativeLayout ... >
       <TextView android:text="@{user.firstName}" ... />
       <TextView android:text="@{String.valueOf(index + 1)}"
                android:visibility="@{age < 13 ? View.GONE : View.VISIBLE}"
                android:transitionName='@{"image_" + id}' ... />

      <!-- EVENT wird gebunden -->
      <Button android:text="Save" android:onClick="@{controller.onButtonSaveClicked}"/>
   </RelativeLayout>
</layout>
```

Das Binding erfolg in der Activity, im onCreate:
```java
// Generierte Klasse anhand des Layouts
ActivityMainBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_main);
User user = new User("Peter", "Packet");
binding.setUser(user);
```

Um Daten aus gebundenen Objekten in der View zu aktualisieren wurd das Observer-Pattern benötigt.

```java
public class User {
   public ObservableField<String> firstName = new ObservableField<>();
   public ObservableField<String> lastName  = new ObservableField<>();
   public TextWatcher lastNameWatcher = new TextWatcher() {
   // ...
          if (!Objects.equals(lastName.get(), s.toString())) {
              lastName.set(s.toString());
          }
   };
}
```
