#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <Windows.h>
#include <cstdlib>
#include <regex>

using namespace std;

class carti
{
private:
	string titlu, editura;
	int pretBaza, nrBucati;
	list<string>autori;
public:
	carti(string titlu, list<string>autori, string editura, int pretBaza, int nrBucati)
	{
		this->titlu = titlu;
		this->autori = autori;
		this->editura = editura;
		this->pretBaza = pretBaza;
		this->nrBucati = nrBucati;
	}
	void getAutori()
	{
		for (auto a : autori)
		{
			cout << a << ", ";
		}
		cout << '\n';
	}
	string getTitlu()
	{
		return titlu;
	}
	string getEditura()
	{
		return editura;
	}
	int getNrBucati()
	{
		return nrBucati;
	}
	void achizitionare()
	{
		nrBucati--;
	}
	int getPretBaza()
	{
		return pretBaza;
	}
	int getNrAutori()
	{
		return autori.size();
	}
	list<string> getAutoriFisier()
	{
		return autori;
	}
	virtual int pretTotal() = 0;
	virtual string Tip() = 0;
	virtual void afisareCarte() = 0;
	virtual int calitateTipCarte() = 0;
	int getPretbaza()
	{
		return pretBaza;
	}
};

class fictiune :private carti
{
private:
	int nrPagini;
public:
	fictiune(string titlu, list<string>nume, string editura, int pretBaza, int nrPagini, int nrBucati) :carti(titlu, nume, editura, pretBaza, nrBucati)
	{
		this->nrPagini = nrPagini;
	}
	virtual int pretTotal()override
	{
		return getPretbaza() + nrPagini;
	}
	virtual string Tip()override
	{
		return "Fictiune";
	}
	virtual int calitateTipCarte()override
	{
		return nrPagini;
	}
	virtual void afisareCarte()override
	{
		cout << "Titlu: " << carti::getTitlu() << "\nGen: " << Tip() << "\nAutor/Autori: ";
		carti::getAutori();
		cout << "Editura: " << carti::getEditura() << "\nPret: " << pretTotal() << "\nNumar de bucati in stoc: " << getNrBucati();
	}
};

class non_fictiune :private carti
{
private:
	int anPublicare;
public:
	non_fictiune(string titlu, list<string>nume, string editura, int pretBaza, int anPublicare, int nrBucati) :carti(titlu, nume, editura, pretBaza, nrBucati)
	{
		this->anPublicare = anPublicare;
	}
	virtual int pretTotal()override
	{
		return getPretbaza() - (25 * anPublicare);
	}

	virtual string Tip()override
	{
		return "Non-Fictiune";
	}
	virtual int calitateTipCarte()override
	{
		return anPublicare;
	}
	virtual void afisareCarte()
	{
		cout << "Titlu: " << carti::getTitlu() << "\nGen: " << Tip() << "\nAutor/Autori: ";
		carti::getAutori();
		cout << "Editura: " << carti::getEditura() << "\nPret: " << pretTotal() << "\nNumar de bucati in stoc: " << getNrBucati();
	}
};

class utilizator
{
private:
	string nume, prenume, email, parola, cnp;
public:
	utilizator(string nume, string prenume, string email, string parola, string CNP)
	{
		this->nume = nume;
		this->prenume = prenume;
		this->email = email;
		this->parola = parola;
		this->cnp = CNP;
	}

	string getNume()
	{
		return nume;
	}

	string getPrenume()
	{
		return prenume;
	}
	string getEmail()
	{
		return email;
	}
	string getParola()
	{
		return parola;
	}
	string getCNP()
	{
		return cnp;
	}
	void resetareParola()
	{
		string newpass;
		do
		{
			try
			{
				cout << "Parola noua: ";
				cin >> newpass;
				parola = newpass;
				if (newpass == parola)
				{
					cout << "Parola noua nu poate fi aceeasi cu parola veche\n";
					throw new exception("Parola noua este aceeasi cu parola veche\n");
					system("pause");
				}

			}
			catch (exception* e)
			{
				ofstream f;
				f.open("log.txt", fstream::app);
				f << e;
				f.close();
			}
		} while (newpass == parola);
		cout << "Parola a fost schimbata cu succes!\nPentru a intra in contul de utilizator va trebui sa va logati.";
		system("pause");
	}
};

