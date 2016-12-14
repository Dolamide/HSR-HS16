# WCF

Bei WCF muss sich der Entwicker nicht um die Kommunikation zwischen Server/Client künnern, sondern programmiert nur gegen eine Interface (Transparenter Proxy). In der Konfiguration kann dann festgelegt werden, wie und mit welchen Protokollen gearbeitet werden soll. WPF vereint also verschiedenste Kommunikationstechnologien in einem Framework unter einem identisches API ("unified programming model"). WCF ist Service-Oriented, also eine Spezifikation der Schnittstelle via Attribute und/oder via Konfigurationsfile und nicht über Technologie.

## Konzepte

Die Kommunikation erfolgt über "Endpoints", bestehend aus:

* **A** dresse. Die URL/URI, definiert als das _Wo_
* **B** inding. Spezifizert den Übertragungskanal, das Protokoll; also das _Wie_.
* **C** ontract. Interface-Definition, DTOs, Messages usw., also das _Was_.

Der Server kann einen MEX-Endpoint (Metadata Exchange) anbieten, welche eine WSDL-Definition zur verfügung stellt. Dies ermöglicht beispielsweise einen Client auf dieser basis zu generieren.

WS* ist ein gigantischer Standard rund um SOAP. WPF implementiert ein Subset davon.


## Programmierung

Alles rund um WCF ist im Namespace `System.ServiceModel` im Assembly `System.ServiceModel.dll` definiert.

Aufgrund der WCF Architektur müssen wir nur die Contracts programmieren. Binding & Endpoints können vom Admin verwaltet werden - in der `app.config` welche nebst dem Kompilat als output herauspurzelt. Die Verwendung der XML-Deklaratio ist nicht zwingend - alles auch programmatisch möglich - macht aber selten Sinn!

### Service Interface
```csharp
namespace TimeService
{
    // Interface Definition
    [ServiceContract]
    public interface ITimeService
    {
        [OperationContract]
        string GetTime();
        [OperationContract]
        TimeDescData GetTimeDesc();
    }

    // Definition eines DTOs
    [DataContract]
    public class TimeDescData
    {
        public TimeDescData()
        {
            TimeLong = DateTime.Now.ToLongDateString();
            TimeShort = DateTime.Now.ToShortDateString();
        }
        [DataMember]
        public string TimeShort { get; set; }
        [DataMember]
        public string TimeLong { get; set; }
    }
}
```

!!! warning

    `Data Contract` ist grundsätzlich optional, sollte aber in jedem Fall definiert werden, da sonst automatisch ALLE Properties / Public Fields übertragen werden.

### Client
Für die Programmierung des clients müssen die Metadaten heruntergeladen und ein Proxy generiert und verwendet werden (Visual Studio: Rechtsklick auf Projekt `Add Service Reference`). Bei diesem Ansatz können aber Informationen wie bsp. Properties oder der Typ einer Collection verlohren gehen.

Alternativ (und schöner, wenn Client und Server .NET) kann der Ansatz eines Shared Assembies gegangen werden. Ein solches enthält folgende geteilten Resourcen:

* Service Interfaces
* Data Contracts
* Weitere gemeinsame Komponenten

Dieses Assembli wird Client und Server deployed, wodurch Typeninformationen nicht verlohren gehen. Als Problem bleibt, dass wenn Annotation vergessen gehen findet man diese Fehler nur schwer.

Eine Musterimplementation mit dynamischer Konfiguration (App.config) und einem einfache Programm (`Program.cs`) kann wie folgt aussehen:

```xml
<?xml version="1.0"?>
<configuration>
  <system.serviceModel>
    <client>
      <endpoint address="http://localhost:8732/TimeService"
                binding="basicHttpBinding"
                contract="TimeService.ITimeService"
                name="TimeService" />
    </client>
  </system.serviceModel>
  <startup>
    <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.6"/>
  </startup>
</configuration>
```

