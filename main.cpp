#include <iostream>
#include <vector>
#include <fstream>

#define FILENAME "auto.csv"

using namespace std;

struct macchina
{
    string categoria, marca, modello, colore;
    bool giorni_sett[7] = {false,false,false,false,false,false,false};
};

void leggi_csv_auto(vector<macchina> &vet_macchine);
void suddivisione_stringa_ricerca(string &categoria,bool giorni_sett[], string s);
void ricerca_auto_disponibili(vector<int>& key, vector<macchina> vet_macchine,string categoria,bool giorni_sett[]);
vector<macchina> modifica_vet_key(int key, vector<macchina> vet_macchine,bool giorni_sett[]);
void modifica_csv(vector<macchina> vet_macchine);
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
    system("pause");
    system("cls");
    cout<<"Se si desidera usare il programma ";
    system("pause");
    bool ripetere = true;
do{
        system("cls");
        string s;
        cout<<"Inserire i dati dell'auto secondo il formato:\n \"categoria n_giorno\" (le categorie sono: utilitaria, media, lusso, sportiva e furgone; i giorni sono codificati così: 1=luned"<<(char) 141<<", 2=marted"<<(char) 141<<"..., 7=domenica)"<<(char) 25<<"\n";
        cin.ignore();
        getline(cin, s);

        string categoria;
        bool giorni_sett[7] = {false,false,false,false,false,false,false};
        suddivisione_stringa_ricerca(categoria,giorni_sett,s);

        vector<int> key;
        ricerca_auto_disponibili(key, vet_macchine,categoria,giorni_sett);

        system("cls");

        if (key.size() > 0)
        {
            cout<<"Le macchine disponibili sono:\n";
            for(int c=0; c<key.size(); c++)
                cout<<c+1<<(char) -8<<'-'<<vet_macchine[key[c]].marca<<", "<<vet_macchine[key[c]].modello<<", "<<vet_macchine[key[c]].colore<<endl;
            int scelta;
            cout<<"Inserire il numero dell'auto da prenotare: "; cin>>scelta; scelta--;
            modifica_csv(modifica_vet_key(key[scelta], vet_macchine, giorni_sett));
            ripetere = false;
        }
        else
        {
            cout<<"Non "<<(char) 138<<" stata trovata nessuna macchina con i requisiti richiesti\n";
            string r;
            cout<<"Cercare di nuovo? "; cin>>r;
            if (r!="si" && r!="SI" && r!="Si")
                ripetere = false;
        }
    }while(ripetere);
    system("cls");
    cout<<"Il file testuale ora si presenta in questo modo:\n\n";
    stampa_csv_auto();
    system("pause");
    cout<<"Il vettore del programma ora si presenta in questo modo:\n\n";
    stampa_lista(vet_macchine);


    return 0;
}

void leggi_csv_auto(vector<macchina> &vet_macchine)
{
    ifstream fin(FILENAME);
    string s;
    getline(fin, s);
    getline(fin, s);
    macchina appoggio;
    while (fin)
    {
        getline(fin, appoggio.categoria, ',');
        getline(fin, appoggio.marca, ',');
        appoggio.marca.erase(0,1);
        getline(fin, appoggio.modello, ',');
        appoggio.modello.erase(0,1);
        getline(fin, appoggio.colore, ',');
        appoggio.colore.erase(0,1);
        for(int c=0; c<6; c++)
        {
            getline(fin, s, ',');
            if (s == " L") appoggio.giorni_sett[c] = 0;
            else appoggio.giorni_sett[c] = 1;
            cout<<"\""<<s<<"\""<<endl;
        }
        getline(fin, s);
        if (s.at(1) == 'L') appoggio.giorni_sett[6] = 0;
        else appoggio.giorni_sett[6] = 1;
        cout<<"\""<<s<<"\""<<endl;
        vet_macchine.push_back(appoggio);
    }
    fin.close();
}

void suddivisione_stringa_ricerca(string &categoria, bool giorni_sett[], string s)
{
    categoria = "";
    int c;
    for( c=0;c<s.length() && s.at(c) != ' ' ; c++)
        categoria +=  s.at(c);
    for(c++; c<s.length(); c++)
        if (s.at(c) >= 48 && s.at(c) <= 57)
            giorni_sett[(int) s.at(c) - 49] = true;
}

void ricerca_auto_disponibili(vector<int> &key,vector<macchina> vet_macchine,string categoria,bool giorni_sett[])
{
    for(int c=0; c<vet_macchine.size(); c++)
        if(vet_macchine[c].categoria == categoria)
        {
            for (int i=0; i<7 ;i++)
                if(vet_macchine[c].giorni_sett[i] == giorni_sett[i] && vet_macchine[c].giorni_sett[i])
                    goto salta;
            key.push_back(c);
        salta:
            c=c;
        }
}

vector<macchina> modifica_vet_key(int key, vector<macchina> vet_macchine,bool giorni_sett[])
{
    for (int c=0; c<7 ;c++)
        vet_macchine[key].giorni_sett[c] = vet_macchine[key].giorni_sett[c] | giorni_sett[c];
    return vet_macchine;
}

void modifica_csv(vector<macchina> vet_macchine)
{
    ofstream fout(FILENAME);
    fout<<"\nCategoria, Marca, Modello, Colore, Luned"<<(char) 141<<", Marted"<<(char) 141<<", Mercoled"<<(char) 141<<", Gioved"<<(char) 141<<", Venerdi, Sabato, Domenica\n";
    for (int c=0; c< vet_macchine.size(); c++)
    {
        fout<<vet_macchine[c].categoria<<", "<<vet_macchine[c].marca<<", "<<vet_macchine[c].modello<<", "<<vet_macchine[c].colore<<", ";
        for (int i=0;i<7;i++)
            if(vet_macchine[c].giorni_sett[i]) fout<<"A";
            else fout<<"L";
        fout<<endl;
    }
    fout.close();
}

void stampa_lista(vector<macchina>& vet_macchine)
{
    cout<<"Categoria, Marca, Modello, Colore, Luned"<<(char) 141<<", Marted"<<(char) 141<<", Mercoled"<<(char) 141<<", Gioved"<<(char) 141<<", Venerd"<<(char) 141<<", Sabato, Domenica\n";
    macchina appoggio;
    for(int c=0; c<vet_macchine.size();c++)
    {
        cout<<vet_macchine[c].categoria<<", "<<vet_macchine[c].marca<<", "<<vet_macchine[c].modello<<", "<<vet_macchine[c].colore<<", ";
        for (int i=0;i<7;i++)
            if(vet_macchine[c].giorni_sett[i]) cout<<"A";
            else cout<<"L";
        cout<<endl;
    }
}

void stampa_csv_auto()
{
    ifstream fin(FILENAME);
    string s;
    while (!fin.eof())
    {
        getline(fin, s);
        cout<<s<<endl;
    }
    fin.close();
}
