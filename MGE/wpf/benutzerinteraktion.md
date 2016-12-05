## Benutzerinteraktion

!!! todo

    Testat: W11 - (WPF 04) - Data Binding DEMO App 2 - Transform With Binding.zip 
    
    Modales Fenster:

    > Did you try showing your window using the ShowDialog method?
    > Don't forget to set the Owner property on the dialog window. This will avoid weird behavior when Alt+Tabbing, etc.



### Review C# Events
* Events sind ein in .NET Sprachen eingebauter Publish/Subscribe-Mechanismus.
* Events werden typischerweise in einer Klasse ausgelöst. Externe Klassen können sich von Aussen subscriben.

Beispiel:

```csharp
// Implementierung
public event PropertyChangedEventHandler PropertyChanged;

// Schnittstelle für Event-Handler ist wie
// folgt (als Delegate) definiert
public delegate void PropertyChangedEventHandler(object sender,
                                      PropertyChangedEventArgs e);
// Wobei PropertyChangedEventArg in .NET vordefiniert ist. 
```

### Events in WPF

* In WPF gibt es ganz viele Events - können in Dokumentation oder mittels IntelliSense (Blitz Symbol) gefunden/gesucht werden.
* WPF liefert diverse vordefinierte Event Handler Methoden (`OnStartup`, `OnClosing` etc.) - 

Ob die vordefinierten Event Handler Methoden oder manuelles Eventhandling genutzt werden soll bleibt dem Entwickler überlassen.

```csharp
public partial class App : Application {
    public App() {
        this.Startup += (o, args) => { ... };
    }
    // oder
    protected override void OnStartup(StartupEventArgs e) { ... }
}
```

### WPF App Lifecycle
Eine WPF-App hat keine Lifecycle in gleichem Ausmass wie Android, da WPF nicht auf Single-App-Betrieb ausgelegt its.

#### App Startup
.NET generell: `Main`-Methode wird automatisch beim Ausführen der EXE ausgeführt.

Bei WPF wird im Hintergrund (im `obj`-Ordner) eine Teil der App-Klasse (Partial) generiert, welche die `Main`-Methode definiert & implementiert.

```csharp
public partial class App : System.Windows.Application {
 // ...
 public static void Main() {
    LayoutsAndControls.App app = new HelloWpf.App();
    app.InitializeComponent();
    app.Run();
 }
}
```

![App Startup Ablauf](images/app_startup.png) 
: App Startup Ablauf - Quelle: MGE-Vorlesung (HSR)

Welches Fenster gestartet wird kann entwerde in der `App.xaml` über das Attribut `StartupUri="MyMainWindow.xaml"` oder direkt in der Methode `OnStartup` im Code Behind manuell gemacht werden:

```csharp
protected override void OnStartup(StartupEventArgs e) {
    MainWindow = new MainWindow();
    MainWindow.Show();
}
```

#### Window Close

![Window Close Ablauf](images/window_close.png) 
: Window Close Ablauf - Quelle: MGE-Vorlesung (HSR)

#### App Shutdown

![App Shutdown Ablauf](images/app_shutdown.png) 
: App Shutdown Ablauf - Quelle: MGE-Vorlesung (HSR)

### Routed Events

Routed Events: Events, welche durch den **Visual Tree** gereicht.

Events gehen wie in JS mit dem DOM zuerst von Innen nach Aussen (Preview/Tunneling) und dann von Aussen nach innen.

Alle EventArgs leiten von `RoutedEventArgs` ab und stellen somit mindestens folgende Attribute zur Verfügung(Siehe F42):

* `Handled` - Wenn auf True gesetzt wird die Chain abgebrochen.
* `OriginalSource` - Das "oberste"-Element - das, auf das gemäss dem Control-Template geklickt wurde.
* `Source` - Element, welches den Event gemeldet hat (Bsp. in Controltemplate ist `OriginalSource` ein Bild, aber die `Source` ein Button)
* `RoutedEvent` - Der Routed Event, welches mit diesem Objekt verknüpft ist.


Verschiedene RoutedEvents liefern verschiedenste weiter (mehr oder weniger) nützliche Werte.

Routed Events können auf zwei Varianten behandelt werden:

* Im UI Selbst. Für Methodennamen gilt die Namenskonvention: `[ElementName]_On[EventName]`.

    ```xml
    <Button Name="SaveButton"
            MouseDown="SaveButton_OnMouseDown"
            PreviewMouseDown="SaveButton_OnPreviewMouseDown">Save</Button>
    ```
    
    ```csharp
    private void SaveButton_OnPreviewMouseDown(object sender, MouseButtonEventArgs e)
    { ... }
    private void SaveButton_OnMouseDown(object sender, MouseButtonEventArgs e)
    { ... }
    ```

![](images/routed_events.png) 
: Keyboard: Taste `B` wird gedrückt und wieder losgelassen - Standardverhalten. Quelle MGE-Vorlesung (HSR)

Typischerweise werden Events relativ weit unten behandelt, weil dort entsprechend spezifisch gehandelt werden kann.

RoutedEvents bringen aber durch dieses EventBubbling auch Fallstricke mit sich:


!!! warning

    * Gleichartiges Event kann für verschiedene Controls ausgelöst werden
    * Quelle des Events entscheidend

```csharp
private void MainTabControl_SelectionChanged(object sender,
    SelectionChangedEventArgs e) {
    
    if (this.MainTabControl.SelectedIndex == 0) {
        // (Re-)Populate ListBox
        this.ListBox1.Items.Clear();
        this.ListBox1.Items.Add("...");
        this.ListBox1.Items.Add("...");
        ...
    }
}
```
Im obigen Beispiel wird der Event `SelectionChanged` nicht nur vom `MainTabControl` sondern auch von der `ListBox` geworfen. Genaugenommen endet der obige Code in einer Endlosschleife.

Um dies zu umgehen muss auf die Quelle des Events geprüft werden:

```csharp
private void MainTabControl_SelectionChanged(object sender,
    SelectionChangedEventArgs e) {
    
    if (e.OriginalSource == this.MainTabControl) { ... }
}
```

#### Nützliche Events

* Maus: MouseDown, MouseUp, MouseMove
* Keyboard: KeyDown, KeyUp, TextInput
* Touch: TouchDown, TouchUp, TouchMove

### Hintergrund-Operationen (nächste Woche)


