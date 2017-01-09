## Testing

### Local unit tests

* Laufen auf der **lokalen JVM**: Eigent sich für Logik, welche **nicht von Android frameworks abhängig** ist ("Einfache" interaktionen **Mocken**)
* Verzeichnis: ``module-name/src/test/java/``

```java
public class CalculatorTest extends TestCase {
   private Calculator calculator;
   protected void setUp() { calculator = new Calculator(); }
   public void test_one_plus_one_equals_two() {
       assertEquals(2, calculator.add(1, 1));
   }}
```

### Instrumented tests

* Tests, welche **auf** einem **Android Gerät** (Hardware oder Emulator) laufen.
* Werden eine **APK gepackt und vom Sytem ausgeführt**. Wird im **gleichen Prozess** wie die App under test ausgeführt, damit auf Funktionallität der App zugegriffen werden kann.
* Verzeichnis: ``module-name/src/androidTest/java/``

```java
// Various espresso imports required
@RunWith(AndroidJUnit4.class)
public class ReserveGadgetInstrumentedTest {
@Test
public void testReserveGadget() throws Exception {
    onView(withId(R.id.emailAddressEditText))
           .perform(typeText("test@gmail.com"),
                    closeSoftKeyboard());
    onView(withId(R.id.loginButton))
           .perform(click());
    // ...
}
}
```
