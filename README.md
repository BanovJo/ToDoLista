Uvod:

	Ovaj dokument opisuje program, build, instalaciju, i upute za korištenje MS Windows kompatibilnog programa: jednostavnu ToDo Listu koja pruža 
	mogućnosti dodavanja, editiranja i brisanja zadataka, gdje zadatci mogu biti filtrirani po periodu i prioritetu.


Sadržaj:

	1. Opis datoteka repozitorija
	2. Upute za build
	3. Upute za instalaciju aplikacije
	4. Upute za korištenje aplikacije
	5. Status razvoja aplikacije


 

1.	Opis datoteka repozitorija

	Zaglavlje sadrži Microsoft VisualStudio solution datoteku i
	Zadatci.mdb koju buildom stvorena izvršna datoteka (.exe) koristi kao bazu:

		\ToDoLista.sln
		\Zadatci.mdb	

	Datoteke source koda projekta:

		\ToDoLista\EditDlg.cpp
		\ToDoLista\EditDlg.h
		\ToDoLista\framework.h
		\ToDoLista\pch.cpp
		\ToDoLista\pch.h
		\ToDoLista\resource.h
		\ToDoLista\targetver.h
		\ToDoLista\ToDoLista.filters
		\ToDoLista\ToDoLista.rc
		\ToDoLista\ToDoLista.user
		\ToDoLista\ToDoLista.vcxproj
		\ToDoLista\ToDoLista.vcxproj.filters
		\ToDoLista\ToDoLista.vcxproj.user
		\ToDoLista\ToDoListaApp.cpp
		\ToDoLista\ToDoListaApp.h
		\ToDoLista\ToDoListaDlg.cpp
		\ToDoLista\ToDoListaDlg.h

	Datoteke resourca projekta:

		\ToDoLista\res\ToDoLista.ico
		\ToDoLista\res\ToDoLista.rc2
		




2. 	Upute za build

	Pomoću GIT-a spremite komprimiranu zip datoteku i raspakirajte na proizvoljnom mjestu.
	Izvorni kod je kompatibilan sa MS Windows operativnim sustavom, Microsoft VisualStudio 2019+. 
	U Visual Studiu je potrebno imati dodatak za MFC, C++ i Desktop programiranje.
	Kako se aplikacija spaja na Acccess bazu Zadatci.mdb preko ODBC drivera, potrebno je provjeriti dostupnost drivera:
		- Control panel -> Administrative Tools -> ODBC Data Sources (32-bit) -> Drivers (Tab) -> Na listi mora biti:
		"Microsoft Access Driver (*.mdb)"
	Ukoliko ODBC driver nije prisutan, instalirajte ga preko uputa na Microsoft.com ili šire.
	Završno, otvorite ToDoLista.sln u Visual Studiu, odaberite Release ili Debug konfiguraciju, te pokrenite Build.
	Ukoliko je build bio uspješan, u "Root"\Debug ili "Root"\Release mapi će se pojaviti izvršna aplikacija ToDoLista.exe.

	
	
	
3.	Upute za instalaciju aplikacije

	Nakon builda, izvršna datoteka (.exe) programa se može naći pod "Release/ToDoLista.exe". Također, za rad aplikacije je potrebna datoteka "Zadatci.mdb".
	Na MS Windows stroju stvorite mapu "FolderA" na proizvoljnom mjestu, te ispod njega stvorite podmapu "FolderB". ("FolderA" i "FolderB" mogu biti proizvoljni nazivi) 
	U maou "FolderA" prebacite kopiju datoteke "Zadatci.mdb", dok u podmapu "FolderB" prebacite kopiju datoteke "Release\ToDoLista.exe".
	Hijerarhija datoteka mora izgledati sljedeće:
		FolderA\Zadatci.mdb
		FolderA\FolderB\ToDoLista.exe
	Na MS Windows stroju gdje će biti izvršavana datoteka aplikacije "ToDoLista.exe", mora biti instailrana zadnja verzija 
	Visual C++ Redistributable for Visual Studio. Visual C++ Redistributable instalacija se nalazi na Microsoft.com-u.
	Na MS Windows stroju gdje će biti izvršavana datoteka aplikacije "ToDoLista.exe", mora biti instaliran ODBC driver za MS Access,
	iz razloga što se aplikacija (ToDoLista.exe) spaja na MS Access datoteku baze "Zadatci.mdb".
	Provjera dostupnosti ODBC drivera: Control panel -> Administrative Tools -> ODBC Data Sources (32-bit) -> Drivers (Tab),
	gdje na listi mora biti: "Microsoft Access Driver (*.mdb)"
	Ukoliko ODBC driver nije prisutan, instalirajte ga preko uputa na Microsoft.com ili šire.
	Ukoliko je ODBC driver dostupan, pokrenite datoteku "ToDoLista.exe" kako bi pokrenuli aplikaciju.
	
	

	
4.	Upute za korištenje aplikacije
	
	Nakon pokretanje aplikacije pojavljuje se glavni prozor/dijalog koji se sastoji od:
		
		- Lista s popisom upisanih zadataka s kolonama:
			- Vrijeme: datum roka pojedinog zadatka
			- Prioritet: cjelobrojna vrijednost prioriteta zadatka
			- Opis zadatka: tekstualni opis zadatka
		
		- Filter datuma (od/do) i prioriteta, koji se uključuje/isključuje s Filter kvačicom.
			Ukoliko je filter uključen, lista zadataka će prikazivati samo zadatke koji su definirani preko filtera.
			
		- Tipke:
			Novi (kreiranje novog zadatka), 
			Otvori (označeni zadatak s Liste će se otvoriti za promjenu) i
			Obriši (označeni zadatak/zadatci s Liste će se obrisati)
		
	Kada korisnik pokrene Otvori ili Novi, otvoriti će se novi dijalog Zadatak koji se sastoji od:
	
		- Datuma i vremena koji definiraju rok izvršenja zadatka
		- Polja za upis cjelobrojne vrijednosti Prioriteta
		- Tekstualni opis zadatka
		- Tipki Potvrdi za upis novog zadatka ili promjene na zadatku, Odustani za prekid promjene/upisa zadatka.
	
	Ukoliko korisnik dvostruko pritisne lijevu tipku miša na nekom zadataku s liste, zadatak će se otvoriti za promjenu.
	Lista zadataka omogućava višestuko označavanje redova.
	
	
	
	
5. Status razvoja aplikacije

	Trenutna implementacija uključuje samo x86 (32-bitnu) verziju aplikacije.
	U budućnosti, x64 (64-bitna) verzija će biti dostupna.