bool validare_parola(string& parola)
{
	if (parola.length() < 3)
	{
		cout << "Parola trebuie sa contina cel putin 3 caractere\n";
		system("pause");
		return false;
	}
	return true;
}

bool validare_email_unicitate(string& email, list<utilizator*> listaUtilizatori)
{
	for (auto u : listaUtilizatori)
	{
		try
		{
			if (u->getEmail() == email)
			{
				return false;
				throw new exception("Email invalid la crearea de cont nou\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e;
			f.close();
		}
	}
	return true;
}

bool validare_cnp_unicitate(string cnp, list<utilizator*> listaUtilizatori)
{
	for (auto u : listaUtilizatori)
	{
		try
		{
			if (u->getCNP() == cnp)
			{
				return false;
				throw new exception("CNP invalid la crearea de cont nou\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e;
			f.close();
		}
	}
	return true;
}

bool validare_email_format(string& email)
{
	regex e(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return regex_match(email, e);
}

bool validare_cnp_format(string& cnp)
{
	if (cnp.length() != 13)
	{
		return false;
	}
	for (char c : cnp)
	{
		if (c < 0 && c>9)
			return false;
	}
	return true;
}

bool validare_parola_corect(string email, string parola, list<utilizator*> listaUtilizatori)
{
	for (auto u : listaUtilizatori)
	{
		if (u->getEmail() == email && u->getParola() == parola)
		{
			return true;
		}
	}
	return false;
}

void initializareobiect_fisier(string nume, string prenume)
{
	string nume_fisier = nume + prenume + ".txt";
	ofstream f(nume_fisier);
	f.close();
}

void paginaImprumut(utilizator* u, list<carti*> listaCarti)
{
	string nume, fisier = u->getNume() + u->getPrenume() + ".txt", eroare;
	int opt;
	bool gasitCarte;
	ofstream f;
	f.open(fisier, fstream::app);
	system("CLS");
	cout << "Selectati ce carte doriti sa imprumutati: \n\n";
	for (auto c : listaCarti)
	{
		c->afisareCarte();
		cout << "\n-------------------------\n";
	}
	do
	{
		try
		{
			gasitCarte = false;
			cout << "Numele cartii de imprumutat: ";
			cin >> nume;
			for (auto c : listaCarti)
			{
				if (c->getTitlu() == nume)
				{
					gasitCarte = true;
					break;
				}
			}
			if (gasitCarte == false)
			{
				cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
				system("pause");
				eroare = "Utilizatorul " + u->getNume() + " " + u->getPrenume() + " a introdus o optiune gresita la alegerea unei carti de achizitionat\n";
				throw eroare;
			}
		}
		catch (string e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e;
			f.close();
		}
	} while (gasitCarte == false);
	for (auto c : listaCarti)
	{
		if (c->getTitlu() == nume)
		{
			do
			{
				cout << "Doriti sa imprumutati aceasta carte? \n1-DA 2-NU \nOpt: ";
				try
				{
					cin >> opt;
					if (opt < 1 || opt>3)
					{
						cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
						system("pause");
						eroare = "Optiune introdusa gresit la alegerea de a imprumuta cartea " + nume + "\n";
						throw eroare;
					}
				}
				catch (string e)
				{
					ofstream f;
					f.open("log.txt", fstream::app);
					f << e;
					f.close();
				}
				switch (opt)
				{
				case 1:	cout << "Imprumutul a fost realizat cu succes!\n\nNe bucuram ca v-am putut fi de folos!\n";
					f << c->getTitlu() << " " << c->pretTotal() << " " << c->getEditura() << " Imprumutat\n";
					system("pause");
					break;
				case 2:cout << "Am inteles! Imprumutul a fost anulat...\n";
					break;
				default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
					system("pause");
					break;
				}
			} while (opt < 1 || opt > 2);
			break;
		}
	}
	f.close();
}

void paginaAchizitionare(utilizator* u, list<carti*> listaCarti)
{
	string nume, fisier = u->getNume() + u->getPrenume() + ".txt", eroare;
	int opt;
	bool gasitCarte;
	ofstream f, g;
	list<string> listaAutori;
	f.open(fisier, fstream::app);
	g.open("carti.txt");
	system("CLS");
	cout << "Selectati ce carte doriti sa cumparati: \n\n";
	for (auto c : listaCarti)
	{
		c->afisareCarte();
		cout << "\n-------------------------\n";
	}
	do
	{
		try
		{
			gasitCarte = false;
			cout << "Numele cartii de imprumutat: ";
			cin >> nume;
			for (auto c : listaCarti)
			{
				if (c->getTitlu() == nume)
				{
					gasitCarte = true;
					break;
				}
			}
			if (gasitCarte == false)
			{
				eroare = "Utilizatorul " + u->getNume() + " " + u->getPrenume() + " a introdus o optiune gresita la alegerea unei carti de achizitionat\n";
				throw eroare;
			}
		}
		catch (string e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e;
			f.close();
		}
	} while (gasitCarte == false);
	for (auto c : listaCarti)
	{
		if (c->getTitlu() == nume)
		{
			do
			{
				cout << "Doriti sa cumparati aceasta carte? \n1-DA 2-NU \nOpt: ";
				try
				{
					cin >> opt;
					if (opt < 1 || opt>3)
					{
						eroare = "Optiune introdusa gresit la alegerea de a achizitiona cartea " + nume + "\n";
						throw eroare;
					}
				}
				catch (string e)
				{
					ofstream f;
					f.open("log.txt", fstream::app);
					f << e;
					f.close();
				}
				switch (opt)
				{
				case 1: c->achizitionare();
					cout << "Cartea a fost achiitionata cu succes!\n\nVa multumim ca ati cumparat de la noi!\n";
					f << c->getTitlu() << " " << c->pretTotal() << " " << c->getEditura() << " Cumparat\n";
					system("pause");
					for (auto cr : listaCarti)
					{
						g << cr->Tip() << " " << cr->getTitlu() << " " << cr->getEditura() << " " << cr->getPretBaza() << " " << cr->getNrBucati() << " " << cr->calitateTipCarte() << " " << cr->getNrAutori() << " ";
						listaAutori = cr->getAutoriFisier();
						for (auto a : listaAutori)
						{
							g << a << " ";
						}
						g << "\n";
					}
					break;
				case 2:cout << "Ne pare rau ca nu v-am pututfi de folos...\n";
					break;
				default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
					system("pause");
					break;
				}
			} while (opt < 1 || opt > 2);
			break;
		}
	}
	f.close();
	g.close();
}

void paginaRezervare(utilizator* u, list<carti*> listaCarti)
{
	int opt;
	do
	{
		system("CLS");
		cout << "Bookstore App\n\nUtilizator: " << u->getNume() << " " << u->getPrenume() << "\n\n";
		cout << "Alegeti o opt:\n        1.Achizitionati o carte\n        2.Imprumutati o carte\n        3.Inapoi\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina de rezervare\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:paginaAchizitionare(u, listaCarti);
			break;
		case 2:paginaImprumut(u, listaCarti);
			break;
		case 3:return;
			break;
		default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	} while (true);
	return;
}

void paginaIstoric(utilizator* u, list<carti*> listaCarti)
{
	string fisier = u->getNume() + u->getPrenume() + ".txt", nume, pret, editura, status;
	ifstream f;
	f.open(fisier);
	system("CLS");
	cout << "Bookstore App\n\nUtilizator: " << u->getNume() << " " << u->getPrenume() << "\n\n";
	cout << "Istoric de cumparari: \n\n";
	while (f >> nume >> pret >> editura >> status)
	{
		cout << "Titlu carte: " << nume << "\nEditura: " << editura << "\nPret: " << pret << '\n' << status << "\n---------------------------\n";
	}
	system("pause");
	f.close();
	return;
}

void paginaContactUtilizator(utilizator* u)
{
	ofstream f;
	string mesaj;
	int opt;
	do
	{
		system("CLS");
		cout << "Bookstore App:\n\n";
		cout << "Suport Tehnic:\n\nIn cazul in care intalniti dificultati echipa de suport va sta la datorie.\n\n";
		cout << "Tot ce trebuie sa faceti este sa completati urmatorul formular in care e descrisa problema. \n\n";
		cout << "Alegeti o opt:\n        1.Trimitere sesizare\n        2.Inapoi\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina de contact a utilizatorului\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:f.open("sesizari.txt", fstream::app);
			cout << "Mesaj: ";
			getline(cin, mesaj);
			getline(cin, mesaj);
			f << "Nume/Prenume: " << u->getNume() << " " << u->getPrenume() << " CNP: " << u->getCNP() << "\nEmail : " << u->getEmail() << "\nEmail Companie: suport@bookstoreapp.com\n" << mesaj << "\nSubsemnatul: " << u->getNume() << " " << u->getPrenume() << "\n\n";
			cout << "\n\nSesizare Trimisa!\n";
			f.close();
			system("pause");
			return;
			break;
		case 2:return;
			break;
		default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	} while (true);

}

void paginaUtilizator(utilizator* u, list<carti*> listaCarti)
{
	int opt;
	do
	{
		system("CLS");
		cout << "Bookstore App\n\nUtilizator: " << u->getNume() << " " << u->getPrenume() << "\n\n";
		cout << "Alegeti o opt:\n        1.Achizitie/Imprumut\n        2.Istoric Rezervari\n        3.Contact\n        4.Delogare\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina utilizatorului\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:paginaRezervare(u, listaCarti);
			break;
		case 2:paginaIstoric(u, listaCarti);
			break;
		case 3:paginaContactUtilizator(u);
			break;
		case 4:return;
			break;
		default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	} while (true);
	return;
}

void logare(list<utilizator*> listaUtilizatori, utilizator*& u)
{
	string email, parola;
	bool dataValid;
	do
	{
		do
		{
			try
			{
				dataValid = true;
				cout << "Email: ";
				cin >> email;
				if (validare_email_format(email) == false || validare_email_unicitate(email, listaUtilizatori) == true)
				{
					cout << "Acest Email nu apartine unui cont sau este introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
					system("pause");
					dataValid = false;
					throw new exception("Email introdus gresit la logarea unui utilizator\n");
				}
			}
			catch (exception* e)
			{
				ofstream f;
				f.open("log.txt", fstream::app);
				f << e->what();
				f.close();
			}
		} while (dataValid == false);
		do
		{
			try
			{
				dataValid = true;
				cout << "Parola: ";
				cin >> parola;
				if (validare_parola(parola) == false)
				{
					dataValid = false;
					throw new exception("Parola introdusa gresit la logarea unui utilizator\n");
				}
			}
			catch (exception* e)
			{
				ofstream f;
				f.open("log.txt", fstream::app);
				f << e->what();
				f.close();
			}
		} while (dataValid == false);
		dataValid = false;
		for (auto ul : listaUtilizatori)
		{
			if (ul->getEmail() == email && ul->getParola() == parola)
			{
				u = ul;
				dataValid = true;
				break;
			}
		}
		if (dataValid == false)
		{
			cout << "Parola sau Email-ul sunt introduse gresit.\nAsigurati-va ca ati introdus datele corect.\n";
			system("pause");
		}
	} while (dataValid == false);
}

void resetareParolaUtilizator(list<utilizator*> listaUtilizatori)
{
	string email, CNP;
	ofstream f;
	bool dataValid;
	f.open("date.txt");
	cout << "Pentru a va putea reseta parola va trebui sa introduceti Email-ul contului dvs. si a va confirmati identitatea prin CNP\n";
	do
	{
		do
		{
			try
			{
				dataValid = true;
				cout << "Email: ";
				cin >> email;
				if (validare_email_format(email) == false || validare_email_unicitate(email, listaUtilizatori) == true)
				{
					cout << "Acest Email nu apartine unui cont sau este introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
					system("pause");
					dataValid = false;
					throw new exception("Email introdus gresit la inregistrarea unui utilizator\n");
				}
			}
			catch (exception* e)
			{
				ofstream f;
				f.open("log.txt", fstream::app);
				f << e->what();
				f.close();
			}
		} while (dataValid == false);
		do
		{
			try
			{
				dataValid = true;
				cout << "CNP: ";
				cin >> CNP;
				if (validare_cnp_format(CNP) == false || validare_cnp_unicitate(CNP, listaUtilizatori) == true)
				{
					cout << "Acest CNP nu apartine unui cont sau este introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
					system("pause");
					dataValid = false;
					throw new exception("CNP introdus gresit la inregistrarea unui utilizator\n");
				}
			}
			catch (exception* e)
			{
				ofstream f;
				f.open("log.txt", fstream::app);
				f << e->what();
				f.close();
			}
		} while (dataValid == false);
		dataValid = false;
		for (auto u : listaUtilizatori)
		{
			if (u->getEmail() == email && u->getCNP() == CNP)
			{
				u->resetareParola();
				dataValid = true;
				break;
			}
		}
		if (dataValid == false)
		{
			cout << "Datele introduse nu se potrivesc unui cont anume\nIntroduceti datele contului inca odata\n";
			system("pause");
		}
	} while (dataValid == false);
	for (auto u : listaUtilizatori)
	{
		f << u->getEmail() << " " << u->getParola() << " " << u->getNume() << " " << u->getPrenume() << " " << u->getCNP() << '\n';
	}
	f.close();
}

void inregistrare(list<utilizator*> listaUtilizatori, utilizator*& u)
{
	string nume, prenume, email, parola, CNP;
	bool dataValid;
	ofstream f;
	f.open("date.txt");
	do
	{
		try
		{
			dataValid = true;
			cout << "Nume: ";
			cin >> nume;
			if (nume.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				cout << "Numele trebuie sa contina doar litere mari si mici\n";
				system("pause");
				dataValid = false;
				throw new exception("Nume introdus gresit la inregistrarea unui utilizator\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "Prenume: ";
			cin >> prenume;
			if (prenume.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				cout << "Prenumele trebuie sa contina doar litere mari si mici\n";
				system("pause");
				dataValid = false;
				throw new exception("Prenume introdus gresit la inregistrarea unui utilizator\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "Email: ";
			cin >> email;
			if (validare_email_format(email) == false || validare_email_unicitate(email, listaUtilizatori) == false)
			{
				cout << "Acest Email apartine unui alt cont sau este introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
				system("pause");
				dataValid = false;
				throw new exception("Email introdus gresit la inregistrarea unui utilizator\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "Parola: ";
			cin >> parola;
			if (validare_parola(parola) == false)
			{
				dataValid = false;
				throw new exception("Parola introdusa gresit la inregistrarea unui utilizator\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "CNP: ";
			cin >> CNP;
			if (validare_cnp_format(CNP) == false || validare_cnp_unicitate(CNP, listaUtilizatori) == false)
			{
				cout << "Acest CNP apartine unui alt cont sau este introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
				system("pause");
				dataValid = false;
				throw new exception("CNP introdus gresit la inregistrarea unui utilizator\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	initializareobiect_fisier(nume, prenume);
	u = new utilizator(nume, prenume, email, parola, CNP);
	listaUtilizatori.push_back(u);
	for (auto u : listaUtilizatori)
	{
		f << u->getEmail() << " " << u->getParola() << " " << u->getNume() << " " << u->getPrenume() << " " << u->getCNP() << '\n';
	}
	f.close();
}

void paginaLogare(list<utilizator*> listaUtilizatori, list<carti*> listaCarti)
{
	utilizator* u;
	int opt;
	do
	{
		system("CLS");
		cout << "Bookstore App:\n\n\n";
		cout << "Alegeti o opt:\n        1.Autentificare\n        2.Inregistrare\n        3.Resetare parola\n        4.Inapoi\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina de logare\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:logare(listaUtilizatori, u);
			paginaUtilizator(u, listaCarti);
			break;
		case 2:inregistrare(listaUtilizatori, u);
			paginaUtilizator(u, listaCarti);
			break;
		case 3:resetareParolaUtilizator(listaUtilizatori);
			break;
		case 4:return;
			break;
		default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	} while (true);
	return;
}

void scriereSesizare()
{
	ofstream f;
	string nume, prenume, email, mesaj, CNP;
	bool dataValid;
	f.open("sesizari.txt", fstream::app);
	do
	{
		try
		{
			dataValid = true;
			cout << "Nume: ";
			cin >> nume;
			if (nume.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				dataValid = false;
				throw new exception("Nume introdus gresit la scrierea unei sesizari\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "Prenume: ";
			cin >> prenume;
			if (prenume.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				cout << "Prenume introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
				system("pause");
				dataValid = false;
				throw new exception("Prenume introdus gresit la scrierea unei sesizari\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (dataValid == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "Email: ";
			cin >> email;
			if (validare_email_format(email) == false)
			{
				cout << "Email introdus gresit.\nAsigurati-va ca ati scris CNP-ul corect\n";
				system("pause");
				dataValid = false;
				throw new exception("Email introdus gresit la scrierea unei sesizari\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (validare_email_format(email) == false);
	do
	{
		try
		{
			dataValid = true;
			cout << "CNP: ";
			cin >> CNP;
			if (validare_cnp_format(CNP) == false)
			{
				dataValid = false;
				throw new exception("CNP introdus gresit la scrierea unei sesizari\n");
			}
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
	} while (validare_cnp_format(CNP) == false);
	cout << "Mesaj: ";
	getline(cin, mesaj);
	getline(cin, mesaj);
	f << "Nume/Prenume: " << nume << " " << prenume << " CNP: " << CNP << "\nEmail : " << email << "\nEmail Companie: suport@bookstoreapp.com\n" << mesaj << "\nSubsemnatul: " << nume << " " << prenume << "\n\n";
	cout << "\n\nSesizare Trimisa!\n";
	f.close();
	system("pause");
}

void paginaContact()
{

	int opt;
	do
	{
		system("CLS");
		cout << "Bookstore App:\n\n";
		cout << "Suport Tehnic:\n\nIn cazul in care intalniti dificultati echipa de suport va sta la datorie.\n\n";
		cout << "Tot ce trebuie sa faceti este sa completati urmatorul formular in care e descrisa problema. \n\n";
		cout << "Alegeti o opt:\n        1.Trimitere sesizare\n        2.Inapoi\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina de contact\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:scriereSesizare();
			return;
			break;
		case 2:return;
			break;
		default:cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	} while (opt != 2);
	return;
}

void paginaPornire(list<utilizator*> listaUtilizatori, list<carti*> listaCarti)
{
	int opt, iesire = 0;
	while (iesire == 0)
	{
		system("CLS");
		cout << "Bookstore App:\n\n\n";
		cout << "Alegeti o opt:\n        1.Conectare\n        2.Contact\n        3.Inchidere Aplicatie\n";
		try
		{
			cin >> opt;
			if (opt < 1 || opt>3)
				throw new exception("Optiune introdusa gresit in pagina de pornire\n");
		}
		catch (exception* e)
		{
			ofstream f;
			f.open("log.txt", fstream::app);
			f << e->what();
			f.close();
		}
		switch (opt)
		{
		case 1:
			paginaLogare(listaUtilizatori, listaCarti);
			break;
		case 2:
			paginaContact();
			break;
		case 3:cout << "La revedere!";
			return;
			break;
		default: cout << "Ati introdus o optiune gersita!\n Va rog alegeti o optiune valida!\n";
			system("pause");
			break;
		}
	}

}

ifstream& operator>>(ifstream& fin, utilizator*& u)
{
	string nume, prenume, email, parola, CNP;
	fin >> email >> parola >> nume >> prenume >> CNP;
	u = new utilizator(nume, prenume, email, parola, CNP);
	return fin;
}

ifstream& operator>>(ifstream& fin, carti*& c)
{
	list<string>autori;
	string tip, titlu, editura, autor;
	int pretBaza, anPublicatie, nrPagini, nrAutori, nrBucati;
	fin >> tip;
	if (tip == "Fictiune")
	{
		fin >> titlu >> editura >> pretBaza >> nrBucati >> nrPagini >> nrAutori;
		while (nrAutori > 0)
		{
			fin >> autor;
			autori.push_back(autor);
			nrAutori--;
		}
		c = (carti*)new fictiune(titlu, autori, editura, pretBaza, nrPagini, nrBucati);
	}
	else
	{
		fin >> titlu >> editura >> pretBaza >> nrBucati >> anPublicatie >> nrAutori;
		while (nrAutori > 0)
		{
			fin >> autor;
			autori.push_back(autor);
			nrAutori--;
		}
		c = (carti*)new non_fictiune(titlu, autori, editura, pretBaza, anPublicatie, nrBucati);
	}
	return fin;
}

void utilizatoriInregistrati(list<utilizator*>& listaUtilizatori)
{
	utilizator* u;
	ifstream f;
	f.open("date.txt");
	while (f >> u)
	{
		listaUtilizatori.push_back(u);
	}
	f.close();
}

void cartiStoc(list<carti*>& listaCarti)
{
	carti* c;
	ifstream f;
	f.open("carti.txt");
	while (f >> c)
	{
		listaCarti.push_back(c);
	}
	f.close();
}

int main()
{
	list<utilizator*> listaUtilizatori;
	list<carti*> listaCarti;
	utilizatoriInregistrati(listaUtilizatori);
	cartiStoc(listaCarti);
	paginaPornire(listaUtilizatori, listaCarti);
	return 0;
}