#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//----------CLASA----------
class Angajat 
{
    protected:
        string nume;
        string functie;
        int ora_start;
        int ora_final;
        int salariu;

    public:
        //----------CONSTRUCTOR----------
        Angajat(string n, string f, int start, int final, int s)
        {
            nume = n;
            functie = f;
            ora_start = start;
            ora_final = final;
            salariu = s;
        } 

        //----------DESTRUCTOR----------
        virtual ~Angajat() = default;

        //----------ABSTRACTIZARE----------
        virtual void sarcini() = 0;

        //----------INCAPSULARE----------
        string getNume()
        { 
            return nume; 
        }

        string getFunctie()
        { 
            return functie; 
        }

        int getOraStart() 
        { 
            return ora_start; 
        }

        int getOraFinal()
        { 
            return ora_final; 
        }

        int getSalariu()
        {
            return salariu;
        }
};

//pentru fiecare functie exista un salariu prestabilit de cafenea, nu exista angajati cu aceeasi functie si cu salarii diferite
//salariile sunt per ora

//----------MOSTENIRE----------
class Barista : public Angajat 
{
    public:
        Barista(string n, int start, int final): Angajat(n, "barista", start, final, 18) {}

        void sarcini()
        {
            cout << "Un barista prepara si serveste bauturile pe baza de cafea" << endl;
        }
};

class Manager : public Angajat 
{
    public:
        Manager(string n, int start, int final): Angajat(n, "manager", start, final, 30) {}

        void sarcini()
        {
            cout << "Un manager coordoneaza operatiunile si gestioneaza personalul cafenelei" << endl;
        }
};

class Ospatar : public Angajat 
{
    public:
        Ospatar(string n, int start, int final): Angajat(n, "ospatar", start, final, 13) {}

        void sarcini()
        {
            cout << "Un ospatar serveste clientii si preia comenzile la mese" << endl;
        }
};

class Produs
{
    private:
        string nume;
        int pret_cumparare;
        int pret_vanzare;
        int nr_bucati;

    public:
        Produs(string n, int c, int v, int nr)
        {
            nume = n;
            pret_cumparare = c;
            pret_vanzare = v;
            nr_bucati = nr;
        }

        virtual ~Produs() = default;

        string getNume()
        {
            return nume;
        }

        int getPretCumparare()
        {
            return pret_cumparare;
        }

        int getPretVanzare()
        {
            return pret_vanzare;
        }

        int getNrBucati()
        {
            return nr_bucati;
        }

        void decreaseNrBucati()
        {
            nr_bucati--;
        }
};

//aceasta clasa este creata pentru a contabiliza daca un client este fidel sau nu
class Client
{
    private:
        string nume;
        int nr_comenzi;

    public:
        Client(string n, int nr)
        {
            nume = n;
            nr_comenzi = nr;
        }

        virtual ~Client() = default;

        string getNume()
        {
            return nume;
        }

        int getNrComenzi()
        {
            return nr_comenzi;
        }

        void incrementNrComenzi()
        {
            nr_comenzi++;
        }
};

class Raport
{
    private:
        float venit;
        float bani_cheltuiti;
        float bani_castigati;
        string oras;

    public:
        //----------POLIMORFISM----------
        Raport(float v, float cheltuiala, float castig, string o)
        {
            venit = v;
            bani_cheltuiti = cheltuiala;
            bani_castigati = castig;
            oras = o;
        }

        Raport(string o)
        {
            venit = 0;
            oras = o;
            bani_castigati = 0;
            bani_cheltuiti = 0;
        }

        virtual ~Raport() = default;

        float getBaniCheltuiti()
        {
            return bani_cheltuiti;
        }

        float getBaniCastigati()
        {
            return bani_castigati;
        }

        float getProfit()
        {
            return bani_castigati - bani_cheltuiti;
        }

        float getVenit()
        {
            return venit;
        }

        string getOras()
        {
            return oras;
        }

        void increaseCheltuieli(float suma)
        {
            bani_cheltuiti += suma;
        }

        void increaseCastiguri(float suma)
        {
            bani_castigati += suma;
        }

        void increaseVenit()
        {
            venit += bani_castigati - bani_cheltuiti;
        }

        void setVenit(float v)
        {
            venit = v;
        }
};

class Eveniment
{
    private:
        string nume;
        int cost;
        int pret_bilet;
        int bilete_vandute;
    
    public:
        Eveniment(string n, int c, int p, int b)
        {
            nume = n;
            cost = c;
            pret_bilet = p;
            bilete_vandute = b;
        }

        virtual ~Eveniment() = default;

        string getNume()
        {
            return nume;
        }

        int getCost()
        {
            return cost;
        }

        int getPretBilet()
        {
            return pret_bilet;
        }

        int getBileteVandute()
        {
            return bilete_vandute;
        }
};

//clasa care se ocupa cu fisierele csv
class CSV 
{
    public:
        vector<Angajat*> readAngajati(const string &fisier) 
        {
            vector<Angajat*> angajati;
            ifstream f(fisier);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return angajati;
            }

