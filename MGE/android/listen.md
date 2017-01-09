## Listen

### Einfache ListView

```xml
<ListView
   android:layout_width="match_parent"
   android:layout_height="match_parent"
   android:id="@+id/listView"/>
```

Folgt Adapter Pattern: Client ist ListView
Adapter vermittelt

```java
ArrayAdapter<String> adapter =
   new ArrayAdapter<String>(
           this,
           android.R.layout.simple_list_item_1, // oder eigenes Layout
           // bei eigenem Layout muss die ID mitgegeben werden - wo halt der Text rein kommt
           myStringArray);

listView.setAdapter(adapter);
```

Der ArrayAdapter kann auch erweitert werden - bsp. ``getView``-Methode überschreiben.

Beispiel für Modul Object:

```java
// Siehe http://github.com/HSR-MGE/W04-CustomArrayAdapterDemo

public View getView(int position, View convertView, ViewGroup parent) {
    // Zugriff auf Domaindaten
    final Module module = modulList.get(position);

    // Layout beim ersten Mal erstellen
    if (convertView == null) {
       LayoutInflater layoutInflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
       convertView = layoutInflater.inflate(R.layout.rowlayout, null);

       // Kindelemente im Layout finden
       TextView textView = (TextView) convertView.findViewById(R.id.textView);
       CheckBox checkBox = (CheckBox) convertView.findViewById(R.id.checkBox);

       // Elemente zur besseren performance zwischenspeichern
       Pair<TextView, CheckBox> views = new Pair<>(textView, checkBox);
       convertView.setTag(views); // Beliebiges Objekt kann hier gesetzt werden
    }

    // Zwischengespeicherte Elemente auslesen
    Pair<TextView, CheckBox> views = (Pair<TextView, CheckBox>) convertView.getTag();
    TextView textView = views.first;
    CheckBox checkBox = views.second;


    // Event Handling für die Checkbox
    checkBox.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
            CheckBox cb = (CheckBox) v;
            module.setSelected(cb.isChecked());
        }
    });

    // Setze Daten auf View
    textView.setText(" (" + module.getCode() + ")");
    checkBox.setText(module.getName());
    checkBox.setChecked(module.isSelected());

    return convertView;
}
```

### Performance

* Alte View bei getView wiederverwenden!
* findViewById ist teuer! → Zwischenspeichern

```java
...
Pair<TextView, CheckBox> views = new Pair<>(textView, checkBox);
convertView.setTag(views); // Beliebiges Objekt kann hier gesetzt werden
...
```

Damit das nicht immer "manuell" gemacht werden muss: RecyclerView

### RecyclerView

Nachfolger von List- und GridView. Leicht anderes API - Recycling ist fest eingebaut.

``getView`` Methode ist in 2 Methoden aufgeteilt - ``onCreateViewHolder`` für das
Erstellen und ``onBindViewHolder`` für das "Updaten".


!!! todo

    Mehr nach Übung?
