<p align = "center">
<img src = "Design/Logo/logo_outline_black.png" width = "70%" title = "Logo">
</p>

> **Arduino-powered device** for _near-field_ **remote control of multiple power outlets**. 
> 
> The device can be programmed and scheduled with timers thanks to its internal clock. 
> 
> It can be **easily configured using its Android app** counterpart, which is designed for devices operating with Android provided of a _bluetooth transmitter_.

# CENTRALINO
_Your world in your hand._
<p align = "right">
Last modified: 19th June 2017
</p>

## Hi, I'm Filippo 👋
This is a very old project of mine, it was born in January 2017 and concluded in June the same year. 
This was my first project in the field of electronics and programming.
I was 17 years old and I guess you can tell I was a bit naive, but I was very passionate about it and I still am.

This project has many flaws, but it was a great learning experience, I'm quite fond of it, so I decided to share it here as something to remember. 

Something that will always suggest how ...
<p align = "right">
<b>...every long journey begins with a first step.</b>
</p>

------------------------------------------------------
##### Small note on language:
The project was born in Italian, so unfortunately many of the comments in the code as well as documentation and the report are in Italian.
I apologize for this, but I hope that the code is still understandable and that the documentation is still useful (maybe with the help of a translator).
However, I decided to have at least the README in English, so that the core of the project as well as the repository structure is understandable to everyone.

### Project reference sector.
Novel technologies, Internet of Things.

### Idea and objective:

The project was born with the purpose of making residential and working complex more connected to the people who inhabit it. The project aims to enhance humans environmental control. 
CENTRALINO is designed to control electrical devices such as household appliances, electric, air conditioners, heating systems, and similar.
This centralization of control can, in some cases, change a person's experience with the surrounding world. The CENTRALIzation of automation is sometimes not just a convenience but a necessity, i.e. in case of subjects with disabilities. In such cases, "smart homes" are a topic that companies are vigorously addressing to offer increasing automation and integration between systems and services. 
Home automation involves a complex mix of various technologies and requires strong interdisciplinary collaboration.

Therefore, the CENTRALINO project aims to:

 - Enhance security of electrical devices populated environments.
 - Reduce operating costs.
 - Convert old environments and old systems into more dynamic ones.
 - Simplify the design, installation, maintenance, and use of technology.
 - As a whole: improve the quality of life.

### Description of the project:

The project is named "CENTRALINO" (Italian for "switchboard"), the name reflects its function of both **centralizing** and **managing** control, much like in telecommunications. 
It is a device that allows remote control of multiple power outlets with the ability to be programmed and scheduled at intervals using an internal clock. The device is easily configured with mobile devices such as phones, tablets, or computers. The latter only needs to support applications designed for Android operating systems and have a Bluetooth transmitter.
2.2. Reference sector: new technologies, Internet of Things (IoT), home automation.

Functions
3.7. Currently, there are three functions, but the most important aspect is that there is a foundation that anyone can use to develop their own custom functions. The functions are as follows:

Instant On/Off - For greater safety, future security measures will be implemented to prevent continuous switching on and off of the same outlet to avoid damaging the connected devices and the microcontroller itself.
On/Off with an alarm - It uses the RTC (Real-Time Clock) to compare CENTRALINO's time with the user-set "alarm" time.
On/Off with a timer - It uses the <Time.h> library, which allows the use of a time and date storage tool and ensures an always up-to-date local time without the need for an RTC device. Continuously querying the RTC would consume too much battery power, and since replacing the RTC battery takes time, it is preferred to use the mentioned library to increase battery life. The physical CENTRALINO device receives the timer duration in minutes from the CENTRALINO software application and performs operations to determine the corresponding hours, minutes, and seconds.


### Functions.