            string line;
            while (getline(f, line))
            {
                stringstream ss(line);
                string nume, functie, s, f;
                if (!getline(ss, nume, ',') || !getline(ss, functie, ',') || !getline(ss, s, ',') || !getline(ss, f, ',')) 
                {
                    cout << "Linie invalida in fisier: " << line << endl;
                    continue;
                }

                //----------EXCEPTIONS----------
                try 
                {
                    int ora_start = stoi(s);
                    int ora_final = stoi(f);
                    if (functie == "barista") 
                    {
                        angajati.push_back(new Barista(nume, ora_start, ora_final));
                    } else if (functie == "manager") 
                    {
                        angajati.push_back(new Manager(nume, ora_start, ora_final));
                    } else if (functie == "ospatar") 
                    {
                        angajati.push_back(new Ospatar(nume, ora_start, ora_final));
                    } else 
                    {
                        cout << "Functie necunoscuta: " << functie << endl;
                    }
                } catch (...)
                {
                    cout << "Eroare la conversia datelor in linia: " << line << endl;
                }
            }

            f.close();
            return angajati;
        }

        vector<Produs*> readProdus(const string &fisier)
        {
            vector<Produs*> produse;
            ifstream f(fisier);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return produse;
            }

            string line;
            while (getline(f, line)) 
            {
                stringstream ss(line);
                string nume, c, v, nr;
                if (!getline(ss, nume, ',') || !getline(ss, c, ',') || !getline(ss, v, ',') || !getline(ss, nr, ',')) 
                {
                    cout << "Linie invalida in fisier: " << line << endl;
                    continue;
                }

                try 
                {
                    int pret_cumparare = stoi(c);
                    int pret_vanzare = stoi(v);
                    int nr_bucati = stoi(nr);
                    produse.push_back(new Produs(nume, pret_cumparare, pret_vanzare, nr_bucati));
                } catch (...) 
                {
                    cout << "Eroare la conversia datelor in linia: " << line << endl;
                }
            }

            f.close();
            return produse;
        }

        vector<Client*> readClienti(const string &fisier)
        {
            vector<Client*> clienti;
            ifstream f(fisier);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru citire" << endl;
                return clienti;
            }

            string line;
            while (getline(f, line)) 
            {
                stringstream ss(line);
                string nume, nr;
                if (!getline(ss, nume, ',') || !getline(ss, nr, ',')) 
                {
                    cout << "Linie invalida in fisier: " << line << endl;
                    continue;
                }

                try 
                {
                    int nr_comenzi = stoi(nr);
                    clienti.push_back(new Client(nume, nr_comenzi));
                } catch (...) 
                {
                    cout << "Eroare la conversia datelor in linia: " << line << endl;
                }
            }

            f.close();
            return clienti;
        }

        vector<Raport*> readRaport(const string &fisier)
        {
            vector<Raport*> raport;
            ifstream f(fisier);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru citire" << endl;
                return raport;
            }

            string line;
            while (getline(f, line)) 
            {
                stringstream ss(line);
                string oras, v, castig, cheltuiala, p;
                if (!getline(ss, oras, ',') || !getline(ss, v, ',') || !getline(ss, cheltuiala, ',') || !getline(ss, castig, ',') || !getline(ss, p, ',')) 
                {
                    cout << "Linie invalida in fisier: " << line << endl;
                    continue;
                }

                try 
                {
                    float venit = stof(v);
                    float bani_cheltuiti = stof(cheltuiala);
                    float bani_castigati = stof(castig);
                    float profit = stof(p);
                    raport.push_back(new Raport(venit, bani_cheltuiti, bani_castigati, oras));
                } catch (...) 
                {
                    cout << "Eroare la conversia datelor in linia: " << line << endl;
                }
            }

            f.close();
            return raport;
        }

        void addAngajat(string nume, string functie, int start, int final, const string &fisier)
        {
            ofstream f(fisier, ios::app);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return;
            }

            f << nume << "," << functie << "," << start << "," << final << endl;

            f.close();
        }

        void removeAngajat(string nume_angajat, const string &fisier)
        {
            ifstream fin(fisier);
            if(!fin.is_open())
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru citire" << endl;
                return;
            }

            vector<string> angajati;
            string line;

            //adaug in vector toti angajatii inafara de cel care trebuie scos din fisier
            while(getline(fin, line))
            {
                size_t pozitie = line.find(',');
                if(pozitie != string::npos)
                {
                    string nume = line.substr(0, pozitie);
                    if(nume != nume_angajat)
                    {
                        angajati.push_back(line);
                    }
                }
            }

            fin.close();

            //rescriu fisierul cu noul vector de angajati
            ofstream fout(fisier, ios::trunc);
            if(!fout.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru scriere." << endl;
                return;
            }
            for (const auto &angajat : angajati) 
            {
                fout << angajat << endl;
            }
            fout.close();
        }

        void actualizareStoc(const string &nume_prod, int cantitate, Raport &raport, const string &fisier)
        {
            ifstream f(fisier);
            if(!f.is_open())
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return;
            }

            string line;
            vector<string> lines;
            bool find = false;
            int suma;

            while(getline(f, line)) 
            {
                stringstream ss(line);
                string nume, c, v, nr;
                if (!getline(ss, nume, ',') || !getline(ss, c, ',') || !getline(ss, v, ',') || !getline(ss, nr, ',')) 
                {
                    lines.push_back(line);
                    continue;
                }

                if(nume == nume_prod)
                {
                    try 
                    {
                        int stoc = stoi(nr) + cantitate; //actualizez stocul
                        suma = stoi(c); //contabilizez pretul de cumparare a produsului, pentru a fi folosit la raport
                        line = nume + "," + c + "," + v + "," + to_string(stoc); //noua linie de fisier, cu noua cantitate
                        find = true;
                    } catch(...)
                    {
                        cout << "Eroare la actualizarea stocului pentru " << nume_prod << endl;
                    }
                }

                lines.push_back(line); //adaug noua linie in vector
            }

            f.close();

            if(!find)
            {
                cout << "Produsul " << nume_prod << " nu a fost gasit in fisierul " << fisier << endl;
            }

            //rescriu fisierul
            ofstream fout(fisier);
            if(!fout.is_open())
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru scriere" << endl;
                return;
            }

            for(const auto &l : lines)
            {
                fout << l << endl;
            }

            fout.close();            

            raport.increaseCheltuieli(suma * cantitate); //adaug la cheluieli suma cheltuita pentru actualizarea stocului
        }

        void writeComanda(const string &nume_client, float suma, const string &fisier)
        {
            ofstream f(fisier, ios::app);
            if (!f.is_open()) 
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return;
            }
            f << nume_client << "," << suma << endl;
            f.close();
        }

        void writeClienti(vector<Client*> clienti, const string &fisier)
        {
            ofstream f(fisier);
            if (!f.is_open())
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << " pentru scriere" << endl;
                return;
            }

            for (const auto &client : clienti)
            {
                f << client->getNume() << "," << client->getNrComenzi() << endl;
            }
            f.close();
        }

        void writeRaport(Raport *raport, const string &fisier)
        {
            ofstream f(fisier, ios::app);
            if (!f.is_open())
            {
                cout << "Nu s-a putut deschide fisierul" << fisier << " pentru scriere" << endl;
                return;
            }

            f << raport->getOras() << "," << raport->getVenit() << "," << raport->getBaniCheltuiti() << "," << raport->getBaniCastigati() << "," << raport->getProfit() << endl;
            f.close();
        }

        void writeEveniment(string oras, string nume, int cost, int pret_bilet, int bilete_vandute, const string &fisier)
        {
            ofstream f(fisier, ios::app);
            if (!f.is_open())
            {
                cout << "Nu s-a putut deschide fisierul " << fisier << endl;
                return;
            }
                
            f << oras << "," << nume << "," << cost << "," << pret_bilet << "," << bilete_vandute << endl;
            f.close();
        }
};

