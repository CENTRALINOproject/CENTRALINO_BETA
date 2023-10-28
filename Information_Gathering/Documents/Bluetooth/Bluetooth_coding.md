# Bluetooth Codici 

## Note preliminari:

Citazione dalla grande guida dei moduli HC-0X :

 > "3. Notes. (1) HC-03 and HC-05’s command should end up with “\r\n”. It means when you finish programming, you should add terminator (“ENTER” or “0x0d 0x0a”) to the program. It’s different from HC-04 and HC-06 (They don’t need terminator)." 
 
-cit [source](http://cdn.instructables.com/ORIG/FKY/Z0UT/HX7OYY7I/FKYZ0UTHX7OYY7I.pdf)

Secondo la guide di Arduino e instructables i pin del bluetooth vanno connessi così: 
> Pin del Micro per RX ———->      TX

> Pin del Micro per TX ———->      RX

> 3.3V         ———->      VCC

> GND        ———->      GND


### Librerie necessarie:

#include <SoftwareSerial.h>


### Dichiarazioni:

Pre-setup & post-libreria questo :
 - SoftwareSerial nomedelsoftwareseriale(esempio:"bluetooth")(PIN RX,PIN TX);
Nel setup:
 - Nomedelsoftwareseriale.begin(38400);

"In modalità AT il modulo HC comunica a 38400 baud." -cit
"Gran parte di questo capitolo è preso da questa guida su Instructables. Per cambiare configurazione al vostro modulo (ad es. cambiare velocità di trasmissione, nome, pin, ecc.) dovete entrare in modalità AT. L'HC-06 dovrebbe essere sempre in questa modalità, mentre l'HC-05 dev'essere acceso tenendo premuto il tasto "KEY" oppure mettendo a +3.3v il pin key sulla board. " 
-cit http://www.raspibo.org/wiki/index.php?title=HC-05_e_HC-06#Differenze_HC-05_e_HC-06


## Funzioni:

### Verifica della connessione :
#Questa funzione ritorna 1 se la software serial è attiva e sta "ascoltando" (streammando il flusso dati) mentre ritorna 0 se non sta "ascoltando" .


``` C++
int nomedelsoftwareseriale_connection_state()
  {int a=0;
if (nomedelsoftwareseriale.isListeninig())
{a=1}
return a; 
  }
  ```



### Flush del buffer sul software seriale :
#Questa funzione semplicemente scarta TUTTO quello che c'è nel buffer inserendolo nella variabile flush e sovrascrivendolo ogni volta. Non c'è modo di invertire questa funzione.

``` C++
void buffer_flush()
{
  while(nomedelsoftwareseriale.available()>0)
    {
    char flush = nomedelsoftwareseriale.read();
    }
} 
```

### Trasmissione di un messaggio intero e stringa :
#Questa funzione trasmette sul software seriale inizializzato (qualsiasi dipendentemente dal nomedelsoftwareseriale ) una stringa o un intero passata/o alla funzione, il nome della variabile nella funzione è 'transimission'.
``` C++
void message_string_transmit (string transmission)
{
nomedelsoftwareseriale.write(transmission);
}

Piccola variante della funzioni precedenti che permette di inviare variabili di interi. 

void message_int_transmit (int transmission)
{
nomedelsoftwareseriale.write(transmission);
}
```

### Funzione per la restituzione della lunghezza del buffer del software seriale.

``` C++
int buffer_lenght();
{int lenght=0;
x=nomedelsoftwareseriale.available();
return x;
}
```

### Verifica dei messaggi :
#Questa funzione ritorna il contenuto del buffer del software seriale se presente altrimenti ritorna NULL, se il buffer supera il limite di 2048 elementi il buffer non viene letto e viene flushato poiché illeggibile.
Esiste anche readString ma questo metodo mi sembra più sicuro, non ottimale, sicuro.

``` C++
char serial_buffer_retrieve() 
{int char_ind=0, char_ind2=0, x; 
 x=lenght_buffer();

if (x>0)&&(x<2048)
#'x>0' significa che ci sono x dati nel buffer, svuota (buffer_flush()) il buffer se ci sono più di 2048 elementi, altrimenti si va verso il buffer overflow.
{
      char buffer_retrieve[x];
 
      #inizializzazione buffer_retrieve[x](sotto) 
for (char_ind=0; char_ind<x; char_ind++) 
{
buffer_retrieve[char_ind]=' ';
} 

#scrive su buffer_retrieve[x](sotto)
for (char_ind2=0; char_ind2<x; char_ind2++) 
{
char_retrieve[char_ind2] = nomedelsoftwareseriale.read(); 
} 
return char_retrieve[x]; 
} 
buffer_flush();
return null;
}
```

Funzione per l'identificazione (detecting) di messaggi singoli o multipli contenuti nel vettore di caratteri passato alla funzione. 
Si utilizza la variabile char end_message per stabilire una combinazione di caratteri all'interno del messaggio con il significato di 'fine messaggio'.
Si utilizza la variabile int lenght per sapere quanto è lungo il vettore di caratteri essa sarà calcolabile grazie alla funzione buffer_lenght(), la funzione appena esplicitata andrà posizionata con criterio prima della funzione serial_buffer_retrieve;
La funzione ritorna il numero di messaggi (il numero di volte che viene trovato nel vettore 'detecting' il vettore char 'end_message') sotto forma di intero.

### Esempio : 

Vettore end_message = "*r"
Vettore detecting = "ciao *r come *r stai? *r"
in questo esempio verrano detectati 3 messaggi (3 volte è presente "*r").

``` C++
int message_detect(char detecting[], char end_message[|2 circa?|], int lenght)
{int number_of_messages=0, utility_ind=0;
for( utility_ind=0; utility_ind<lenght; utility_ind++)
{
if( detecting[utility_ind] == end_message[1])
if(( detecting[utility_ind+1] == end_message[2])&&(utility_ind!=lenght-1))
#la riga sovrastante serve ad evitare che venga letto un carattere in più rispetto alla lunghezza del vettore stesso. (esempio utility_ind==19 allora utility_ind+1==20 QUESTO NON DEVE ACCADERE) questo problema è anche risolvibile modificando il for ma una soluzione vale l'altra in questo caso.
  number_of_messages++; 
}
return number_of_messages;
}
```