### Tools used (Software).
-Fritzing: is a free software for electronic design, focused on the transition from simple prototypes to the printed circuit board to be sent to production. It is useful for designing the prototype of the circuit even before it is built.
-Arduino IDE: is the integrated development environment (Integrated Development Environment) of Arduino, it is a multiplatform application in Java used to compile the code with which the microcontroller that manages the sensors and other components is programmed.
-AliExpress: is a branch of the "Alibaba Group" company that unites Chinese companies and offers a retail service to an international market, mainly targeting European buyers. It is the supplier of our components.
-Python interpreter: It is a high-level, object-oriented, suitable programming language, among other uses, for developing distributed applications, scripting, numerical computation and system testing. It is useful for writing and running programs for Windows, Android and a selected distribution of Linux.
-Android SDK: (Software Development Kit) Software Development Kit. Through the SDK we can go from the description of our application to its actual execution both in emulation and on a concrete device. It is useful for creating an Android application in Java that will interface with Glovino © via the phone's Bluetooth module.

### Tools used (Hardware):

     • Welder.
     • Pond.
     • Cellulose adhesive tape (scotch).
     • Technical material for the construction of the membrane that will be applied to the user's hand and the components that will in turn be applied to it.
     • Still unknown plastic material for the creation of a portable and good-looking structure that will be applied to the user's forearm. It will contain the "control unit" with microcontroller and all the components at risk of impact and will obviously be connected to the components on the hand. The aim is to create a structure made up of a single piece that is easily and comfortably wearable (the part on the hand and the part on the forearm are not physically separated at all even if they are sometimes spoken of separately).

### Components used (Hardware):

     • Jumpers for solderless male-male connections.
     • Bread Board for experimental prototypes of solderless circuits.
     • Buzzer Module – Buzzer Module.
     • Pulse sensor - sensor module for heart rate detection.
     • Infrared emitting LEDs.
     • Infrared receiver.
     • Buttons/Buttons.
     • MPU 6050 3-Axis (gyroscope) + 3-Axis (accelerometer) module using I2C protocol.
     • Tags NFC (Near Field Connection) Narrow field connection, adhesive tags.
     • RFID Tag NFC Reader – NFC tag reader/programmer.
     • Membrane switch with 4 buttons for selection.
     • Bluetooth transceiver module – module for Bluetooth transmission and reception.
     • Micro SD Mini Slot – Module for connection with a micro SD card for data storage.
     • Assortment of resistors from 1 to 10 M Ohm (Ω).
     • 0.96'' OLED DISPLAY (screen) using I2C protocol.
     • RTC (Real Time Clock) Real Time Clock – module with battery.
     • Micro ATmegax32u4 powered by 5V (microcontroller).
     • Flex Sensor – sensors for flexion (research stage).

### Cost of components:

     • Jumpers = 120 pieces for €2.39.
     • Bread Board = 2 pieces for €0.74.
     • Buzzer Module = 1 piece for €0.38.
     • Pulse sensor = 1 piece for €2.09.
     • Infrared LEDs = 20 pieces for €1.25.
     • IR receiver = 10 pieces for €0.73.
     • Buttons/Buttons = 100 pieces for €1.44.
     • NFC Tags = 10 pieces for €1.72.
     • RFID (Radio Frequency IDentifier) = 1 piece for €2.77.
     • RTC (Real Time Clock) = 1 piece for €1.20.
     • Assortment of resistors = 300 pieces for €1.62.
     • MPU 6050 Module = 2 pieces for €1.30 each.
     • Membrane switch = 2 pieces for €0.53 each.
     • Bluetooth = 2 pieces for €2.73 each.
     • Micro SD Mini slot = 2 pieces for €0.47 each.
     • 0.96'' OLED DISPLAY = 3 pieces for €2.49 each.
     • Micro ATmegax32u4 = 3 pieces for €4.59 each.
TOTAL = €54.15 + €10 (shipping costs) = €64.15


