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
