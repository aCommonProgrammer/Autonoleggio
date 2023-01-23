#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct macchina
{
    string categoria, marca, modello, colore;
    char lunedi, martedi, mercoledi, giovedi, venerdi, sabato, domenica;
};

void leggi_csv_auto(vector<macchina> &vet_macchine);
void suddivisione_stringa_ricerca(string &categoria,char &lun,char &mar,char &mer,char &gio,char &ven,char &sab,char &dom, string s);
vector<int> ricerca_auto_disponibili(vector<macchina> vet_macchine,string categoria,char lun,char mar,char mer,char gio,char ven,char sab,char dom);
void stampa_lista(vector<macchina> &vet_macchine);
void stampa_csv_auto();

int main()
{
    vector<macchina> vet_macchine;
    cout<<"Il programma gestisce le prenotazioni in un autonoleggio di un'auto per una settimana"
        "\nda luned"<<(char) 141<<" a domenica, nell'ipotesi che una macchina possa essere affittata solo per"
        "\ngiornate intere e non spezzoni di giornata.\n";
    system("timeout 10");
    leggi_csv_auto(vet_macchine);
    system("cls");
    cout<<"Se si desidera usare il programma ";
    system("pause");
    system("cls");
    string s;
    cout<<"Inserire i dati dell'auto secondo il formato: \"categoria n_giorno\" (i giorni sono codificati così: 1=luned"<<(char) 141<<", 2=marted"<<(char) 141<<"..., 7=domenica) \n";
    getline(cin, s);

    string categoria;
    char lun, mar, mer, gio, ven, sab, dom;
    suddivisione_stringa_ricerca(categoria,lun,mar,mer,gio,ven,sab,dom,s);

    vector<int> key = ricerca_auto_disponibili(vet_macchine,categoria,lun,mar,mer,gio,ven,sab,dom);

   /* if (key.size() > 0)
    {

    }
    else
        cout<<"Non "<<(char) 138<<" stat trovata nessuna macchina con i requisiti richiesti";*/



    return 0;
}

void leggi_csv_auto(vector<macchina> &vet_macchine)
{
    fstream fin("auto.csv");
    string s;
    getline(fin, s);
    getline(fin, s);
    macchina appoggio;
    while (!fin.eof())
    {
        getline(fin, appoggio.categoria, ',');
        getline(fin, appoggio.marca, ',');
        appoggio.marca.erase(0,1);
        getline(fin, appoggio.modello, ',');
        appoggio.modello.erase(0,1);
        getline(fin, appoggio.colore, ',');
        appoggio.colore.erase(0,1);
        getline(fin, s, ',');
        appoggio.lunedi = s.at(1);
        getline(fin, s, ',');
        appoggio.martedi = s.at(1);
        getline(fin, s, ',');
        appoggio.mercoledi = s.at(1);
        getline(fin, s, ',');
        appoggio.giovedi = s.at(1);
        getline(fin, s, ',');
        appoggio.venerdi = s.at(1);
        getline(fin, s, ',');
        appoggio.sabato = s.at(1);
        getline(fin, s);
        appoggio.domenica = s.at(1);

        vet_macchine.push_back(appoggio);
    }
    fin.close();
}

void suddivisione_stringa_ricerca(string &categoria,char &lun,char &mar,char &mer,char &gio,char &ven,char &sab,char &dom, string s)
{
    categoria = "";
    lun='L'; mar='L'; mer='L'; gio='L'; ven='L'; sab='L'; dom='L';

    int c;
    for( c=0;c<s.length() && s.at(c) != ' ' ; c++)
        categoria +=  s.at(c);
    for(c++; c<s.length(); c++)
        switch (s.at(c))
        {
        case '1': lun = 'A';
                  break;
        case '2': mar = 'A';
                  break;
        case '3': mer = 'A';
                  break;
        case '4': gio = 'A';
                  break;
        case '5': ven = 'A';
                  break;
        case '6': sab = 'A';
                  break;
        case '7': dom = 'A';
        }
}

vector<int> ricerca_auto_disponibili(vector<macchina> vet_macchine,string categoria,char lun,char mar,char mer,char gio,char ven,char sab,char dom)
{
    vector<int> key;
    for(int c=0; c<vet_macchine.size(); c++)
        if(vet_macchine[c].categoria == categoria && vet_macchine[c].lunedi == lun && vet_macchine[c].martedi == mar && vet_macchine[c].mercoledi == mer && vet_macchine[c].giovedi == gio && vet_macchine[c].venerdi == ven && vet_macchine[c].sabato == sab && vet_macchine[c].domenica == dom)
            key.push_back(c);

    return key;
}

void stampa_lista(vector<macchina>& vet_macchine)
{
    cout<<"Categoria, Marca, Modello, Colore, Luned"<<(char) 141<<", Marted"<<(char) 141<<", Mercoled"<<(char) 141<<", Gioved"<<(char) 141<<", Venerd"<<(char) 141<<", Sabato, Domenica"<<endl;
    macchina appoggio;
    for(int c=0; c<vet_macchine.size();c++)
    {
        cout<<vet_macchine[c].categoria<<','<<vet_macchine[c].marca<<','<<vet_macchine[c].modello<<','<<vet_macchine[c].colore<<','<<vet_macchine[c].lunedi<<','<<vet_macchine[c].martedi<<','<<vet_macchine[c].mercoledi<<','<<vet_macchine[c].giovedi<<','<<vet_macchine[c].venerdi<<','<<vet_macchine[c].sabato<<','<<vet_macchine[c].domenica<<endl;
    }
}

void stampa_csv_auto()
{
    fstream fin("auto.csv");
    string s;
    while (!fin.eof())
    {
        getline(fin, s);
        cout<<s<<endl;
    }
    fin.close();
}
