# REST


## POST vs. PUT vs. PATCH

POST: Insert ohne ID

```
 POST api/orders/
 BODY: { productId : 1234, amount: 2 }
```

Server wählt die ID aus und returniert die erzeugte URL im Location-Header

```
Location: http://localhost:25211/api/orders/3
```

PUT: Insert mit ID

```
 PUT api/orders/3
 BODY: { productId : 1234, amount: 2 }
```

PATCH: Partial update:

```
 PATCH /order/1
 BODY: { status: "versendet" }
```

## HATEOAS
Hypermedia as the engine of application state

Hypertext sollte genutzt werden können um einen Pfad durch die API zu finden.
Der Client muss also nur Hypermedia verstehen und nichts spezifisches über die Applikation. Bsp. SOA ist das Gegenstück dazu - wo gegen ein applikationsspezifisches, fixes Interface gearbeitet wird.

### Beispiel Bank

Mit +100 Dollar balance sind Aktionen: `deposit`, `withdraw`, `transfer` und `close` aufrufbar.

```
GET /account/12345 HTTP/1.1

HTTP/1.1 200 OK
<?xml version="1.0"?>
<account>
    <account_number>12345</account_number>
    <balance currency="usd">100.00</balance>
    <link rel="deposit" href="/account/12345/deposit" />
    <link rel="withdraw" href="/account/12345/withdraw" />
    <link rel="transfer" href="/account/12345/transfer" />
    <link rel="close" href="/account/12345/close" />
</account>
```

Mit -25 Dollar balance sind ist nur noch die Aktione `deposit` aufrufbar.

```
GET /account/12345 HTTP/1.1

HTTP/1.1 200 OK
<?xml version="1.0"?>
<account>
    <account_number>12345</account_number>
    <balance currency="usd">-25.00</balance>
    <link rel="deposit" href="/account/12345/deposit" />
</account>
```

Quellen: [Rest Cookbook](http://restcookbook.com/Basics/hateoas/)