### Main issues:
As we still have to delve into the project, the problems are still being studied, however some appear obvious:
     • Studying computer languages in an indigenous way, time represents the biggest obstacle for this problem, everything can be learned if you have enough time to try and try again what you are creating. There are 3 (approximately) languages to learn. Java, Python and C (despite its affinities with C++ learned at school, writing with C involves some differences).
     • The search for specific and as approximate documentation as possible. This research concerns everything we have to study on our own (practically everything, from the PRACTICAL side), in fact these documents are less easy to find than one might think. It may seem trivial but when you find yourself having to connect all the sensors and the different components it is more than a good idea to have done in-depth research regarding the current voltages of each one, the types of connections, the types of communication protocols used and all the small details relating to each of them. Same thing goes for all software used (as far as knowing the details is concerned).
     • The BIGGEST problem is undoubtedly the one linked to funds. In fact, the components we are going to buy are rather "convenient", for two reasons:
         1. Because it is a prototype.
         2. (Most relevant reason) Because we don't have the funds to pay for more accurate and better made components. The ones we are buying are clones. Their creation is possible thanks to the fact that this market sector is almost strictly open source and therefore allows each manufacturer to produce their own components even if they are of poor quality. The "better" components would cost much more than we can afford. (For example, the same microcontroller we are buying at €4.59 each "officially" costs €20 and is certainly of better quality, however it is not a choice that we can consider for our funds).
     • Convince the class council to accept this project.

Date
Castellani Filippo
01/20/2017


# Nome del progetto
Centralino 

# Settore di riferimento.
Nuove tecnologie, Internet of Things (Internet delle Cose).
Obbiettivo:
Realizzare un rivestimento coprente parzialmente l'area compresa tra avambraccio e dita, provvisto di una serie di sensori e una centralina che permetta l'interfacciamento di un utente umano ad : 
    • Un PC provvisto di sistema operativo Windows o una distribuzione selezionata di Linux.
    • Un telefono con sistema operativo Android.
    • Qualsiasi apparecchio elettronico provvisto di un ricevitore e/o un emettitore infrarossi.
Si potrà interagire in vari modi :
    • Modificando posizionamento e orientamento della mano.
    • Tramite l'utilizzo di "gestures" (gesti volontari della mano adibiti all'esecuzione di specifiche azioni).
    • Tramite la flessione delle dita (in particolare indice e pollice).
    • Tramite la pressione di diversi pulsanti posti sulla centralina presente sull' avambraccio.
    • L'output sarà visivo tramite la visualizzazione di informazioni su un piccolo schermo posto sul dorso della mano.
Descrizione del progetto:
Il guanto permetterà di eseguire comandi, interagire con funzioni del sistema con cui è connesso (ad esempio: Stato del Wi-Fi, Volume degli altoparlanti, e così via… ).
Mediante un software di supporto, da noi sviluppato, sarà possibile registrare e replicare una trasmissione a infrarossi, al fine di controllare dispositivi come televisori, ventilatori o luci. Questa applicazione è interamente attinente ad un intera area di sviluppo tecnologica che in questi anni sta prendendo largamente piede, ovvero la IoT (Internet of Things), letteralmente tradotto come "Internet delle Cose" è un neologismo riferito all'estensione di Internet al mondo degli oggetti e dei luoghi concreti
Funzioni.
Saranno sviluppate alcune funzionalità indicative delle diverse possibilità d'utilizzo del guanto:
    • Sincronizzazione con l'applicazione navigatore di Android (solo con telefono), che permette di utilizzare il guanto come un navigatore grazie al suo schermo.
    • Ricezione delle notifiche da telefono (Android).
    • Avviso di chiamate in entrata, e possibilità di accettare o rifiutare la chiamata(Android).
    • Glovino ©  sarà provvisto di un sensore adibito al rivelamento della frequenza cardiaca e questo potrebbe portare ad un ampio utilizzo dello stesso per funzionalità quali : utilizzo per il fitness, possibili segnalazioni di emergenza in caso di arresto cardiaco, monitoraggio del sonno, e molte altre…
    • Modalità Mouse e Tastiera configurabile con qualsiasi sistema operativo tra Windows, Android e una distribuzione selezionata di Linux.
    • Lanciare applicazioni del PC o del cellulare mediante delle scorciatoie ("shortcut") configurabili attraverso gli appositi programmi di configurazione del guanto, da noi sviluppati. 
    • Glovino © sarà provvisto di un sensore RFID (Radio Frequency IDentification= Identificatore di Radio Frequenze) per il rilevamento e la riprogrammazione di Tag NFC (targhette NFC, chip magnetici che non necessitano di energia per conservare piccole quantità di dati, ma che hanno un piccolo raggio di trasmissione dati). Questo sarà utile per funzioni quali: lancio di alcune sequenze pre-programmate (scriptate) e/o personalizzate, il tutto tramite il semplice contatto tra una targhetta NFC(dimensione di una moneta) e Glovino ©. Lo si utilizzerebbe come con una tessera magnetica utile ad aprire porte o accedere a determinate informazioni, riservate o meno.


    • La possibilità di riprodurre "macro" (sequenze di tasti), utili per automatizzare diversi compiti di un utente.
    • La possibilità di creare diversi profili personalizzando i controlli del guanto per ogni utenza creata. La personalizzazione di un profilo varierà in base all' impostazione di combinazioni. Al fine di creare più combinazioni possibili tutti i seguenti fattori permetteranno di creare una combinazione differente.
        I. Inclinamento del polso.
        II. Posizionamento di indice e pollice.
        III. Spostamento della mano.
        IV. Pressione di diversi pulsanti.
