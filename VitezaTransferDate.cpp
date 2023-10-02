//Proiectul 17 SSC, masurarea vitezei de transfer:




//Informatii despre proiect:

/*

-Masurarea vitezei de transfer: Folosesc structuri de date si fisiere pentru a transmite date de la o structura/fisier la altul;
Masor de 3 ori la rand cat dureaza transmiterea, si iau aceste masuratori de un numar variabil de ori, sa zicem 10/100, etc...;
Dupa, fac media lor si creez un graf pentru a afisa diferenta de viteza de transfer;
La primul transfer este cel mai lent, si dupa, urmatoarele incep sa se asemene, deci in mare, se foloseste memoria cache;
In mare, la structuri de date se vede mult mai tare diferenta intre timpul de transfer fata de fisiere, prima rulare
(considerata rularea folosind memoria RAM) dureaza mai mult, si asta se vede in graf;
-Alte informatii se afla in documentatie;

*/




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//1) Librariile folosite:
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Profiler.h"

#include<iostream>

//Pentru fisiere:
#include <fstream>

//Pentru timp:
#include "bits-stdc++.h" 
#include <chrono>

//Pentru mai multe aspecte:
using namespace std; 




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Cat de mare sa fie numarul de bytes transferati;
//1KB = 1 000 chars;
//1MB = 1 000 000 chars;
//1GB = 1 000 000 000 chars; 
long long numarBytesStructuraFisiere = 20000000; //100000000; //10MB;
int numarTeste = 20; //100; //30; //10 sau 100 sau 1000 etc...;

//Pentru structura, cat timp a durat pentru toate transferurile;
long long timpTransferStruct1[1000];
long long timpTransferStruct2[1000];
long long timpTransferStruct3[1000];

//Pentru fisiere, cat timp a durat pentru toate transferurile;
long long timpTransferFile1[1000];
long long timpTransferFile2[1000];
long long timpTransferFile3[1000];

//Sirul unde retin indecsii la sirurile de mai sus:
long long numarBytes[1000];


//Structura 1 si 2, au siruri de tip char *;
typedef struct structuraDate1 {
    
    char* sirStruct1;
    
}sd1; 

