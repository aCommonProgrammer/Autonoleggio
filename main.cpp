#include <iostream>
#include <list>
#include <fstream>

using namespace std;

struct macchina
{
    string categoria, marca, modello, colore;
    char lunedi, martedi, mercoledi, giovedi, venerdi, sabato, domenica;
};

void leggi_csv_auto(list<macchina> lista_macchine);
void stampa_csv_auto();
void stampa_lista(list<macchina> lista_macchine);

int main()
{
    list<macchina> lista_macchine;
    cout<<"Il programma gestisce le prenotazioni in un autonoleggio di un'auto per una settimana"
        "\nda luned"<<(char) 141<<" a domenica, nell'ipotesi che una macchina possa essere affittata solo per"
        "\ngiornate intere e non spezzoni di giornata.\n";
    system("timeout 10");
    system("cls");
    leggi_csv_auto(lista_macchine);
    stampa_lista(lista_macchine);


    return 0;
}

void leggi_csv_auto(list<macchina> lista_macchine)
{
    fstream fin("auto.csv");
    string s;
    macchina appoggio;
    getline(fin, s);
    getline(fin, s);
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
        getline(fin, s, ',');
        appoggio.domenica = s.at(1);

        lista_macchine.push_front(appoggio);
    }
}

void stampa_lista(list<macchina> lista_macchine)
{
    cout<<"Categoria, Marca, Modello, Colore, Luned"<<(char) 141<<", Marted"<<(char) 141<<", Mercoled"<<(char) 141<<", Gioved"<<(char) 141<<", Venerd"<<(char) 141<<", Sabato, Domenica";
    macchina appoggio;
    for (int c=lista_macchine.size(); c>0; c++)
    {
        appoggio = lista_macchine.front();
        cout<<appoggio.categoria<<','<<appoggio.marca<<','<<','<<appoggio.modello<<','<<appoggio.colore<<','<<appoggio.lunedi<<','<<appoggio.martedi<<','<<appoggio.mercoledi<<','<<appoggio.giovedi<<','<<appoggio.venerdi<<','<<appoggio.sabato<<','<<appoggio.domenica;
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
}