Strumenti utilizzati (Software).
-Fritzing: è un software libero per la progettazione elettronica, focalizzato sul passaggio da semplici prototipi al circuito stampato da inviare alla produzione. Ci è utile per disegnare il prototipo del circuito ancora prima che venga costruito.
-Arduino IDE: è l'ambiente di sviluppo integrato (Integrated Development Enviroment) di Arduino, è un'applicazione multipiattaforma in Java usata per compilare il codice con cui viene programmato il microcontrollore che gestisce i sensori e gli altri componenti.
-AliExpress: è un ramo dell'azienda "Alibaba Group" che unisce imprese cinesi e offre un servizio di vendita al dettaglio a un mercato internazionale, rivolgendosi prevalentemente a compratori europei. E' il fornitore dei nostri componenti.
-Interprete di Python: è un linguaggio di programmazione ad alto livello, orientato agli oggetti, adatto, tra gli altri usi, per sviluppare applicazioni distribuite, scripting, computazione numerica e system testing (verifiche di sistema). Ci è utile per scrivere ed eseguire i programmi per Windows, Android e una distribuzione selezionata di Linux.
-Android SDK: (Software Development Kit) Kit per lo Sviluppo del Software . Tramite l'SDK possiamo passare dalla descrizione della nostra applicazione alla sua effettiva esecuzione sia in emulazione, sia su un dispositivo concreto. Esso ci è utile per creare in Java un' applicazione Android che si andrà ad interfacciare con Glovino © tramite il modulo bluetooth del telefono.
Strumenti utilizzati (Hardware):
    • Saldatore.
    • Stagno.
    • Nastro adesivo di cellulosa (scotch).


    • Materiale tecnico per la costruzione della membrana che andrà applicata sulla mano dell'utente ed i componenti che verranno applicati a loro volta su essa.
    • Materiale plastico ancora sconosciuto per la realizzazione di una struttura portatile e di bell'aspetto che andrà applicata sull'avambraccio dell'utente. Essa conterrà la "centralina" con microcontrollore e tutti i componenti a rischio urto e sarà ovviamente connessa ai componenti sulla mano. Si punta a creare una struttura composta di un unico pezzo facilmente e comodamente indossabile (la parte sulla mano e quella sull'avambraccio non sono per nulla staccate a livello fisico anche se si parla di loro a volte in modo separato). 