typedef struct structuraDate2 {

    char* sirStruct2;

}sd2;




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Pentru calcul cat dureaza transfer pe structuri si pe fisiere;
void CalculareTimpTransfer()
{
    //1) Pentru structuri de date:
    cout << "\nTestarea vitezei de transfer pentru structuri si fisiere:\n\n";
    cout << "Duratele de timp pentru transfer in structuri de date:\n\n";

    //Structurile initiate:
    sd1 structura1;
    sd2 structura2;

    //Merg din 1 000 000 cu generarea a ce trimit, transfer; (MB extra)
    for (long long i = 1000000; i <= numarBytesStructuraFisiere; i = i + 1000000)
    {
        //Pentru transferuri:
        cout << "\n" << i / 1000000 << ") Transfer a " << i << " numar de bytes din sirul 1 in sirul 2: " << endl << endl; 

        //Indexul de la sirul la care retin cat a durat;
        long long index = (i / 1000000) - 1;
        //Aici pun indexul:
        numarBytes[index] = i;

        //Aloc dinamic, cu malloc sirurile din structuri:
        structura1.sirStruct1 = (char*) malloc(sizeof(char) * i);
        structura2.sirStruct2 = (char*) malloc(sizeof(char) * i);

        //Generez sir random de numere, cu literele din alfabet + spatii;
        //Merg pe i, adica pe lungimea a cat transfer acum:
        for (long long j = 0; j < i; j++)
        {
            //Pentru a alege intre litera si spatiu;
            int testSpatiu = rand() % 2;
            char caracter;

            //Daca este 1, atunci avem litera:
            if (testSpatiu == 1)
            {
                caracter = 'a' + rand() % 26;
            }
            //Daca este 0, atunci avem spatiu:
            else
            {
                caracter = ' ';
            }
            
            //Introduc caracterul generat;
            structura1.sirStruct1[j] = caracter;
        }


        //A)
        //Pentru a vedea lungimile, voi verifica de mai multe ori:
        cout << "Verificare lungime sir2 inainte de primul transfer: " << strlen(structura2.sirStruct2) << " .\n";

        //Pentru masurare timp: start1, end1, start2, end2, start3, end3:
        //Fac de 3 ori verificarea transferului, cu ideea ca urmatoarele 2 dati vor fi mai rapide comparate cu primul transfer:
        auto start1 = chrono::steady_clock::now();
        //Aici puteam copia si rand pe rand, memcpy pare o functie potrivita pentru slujba!
        //Copiez din sirul 1 in sirul 2 acel numar de i caractere;
        memcpy(structura2.sirStruct2, structura1.sirStruct1, i);
        //End la transfer;
        auto end1 = chrono::steady_clock::now();
        //Dupa tranfer, verific daca este cat trebuie sirul 2;
        cout << "Verificare lungime sir2 dupa primul transfer: " << strlen(structura2.sirStruct2) << " .\n";
        
        //Pun timpul generat in alt sir, la index-ul anume, si il retin pentru profiler;
        timpTransferStruct1[index] = chrono::duration_cast <chrono::nanoseconds> (end1 - start1).count();

        //Afisez durata cat a durat pentru primul transfer;
        cout << "1) Prima durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end1 - start1).count()
            << endl;
        cout << "1) Prima durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end1 - start1).count() << "\n\n";  

        //Resetez sirul 2:
        structura2.sirStruct2[0] = '\0';



        //B) Se intampla ca si la A): (nu mai reiau explicatiile!)
        //Timpul ar trebui pentru B si C sa fie mai scurt, si se va vedea pe graf;
        cout << "Verificare lungime sir2 inainte de al doilea transfer: " << strlen(structura2.sirStruct2) << " .\n";

        auto start2 = chrono::steady_clock::now();
        memcpy(structura2.sirStruct2, structura1.sirStruct1, i);
        auto end2 = chrono::steady_clock::now();

        cout << "Verificare lungime sir2 dupa al doilea transfer: " << strlen(structura2.sirStruct2) << " .\n";
        cout << "2) A doua durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end2 - start2).count()
            << endl;
        cout << "2) A doua durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end2 - start2).count() << "\n\n";
        timpTransferStruct2[index] = chrono::duration_cast <chrono::nanoseconds> (end2 - start2).count();

        structura2.sirStruct2[0] = '\0';



        //C) Se intampla ca si la A): (nu mai reiau explicatiile!)
        cout << "Verificare lungime sir2 inainte de al treilea transfer: " << strlen(structura2.sirStruct2) << " .\n";

        auto start3 = chrono::steady_clock::now();
        memcpy(structura2.sirStruct2, structura1.sirStruct1, i);
        auto end3 = chrono::steady_clock::now();

        cout << "Verificare lungime sir2 dupa al treilea transfer: " << strlen(structura2.sirStruct2) << " .\n";
        cout << "3) A treia durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end3 - start3).count()
            << endl;
        cout << "3) A treia durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end3 - start3).count() << "\n\n";

        timpTransferStruct3[index] = chrono::duration_cast <chrono::nanoseconds> (end3 - start3).count();


        //Dupa cele 3 transferuri, dezaloc cele 2 structuri:
        free(structura1.sirStruct1);
        free(structura2.sirStruct2);
    }



    //Pentru cele 3 transferuri, afisez timpii, daca se doreste observarea lor in consola: (Deci doar 3 for-uri pentru afisare siruri de timp generate)
    cout << "\nRezultatele transferului pentru structuri:\n";
    cout << "Pentru primul transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferStruct1[i] << " ";
    }
    cout << endl;
    cout << "Pentru al doilea transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferStruct2[i] << " ";
    }
    cout << endl;
    cout << "Pentru al treilea transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferStruct3[i] << " ";
    }
    cout << endl << endl << endl;







    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   






    //2) Pentru fisiere, la fel ca pentru structurile de date:
    cout << "\n\nDuratele de timp pentru transfer in fisiere:\n\n";

    //Tot din 1MB in 1MB: (Scriu doar ce este relevant din nou)
    for (long long i = 1000000; i <= numarBytesStructuraFisiere; i = i + 1000000)
    {
        cout << "\n" << i / 1000000 << ") Transfer a " << i << " numar de bytes din fisierul 1 in fisierul 2: " << endl << endl;
        long long index = (i / 1000000) - 1;
        numarBytes[index] = i;

        //Pentru generarea fisierelor de in, out, din in fac transfer in out;
        char fisierIn[100];
        char fisierOut[100];

        //Generarea numelui fisierului (cel din care citim si cel in care scriem)
        sprintf_s(fisierIn, "Fisier_ProiectSSC_in%d.txt", index + 1); 
        sprintf_s(fisierOut, "Fisier_ProiectSSC_out%d.txt", index + 1);  

        //Obiectul in care scriu+citesc si scriu:
        fstream FisierIn;
        ofstream FisierOut;

        //Dau open inainte de operatii: fisierIn este important sa fie out pentru a putea scrie in el;
        FisierIn.open(fisierIn, ios::out);
        FisierOut.open(fisierOut, ios::out); 

        //Generarea unui sir random de scris in fisier: (la fel ca mai sus!)
        char* sirScriereFisierIn = (char*)malloc(sizeof(char) * i); 
        for (long long j = 0; j < i; j++)
        {
            int testSpatiu = rand() % 2;
            char caracter;

            if (testSpatiu == 1)
            {
                caracter = 'a' + rand() % 26;
            }
            else
            {
                caracter = ' ';
            }

            //Scriere caracter cu caracter, nu iau in considerare la timp transfer!
            sirScriereFisierIn[j] = caracter;
        }

        //Scriu in fisier ce am generat, o singura data:
        FisierIn << sirScriereFisierIn << std::endl; 

        //Il redeschid, acum vrand sa citesc din el:
        FisierIn.close();
        FisierIn.open(fisierIn, ios::in);
        //Cate o linie citita din fisier:
        string lineCitit;

        //A) Transfer 1 fisiere:
        auto start1 = chrono::steady_clock::now(); 

        //Doar aici calculez cat timp ia transferul:
        //Daca fisierul este open:
        if(FisierIn.is_open())
        {
            //Luam linie cu linie:
            while (getline(FisierIn, lineCitit)) 
            {
                //Si dupa ce citim linia, o scriu in fisierul out, deci aici se executa transferul:
                FisierOut << lineCitit << std::endl; 
            }
        }
        //Daca nu este bun fisierul:
        else
        {
            cout << "Unable to use file.";
            cout << "\n";
        }
        //Gata acest transfer;

        auto end1 = chrono::steady_clock::now();

        timpTransferFile1[index] = chrono::duration_cast <chrono::nanoseconds> (end1 - start1).count();
        cout << "1) Prima durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end1 - start1).count()
            << endl;
        cout << "1) Prima durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end1 - start1).count() << "\n\n";



        //Cum sa fac intre acele transferuri:
        FisierIn.clear();
        FisierIn.seekg(0, std::ios::beg);
        FisierOut.close();
        //Pentru a face clear in FisierOut, sa fie un nou fisier cum ar fi!
        FisierOut.open(fisierOut, std::ofstream::out | std::ofstream::trunc);
        //FisierOut.open(fisierOut, ios::out);



        //B) Transfer 2 fisiere:
        auto start2 = chrono::steady_clock::now();

        //Al doilea:
        if (FisierIn.is_open())
        {
            while (getline(FisierIn, lineCitit))
            {
                FisierOut << lineCitit << std::endl;
            }
        }
        else
        {
            cout << "Unable to use file.";
            cout << "\n";
        }

        auto end2 = chrono::steady_clock::now();
        cout << "2) A doua durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end2 - start2).count()
            << endl;
        cout << "2) A doua durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end2 - start2).count() << "\n\n";
        timpTransferFile2[index] = chrono::duration_cast <chrono::nanoseconds> (end2 - start2).count();



        FisierIn.clear();
        FisierIn.seekg(0, std::ios::beg);
        FisierOut.close();
        FisierOut.open(fisierOut, std::ofstream::out | std::ofstream::trunc);
        //FisierOut.open(fisierOut, ios::out);




        //C) Transfer 3 fisiere:
        auto start3 = chrono::steady_clock::now();

        //Al treilea:
        if (FisierIn.is_open())
        {
            while (getline(FisierIn, lineCitit))
            {
                FisierOut << lineCitit << std::endl;
            }
        }
        else
        {
            cout << "Unable to use file.";
            cout << "\n";
        }

        auto end3 = chrono::steady_clock::now();
        cout << "3) A treia durata: Durata transferului " << i / 1000000 << " in secunde este: "
            << chrono::duration_cast <chrono::seconds> (end3 - start3).count()
            << endl;
        cout << "3) A treia durata: Durata transferului " << i / 1000000 << " in nanosecunde este: "
            << chrono::duration_cast <chrono::nanoseconds> (end3 - start3).count() << "\n\n";
        timpTransferFile3[index] = chrono::duration_cast <chrono::nanoseconds> (end3 - start3).count();



        //Dupa transferuri, inchid fisierul in si fisierul out;
        //De asemenea, dau free la ce am alocat:
        FisierIn.close();
        FisierOut.close();
        //Free la ce am generat:
        free(sirScriereFisierIn);
    }


    //Rezultatele pentru fisiere, de asemenea afisate:
    cout << "\nRezultatele transferului pentru fisiere:\n\n";
    cout << "Pentru primul transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferFile1[i] << " ";
    }
    cout << endl;
    cout << "Pentru al doilea transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferFile2[i] << " ";
    }
    cout << endl;
    cout << "Pentru al treilea transfer:\n";
    for (long long i = 0; i < numarTeste; i++)
    {
        cout << timpTransferFile3[i] << " ";
    }
    cout << endl;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Pentru profiler: voi crea o pagina unde se vad grafurile comparative pentru structurile de date si pentru fisiere!