```csharp
// Channel Factory erzeugen
var factory = new ChannelFactory<ITimeService>("TimeService");

// Proxy erzeugen - Verbindungsaufbau
ITimeService proxy = factory.CreateChannel();

// Aufruf 1
Console.WriteLine("GetTime {0}", proxy.GetTime());

// Aufruf 2
var timeDesc = proxy.GetTimeDesc();
Console.WriteLine("GetDimeDesc {0}, {1}", timeDesc.TimeShort, timeDesc.TimeLong);

// Dispose (Verbindungsabbau)
((IDisposable)proxy).Dispose();
```

### Server
Auf der Serverseite werden Contracts definieren (oder im Shared Assembly) und die Contracts implementiert. Zudem Hostet der Server den Service.

Die Implementation kann wie folgt aussehen:

```csharp
using System;
using System.Collections.Generic;

namespace TimeService
{
    public class TimeService : ITimeService
    {
        public string GetTime()
        {
            return DateTime.Now.ToString();
        }

        public TimeDescData GetTimeDesc()
        {
            return new TimeDescData();
        }

        public string MyTestString { get; set; }
        public SortedList<string, string> MySortedList { get; set; }
    }
}

```

#### Hosting

Ein WCF Service kann auf 3 verschiedene Arten gehosted werden:

* Visual Studio Autohosting (Development)
* Manuell via ServiceHost Klasse
    * Windows Service
    * Client Application
    * ...
* Internet Information Services IIS
    * Internet Information Service IIS 5+ / Express
    * Windows Activation Service WAS

Wie der Service effektiv gehosted wird kann in der `App.config` angegeben werden:

```xml
...
<services>
  <!-- Name muss gleich wie Name in behavior sein -->
  <service behaviorConfiguration="TimeService.TimeServiceBehavior" name="TimeService.TimeService">
    <!-- Entpoint für das Interface TimeService.ITimeService, relativer pfad zur baseAddress -->
    <endpoint address="" binding="basicHttpBinding" contract="TimeService.ITimeService"/>
    <!-- Entpoint für das Interface TimeService.ITimeService, relativer
         pfad zur baseAddress (http://.../TimeService/mex) -->
    <endpoint address="mex" binding="mexHttpBinding" contract="IMetadataExchange"/>
    <host>
      <baseAddresses>
        <add baseAddress="http://localhost:8732/TimeService/"/>
      </baseAddresses>
    </host>
  </service>
</services>

<behaviors>
  <serviceBehaviors>
    <behavior name="TimeService.TimeServiceBehavior">
        <!-- Metadaten können abgefragt werden -->
      <serviceMetadata httpGetEnabled="True"/>
      <!--  Exceptions nicht an den Client weitergeben -->
      <serviceDebug includeExceptionDetailInFaults="False"/>
    </behavior>
  </serviceBehaviors>
</behaviors>
...
```

### Faults
Exception-Klassen sind nicht serialisierbar (Ausnahme `FaultException<T>` (generisch, nicht generisch)). Für die Übertragung von Fehlern werden darum Faults-Klassen (nicht von Exception abgeleitet!) definiert und im Fehlerfall abgefüllt. = Fehlerinfo.

```csharp
// Service definition
[ServiceContract]
public interface ICalculator
{
    // ...
    [OperationContract]
    [FaultContract(typeof(MathFault))]
    int Divide(int n1, int n2);
}

// DTO Fault Typ
[DataContract]
public class MathFault
{
    [DataMember]
    public string Operation { get; set; }
    [DataMember]
    public string ProblemType { get; set; }
}

// Implementation im Service
public class CalculatorService : ICalculator
{
    public int Divide(int n1, int n2)
    {
        try
        {
            return n1 / n2;
        }
        catch (DivideByZeroException)
        {
            MathFault mf = new MathFault { Operation = "division", ProblemType = "divide by zero" };
            throw new FaultException<MathFault>(mf);
        }
    }
}

// Abfangen im Client
try{
    proxy.Divide(1, 0);
catch (FaultException<MathFault> e)
{
    // ...
}
catch (FaultException e)
{
    // ...
}
catch (Exception e)
{
    // ...
}
```