Componenti utilizzati (Hardware):
    • Ponticelli per la connessione senza saldature del tipo maschio-maschio.
    • Bread Board per prototipi sperimentali di circuiti senza saldature.
    • Buzzer Module – Modulo Buzzer.
    • Pulse sensor - modulo sensore per rivelamento della frequenza cardiaca.
    • Led emettitori di infrarossi.
    • Ricevitore infrarossi.
    • Bottoni/Pulsanti.
    • MPU 6050 Modulo a 3 Assi (giroscopio) + 3 Assi (accelerometro) utilizzante protocollo I2C.
    • Tags NFC (Near Field Connection) Connessione a Campo Ristretto, targhette adesive.
    • RFID Tag NFC Reader – Lettore/Programmatore di targhette NFC.
    • Interruttore a membrana con 4 tasti per la selezione.
    • Bluetooth transceiver module – modulo per la trasmissione e la ricezione bluetooth.
    • Slot Micro SD Mini – Modulo per la connessione con una scheda micro SD per la conservazione dei dati.
    • Assortimento di resistenze da 1 a 10 M Ohm (Ω).
    •  0.96'' OLED DISPLAY (schermo) utilizzante protocollo I2C.
    • RTC (Real Time Clock) Orologio Tempo Reale – modulo con batteria.
    • Micro ATmegax32u4 alimentato a 5V (microcontrollore).
    • Flex Sensor – sensori per la flessione (stadio di ricerca).

Costo dei componenti:
    • Ponticelli = 120 pezzi per 2,39 €.
    • Bread Board = 2 pezzi per 0,74 €.
    • Buzzer Module = 1 pezzo per 0.38 €.
    • Pulse sensor = 1 pezzo per 2,09 €.
    • Led infrarossi = 20 pezzi per 1,25 €.
    • Ricevitore IR = 10 pezzi per 0,73 €.
    • Bottoni/Pulsanti = 100 pezzi per 1,44 €.
    • Tags NFC = 10 pezzi per 1,72 €.
    • RFID (Radio Frequence IDentifier) = 1 pezzo per 2,77 €.
    • RTC (Real Time Clock) = 1 pezzo per 1,20 €.
    • Assortimento resistenze = 300 pezzi per 1,62 €.
    • MPU 6050 Modulo = 2 pezzi per 1,30 € cada uno.
    • Interruttore a membrana = 2 pezzi per 0,53 € cada uno.
    • Bluetooth = 2 pezzi per 2,73 € cada uno.
    • Slot Micro SD Mini = 2 pezzi per 0,47 € cada uno.
    •  0.96'' OLED DISPLAY = 3 pezzi per 2,49 € cada uno.
    • Micro ATmegax32u4 = 3 pezzi per 4,59 € cada uno.
TOTALE = 54,15 € + 10 € (spese spedizione) = 64,15 € 
(Per la produzione di 2 Glovino ©).

Da notare che non sono ancora assenti i Flex Sensor, i sensori per la flessione per pollice ed indice il cui costo è tra i più alti e si aggira tra i 7 € cada uno, prendendone 4 (per 2 Glovino ©) si stimano 28 € e più da aggiungere al totale.
Competenze necessarie:
-Inglese: 
Le ricerche necessarie a comprendere e documentarsi sulle strumentazioni più adatte a dar vita a questo progetto sono in vasta preponderanza presenti sul web in lingua inglese.
Senza la conoscenza della lingua fare ricerche specifiche sarebbe quasi impossibile.
C'è inoltre grande bisogno di una conoscenza di termini tecnici della lingua poiché si utilizza un determinato tipo di lessico nelle documentazioni al proposito di apparecchi elettronici.


-Fisica e Matematica:
Conoscenza necessaria per la scrittura di algoritmi adibiti ai calcoli relativi al calcolo di inclinazione del giroscopio e accelerazione dell' accelerometro. Questi ultimi avvengono in particolare mediante l'utilizzo di formule fisiche relative a:
    • La velocità angolare per quanto riguarda l'orientamento del giroscopio.
    • La distanza mediante accelerazione e tempo di accelerazione. 