Profiler p("Comparatie_Viteze_De_Transfer"); 

//Numarul de teste ca mai sus, 10, 100, 1000, etc...;
#define NrTests 20 //100 //10 
int NrElemente = 0; 



//1) PENTRU STRUCTURI DE DATE, GENERAREA GRAFURILOR:

//A) Pentru Cache: (Ultimul transfer)
//Este la fel pentru toate, explic mai mult doar unde consider!
void MemorieCacheStructuri() 
{
    //Avem o operatie:
    Operation cacheMemory = p.createOperation("TrSpeed_Cache_Str", NrElemente); 

    //Ma uit la indexul din sirul anume, pentru a stii pana unde ma duc;
    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferStruct3[indexTimpTransfer];

    //Dupa, stiu cat de mult sa dau count, pentru afisare pe graf;
    for (long long i = 0; i < numarCounts; i++)
    {
        cacheMemory.count();
    }
}



//B) Pentru Memorie Interna: (Primul transfer) (se vede din numarul sirului folosit, timpTransferStruct1)
void MemorieInternaStructuri()
{
    Operation RAMMemory = p.createOperation("TrSpeed_RAM_Str", NrElemente);

    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferStruct1[indexTimpTransfer];

    for (long long i = 0; i < numarCounts; i++)
    {
        RAMMemory.count();
    }
}


