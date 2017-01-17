# GUI-Design
## GUI Design Principles

Es gibt keine Design Guidelines wie bei Android aber Grobe Grundsätze (Design Principles):

* Pride in craftsmanship
* Be fast and fluid
* Authentically digital
* Do more with less
* Win as one

## Resources

WPF-Resources sind im XAML hinterlegte Elemente wie Brush, Style, Color, String usw. Das Konzept ist _entfernt_ vergleichbar mit CSS im Browser. Die **Ordnerstruktur** ist im Gegensatz zu WPF **völlig frei**.

Eine Resource wird einmal definiert mit einen Key (`x:Key` in XAML). Über diesen Key kann Resource im Projekt referenziert werden. **Key ≠ Name**

* Effizient: Einmal definieren, n mal verwenden = Wenig code & Wenig Speicher
* Wartbar da Zentral abgelegt (cooperate design)
* Adaptierbarkeit: Trennung Darstellung und Struktur = Bessere Anpassbarkeit an User, System usw.

(NB: Der `x` Namespace ist für allgemeine XAML Eigenschaften/Elemente, während der default Namespace in XAML-Files die WPF-Elemente beinhaltet)

```xml
<Application.Resources> <!-- Definition in irgend einem Ressource Dict -->
    <SolidColorBrush x:Key ="MyButtonBackground" Color="#EEEEEE" />
</Application.Resources>

<!-- Verwenden (Data Binding im Hintergrund)-->
<Button Background="{StaticResource MyButtonBackground}" Content="Save" />
```
#### Zugriff auf Resource
<figure  style="max-width: 50%; float: right">
    <img src="images/resolve_resource_key_tree.png"/>
</figure>
Eine Resource wird **Bottom-Up im _locical Tree_** (also dieselbe Struktur wie im XAML) gesucht.

```xml
<!-- Zugriff auf Resource - 1x mit static binding -->
<Button Content="Save"
  Background="{StaticResource MyButtonBackground}"/>

<!-- Zugriff auf Resource, jedes mal dyn. binding -->
<Button Content="Save"
  Background="{DynamicResource MyButtonBackground}"/>

<!-- Zugriff auf Systemresourcen -->
<Button Content="Save"
  Background="{x:Static SystemColors.ControlBrush}"/>
```

**Im Code** wird über die Methode `FindResource` zugegriffen, welche auf `FrameworkElement` deklariert ist.

```csharp
var okText = (string)FindResource("OkText");
var bgBrush = FindResource("DarkBrush") as Brush;
```
<hr>
### Dynamische vs. Statische Resources

**Statische Resourcen**: Zur Compile Time = Einmalige Auswertung = satic Binding → Compile Error wenn key nicht vorhanden.

**Dynamic Resource**: Zur Laufzeit = Wird N-Mal ausgewertet
= dynamic binding → Check zur Laufzeit (Exception

Ein Theme Switch wie in VisualStudio geht also nur mit Dynamic Resource.

### Resource Dictionary

**Resource Dictionary**: Behälter, um Resources zu speichern - einfacher Key-Value-Store. Bsp. `Application.Resources` `Window.Resources` `Button.Resources`.

Resource Dictionaries können gemerged werden. Dies ermöglicht flexible Strukturierung (separation of concerns).

```xml
<Application.Resources>
    <ResourceDictionary>
        <SolidColorBrush x:Key ="MyButtonBackground" Color="#EEEEEE" />
        <ResourceDictionary.MergedDictionaries> <!– include external resource dictionaries -->
            <ResourceDictionary Source="Colors.xaml"/>
            <ResourceDictionary Source="Brushes.xaml"/>
        </ResourceDictionary.MergedDictionaries>
        <!– Kaskadierung - sprich Verwendung von Properties aus bsp. Colors.xaml möglich -->
        <SolidColorBrush x:Key="ButtonBgBrush" Color="{StaticResource ThemeColor1}" />
    </ResourceDictionary>
</Application.Resources>
```
**Externe Ressourcen** können über externe Assemblys eingebunden werden. Dabei wird als Key eine **PackageURI** angegeben.

```xml
<Image Source="/BasePicLib;component/media/pix/open.png" />
<!-- ist die Kurzform für -->
<Image Source="pack://application:,,,/BasePicLib;component/media/pix/open.png" />
```

Varianten für Package-URIs sind Relativ zum aktuellen Ordner (`siteOfOrigin:///`) und Relativ zur Assembly (`application:///`).

### Control Templates "HTML"
ControlTemplates ermöglicht ein kompletter Aufbau für ein Beliebiges WPF-Control festzulegen. Jedes Control hat ein Default-ControlTemplate. Die visuelle Darstellung der Controls kann dadurch 100% selbst gewählt werden

```xml
<Setter Property="Template"><Setter.Value>
        <ControlTemplate TargetType="Button" >
            <Label Background="{TemplateBinding Background}" Content="{TemplateBinding Content}">
        </ControlTemplate>
</Setter.Value></Setter>
```
<hr>
## Styles & Themes - "CSS (Klassen)"
Generelle Definition ("Klassen") & Für Typen. "Klassen" macht nur für spezielle Styles wie bsp. `DangerButton` Sinn.

```xml
<Style x:Key="MyButtonStyle"> <!-- Definition (im Resource Dictionary) -->
    <!-- Gleiche Werte gelten auch auf Labels etc... -->
    <Setter Property="Button.Background" Value="Transparent" />
</Style>

<!-- Nutzung im XAML  -->
<Button Style="{StaticResource MyButtonStyle}" Content="Cancel" />
```

NB: Komplexe Werte möglich - bsp. `<Setter.Value><LinearGradientBrush ...></Setter.Value>`

Sinnvoller ist es, für **sepzifische Typen** Styles zu Definieren. Diese gelten dann für alle Elemente, welche von diesem Typ sind.

```xml
<!-- KEIN x:Key!  -->
<Style TargetType="Button"> <!-- kurz für TargetType="{x:Type Button}" -->
    <Setter Property="Background" Value="Transparent" />
    <Setter Property="Foreground" Value="Black" />
    <Setter Property="BorderBrush" Value="Silver" />
    <!-- ... -->
</Style>
```

Styles können **vererbt** werden

```xml
<Style x:Key="DangerButtonStyle" TargetType="Button" BasedOn="{StaticResource MyButtonStyle}">
        <Setter Property="Background" Value="Red" />
</Style>
```

### Trigger "Pseudo-Klassen"

```xml
<Style TargetType="ListBoxItem">
    <Style.Triggers>
        <DataTrigger Binding="{Binding InStock}" Value="0">
            <Setter Property="Foreground" Value="Red" />
        </DataTrigger>
        <Trigger Property="IsMouseOver" Value="True">
            <Setter Property="Foreground" Value="White" />
        </Trigger>
    </Style.Triggers>
</Style>
```
(NB: Geht bei bsp. Button wegen VisualStateManager nich. Fix: Eigenes ControlTemplate)

### Best Practice

* Kleinstprojekte: Styling direkt in Window.Resources (oder teilweise direkt inline bei Controls)
* **Kleine bis mittlere Projekte:**: Eigene Resource Dictionaries für verschiedene Typen (z.B. nach Grundfarben, Pinsel, Control-Styles, etc.)
* Grössere Projekte: Eigene Assemblies mit Resource Dictionaries und Image-Resources pro Design/Theme
