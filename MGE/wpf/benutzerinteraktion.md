# Benutzerinteraktion

## Events in WPF

WPF liefert diverse **vordefinierte Event Handler Methoden** (`OnStartup`, `OnClosing` etc.) -
Ob die vordefinierten Event Handler Methoden oder **manuelles Eventhandling **genutzt werden soll bleibt dem Entwickler überlassen.

```csharp
public partial class App : Application {
    public App() {
        this.Startup += (o, args) => { ... };
    }
    // oder
    protected override void OnStartup(StartupEventArgs e) { ... }
}
```

## WPF App Lifecycle
WPF-Apps haben keine starren Lifecycle wie Android, da WPF nicht auf Single-App-Betrieb ausgelegt ist.

### App Startup
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

<figure>
    <img src="images/app_startup.png" style="max-width: 70%;"/>
</figure>

Welches Fenster gestartet wird kann entwerde in der `App.xaml` über das **Attribut** `StartupUri="MyMainWindow.xaml"` oder direkt in der **Methode** `OnStartup` im Code Behind manuell gemacht werden:

```csharp
protected override void OnStartup(StartupEventArgs e) {
    MainWindow = new MainWindow();
    MainWindow.Show();
}
```

### Window Close & App Shutdown

<figure style="max-width: 48%;float: left;">
    <img src="images/window_close.png" />
    <figcaption>Window close</figcaption>
</figure>
<figure style="max-width: 48%; float: right">
    <img src="images/app_shutdown.png"/>
    <figcaption>APP shutdown</figcaption>
</figure>
<br><br><br><br><br><br><br><br><br><br>

## Routed Events (VISUAL TREE)

Events gehen wie in JS mit dem DOM zuerst **Aussen nach Innen (Preview)** und dann von **Innen nach Aussen** (Tunneling).

<figure>
    <img src="images/routed_events.png" style="max-width: 70%;"/>
    <figcaption>Keyboard: Taste B wird gedrückt und wieder losgelassen - Standardverhalten</figcaption>
</figure>

Alle EventArgs leiten von `RoutedEventArgs` ab und stellen somit mindestens folgende Attribute zur Verfügung.

* `Handled` - Wenn auf True gesetzt wird die Chain abgebrochen.
* `OriginalSource` - Das "oberste"-Element - das, auf das gemäss dem Control-Template geklickt wurde.
* `Source` - Element, welches den Event gemeldet hat (Bsp. in Controltemplate ist `OriginalSource` ein Bild, aber die `Source` ein Button)
* `RoutedEvent` - Der Routed Event, welches mit diesem Objekt verknüpft ist.

Routed Events können **auf dem Element** selbst oder auf** einem Parent** behandelt werden. (Typ. relativ weit unten im Visual Tree)

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
### Nützliche Events

* Maus: MouseDown, MouseUp, MouseMove
* Keyboard: KeyDown, KeyUp, TextInput
* Touch: TouchDown, TouchUp, TouchMove
<hr>
### Probleme mit Event Handling im Parent
* Gleichartiges Event kann für verschiedene Controls ausgelöst werden
* Quelle des Events entscheidend

Problem Beispiel: Der Event `SelectionChanged` nicht nur vom `MainTabControl` sondern auch von der `ListBox` geworfen. Darum gibt es eine **Endlosschleife**.


```csharp
private void MainTabControl_SelectionChanged(object sender,
    SelectionChangedEventArgs e) {

    if (this.MainTabControl.SelectedIndex == 0) {
        this.ListBox1.Items.Clear();         // (Re-)Populate ListBox
        this.ListBox1.Items.Add("...");
        ...
    }
}
```

Fix: Auf Quelle des Events Prüfen

```csharp
private void MainTabControl_SelectionChanged(object sender,
    SelectionChangedEventArgs e) {
    if (e.OriginalSource == this.MainTabControl) { ... }
}
```

## Hintergrund-Operationen
Problem wie bei Android: Wenn **lange Operationen** gleichen Thread laufen wird das **UI blockiert** - ein Effekt, den man nie will! (Bsp. Download, DB-Zugriff usw.)

Vorgehen:

1. Visuelles Feedback geben: **Spinner, Overlay, Popup**. Beispiel Button:
    * Eigenes ContolTemplate für Button mit Spinner
    * Spinner Visibility an IsEnabled von Button binden
    * Dafür ist ein eigener Converter nötig
    * Nach Klick wird Button deaktiviert - und und somit wird gleich der Spinner angezeigt.
2. Starten eines Background-Threads als Reaktion auf ein Event + Kontrolle an UI Thread zurückgeben
    * `Task.Run(() => { /* Code läuf im Background-Tread */ } );`
    * Wenn Berechnung komplett, zurück in UI-Tread mit `Displatcher.Invoke(() => { /* Code läuft im UI Thread */});`
    * Dispatcher ist Property auf UI-Control. Wenn nicht in Code-Behind Statische Variante `System.Windows.Threading.Dispatcher.DurrentDispatcher` verwenden (Bsp. in ViewModel)
