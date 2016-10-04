Struktur
========

Vorgehen
--------

#. Domainmodell entwerfen
#. Screens ableiten
#. Screens in Beziehung bringen ("Sollte erreichbar sein über") und gruppieren (Orientation/Screen Size)
#. Navigation zwischen den Screens festlegen
#. Wireframe/Storyboard für die Gesamtübersicht erstellen
#. Usability Test mit einem Paper-Prototypen des Wireframes

.. seealso::

    `Visualisierungen in den Vorlesungsfolien Nr. 6 ff. <https://docs.google.com/presentation/d/1ulzBi2fpOOTSRnb-nIdhZ7DC6khVDUPl24L9DaOS8Jc/edit#slide=id.gc4a87769a_0_6>`_

    `Designing Effective Navigation <https://developer.android.com/training/design-navigation/index.html>`_

    `Navigation Patterns <https://developer.android.com/design/patterns/navigation.html>`_


Zurück ≠ Zurück
---------------
Zurück kann entweder *zum hierarchischen Parent* **up** (ancestral) oder aber zurück zum *vorherigen Element* **back** (temporal) bedeuten.

In Android wird typischeweise *ancestral* über den Button oben Links implementiert **Up** ("zum Parent screen")
Der Up-Button muss manuell implementiert werden und zu dessen hierarchischen Parent (oder typisch
hierarchischen Parent bzw. Root) führen.

*Temporal* dagegen wird über den "hardware" **Back-Button** implementiert ("zurück zum vorherigen Screen").
Typischerweise muss der Back-Button nicht manuell gemanaged werden - das Default Verhalten entspricht
meistens dem, was der User erwartet. Tabs, Filter, Zoom, Sorting usw. macht der Back-Button
nicht "rückggängig".


.. image:: images/ancestral-temporal-navigation.png

 (Quelle: https://developer.android.com/training/design-navigation/ancestral-temporal.html)

Fragments
---------
**Problem**: Je nach Formfaktor wäre es nützlich, mehrere Screens anzuzeigen
aber es kann nur eine Activity aufs Mal angezeigt werden.

.. image:: images/activity-fragment-communication.png

**Fragment**
    Modularer Teil einer Activity mit eigenem Lebenszyklus (analog Activity - aber umfangreicher!)

Sollten immer dann verwendet werden, wenn die Ansicht kein möglicher Eintrittspunkt in die App ist (sonst Activity).


Implementierung eines Fragments mehrheitlich analog zu einer Activity, mit dem Unterschied, dass die
View explizit erstellt werden muss.

.. code:: java

    public class MainActivityFragment extends Fragment {

       public MainActivityFragment() {
       }

       @Override
       public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                Bundle savedInstanceState) {
           return inflater.inflate(R.layout.fragment_main, container, false);
       }
    }

Implementations Variaten
.........................

Statisch
''''''''

Deklarativ mittels Fragment-Tag im Layout der Activity.

.. code:: xml

    <LinearLayout ...>
       <fragment
           android:id="@+id/fragment"
           android:name="com.example.myfragmentapplication.MainActivityFragment"
           android:layout_width="match_parent"
           android:layout_height="match_parent"
           tools:layout="@layout/fragment_main" />
    </LinearLayout>

Der Code der Activity ändert sich nicht.

