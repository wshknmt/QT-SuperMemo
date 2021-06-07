ZPR 21L, projekt - szkielet aplikacji
Michał Kopyt (300231), Paweł Martyniuk (300220)

Treść zadania w pliku temat_projektu.txt



Instrukcja kompilacji i uruchomienia (Ubuntu):

Aktualna lista wymaganych pakietów:
sudo apt-get install g++
sudo apt-get install make
sudo apt-get install qt5-default
sudo apt-get install qtmultimedia5-dev
sudo apt-get install libboost-test-dev
sudo apt install libqt5charts5-dev

W katalogu głównym projektu uruchomić narzędzie qmake:
	qmake
Zostanie wygenerowany Makefile dla projektu. Poleceniem:
	make
skompilujemy program. Plik wykonywalny "app" zostanie utworzony w katalogu "bin" projektu:
	./bin/app

Aby skompilować i uruchomić testy, możemy wykorzystać dodatkowy target Makefile'a:
	make test
Testy są umieszczone w katalogu tests jako oddzielny projekt qmake.

Makefile generowany przez qmake posiada też target clean do czyszczenia katalogów projektu z wyników kompilacji.
	make clean
