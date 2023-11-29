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