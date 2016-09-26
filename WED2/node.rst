Node.JS
========

Lernziele
---------

Die Teilnehmer...

* verstehen den unterschied zwischen Server und Client JavaScript Code
* kennen den Unterschied zwischen klassischen und event-driven Web Services.
* können die Konzepte von Node.js anwenden.
* können mit dem Online API von Node.js umgehen.


Varianten
---------

BeurteAspekte:
* Kosten (Strom)
* Skallierung ()
* Aufgabe

**1 prozesse, n Clients**
    Problem: Nur einer gleichzeitig!
    Kosten: Günstig
    Eignung: Viele kleine Aufgaben

**n Prozesse, n Clients**
    Mehrere CPUs nutzbar
    Viele grosse Aufgaben
    grosse Aufgaben

**1 Server Prozess - Event Basiert**
    Kosten: Günstig
    Eignung: Viele, kleine Aufgaben
    -> Node!

Asynchron
----------
Für ES6: Promise!

.. code:: javascript

    function myFunc(a, b, fn) {
	setTimeout(function(){
		fn(a + b);
	}, 1000);
    }
     myFunc(2, 4, console.log);
     myFunc(10, 3, console.error );

In Node ist das Callback immer das letzte argument
Asynchron wann immer möglich bevorzugen

Promise(nicht relevant)
........................
* Hilft der Lesbarkeit! (vs. Callback-Hell)
* Noch kein Support in Node.JS

.. code:: javascript

    var p1 = function readFile(filename, enc){
      return new Promise(function (fulfill, reject){
        fs.readFile(filename, enc, function (err, res){
          if (err) reject(err);
          else fulfill(res);
        });
      });
    }
     p1.then(function(val) {
         console.log()
     })
     .catch(function(reason) {
         console.log('Handle rejected promise ('+reason+') here.');
     });

Core APIs
----------

.. todo::

    * Welche Methoden von clientrequest sind relevant?
    * Welche Methoden von serverresponse sind relevant?


Streams
-------
* read, write, end, pipe
* Können read-only, write-only, duplex oder Transformation sein.