Dynamisch
'''''''''

Explizit wird ein Platzhalter im Layout der Activity (mit id!) hinzugefügt (Per Konvention
FrameLayout)

.. code:: xml

    <LinearLayout ...>
       <FrameLayout
          android:id="@+id/fragment_container"
          android:layout_width="match_parent"
          android:layout_height="match_parent" />
    </LinearLayout>

In der Activity kann nun mit dem FragmentManager das ensprechende Fragment geladen und
der Placeholder damit überschrieben werden.

.. code:: java

    public class MainActivity extends Activity {
        @Override
        protected void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);
           setContentView(R.layout.activity_main);

           // Starte Transaktion auf FragmentManager
           FragmentManager fragmentManager = getFragmentManager();
           FragmentTransaction fragmentTransaction =
                                   fragmentManager.beginTransaction();

           // Instantiere Fragment und dem FragmentManager übergeben
           MainActivityFragment fragment = new MainActivityFragment();
           fragmentTransaction.add(R.id.fragment_container, fragment);

           // mehrere Fragments können hier hinzugefügt / entfernt werden

           // Transaktion abschliessen
           fragmentTransaction.commit();
        }
    }


.. note::

    Während Activities nie "von Hand" mittels ``new`` instantiert werden
    dürfen, muss man das bei dynamischen Fragments explizit machen!

Activity-Fragment Kommunikation
--------------------------------
Fragments dürfen (sollten) keine Abhängigkeit auf Parent haben.

**Best Practice**: Implementiere Interface auf dem Parent zur Kommunikation.


.. code:: java

   public class MainActivityFragment extends Fragment {

       public interface OnItemSelectedListener {
           void onItemSelected(String item);
       }

       OnItemSelectedListener parentActivity;

       @Override
       public void onAttach(Context activity) {
           super.onAttach(activity);
           if (!(activity instanceof OnItemSelectedListener)) {
               throw new AssertionError(
                "Activity must implement View.OnClickListener!");
            }
            parentActivity = (OnItemSelectedListener) activity;
        }
    }

Master-Detail Navigation
-------------------------

.. image:: images/master-detail-navigation.png

Für unterschiedliche Screens werden unterschiedliche XML Layouts entworfen, welche
1..n Fragments nutzen (Hier 1 oder 2).

Die Activity list zur Laufzeit aus, welche Fragments vorhanden sind und reagiert ensprechend.

.. code:: java

    public class ItemListActivity
    extends Activity
    implements ItemListFragment.Callbacks {

    private boolean twoPane;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
       setContentView(R.layout.activity_item_list);

       // Gibt es das 2te Fragment? Falls ja: Tablet mode
       if (findViewById(R.id.item_detail_container) != null) {
           twoPane = true;
       }
    }
    // ...
    @Override
    public void onItemSelected(String id) {
        if (twoPane) {
            Bundle arguments = new Bundle();
            arguments.putString(ItemDetailFragment.ARG_ITEM_ID, id);
            ItemDetailFragment fragment = new ItemDetailFragment();
            fragment.setArguments(arguments);
            getFragmentManager()
                    .beginTransaction()
                    .replace(R.id.item_detail_container, fragment)
                    .commit();
        } else {
            Intent detailIntent = new Intent(this, ItemDetailActivity.class);
            detailIntent.putExtra(ItemDetailFragment.ARG_ITEM_ID, id);
            startActivity(detailIntent);
        }
    }
    }

Option Menu
-----------
Implementation Deklarativ in XML (im bsp. menu/main.xml). Eine Imperative implementierung
wäre auch möglich, deklarativ ist aber wann immer möglich vorzuziehen.

.. code:: xml

    <menu xmlns:android="http://schemas.android.com/apk/res/android"
       xmlns:tools="http://schemas.android.com/tools" tools:context=".MainActivity">

       <item android:id="@+id/action_search"
           android:title="@string/action_search"
           android:icon="@drawable/ic_action_search"
           android:orderInCategory="100"
           android:showAsAction="never" />

       <item android:id="@+id/action_settings"
           android:title="@string/action_settings"
           android:orderInCategory="100"
           android:showAsAction="never" />
    </menu>

.. code:: java

    public class MainActivity extends Activity {

       public boolean onCreateOptionsMenu(Menu menu) {
           // Inflate the menu; this adds items to the action bar if it is present.
           getMenuInflater().inflate(R.menu.menu_main, menu);
           return true;
       }

       public boolean onOptionsItemSelected(MenuItem item) {
           switch (item.getItemId()) {
           case R.id.action_search: // ID aus main.xml
               // handle start
               ...
           }
       }
       ...
   }

.. note::

    Auch Fragments können Einträge dem Menu der Activity hinzufügen. Dafür muss
    in der ``onCreate`` die Methode ``setHasOptionsMenu(true);`` aufgerufen werden und
    analog zur Activity die onCreateOptionsMenu Methode überschrieben werden.


Settings-Page
-------------

.. seealso::

    Folie #37/#38


Fragment Menu
-------------
Analog

Toolbar
-------

Früher Action-Bar (deprecated seit Android 5.0)

.. image:: images/actionbar.png

#. App Icon und ev. Up- / Home-Navigation
#. Name der App oder View-Switcher
#. Actions (Teil des Options Menu)
#. Action-Overflow mit dem Rest des Menus


.. code:: java

    public class MainActivity extends AppCompatActivity {

       @Override
       protected void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);
           setContentView(R.layout.activity_main);

           Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
           setSupportActionBar(toolbar);
       }
    }


Navigation Drawer
-----------------

Der Navigation Drawer ist platzsparend - hat aber eine schlechte Usuability.
Das Widget ist nicht Teil von Android und muss über eine Support-Library eingebunden werden.

Toast vs. Snack
---------------
**Toast**
    Eine kleine Feedback-Nachricht

.. code:: java

    Toast toast = Toast.makeText(getActivity(), "Hello MGE!", Toast.LENGTH_SHORT);
    toast.show();

**Snackbar**
    Nachfolger von Toast - mächtiger, da auch Aktionen angegeben werden können.

.. code:: java

    private void mkSnack() {
       Snackbar snackbar = Snackbar.make(content, "Hello MGE!", Snackbar.LENGTH_LONG);
       snackbar.setAction("Again!", new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               mkSnack();
           }
       });
       snackbar.show();
    }
