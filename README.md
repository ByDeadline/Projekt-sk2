
# Sieciowy Type-Rircer 
### Projekt-sk2

strona serwerowa napisana w C++ uzywajac BSD Api
client napisany w pythonie uzywajac PyGame

## Plan Gry:
### Gracz: 
Gracz łączy się z serwerem, i wybiera nick.

Następnie trafia do lobby gdzie widzi listę pokoi oczekujących na rozpoczęcie gry z którymi może się połączyć.

Gracz po dołączeniu widzi tabelę z nickami graczy oraz ich stanem gotowości. 

Gra rozpoczyna się jeśli jest minimum 2 graczy i każdy z nich ma status gotowy.

W czasie gry gracz widzi tekst który musi napisać, tekst który już napisał, procentowy progres. 

Gra trwa tak długo aż wszyscy gracze nie skończą pisać lub do końca określonego czasu. 

Wygrywa gracz który skończy pisać jako pierwszy. Po zakończeniu wyświetlana jest tabela wyników i guzik powrotu do lobby. 

### Admin: 
Admin ma możliwość:
- wyświetlania, wszystkich graczy i pokoi w których są
- wyświetlania wszystkich pokoi
- tworzenia i zamykania pokoi