//C) Pentru Memoria Virtuala: (Al doilea transfer)
void MemorieVirtualaStructuri()
{
    Operation virtualMemory = p.createOperation("TrSpeed_Virtual_Str", NrElemente);

    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferStruct2[indexTimpTransfer];

    for (long long i = 0; i < numarCounts; i++)
    {
        virtualMemory.count();
    }
}





//2) PENTRU FISIERE, GENERAREA GRAFURILOR:
//Aceeasi strategie si aici, doar alte date pentru retinerea grafurilor; (grafe)

//A) Pentru Cache: (Ultimul transfer)
void MemorieCacheFisiere()
{
    Operation cacheMemory = p.createOperation("TrSpeed_Cache_File", NrElemente);

    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferFile3[indexTimpTransfer];

    for (long long i = 0; i < numarCounts; i++)
    {
        cacheMemory.count();
    }
}


//B) Pentru Memorie Interna: (Primul transfer)
void MemorieInternaFisiere()
{
    Operation RAMMemory = p.createOperation("TrSpeed_RAM_File", NrElemente);

    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferFile1[indexTimpTransfer];

    for (long long i = 0; i < numarCounts; i++)
    {
        RAMMemory.count();
    }
}


//C) Pentru Memoria Virtuala: (Al doilea transfer)
void MemorieVirtualaFisiere()
{
    Operation virtualMemory = p.createOperation("TrSpeed_Virtual_File", NrElemente);

    long long indexTimpTransfer = NrElemente / 1000000;
    indexTimpTransfer--;
    long long numarCounts = timpTransferFile2[indexTimpTransfer];

    for (long long i = 0; i < numarCounts; i++)
    {
        virtualMemory.count(); 
    }
}




