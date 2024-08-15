#include <iostream>
using namespace std;

template <class T>
class tablicaDynamiczna {
private:
    T* tablica{NULL};
    int rozmiar{0}, pojemnosc{1}, powiekszanie{2};

public:
    tablicaDynamiczna() :
            rozmiar(0),
            pojemnosc(1),
            powiekszanie(2),
            tablica(new T[1])
    {}
    ~tablicaDynamiczna() {
        delete[] tablica;
    }
    void dodawanieElementu(T element) {
        if (rozmiar == pojemnosc) {
            powiekszanieTablicy();
        }
        tablica[rozmiar] = element;
        rozmiar = rozmiar + 1;
    }
    void powiekszanieTablicy() {
        pojemnosc *= powiekszanie;
        T* powiekszonaTablica = new T[pojemnosc];
        for (int i = 0; i < rozmiar; i++)
        {
            powiekszonaTablica[i] = tablica[i];
        }
        delete[] tablica;
        tablica = powiekszonaTablica;
    }
    void wyswietlanie() {
        for (int i = 0; i < rozmiar; i++)
        {
            cout << tablica[i] << endl;
        }
        cout << "\nAktualna liczba danych w tablicy: " << rozmiar << endl;
        cout << "Aktualna pojemnosc tablicy: " << pojemnosc << endl;;
    }
    void zwrocenieDanych() {
        int indeks;
        cout << "Podaj indeks elementu tablicy: " << endl;
        cin >> indeks;
        if (indeks < rozmiar && indeks >= 0) {
            cout << tablica[indeks] << endl << endl;
        }
        else {
            //cout << "Podana wartosc jest poza zakresem tablicy. Sprobuj jeszcze raz. " << endl;
            zwrocenieDanych();
        }
    }
    void czyszczenie() {
        delete[] tablica;
        tablica = new T[pojemnosc];
        rozmiar = 0;
        pojemnosc = 1;
    }
    void bubbleSort() {
        bool swapped;
        for (int i = 0; i < rozmiar; i++)
        {
            swapped = false;
            for (int j = 0; j < rozmiar - 1; j++)  /// tu poprawic
            {
                if (tablica[j] > tablica[j + 1]) { /// tu poprawic
                    swap(tablica[j + 1], tablica[j]);
                    swapped = true;
                }
            }
            if(!swapped) {
                break;
            }
        }
    }
    void podmianaDanych() {
        int indeks;
        cout << "Podaj indeks tablicy: " << endl;
        cin >> indeks;
        if (indeks < rozmiar && indeks >= 0) {
            T nowyelement;
            cout << "Podaj nowa wartosc: ";
            cin >> nowyelement;
            tablica[indeks] = nowyelement;

        }
        else {
            //cout << "Podana wartosc jest poza zakresem tablicy. Sprobuj jeszcze raz. " << endl;
            podmianaDanych();
        }
    }
};

int main()
{
    auto* obiekt = new tablicaDynamiczna<std::string>();
    obiekt->dodawanieElementu("4");
    obiekt->dodawanieElementu("b");
    obiekt->dodawanieElementu("z");
    obiekt->dodawanieElementu("f");
    obiekt->dodawanieElementu("a");

    /* for (int i = 0; i < 50; i++)
     {
         obiekt->dodawanieElementu(rand() % 100);
     }*/


    obiekt->wyswietlanie();
    obiekt->podmianaDanych();
//    obiekt->wyswietlanie();
    //obiekt->zwrocenieDanych();
    obiekt->bubbleSort();
    obiekt->wyswietlanie();
    obiekt->czyszczenie();
    obiekt->wyswietlanie();
}