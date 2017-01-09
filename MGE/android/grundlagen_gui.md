## Grundlagen GUI Programmierung

* Imperativ mit Java-Code
* Deklarativ mit XML und GUI-Builder
    * **IDs deklarieren** mit beispielsweise ``android:id="@+id/myId"`` (mit Plus)
    * Alle IDs werden **in die Klasse ``R`` generiert**
    * **ID/Referenz verwenden** mit beispielsweise ``android:src=@mipmap/ic_launcher`` (ohne Plus)
    * Name eines Tags = Klasse im SDK.
    * Resourcen ermöglichen unterschiedliche Varianten je Gerät, Sprache usw. zu verwenden
* ``tools:`` namespace nur für GUI-Builder
* View wird in `onCreate` der `Activity` wird das Layout festgelegt: `setContentView(R.layout.activity_main);`


### Views

View ist Basisklasse um Userinterfaces zu bauen und verantwortlich für ...

* ... **Inhalt zu zeichnen**
* ... **Events behandeln** (Touchinput...)

Widgets und ViewGroups (beinhaltet andere Views, Bsp. LinearLayout) sind Unterklassen von View.

Views, die in XML deklariert sind **werden automatisch instantiiert** ( Beispielsweise ``R.layout.activity_main``).

### Widgets
**Lösen Events aus!**. Widgests sind "Konkrete Elemente" wie Button, Passwort, Telefon Nummer, Uhrzeit, Toggle, Stars usw.
für **Optimale Eingabemethode**. Widgets für im GUI und nicht Widgets auf dem Home-Screen!

### Layouts
<img src="images/layouts.png" style="max-width: 80%" />

<figure style="max-width: 60%;float: right;">
    <img src="images/layout_params.png"/>
</figure>
* **`match_parent`**: Nimmt den gesammten Platz des Parents ein
* **`wrap_content`**: Nur so viel platz wie nötig.
* Absolute Grössen: nur selten empfehlenswert

### Linear Layout
* Alle gleich viel Platz
* **`layout_weight`**: Gewichtung, für mehr Platz.

<figure>
    <img src="images/linear_layout.png" style="max-width: 70%;"/>
    <figcaption>layout_weight: Gewichtung, für mehr Platz.</figcaption>
</figure>
---
### Relative Layout
* Kinder werden relativ zu einander angeordnet
  Bsp: "unterhalb von X und neben Z"

```xml
<RelativeLayout xmlns:android="...">
   <TextView android:text="1. Platz" android:id="@+id/first"
       android:layout_centerHorizontal="true"/>
   <TextView android:text="2. Platz" android:id="@+id/textView2"
       android:layout_below="@id/first"
       android:layout_toStartOf="@id/first" />
   <TextView android:text="3. Platz" android:id="@+id/textView3"
       android:layout_below="@id/first"
       android:layout_toEndOf="@id/first" />
</RelativeLayout>
```

## Ressourcen
Bsp. drawables (Bilder), menu (Menus) und values (Strings/Konstanten).

* Zugriff mit ``getString(R.string.app_name``)
* Zugriff in XML über: ``@string/app_name``
* ``strings.xml`` (Unterordner für Sprache, bsp. de)

    ```xml
    <resources> <string name="app_name">My Application</string>   </resources>
    ```

### Dimensionen
* Einheit: dp/dip (Density-independent Pixels). Für **Schriften**: sp
    * Werden Pixel werden mit der Auflösung skaliert - sind also **unabhängig von der Auflösung**.
* Typische werte können in in ``dimens.xml`` konfiguriert und referenziert werden

    ```xml
    <dimen name="activity_horizontal_margin">16dp</dimen>
    <!-- Referenz: -->
    < ... android:paddingLeft="@dimen/activity_horizontal_margin" />
    ```

### Events und Listeners
* Eventloop - analog zu JS
* **Nur Main-Thread darf GUI verändern**
* Listener auf Objekt registrieren, bsp. ``OnTouchListener``, ``OnClickListener`` [usw.](https://developer.android.com/guide/topics/ui/ui-events.html)


    ```java
    button.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            // ...
            // Fallunterscheidungen mit if(v == myBtn) { ... }
        }
    });
    ```

(Alternativ: im XML definieren (`android:onClick="onButtonClicked"`). Dafür muss Activity-Klasse die Methode implementieren (für kleine Acitvities) (`public void onButtonClicked(View view)`)
)

### GUI-Objekte finden

```java
// Sucht im **aktuellen Layout** - das mit setContentView gesetzt wurde
Button button = (Button) findViewById(R.id.button);
EditText editText = (EditText) findViewById(R.id.editTextA);
```

### Inputvalidierung

```java
final EditText password = (EditText) findViewById(R.id.password);
password.addTextChangedListener(new TextWatcher() {
   @Override
   public void afterTextChanged(Editable s) {
       String pw = s.toString();
       if (s.length() < 8) {
           password.setError("Passwort muss mindestens 8 Zeichen lang sein.");
       }
   }
   // analog müssen Methoden `beforeTextChanged` und  `onTextChanged` implementiert werden.
});
```
