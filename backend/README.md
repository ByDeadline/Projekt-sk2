# Backend serwera napisany w C++ instrukcja kompilacji
### Potrzebne zależności
- Linux
- g++ >= 9.4.0
- make
- cmake >= 3.16.3
- bash

### Najprostsze polecenie kompilacji
W bash'u odpalić plik **compile.sh**
```
./compile.sh
```

W folderze **build** znajduje się skompilowany program **server**

### Ręczene budowanie
Jak ktoś nie ma basha to mając te powyższe zależności na linuxie można po kolei te instrukcje wykonać będąc w folderze **backend**.
```
mkdir -p build
```
```
cmake -S . -B build
```
```
make -C build
```

# Wysyłanie zapytań do serwera i otrzymywanie odpowiedzi
### Definuje się następujące szablony:
- **<username>** Wybrana nazwa użytkownika. np. "Dominik"
- **<userId>** Unikalne id użytkownika, który jest zalogowany. np. "#0"
- **<targetUserId>** Id użytkownika, z którym chcemy coś zrobić
- **<lobbyId>** Unikalne id lobby. np. "$1"
- **<inLobbyCount>** Ilość użytkowników w lobby
- **<maxLobbyCount>** Maksymalna liczba użytkowników w lobby
- **<inGame>** Czy jest w grze. "y" lub "n"
- **<isReady>** Czy gracz jest gotowy. "y" lub "n"
- **<wordCount>** Ilość słów w tekscie
- **<userProgress>** Indywidualny postęp gracza

### Logowanie, oraz wylogowywanie
Zanim będzie można wysyłać jakiekolwiek inne zapytanie do serwera trzeba się zalogować.

**Zaloguj się:**
```
login,<username>
```
Odpowiedź serwera:
```
success,<userId>
```
Możliwe niepowodzenie:
```
failed,A user with the same nickname already exists
```
```
failed,Client is already logged in
```
Teraz używając **clientId** można dokonywać reszty zapytań.

**Wyloguj się:**
```
logout,<userId>
```

**Zaloguj się jako admin**
```
admin,<username>
```
Jako admin można:

**Wyświetl wszystkich użytkowników**
```
show_users,<userId>
```
Odpowiedź serwera:
```
success,<username>,<lobbyId>,<inGame>
<username>,<lobbyId>,<inGame>
...
```

**Usuń użytkownika**
```
remove_user,<userId>,<targetUserId>
```

### Tworzenie i dołączanie do lobby
Jako użytkownik można stworzyć lobby, dołączyć do istniejącego lub wyświetlić wszystkie stworzone lobby

**Stwórz nowe lobby**
```
create_lobby,<userId>
```

**Dołącz do istniejącego lobby**
```
join_lobby,<userId>,<lobbyId>
```

**Pokaż wszystkie lobby**
```
show_lobbies,<userId>
```
Odpowiedź serwera:
```
success,<lobbyId>,<inLobbyCount>,<maxLobbyCount>
<lobbyId>,<inLobbyCount>,<maxLobbyCount>
...
```

**Wyjdź z lobby**
```
leave_lobby,<userId>,<lobbyId>
```

Jako admin można:

**Usuń lobby**:
```
remove_lobby,<userId>,<lobbyId>
```

Będąc w lobby dostaje się od serwera aktualny status graczy:
```
status,<username>,<isReady>
<username>,<isReady>
...
```

### Rozpoczęcie gry i rozgrywka
**Ustaw gotowość (będąc w lobby)**
```
ready,<userId>,<lobbyId>
```
Gdy jest co najmniej dwóch graczy i wszyscy są gotowi rozpoczyna się gra i serwer wysyła taki komunikat:
```
text,<wordCount>,<theText>,<username>,<username>,...
```
Teraz będąc w grze żeby zaktualizować swój postęp wysyła się zapytanie:

**Zaktualizuj postęp (będąc w lobby)**
```
progress,<userId>,<lobbyId>,<userProgress>
```
Serwer z każdą aktualizacją postępu wysyła wszystkim graczom w danym lobby tekst:
```
status,<username>,<userProgress>
<username>,<userProgress>
...
```
Gdy gra się skończy serwer wysyła ostatni status:
```
finished,<username>,<userProgress>
<username>,<userProgress>
...
```