//1) PENTRU AFISARE PE GRAF A DATELOR PENTRU STRUCTURI:
void testareVitezaTransferMemoriiStructura() 
{
    //Merg pe toate testele, si ma uit la fiecare cat de mult a durat acel transfer;
    for (int t = 0; t < NrTests; t++)
    {
        //Aici am indexul anume pentru folosit la aflarea timpului specific!
        NrElemente = numarBytes[t];

        //Aici dau apelul celor 3 pentru structuri:
        MemorieCacheStructuri();
        MemorieInternaStructuri();
        MemorieVirtualaStructuri();
    }

    //Aici creez grupul de afisare pe pagina web a grafului anume, care reprezinta diferenta intre cele 3 timpuri de rulare:
    p.createGroup("Viteze_Transfer_Memorii_Str", "TrSpeed_Cache_Str", "TrSpeed_RAM_Str", "TrSpeed_Virtual_Str");
}




//2) PENTRU AFISARE PE GRAF A DATELOR PENTRU STRUCTURI:
void testareVitezaTransferMemoriiFisier()
{
    //Analog ca mai sus, la fisiere la fel ca si la structuri aceasta logica:
    for (int t = 0; t < NrTests; t++)
    {
        NrElemente = numarBytes[t];

        MemorieCacheFisiere();
        MemorieInternaFisiere();
        MemorieVirtualaFisiere();
    }

    p.createGroup("Viteze_Transfer_Memorii_File", "TrSpeed_Cache_File", "TrSpeed_RAM_File", "TrSpeed_Virtual_File");
}




//Graficele finale, apelate:
void GraficeFinaleVitezaTransfer()
{
    //Pentru structuri de date:
    testareVitezaTransferMemoriiStructura();

    //Pentru fisiere:
    testareVitezaTransferMemoriiFisier();

    //Arat raportul celor 2 pe aceeasi pagina, sus fisier, jos structura, pentru ca se iau in ordine alfabetica!
    p.showReport();
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//Functionalitatea apelata in main:
int main()
{


    //Pentru calcularea timpilor, se retin datele in siruri globale;
    CalculareTimpTransfer();



    //Pentru afisarea grafurilor, pentru diferenta timpi transfer intre date pentru structuri si fisiere;
    //Din datele retinute din functia de mai sus, obtin grafuri ce reprezinta diferentele de transfer;
    //Trebuie aceasta ordine pentru a avea datele de mai sus, sa le afisez pe grafuri;
    //Doar daca vreau generarea fisierului cu grafuri rulez aceasta linie:
    GraficeFinaleVitezaTransfer();



    //Am terminat programul;
    printf("\n\nTerminarea programului.\n");
    return 0;
}



//Done.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Informatii finale / Ciorne:

/*


1) - Ciorna:
        //Aflare ce numar este fisierul:
        //char numarFisier = (i + 1) + '0';
        //strcat(fisierIn, &numarFisier);

2) -

3) -

4) -

5) -


*/






















































































