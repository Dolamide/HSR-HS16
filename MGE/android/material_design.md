## Material Design

* eigenes Styling und Theme
* Material Design-Guidelines umsetzen
* Material UI-Komponenten einsetzen

Design Language
: "Hilfestellung für den Designprozess". Beschreibt wie die Teile einer Applikation aussehen und sich verhalten sollen.

### Vision
Der [Styleguide](https://material.google.com) umfasst Layout, Style, Animation, Components (Fertige, verwendabar Komponente), Patterns (Hilfestellung bei oft auftretenden Problemen), Usability (Bsp: Texte in Grafiken sind problematisch).

![](images/material_design_zusammenfassung.png)

### Integration in die eigenen App

Das aussehen sollte nicht direkt auf den Elementen verändert werden sondern global (analog nicht inline in HTML sondern extern in CSS). Ermöglicht unterschiedliche Styles für Tablets, Regionen usw. In der View können Styles referenziert werden (analog "class"):

```xml
<Button style="@style/MyButtonStyle" ... />
```

Dieser Style kann dann in `res/values/styles.xml` definiert:

```xml
<style name="MyButtonStyle">
   <item name="android:background">#ff85e1</item>
   <item name="android:minWidth">64dp</item>
   <item name="android:padding">8dp</item>
</style>
```
*Styles werden vererbt - gelten also nur für die aktuelle View!*

#### Themes
Themes ermöglichen generelles look-and-feel für App/Activity uund wird in Manifest.xml angegeben:

```xml
<application ... android:theme="@style/AppTheme" > <!-- Globales Theme -->
   <activity android:name=".MainActivity" android:theme="@style/AppTheme" > <!-- Theme für Activity -->
```

```xml
<!-- In `res/values/styles.xml` implementieren -->
<style name="AppTheme" parent="Theme.AppCompat.Light.NoActionBar">
   <!-- Hier können wir Theme-Einstellungen überschreiben -->
   <item name="colorPrimary">@color/colorPrimary</item> <!-- Bsp. Farben in res/values/colors.xml-->
</style>
```
Vorsicht: GUI-Builder zeigt nicht zwinged das GUI an, welches verwendet wird

### UI-Komponenten

FAB – Floating Action Button
: Wenn Aktion nicht eindeutig ist, lieber keinen FAB nehmen

TextInputLayout (Placeholder gleited nach oben) AppBarLayout, CollapsingToolbarLayout,
TabLayout(Liste der Tabs) und ViewPager(mit & ohne Tabs, wechselt also zwischen Fragments).

### Anwenden
Nicht im Standard-SDK → Android Design Support Library in `build.gradle` ergänzen.
