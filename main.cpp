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
void stampa_csv_auto();
void stampa_lista(vector<macchina> &vet_macchine);

int main()
{
    vector<macchina> vet_macchine;
    macchina* bottom;
    cout<<"Il programma gestisce le prenotazioni in un autonoleggio di un'auto per una settimana"
        "\nda luned"<<(char) 141<<" a domenica, nell'ipotesi che una macchina possa essere affittata solo per"
        "\ngiornate intere e non spezzoni di giornata.\n";
    system("timeout 10");
    system("cls");
    leggi_csv_auto(vet_macchine);
    stampa_lista(vet_macchine);


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
        getline(fin, s, '\n');
        appoggio.domenica = s.at(1);

        vet_macchine.push_back(appoggio);


    }
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
}
