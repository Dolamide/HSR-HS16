# Data Binding

Vorteile von Databinding:

* ermöglicht extrem lose gekoppelte Applikation
* viel Programmcode kann gespart werden, da sich vieles deklarativ direkt in XAML formulieren lässt

Relevant für Binding sind 3 Klassen. Alle Klassen definieren Properties, welche direkt im XAML verwendet werden. Vorsicht: Converter unterschieden sich bei `Binding` und `MultiBinding`.


## BindingBase (abstract)
* `StringFormat` Umwandung eines Werts in einen String (Analog zu `String.Format(...)`). Im XAML wird `{}` als Escaping ausdruck benötigt

```xml
<!-- string.Format("{0:0.0}", ScaleX) -->
<TextBox Text="{Binding ScaleX, ElementName=WpfLabelScale, StringFormat={}{0:0.0}}" />
```

* `TargetNullValue` Wert, welcher verwendet werden soll, wenn die Quelle `null` ist.

## Binding
* extends BindingBase
* `Path` ist das `Standard Property`, kann also mit `{Binding}` oder `{Binding NachName}` angegeben werden.
    * Definiert den _Pfad_ auf der Binding-Source, der gebunden werden soll.
* `Mode`: Definiert in welche Richting die Daten gebunden werden
    * muss Typischerweise nicht angepasst werden
    * Default Variiert je nach gebundenem Property.
    * `OneTime`, `OneWay` (r), `TwoWay` (rw), `OneWayToSource` (w)
* `Converter` - Converter, welcher für eine (optionale) Umwandung verwendet werden soll.
    * Methoden: `Convert` und `ConvertBack` (optional)

    ```csharp
    public sealed class BooleanToVisibilityConverter : IValueConverter {
        public object Convert(object value, Type targetType,
                              object parameter, CultureInfo culture) {
            return value is bool && (bool)value == true ?
                Visibility.Visible : Visibility.Collapsed;
        }
        public object ConvertBack(object value, Type targetType,
                                  object parameter, CultureInfo culture) {
            return value as Visibility? == Visibility.Visible;
        }
    }
    ```

    * Anwendung

    ```xml
    <!-- Bsp. in app.xaml -->
    <Application.Resources>
        <local:BooleanToVisibilityConverter x:Key="MyVisibilityConverter" />
    </Application.Resources>
    ...
    <!-- Bei effektiver Benützung -->
    <Label Visibility="{Binding IsAvailable, Converter={StaticResource MyVisibilityConverter}}" />
    ```

* `ElementName` Name des Elements, welches als Binding-Source verwendet werden soll (Ein anders Control)

## MultiBinding
* extends BindingBase
* `Bindings` - Multibinding

    ```xml
    <TextBlock>
        <TextBlock.Text>
            <!-- string.Format("{0} – Now only {1:C}", Description, Price) -->
            <MultiBinding StringFormat="{}{0} -- Now only {1:C}!">
                <Binding ElementName="Description" Path="Text"/>
                <Binding ElementName="Price" Path="Text"/>
            </MultiBinding>
        </TextBlock.Text>
    </TextBlock>
    ```

* `Converter` Analog zu `Converter` von `Binding`, aber mit Object-Array.

## Zu Bindendes Objekt
Standardmässig wird nichts gebunden - das muss alles manuell gemacht werden. Dafür gibt es wider verschiedene Varianten

### DataContext (Regelfall)
* Ist ein Property, das auf `FrameworkElement` definiert ist - also auf fast allem (`Window`, `TextBox`, `Label`...)
* Kann ein Beliebiges Objekt sein. Wird typischweise auf das ViewModel gesetzt (Siehe MVVM)
* Grundlegender Kontext gilt auch für Kinder (falls nicht explizit überschrieben). Dadurch kann `DataContext` auf dem Window gesetzt werden und von allen Controls bequem verwendet werden.

    > [...]If there are child elements without other values for DataContext established through local values or styles, then the property system will set the value to be the DataContext value of the nearest parent element with this value assigned.[...] <cite><a href="https://msdn.microsoft.com/en-us/library/system.windows.frameworkelement.datacontext%28v=vs.110%29.aspx">MSDN Documentation</a></cite>

