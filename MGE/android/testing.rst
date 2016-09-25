Testing
=======

**Local unit tests**
    Laufen auf der lokalen JVM - ohne zugriff auf Android Framework APIs

    Eigent sich für Logik, welche nicht von Android frameworks abhängig ist.

    "Einfache" interaktionen des Android frameworks können mittels Mocking
    umgangen werden (Bsp. mit Mockito)

    Verzeichnis: ``module-name/src/test/java/``
**Instrumented tests**
    Tests, welche auf einem Android Gerät (Hardware oder Emulator) laufen.

    Werden eine APK gepackt und vom Sytem ausgeführt. Wird im gleichen Prozess wie
    die App under test ausgeführt, damit auf Funktionallität der App zugegriffen werden
    kann.

    Verzeichnis: ``module-name/src/androidTest/java/``


.. seealso::

        `Getting Started with Testing <https://developer.android.com/training/testing/start/index.html>`_
        `Building Local Unit Tests <https://developer.android.com/training/testing/unit-testing/local-unit-tests.html>`_