void plaseazaComanda(const string &nume_client, vector<string> &prod_comandate, Raport &raport, const string &fisier_produse, const string &fisier_comenzi)
{
    CSV csv;
    vector<Produs*> produse = csv.readProdus(fisier_produse);
    float suma = 0;
    for(const auto &nume_produs : prod_comandate) //parcurg produsele din comanda
    {
        bool find = false;
        for(const auto &produs : produse) //parcurg produsele cafenelei
        {
            if(produs->getNume() == nume_produs && produs->getNrBucati() > 0) //daca produsul este gasit in meniu si mai exista stocuri in camara se produce vanzarea
            {
                suma += produs->getPretVanzare();
                produs->decreaseNrBucati();
                csv.actualizareStoc(nume_produs, -1, raport, fisier_produse);
                find = true;
                break;
            }
        }
               
        if(!find)
        {
            cout << "Produsul " << nume_produs << " nu este disponibil. Va rugam sa comandati altceva" << endl;
        }
    }

    vector<Client*> clienti = csv.readClienti("clienti.csv");
    bool find = false;

    for(auto &client : clienti) //parcurg lista clientilor fideli
    {
        if(client->getNume() == nume_client)
        {
            find = true;
            if(client->getNrComenzi() >= 5) //daca un client are cel putin 5 comenzi, acesta este client fidel, si primeste 10% reducere
            {
                suma = suma - suma * 0.1;
                cout << nume_client << " este client fidel, acestuia i se va aplica o reducere de 10%" << endl;
            }

            client->incrementNrComenzi(); //actualizez numarul de comenzi al clientului
            break;
        }
    }

    //in cazul in care clientul este nou, el este adaugat in fisier cu o comanda, cea actuala
    if(!find) 
    {
        clienti.push_back(new Client(nume_client, 1));
    }

    csv.writeClienti(clienti, "clienti.csv");
    csv.writeComanda(nume_client, suma, fisier_comenzi);
    cout << "Comanda a fost plasata. Nota de plata este in valoare de " << suma << " lei" << endl;

    for (auto &client : clienti)
    {
        delete client;
    }

    raport.increaseCastiguri(suma); //adaug suma comenzii la castiguri
}