* Kann im Code-Behind gesetzt werden - typischerweise mit Dependency-Injection.

    ```csharp
    public partial class MainWindow : Window {
        public PersonViewModel MyViewModel { get; set; }
        public MainWindow(PersonViewModel model) {
            InitializeComponent();
            MyViewModel = model;
            // DataContext ist Typ `object`
            DataContext = model;
        }
    }
    ```

* Für Listen `ObservableCollection<PersonViewModel>` verwenden

### Source
Binde an explizit angegebene Stelle im Code. (Pfui!)

```xml
<Label Content="{Binding Source={StaticResource NameLabelCaption}}" />
```

### RelativeSource
Binde an ein Element relativ im Visual Tree.

```xml
<!-- Binde Wert des Labels auf den Fenstertitel -->
<Label Content="{Binding RelativeSource={RelativeSource FindAncestor,
    AncestorType=Window}, Path=Title}"/>
```
### ElementName

Binde an ein anderes, benanntes XAML-Element

```xml
<TextBlock Name="MyText" Margin="10" ... />
<TextBlock Name="OtherText"
    Margin="{Binding ElementName=MyText, Path=Margin}" ...
     />
```

## Binding auf eigene Objekte

Das Interface `INotifyPropertyChanged` (Kurz INPC) ist von zentraler Bedeutung. Wird dieses implementiert, so kann sich das UI automagisch updaten indem sich WPF automatisch auf diesen Event abonniert und sofort aktualisiert wird, wenn der Event gefeuert wird. Alternativ kann ein Framework wie Fody genutzt werden.

```csharp
public class PersonV2 : INotifyPropertyChanged {

    private string _firstName;
    public string FirstName
    {
        get { return _firstName; }
        set { SetProperty(ref _firstName, value, nameof(FirstName), nameof(FullName));}
    }

    private string _lastName;
    public string LastName
    {
        get { return _firstName; }
        set { SetProperty(ref _lastName, value, nameof(LastName), nameof(FullName)); }
    }

    // Generated Property - Will also change,
    public string FullName => _firstName + " " + _lastName;

    public event PropertyChangedEventHandler PropertyChanged;

    protected void SetProperty<T>(ref T storage, T value,
                                  string name, params string[] otherNames)
    {
        if (Equals(storage, value)) {
            return;
        }
        storage = value;
        OnPropertyChanged(name);
        foreach (var n in otherNames) {
            OnPropertyChanged(n);
        }
    }

    protected virtual void OnPropertyChanged(string propertyName = null) {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
```

## ItemsControl

Mit dem `ItemTemplate` kann eine Template für die Darstellung eines Items inklusive binding angegeben werden.

```xml
<ListBox ItemsSource="{Binding Source={StaticResource myTodoList}}"
        HorizontalContentAlignment="Stretch">
    <ListBox.ItemTemplate>
        <DataTemplate>
            <StackPanel>
                <TextBlock Text="{Binding TaskName}" />
                <TextBlock Text="{Binding Description}"/>
                <TextBlock Text="{Binding Priority}"/>
            </StackPanel>
        </DataTemplate>
    </ListBox.ItemTemplate>
</ListBox>
```

Bessere & Wiederverwendbare Variante:
```xml
<!-- Deklaration in einem ResourceDictionary -->
<DataTemplate x:Key="myTaskTemplate" DataType="local:Task">
    <DockPanel HorizontalAlignment="Stretch">
        <TextBlock Text="{Binding TaskName}" />
        <TextBlock Text="{Binding Description}"/>
        <TextBlock Text="{Binding Priority}"/>
    </DockPanel>
</DataTemplate>
<!-- Verwendung im XAML -->
<ListBox ItemsSource="{Binding Source={StaticResource myTodoList}}"
         ItemTemplate="{StaticResource myTaskTemplate}"
         HorizontalContentAlignment="Stretch" />
```
