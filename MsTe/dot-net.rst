.NET Framework Architektur
==========================

Common Language Specification (CLS)
------------------------------------
.NET-Anwendungen sind nicht Sprachgebunden (Bsp. Java dagegen schon).

-> Kann nur Funktionieren, wenn gemeinsame Regeln fetsgelegt: Die Common Language Specification.

Die CLS von .NTE ist ein offener Standard.

.. image:: http://openbook.rheinwerk-verlag.de/visual_csharp_2012/bilder/01_02.png

(c) Rheinwerk Verlag


Common Type System (CTS)
------------------------
Sprachübergreiffendes Typensystem für die .NET Plattform.
CLS wäre ohne CTS nicht möglich.

-> Das Typensystem wandert aus der Sprache in die .NET-Umgebung.
Hat zur folge, dass keine Konvertierung von Typen unterschiedlicher
Sprachen notwendig ist.

**Wertetypen**
    Werden auf dem Stack abgelegt: Bsp. int, float, long usw.

**Referenztypen**
    Werden auf dem Heap abgelegt: alle Objekte

**Boxing/Unboxing**
    Automatisches umwandeln zwischen Referenz und Wertetyp. (Analog zu Java)

Common Language Runtime (CLR)
------------------------------
CLR ist die Laufzeitumgebung von .NET-Anwendungen.

Besteht unter anderem aus:
* Class Loader
* Type Checker
* JITter
* Exception Manager
* Garbage Collector
* Code manager
* Security engine
* Debug Machine
* ...

**Managed Code**
    Code, der von der CRL "verwaltet" wird: Plattformunabhängig.
**Unmanaged Code**
    Code, der nicht von der CRL "verwaltet" wird - bsp. Treiber, welche
    plattformabhängig sind.

.NET-Klassenbibliothek
-----------------------
Komplett Objektorientiert (auch ints usw.)

Namespaces
-----------
Dient der Strukturierung - analog zu den Packages in Java.
Verhindern Kollisionen von Klassenbezeichnern
Können hierarchisch Strukturiert werden.

Beispiele von Namespaces aus dem .NET-Framework sind ``System.Collections`` und ``System.IO``.


Microsoft Intermediate Language (MSIL)
---------------------------------------

* Vorkompilierte Zwischensprache
* Prozessor unabhängig
* Assembler ähndlich
* Analog zu Java Byte-Code

Macht .NET Plattformunabhängig (vgl. Mono-Projekt)

-> Bei der ersten Ausführung des betreffenden Codes wird
dieser just in time in nativen code übersetzt und gecached

Assembly
--------

Ein Assembly ist das Ergebnis einer Kompilierung von .NET-Quellcode.
Ist entweder ausführbar (EXE) oder eine Bibliothek(DLL).

Assemblys Können mehrere Dateien beinhalten.

Ein Assembly beinhaltet:

* MSIL-Code
* Metadaten zu den Klassen ("Inhaltsverzeichnis")
* Manifset (Metadaten zum Assembyl):
    * Name und Versionsnummer
    * Abhängigkeiten
    * Veröffentlichte Typen
    * Sicherheitsrichtlinien

Es gibt 2 Arten von Assemblies

**Private Assemblies**
    Nur für eine Applikation, typischerweise im Application-Root der Applikation.

**Public/Shared Assemblies**
    Können (gleichzeitig) von mehreren Applikationen verwendet werden (`C:\Windows\Assembly`)

.. seealso::

    `What are .NET Assemblies? - Stackoverflow <http://stackoverflow.com/questions/2972732/what-are-net-assemblie>`_


Ein Beispiel
-------------

Im Folgenden Beispiel verwendet ``ClassB`` ``ClassA`` aus
einer anderen Datei und einem anderen Namespace.

.. code:: c#

    // File ClassA.cs
    namespace A {
            public class ClassA {
                public void DoSomething() { /* ... */}
            }
     }

     // File ClassB.cs
     namespace B {
         using A;
         class ClassB {
             private void Work() {
                 ClassA a = new ClassA();
                 a.DoSomething();
             }
         }
     }

Um den Code zu Kompilieren muss wie folgt vorgegangen werden:

#. ``ClassA`` in eine DLL-bibliothek kompilieren:

    .. code::

        csc.exe /target:library ClassA.cs

#. ``ClassB`` in als Executable kompilieren und die ``ClassA`` libary linken

    .. code::

        csc.exe /target:exe /r:ClassA.dll ClassB.cs