int main() 
{
    string nume_angajat, functie, nume_produs, nume_client, prod, nume_eveniment;
    int ora_start, ora_final, cantitate, n, cost, pret_bilet, bilete_vandute, optiune, oras;
    //----------OBIECT----------
    CSV csv; 

    //fiecare cafenea are cate un raport separat, iar la final o sa fie facut unul pentru tot lantul de cafenele
    Raport bucuresti("Bucuresti");
    Raport cluj("Cluj-Napoca");
    Raport timisoara("Timisoara");
    Raport iasi("Iasi");
    Raport brasov("Brasov");

    vector<Raport*> raport = csv.readRaport("raport_financiar.csv");

    //citesc din fisier veniturile pentru fiecare cafenea
    for(const auto &r: raport)
    {
        if(r->getOras() == "Bucuresti")
        {
            bucuresti.setVenit(r->getVenit());
        }
        else if(r->getOras() == "Cluj-Napoca")
        {
            cluj.setVenit(r->getVenit());
        }
        else if(r->getOras() == "Timisoara")
        {
            timisoara.setVenit(r->getVenit());
        }
        else if(r->getOras() == "Iasi")
        {
            iasi.setVenit(r->getVenit());
        }
        else if(r->getOras() == "Brasov")
        {
            brasov.setVenit(r->getVenit());
        }
    }

    //preturile de cumparare si vanzare ale produselor sunt aceleasi pentru toate cafenelele, iar meniul este acelasi, difera doar stocul
    
    vector<string> produseComandate;

    cout << "Alege limba:" << endl;
    cout << "1) Romana" << endl;
    cout << "2) Engleza" << endl;
    int limba;
    cin >> limba;
    if(limba == 1)
    {
        cout << "Bun venit in lantul nostru de cafenele!" << endl;
        do
        {
            cout << "Alege unul dintre orasele in care avem cafenele:" << endl;
            cout << "1) Bucuresti" << endl;
            cout << "2) Cluj-Napoca" << endl;
            cout << "3) Timisoara" << endl;
            cout << "4) Iasi" << endl;
            cout << "5) Brasov" << endl;
            cout << "6) Iesire" << endl;
            cin >> oras;

            switch(oras)
            {
                case 1:
                    cout << "Bun venit in cafeneaua noastra din Bucuresti!" << endl;
                    do
                    {
                        cout << "Alege o optiune:" << endl;
                        cout << "1) Adauga un angajat" << endl;
                        cout << "2) Elimina un angajat" << endl;
                        cout << "3) Actualizeaza stocul pentru un produs" << endl;
                        cout << "4) Plaseaza o comanda" << endl;
                        cout << "5) Adauga un eveniment" << endl;
                        cout << "6) Iesire" << endl;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                cout << "Functie(barista, manager sau ospatar): ";
                                cin >> functie;
                                cout << "Ora de start a programului de munca: ";
                                cin >> ora_start;
                                cout << "Ora de final a programului de munca: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_bucuresti.csv");
                                break;
                            case 2:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_bucuresti.csv");
                                break;
                            case 3:
                                cout << "Nume produs: ";
                                cin >> nume_produs;
                                cout << "Cantitatea cumparata: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, bucuresti, "produse_bucuresti.csv");
                                cout << "Stocul pentru " << nume_produs << " a fost actualizat" << endl;
                                break;
                            case 4:
                                cout << "Numele clientului: ";
                                cin >> nume_client;
                                cout << "Numarul de produse comandate: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, bucuresti, "produse_bucuresti.csv", "comenzi_bucuresti.csv");
                                break;
                            case 5:
                                cout << "Numele evenimentului: ";
                                cin >> nume_eveniment;
                                cout << "Costul organizarii evenimentului: ";
                                cin >> cost;
                                cout << "Pretul unui bilet: ";
                                cin >> pret_bilet;
                                cout << "Numarul de bilete vandute: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Bucuresti", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Evenimentul " << nume_eveniment << " a fost organizat cu succes" << endl;
                                bucuresti.increaseCheltuieli(cost);
                                bucuresti.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Optiune invalida!" << endl;
                        } 
                    } while(optiune != 6);
                    break;
                case 2:
                    cout << "Bun venit in cafeneaua noastra din Cluj-Napoca!" << endl;
                    do
                    {
                        cout << "Alege o optiune:" << endl;
                        cout << "1) Adauga un angajat" << endl;
                        cout << "2) Elimina un angajat" << endl;
                        cout << "3) Actualizeaza stocul pentru un produs" << endl;
                        cout << "4) Plaseaza o comanda" << endl;
                        cout << "5) Adauga un eveniment" << endl;
                        cout << "6) Iesire" << endl;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                cout << "Functie(barista, manager sau ospatar): ";
                                cin >> functie;
                                cout << "Ora de start a programului de munca: ";
                                cin >> ora_start;
                                cout << "Ora de final a programului de munca: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_cluj.csv");
                                break;
                            case 2:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_cluj.csv");
                                break;
                            case 3:
                                cout << "Nume produs: ";
                                cin >> nume_produs;
                                cout << "Cantitatea cumparata: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, cluj, "produse_cluj.csv");
                                cout << "Stocul pentru " << nume_produs << " a fost actualizat" << endl;
                                break;
                            case 4:
                                cout << "Numele clientului: ";
                                cin >> nume_client;
                                cout << "Numarul de produse comandate: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, cluj, "produse_cluj.csv", "comenzi_cluj.csv");
                                break;
                            case 5:
                                cout << "Numele evenimentului: ";
                                cin >> nume_eveniment;
                                cout << "Costul organizarii evenimentului: ";
                                cin >> cost;
                                cout << "Pretul unui bilet: ";
                                cin >> pret_bilet;
                                cout << "Numarul de bilete vandute: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Cluj-Napoca", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Evenimentul " << nume_eveniment << " a fost organizat cu succes" << endl;
                                cluj.increaseCheltuieli(cost);
                                cluj.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Optiune invalida!" << endl;
                        } 
                    } while(optiune != 6);
                    break;
                case 3:
                    cout << "Bun venit in cafeneaua noastra din Timisoara!" << endl;
                    do
                    {
                        cout << "Alege o optiune:" << endl;
                        cout << "1) Adauga un angajat" << endl;
                        cout << "2) Elimina un angajat" << endl;
                        cout << "3) Actualizeaza stocul pentru un produs" << endl;
                        cout << "4) Plaseaza o comanda" << endl;
                        cout << "5) Adauga un eveniment" << endl;
                        cout << "6) Iesire" << endl;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                cout << "Functie(barista, manager sau ospatar): ";
                                cin >> functie;
                                cout << "Ora de start a programului de munca: ";
                                cin >> ora_start;
                                cout << "Ora de final a programului de munca: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_timisoara.csv");
                                break;
                            case 2:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_timisoara.csv");
                                break;
                            case 3:
                                cout << "Nume produs: ";
                                cin >> nume_produs;
                                cout << "Cantitatea cumparata: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, timisoara, "produse_timisoara.csv");
                                cout << "Stocul pentru " << nume_produs << " a fost actualizat" << endl;
                                break;
                            case 4:
                                cout << "Numele clientului: ";
                                cin >> nume_client;
                                cout << "Numarul de produse comandate: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, timisoara, "produse_timisoara.csv", "comenzi_timisoara.csv");
                                break;
                            case 5:
                                cout << "Numele evenimentului: ";
                                cin >> nume_eveniment;
                                cout << "Costul organizarii evenimentului: ";
                                cin >> cost;
                                cout << "Pretul unui bilet: ";
                                cin >> pret_bilet;
                                cout << "Numarul de bilete vandute: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Timisoara", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Evenimentul " << nume_eveniment << " a fost organizat cu succes" << endl;
                                timisoara.increaseCheltuieli(cost);
                                timisoara.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Optiune invalida!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 4:
                    cout << "Bun venit in cafeneaua noastra din Iasi!" << endl;
                    do
                    {
                        cout << "Alege o optiune:" << endl;
                        cout << "1) Adauga un angajat" << endl;
                        cout << "2) Elimina un angajat" << endl;
                        cout << "3) Actualizeaza stocul pentru un produs" << endl;
                        cout << "4) Plaseaza o comanda" << endl;
                        cout << "5) Adauga un eveniment" << endl;
                        cout << "6) Iesire" << endl;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                cout << "Functie(barista, manager sau ospatar): ";
                                cin >> functie;
                                cout << "Ora de start a programului de munca: ";
                                cin >> ora_start;
                                cout << "Ora de final a programului de munca: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_iasi.csv");
                                break;
                            case 2:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_iasi.csv");
                                break;
                            case 3:
                                cout << "Nume produs: ";
                                cin >> nume_produs;
                                cout << "Cantitatea cumparata: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, iasi, "produse_iasi.csv");
                                cout << "Stocul pentru " << nume_produs << " a fost actualizat" << endl;
                                break;
                            case 4:
                                cout << "Numele clientului: ";
                                cin >> nume_client;
                                cout << "Numarul de produse comandate: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, iasi, "produse_iasi.csv", "comenzi_iasi.csv");
                                break;
                            case 5:
                                cout << "Numele evenimentului: ";
                                cin >> nume_eveniment;
                                cout << "Costul organizarii evenimentului: ";
                                cin >> cost;
                                cout << "Pretul unui bilet: ";
                                cin >> pret_bilet;
                                cout << "Numarul de bilete vandute: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Iasi", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Evenimentul " << nume_eveniment << " a fost organizat cu succes" << endl;
                                iasi.increaseCheltuieli(cost);
                                iasi.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Optiune invalida!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 5:
                    cout << "Bun venit in cafeneaua noastra din Brasov!" << endl;
                    do
                    {
                        cout << "Alege o optiune:" << endl;
                        cout << "1) Adauga un angajat" << endl;
                        cout << "2) Elimina un angajat" << endl;
                        cout << "3) Actualizeaza stocul pentru un produs" << endl;
                        cout << "4) Plaseaza o comanda" << endl;
                        cout << "5) Adauga un eveniment" << endl;
                        cout << "6) Iesire" << endl;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                cout << "Functie(barista, manager sau ospatar): ";
                                cin >> functie;
                                cout << "Ora de start a programului de munca: ";
                                cin >> ora_start;
                                cout << "Ora de final a programului de munca: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_brasov.csv");
                                break;
                            case 2:
                                cout << "Nume angajat: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_brasov.csv");
                                break;
                            case 3:
                                cout << "Nume produs: ";
                                cin >> nume_produs;
                                cout << "Cantitatea cumparata: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, brasov, "produse_brasov.csv");
                                cout << "Stocul pentru " << nume_produs << " a fost actualizat" << endl;
                                break;
                            case 4:
                                cout << "Numele clientului: ";
                                cin >> nume_client;
                                cout << "Numarul de produse comandate: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, brasov, "produse_brasov.csv", "comenzi_brasov.csv");
                                break;
                            case 5:
                                cout << "Numele evenimentului: ";
                                cin >> nume_eveniment;
                                cout << "Costul organizarii evenimentului: ";
                                cin >> cost;
                                cout << "Pretul unui bilet: ";
                                cin >> pret_bilet;
                                cout << "Numarul de bilete vandute: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Brasov", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Evenimentul " << nume_eveniment << " a fost organizat cu succes" << endl;
                                brasov.increaseCheltuieli(cost);
                                brasov.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Optiune invalida!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 6:
                    cout << "Programul se ve incheia!";
                    break;
                default:
                    cout << "Optiune invalida!";
            } 
        } while(oras != 6);
    }
    else if(limba == 2)
    {
        cout << "Welcome to our chain of coffee shops!" << endl;
        do
        {
            cout << "Choose one of the cities where we have coffee shop:" << endl;
            cout << "1) Bucharest" << endl;
            cout << "2) Cluj-Napoca" << endl;
            cout << "3) Timisoara" << endl;
            cout << "4) Iasi" << endl;
            cout << "5) Brasov" << endl;
            cout << "6) Exit" << endl;
            cin >> oras;

            switch(oras)
            {
                case 1:
                    cout << "Welcome to our Bucharest coffee shop!" << endl;
                    do
                    {
                        cout << "Choose a option:" << endl;
                        cout << "1) Add an employee" << endl;
                        cout << "2) Remove an employee" << endl;
                        cout << "3) Update the stock for a product" << endl;
                        cout << "4) Take the order" << endl;
                        cout << "5) Add an event" << endl;
                        cout << "6) Exit" << endl;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                cout << "Function(barista, manager or ospatar = server): ";
                                cin >> functie;
                                cout << "Start time of the work schedule: ";
                                cin >> ora_start;
                                cout << "End time of the work schedule: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_bucuresti.csv");
                                break;
                            case 2:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_bucuresti.csv");
                                break;
                            case 3:
                                cout << "Product's name: ";
                                cin >> nume_produs;
                                cout << "Quantity purchased: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, bucuresti, "produse_bucuresti.csv");
                                cout << "Stock for " << nume_produs << " was updated" << endl;
                                break;
                            case 4:
                                cout << "Customer's name: ";
                                cin >> nume_client;
                                cout << "Number of products purchased: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, bucuresti, "produse_bucuresti.csv", "comenzi_bucuresti.csv");
                                break;
                            case 5:
                                cout << "Event's name: ";
                                cin >> nume_eveniment;
                                cout << "Cost of event: ";
                                cin >> cost;
                                cout << "Ticket price: ";
                                cin >> pret_bilet;
                                cout << "Number of tickets sold: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Bucuresti", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Event " << nume_eveniment << " was successfully organized" << endl;
                                bucuresti.increaseCheltuieli(cost);
                                bucuresti.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Invalid option!" << endl;
                        } 
                    } while(optiune != 6);
                    break;
                case 2:
                    cout << "Welcome to our Cluj-Napoca coffee shop!" << endl;
                    do
                    {
                        cout << "Choose a option:" << endl;
                        cout << "1) Add an employee" << endl;
                        cout << "2) Remove an employee" << endl;
                        cout << "3) Update the stock for a product" << endl;
                        cout << "4) Take the order" << endl;
                        cout << "5) Add an event" << endl;
                        cout << "6) Exit" << endl;
                        cin >> optiune;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                cout << "Function(barista, manager or ospatar = server): ";
                                cin >> functie;
                                cout << "Start time of the work schedule: ";
                                cin >> ora_start;
                                cout << "End time of the work schedule: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_cluj.csv");
                                break;
                            case 2:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_cluj.csv");
                                break;
                            case 3:
                                cout << "Product's name: ";
                                cin >> nume_produs;
                                cout << "Quantity purchased: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, cluj, "produse_cluj.csv");
                                cout << "Stock for " << nume_produs << " was updated" << endl;
                                break;
                            case 4:
                                cout << "Customer's name: ";
                                cin >> nume_client;
                                cout << "Number of products purchased: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, cluj, "produse_cluj.csv", "comenzi_cluj.csv");
                                break;
                            case 5:
                                cout << "Event's name: ";
                                cin >> nume_eveniment;
                                cout << "Cost of event: ";
                                cin >> cost;
                                cout << "Ticket price: ";
                                cin >> pret_bilet;
                                cout << "Number of tickets sold: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Cluj-Napoca", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Event " << nume_eveniment << " was successfully organized" << endl;
                                cluj.increaseCheltuieli(cost);
                                cluj.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Invalid option!" << endl;
                        } 
                    } while(optiune != 6);
                    break;
                case 3:
                    cout << "Bun venit in cafeneaua noastra din Timisoara!" << endl;
                    do
                    {
                        cout << "Choose a option:" << endl;
                        cout << "1) Add an employee" << endl;
                        cout << "2) Remove an employee" << endl;
                        cout << "3) Update the stock for a product" << endl;
                        cout << "4) Take the order" << endl;
                        cout << "5) Add an event" << endl;
                        cout << "6) Exit" << endl;
                        cin >> optiune;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                cout << "Function(barista, manager or ospatar = server): ";
                                cin >> functie;
                                cout << "Start time of the work schedule: ";
                                cin >> ora_start;
                                cout << "End time of the work schedule: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_timisoara.csv");
                                break;
                            case 2:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_timisoara.csv");
                                break;
                            case 3:
                                cout << "Product's name: ";
                                cin >> nume_produs;
                                cout << "Quantity purchased: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, timisoara, "produse_timisoara.csv");
                                cout << "Stock for " << nume_produs << " was updated" << endl;
                                break;
                            case 4:
                                cout << "Customer's name: ";
                                cin >> nume_client;
                                cout << "Number of products purchased: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, timisoara, "produse_timisoara.csv", "comenzi_timisoara.csv");
                                break;
                            case 5:
                                cout << "Event's name: ";
                                cin >> nume_eveniment;
                                cout << "Cost of event: ";
                                cin >> cost;
                                cout << "Ticket price: ";
                                cin >> pret_bilet;
                                cout << "Number of tickets sold: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Timisoara", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Event " << nume_eveniment << " was successfully organized" << endl;
                                timisoara.increaseCheltuieli(cost);
                                timisoara.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Invalid option!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 4:
                    cout << "Bun venit in cafeneaua noastra din Iasi!" << endl;
                    do
                    {
                        cout << "Choose a option:" << endl;
                        cout << "1) Add an employee" << endl;
                        cout << "2) Remove an employee" << endl;
                        cout << "3) Update the stock for a product" << endl;
                        cout << "4) Take the order" << endl;
                        cout << "5) Add an event" << endl;
                        cout << "6) Exit" << endl;
                        cin >> optiune;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                cout << "Function(barista, manager or ospatar = server): ";
                                cin >> functie;
                                cout << "Start time of the work schedule: ";
                                cin >> ora_start;
                                cout << "End time of the work schedule: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_iasi.csv");
                                break;
                            case 2:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_iasi.csv");
                                break;
                            case 3:
                                cout << "Product's name: ";
                                cin >> nume_produs;
                                cout << "Quantity purchased: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, iasi, "produse_iasi.csv");
                                cout << "Stock for " << nume_produs << " was updated" << endl;
                                break;
                            case 4:
                                cout << "Customer's name: ";
                                cin >> nume_client;
                                cout << "Number of products purchased: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, iasi, "produse_iasi.csv", "comenzi_iasi.csv");
                                break;
                            case 5:
                                cout << "Event's name: ";
                                cin >> nume_eveniment;
                                cout << "Cost of event: ";
                                cin >> cost;
                                cout << "Ticket price: ";
                                cin >> pret_bilet;
                                cout << "Number of tickets sold: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Iasi", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Event " << nume_eveniment << " was successfully organized" << endl;
                                iasi.increaseCheltuieli(cost);
                                iasi.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Invalid option!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 5:
                    cout << "Bun venit in cafeneaua noastra din Brasov!" << endl;
                    do
                    {
                        cout << "Choose a option:" << endl;
                        cout << "1) Add an employee" << endl;
                        cout << "2) Remove an employee" << endl;
                        cout << "3) Update the stock for a product" << endl;
                        cout << "4) Take the order" << endl;
                        cout << "5) Add an event" << endl;
                        cout << "6) Exit" << endl;
                        cin >> optiune;

                        int optiune;
                        cin >> optiune;

                        switch(optiune)
                        {
                            case 1:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                cout << "Function(barista, manager or ospatar = server): ";
                                cin >> functie;
                                cout << "Start time of the work schedule: ";
                                cin >> ora_start;
                                cout << "End time of the work schedule: ";
                                cin >> ora_final;
                                csv.addAngajat(nume_angajat, functie, ora_start, ora_final, "angajati_brasov.csv");
                                break;
                            case 2:
                                cout << "Employee's name: ";
                                cin >> nume_angajat;
                                csv.removeAngajat(nume_angajat, "angajati_brasov.csv");
                                break;
                            case 3:
                                cout << "Product's name: ";
                                cin >> nume_produs;
                                cout << "Quantity purchased: ";
                                cin >> cantitate;
                                csv.actualizareStoc(nume_produs, cantitate, brasov, "produse_brasov.csv");
                                cout << "Stock for " << nume_produs << " was updated" << endl;
                                break;
                            case 4:
                                cout << "Customer's name: ";
                                cin >> nume_client;
                                cout << "Number of products purchased: ";
                                cin >> n;
                                for(int i = 0; i < n; i++)
                                {
                                    cin >> prod;
                                    produseComandate.push_back(prod);
                                }
                                plaseazaComanda(nume_client, produseComandate, brasov, "produse_brasov.csv", "comenzi_brasov.csv");
                                break;
                            case 5:
                                cout << "Event's name: ";
                                cin >> nume_eveniment;
                                cout << "Cost of event: ";
                                cin >> cost;
                                cout << "Ticket price: ";
                                cin >> pret_bilet;
                                cout << "Number of tickets sold: ";
                                cin >> bilete_vandute;
                                csv.writeEveniment("Brasov", nume_eveniment, cost, pret_bilet, bilete_vandute, "evenimente.csv");
                                cout << "Event " << nume_eveniment << " was successfully organized" << endl;
                                brasov.increaseCheltuieli(cost);
                                brasov.increaseCastiguri(pret_bilet * bilete_vandute);
                                break;
                            case 6:
                                break;
                            default:  
                                cout << "Invalid option!" << endl;
                        }
                    } while(optiune != 6);
                    break;
                case 6:
                    cout << "The program will end!";
                    break;
                default:
                    cout << "Invalid option!";
            } 
        } while(oras != 6);
    }
    else
    {
        cout << "Comanda incorecta";
    }

    //citesc fisierle cu angajati si adaug salariile lor la cheltuieli
    vector<Angajat*> angajati;
    angajati = csv.readAngajati("angajati_bucuresti.csv");
    for(const auto &ang : angajati) 
    {
        int ore = ang->getOraFinal() - ang->getOraStart();
        bucuresti.increaseCheltuieli(ang->getSalariu() * ore);
        delete ang; 
    }
    bucuresti.increaseVenit();

    angajati = csv.readAngajati("angajati_cluj.csv");
    for(const auto &ang : angajati) 
    {
        int ore = ang->getOraFinal() - ang->getOraStart();
        cluj.increaseCheltuieli(ang->getSalariu() * ore);
        delete ang; 
    }
    cluj.increaseVenit();

    angajati = csv.readAngajati("angajati_timisoara.csv");
    for(const auto &ang : angajati) 
    {
        int ore = ang->getOraFinal() - ang->getOraStart();
        timisoara.increaseCheltuieli(ang->getSalariu() * ore);
        delete ang; 
    }
    timisoara.increaseVenit();

    angajati = csv.readAngajati("angajati_iasi.csv");
    for(const auto &ang : angajati) 
    {
        int ore = ang->getOraFinal() - ang->getOraStart();
        iasi.increaseCheltuieli(ang->getSalariu() * ore);
        delete ang; 
    }
    iasi.increaseVenit();

    angajati = csv.readAngajati("angajati_brasov.csv");
    for(const auto &ang : angajati) 
    {
        int ore = ang->getOraFinal() - ang->getOraStart();
        brasov.increaseCheltuieli(ang->getSalariu() * ore);
        delete ang; 
    }
    brasov.increaseVenit();

    //calculez venitul, cheltuielile si castigurile totale, si le adaug in fisierul de raport
    int venit, bani_cheltuiti, bani_castigati;
    venit = bucuresti.getVenit() + cluj.getVenit() + timisoara.getVenit() + iasi.getVenit() + brasov.getVenit();
    bani_cheltuiti = bucuresti.getBaniCheltuiti() + cluj.getBaniCheltuiti() + timisoara.getBaniCheltuiti() + iasi.getBaniCheltuiti() + brasov.getBaniCheltuiti();
    bani_castigati = bucuresti.getBaniCastigati() + cluj.getBaniCastigati() + timisoara.getBaniCastigati() + iasi.getBaniCastigati() + brasov.getBaniCastigati();
    Raport total(venit, bani_cheltuiti, bani_castigati, "Total");

    csv.writeRaport(&bucuresti, "raport_financiar.csv");
    csv.writeRaport(&cluj, "raport_financiar.csv");
    csv.writeRaport(&timisoara, "raport_financiar.csv");
    csv.writeRaport(&iasi, "raport_financiar.csv");
    csv.writeRaport(&brasov, "raport_financiar.csv");
    csv.writeRaport(&total, "raport_financiar.csv");

    return 0;
}
