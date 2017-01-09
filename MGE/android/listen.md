## Listen

### Einfache ListView

```xml
<ListView android:layout_width="match_parent" android:layout_height="match_parent"
   android:id="@+id/listView"/>
```
```java
ArrayAdapter<String> adapter =
   new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, // oder eigenes Layout
           // bei eigenem Layout muss die ID mitgegeben werden - wo halt der Text rein kommt
           myStringArray){
             // überschreibe beispielsweise getView() - siehe unten
           };
listView.setAdapter(adapter);
```

Der ArrayAdapter kann auch erweitert werden - bsp. ``getView``-Methode überschreiben.
```java
private class MyCustomAdapter extends ArrayAdapter<Module> {
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
}}
```

### Performance

* Alte View bei getView wiederverwenden!
* findViewById ist teuer! → Zwischenspeichern (S. Code oben!)
* Damit das nicht immer "manuell" gemacht werden muss: RecyclerView

### RecyclerView

Nachfolger von List- und GridView. Leicht anderes API - Recycling ist fest eingebaut. ``getView`` Methode ist in 2 Methoden aufgeteilt - ``onCreateViewHolder`` für das Erstellen und ``onBindViewHolder`` für das "Updaten".

```xml
<android.support.v7.widget.RecyclerView
    android:id="@+id/recyclerView"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
app:layout_behavior="@string/appbar_scrolling_view_behavior" />
```

```java
// usage
adapter = new MyAdapter(modules);
recyclerView.setAdapter(adapter);
layoutManager = new LinearLayoutManager(getActivity());
recyclerView.setLayoutManager(layoutManager);
```
```java
public class MyAdapter extends RecyclerView.Adapter<ViewHolder> {
    private ArrayList<Module> dataset;
    public MyAdapter(ArrayList<Module> modules) {
        dataset = modules;
    }
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View v = layoutInflater.inflate(R.layout.rowlayout, parent, false);
        TextView textView = (TextView) v.findViewById(R.id.textView);
        CheckBox checkBox = (CheckBox) v.findViewById(R.id.checkBox);
        ViewHolder viewHolder = new ViewHolder(v, textView, checkBox);
        return viewHolder;
    }
    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        final Module module = dataset.get(position);
        holder.textView.setText(" (" + module.getCode() + ")");
        holder.checkBox.setText(module.getName());
        holder.checkBox.setChecked(module.isSelected());
    }
    @Override
    public int getItemCount() {
        return dataset.size();
    }
    public void add(int position, Module module) {
        dataset.add(position, module);
        notifyItemInserted(position);
    }
    public void remove(Module module) {
        int position = dataset.indexOf(module);
        dataset.remove(position);
        notifyItemRemoved(position);
    }
    public class ViewHolder extends RecyclerView.ViewHolder {
        final TextView textView;
        final CheckBox checkBox;
        public ViewHolder(View v, TextView textView, CheckBox checkBox) {
            super(v);
            this.textView = textView;
            this.checkBox = checkBox;
        }
    }
}
```