In più sono necessarie diverse formule e algoritmi indispensabili per il funzionamento dei programmi.

-Informatica:
Vengono utilizzati per la produzione del progetto i seguenti linguaggi di programmazione :
    • Python.
    • Java.
    • C.
Non sono strettamente collegati allo studio effettuato a scuola, tuttavia i metodi per interfacciarci ed imparare nuovi linguaggi sono in maggior parte legati allo studio in aula.
-Elettronica:
Conoscenze per l'assemblaggio, la saldatura dei componenti e la realizzazione del circuito.

-Italiano:
Capacità descrittive per la più adeguata forma di descrizione e spiegazione per un progetto che necessita di alte capacità lessicali per non fraintenderne il funzionamento.
Necessarie per la compilazione di un manuale tecnico facilmente interpretabile.

-Tecnologia progettazione di sistemi:
Conoscenza di tecniche per lo sviluppo di:
    • Software.
    • Interfaccia per l'utente.
    • Interfacciamento tra il sistema operativo di Glovino © e ogni altro sistema operativo e apparecchio elettronico. 
Le sottocategorie sono innumerevoli perciò adottiamo queste due grandi categorie a simbolo delle vaste conoscenze necessarie.


-Organizzazione d'impresa:
Possibili risvolti futuri non ancora presi in considerazione per mancanza di tempo.
La parte relativa ad "Organizzazione d'impresa" 
potrebbe essere facilmente 
soggetta a cambiamenti futuri. 18/01/2017
-Capacità manuali e di inventiva:
Da non sottovalutare.
Problematiche principali:
Dovendo ancora andare a fondo nel progetto le problematiche sono ancora in fase di studio tuttavia alcune appaiono palesi :
    • Lo studio di linguaggi informatici in modo autoctono, il tempo rappresenta il più grande ostacolo per questo problema, ogni cosa si può imparare se si ha tempo a sufficienza per provare e riprovare ciò che si sta creando. I linguaggi da imparare sono 3 (circa). Java, Python e C (nonostante le sue affinità con C++ imparato a scuola, scrivere con C comporta alcune differenze).
    • La ricerca di documentazioni specifiche e il meno approssimative possibile. Queste ricerche riguardano tutto ciò che dobbiamo studiare da soli (praticamente tutto, dal lato PRATICO),  queste documentazioni infatti sono meno facili da reperire di quanto si creda. Può sembrare banale ma nel momento in cui ci si trova a dover connettere tutti i sensori, i differenti componenti è più che bene aver fatto approfondite ricerche per quanto riguarda le tensioni di corrente di ognuno, i tipi di connessione, i tipi di protocolli di comunicazione usati e tutti i piccoli dettagli relativi ad ognuno di essi. Stessa cosa vale per tutti i software utilizzati (per quanto riguarda la conoscenza dei dettagli).
    • La problematica più GRANDE è senza dubbio quella legata ai fondi. Infatti i componenti che stiamo andando a comperare sono piuttosto "convenienti", questo per due motivi :
        1. Perché è un prototipo.
        2. (Motivo più rilevante) Perché non abbiamo i fondi per pagare dei componenti che siano più accurati e di miglior fattura. Quelli che stiamo comperando sono dei cloni. La loro realizzazione è possibile grazie al fatto che questo settore di mercato è quasi strettamente open source e permette perciò ad ogni produttore di produrre i propri componenti anche se di scarsa qualità. I componenti "migliori" verrebbero a costare molto più di quanto possiamo permetterci. (Per esempio lo stesso microcontrollore che stiamo acquistando a 4,59 € l'uno costa "ufficialmente" 20 € ed è sicuramente di miglior qualità, tuttavia non è una scelta che noi possiamo prendere in considerazione per i nostri fondi).
    •  Convincere il consiglio di classe ad accettare questo progetto.

Data
Castellani Filippo
20/01/2017