## Kommunikations-Muster

Gibt verschiedene Kommunikations-Muster:

* One Way (Fire-and-Forget) - wird asynchron im Hintergrund abgefeuert. Keine Return value - folglich funzen Server-Seitige Exceptions auch nicht.

    ```
    [OperationContract(IsOneWay = trye)]
    void StoreProblem(ComplexProblem p);
    ```
* Request-Reply (synchron)(default)
* Duplex (asynchron) - analog zu OneWay - aber braucht auch CallbackContrackt.
    * Vorsicht: ICalcCallback: Hat KEINE attribute!
    * Client implementiert Callback Interface - server arbeitet gegen dieses Interface.
    * TODO: F45-F46

    ```
    // Server
    [ServiceContract(
        SessionMode = SessionMode.Required,
        CallbackContract = typeof(ICalcCallback))]
    public interface ICalculatorDuplex
    {
        [OperationContract(IsOneWay = true)]
        void Clear();

        [OperationContract(IsOneWay = true)]
        void AddTo(double n);

    }

    // Client
    public interface ICalcCallback {
        [OperationContract(IsOneWay = true)]
        void Result(double result);
    }
    ```

## Address
Ganz normale URIs: `[transport]://[domain][:port][path]`

## Binding

* Definition des Übertragungskanal
   * Reliability: End-to-End, keine, ordered/unordered
   * Security: Transport-Security, Message Security, Authentication/Authorisation
   * Transport-Protokolle (HTTP, TCP/UDP, P2p etc.)
   * Encoding
* Kommunikationsmuster
* Transaktions-Management (Server oder Client Seite)
* Security
* Interoerabilität (WS-*, WCF, REST etc.)

Typischer Fehler: Server und Client haben nicht das gleiche Binding!

Binding wird via im Metadata Exchange (MEX) publiziert.

Mehrere Bindings pro Service und eigene Bindings sind möglich.

Evtl. Aus Folien ergänzen.

## Data Contract v2 (oben ergänzen)
* WCF kann mit allen CLR Typen arbeiten.
* Data Contract: Wie Serialisiere ich meine Klasse

Ganz normale Klasse - mit den Aspekten (Attributen).

Vorsicht: Wenn kein DataContract definiert: Alles wird serialiser (böse)
-> Whitelisting

Generierung von WSDL:

* Suche alle public Service-Interfaces.
* Suche nach exponierten, komplexen Typen auf ServiceContracts.
    * werden rekursiv abgeackert

Problem Vererbung:

* Abgeleitete Klassen nicht sichtbar => Siehe Folien F16. (CommunicationException)

```csharp
[ServiceContract]
public interface IClassroomService
{
    [OperationContract]
    List<Student> GetStudents();
}

[DataContract]
public class Student { }

[DataContract]
public class TiredStudent : Student { }

[DataContract]
public class BoredStudent : Student { }
```

Darum:

```csharp
[KnownType(typeof(TiredStudent))]
[KnownType(typeof(BoredStudent))]
[DataContract]
public class Student { }
```

(Alternativ: Methode: `IEnumerable<Type> GetKnownTypes() {}`) oder in der App.config.

Gleiches gilt für nicht-Generische listen etc. bzw. halt object...

Problem: Typ hinter Interface - auf Operation contract. F18, F19ff

## Serialisierung

23
Wird 2x separat serialisiert

24
Wenn mehrere -> Linke mit id/Ref - Problem: Zyklisch!

25 (NB)

26 -> Version Tolerant (neue Propertiues)

27 sonst default...

## Behaviors

Instanzmodell: Mit welcher Objekt-Instanz wird in einer Response beim Service-Host gearbeitet: 1. Single (geteilte instaz), Per Call, Per Session.

=> INteressiert logischerweise NUR den Server, nicht den client.

Evtl. Code F30

F31: Spezialfall Per Session

..

Concurrency: Skip Transaktionen
