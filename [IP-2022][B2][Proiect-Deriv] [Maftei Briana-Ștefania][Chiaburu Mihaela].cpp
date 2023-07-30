#include <iostream>
#include <graphics.h>
#include <WinBGIm.h>
#include <cstring>
#include<windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define NN 500
#define MM 500

using namespace std;

struct nod
{
    char info[NN];
    nod *st, *dr;
};

struct structuraVectorGreseli
{
    int pozitieInVector=-1;
    int codGreseala;
    char sirDinFunctie[NN]="";
};

struct structuraGreseli
{
    bool parantezareGresita;
    int numarGreseli;
    structuraVectorGreseli vectorGreseli[NN];
};

struct structuraAuxiliar
{
    int pozitieInVector;
};

int esteArboreNul(nod *arbore)
{
    return (arbore==NULL);
}

void initializareArbore(nod* &arbore)
{
    if(esteArboreNul(arbore)==0)
        arbore=NULL;
}


void copiazaArbore(nod *&arboreNou, nod *arbore)
{
    if(esteArboreNul(arbore)==0)
    {
        arboreNou=new nod;
        strcpy(arboreNou->info,arbore->info);
        arboreNou->st=NULL;
        arboreNou->dr=NULL;

        copiazaArbore(arboreNou->st, arbore->st);
        copiazaArbore(arboreNou->dr, arbore->dr);
    }
}

void stergeArbore(nod *&arbore)
{
    if(esteArboreNul(arbore)==0)
    {
        stergeArbore(arbore->st);
        stergeArbore(arbore->dr);
        delete arbore;
        arbore=NULL;
    }
}

///ce tine de teste si proceduri

bool esteCifra(char element)
{
    if(strchr("0123456789", element)!=0) return 1;
    return 0;
}

bool esteNumar(char numar[])
{
    int i, lungimeNumar;
    i=0;
    lungimeNumar=strlen(numar);
    while(i<lungimeNumar)
        if(esteCifra(numar[i])==1) return 1;
        else i++;

    return 0;
}

bool esteX(char element)
{
    return element=='x';
}

bool esteOperator(char element)
{
    if(strchr("*^/+-,", element)!=0) return 1;
    return 0;
}

bool esteParanteza(char element)
{
    if(strchr("()", element)!=0) return 1;
    return 0;
}

bool esteE(char sir[])
{
    if(strcmp(sir, "e")==0) return 1;
    return 0;
}

bool testFunctie(char element)
{
    if(strchr("alcst",element)!=0) return 1;
    return 0;
}

bool esteFunctia(char functia[], char expresie[], int i)
{
    int lungimeFunctie, k;
    lungimeFunctie=strlen(functia);
    k=0;
    while(k<lungimeFunctie)
        if(expresie[i++]!=functia[k++]) return 0;
    return 1;
}

bool esteLog(char sir[])
{
    if(strcmp("log", sir)==0) return 1;
    return 0;
}

bool esteSpatiu(char caracter)
{
    return caracter==' ';
}

void formareNumarPozitiv(char expresie[], int numarCaractere, int &i, char numar[], int &numarPuncte, int &pozitiePunct)
{
    int k;
    numar[0]=0;
    k=0;
    while(i<numarCaractere && ((esteCifra(expresie[i])==1) || expresie[i]=='.'))
    {
        if(expresie[i]=='.')
        {
            numarPuncte++;
            pozitiePunct=k;
        }

        numar[k++]=expresie[i];
        i++;
    }
    numar[k]=0;
}

void puneInVectorSir(char sir[], int &numarElemente, char vectorExpresie[][NN])
{
    numarElemente++;
    strcpy(vectorExpresie[numarElemente], sir);
}

void ilFaceSir(char caracter, char sir[])
{
    sir[0]=0;
    sir[0]=caracter;
    sir[1]=0;
}

void mutaElementele(char sir1[][NN], int numarElemente, char sir2[][NN])
{
    int i;
    for(i=1; i<=numarElemente; i++)
        strcpy(sir1[i],sir2[i]);
}

void stergeSir(char sir[])
{
    int numarCaractere=strlen(sir);
    for(int i=0; i<numarCaractere; i++)
        sir[i]=0;
}

///ce tine de vectorul expresiei

void memoreazaGreseala(structuraGreseli &v, int pozitie, int cod, char sir[])
{
    v.numarGreseli++;
    v.vectorGreseli[pozitie].pozitieInVector=pozitie;
    v.vectorGreseli[pozitie].codGreseala=cod;
    strcpy(v.vectorGreseli[pozitie].sirDinFunctie, sir);
}

void scrieExpresieInVector(char expresie[], char vectorExpresie[][NN], int &numarElemente, structuraGreseli &v)
{
    int i, numarCaractere, numarVirgule;
    char numar[NN];
    char greseala[NN];

    numarVirgule=0;
    numarCaractere=strlen(expresie);
    numarElemente=0;
    i=0;

    strcpy(greseala, "x");

    while(i<numarCaractere)
        if(esteSpatiu(expresie[i])==1)
        {
            i++;
        }
        else if(esteCifra(expresie[i])==1)
        {
            int numarPuncte=0;
            int pozitiePunct=-1;
            formareNumarPozitiv(expresie, numarCaractere, i, numar, numarPuncte, pozitiePunct);
            puneInVectorSir(numar, numarElemente, vectorExpresie);
            if(numar[strlen(numar)-1]=='.' || numarPuncte>1 || (numar[0]=='0' && strlen(numar)>1 && numarPuncte==0) || (numar[0]=='0' && strlen(numar)>1 && numarPuncte!=0 && pozitiePunct!=1))
            {
                numarElemente--;
                puneInVectorSir(greseala, numarElemente, vectorExpresie);
                memoreazaGreseala(v, numarElemente, 1, numar);
            }
            else if(numar[strlen(numar)-1]=='0' && numarPuncte==1)
            {
                int contor=strlen(numar);
                while(numar[contor-1]=='0')
                {
                    numar[contor-1]=0;
                    contor--;
                }

                if(numar[strlen(numar)-1]=='.') numar[strlen(numar)-1]=NULL;
                numarElemente--;
                puneInVectorSir(numar, numarElemente, vectorExpresie);
            }
        }
        else if(esteOperator(expresie[i])==1 || esteParanteza(expresie[i])==1)
        {
            if(expresie[i]==',')
            {
                puneInVectorSir(",", numarElemente, vectorExpresie);
                i++;
                if(numarVirgule!=0)
                {
                    numarVirgule--;
                }
                else
                {
                    memoreazaGreseala(v, numarElemente, 2, ",");
                }
            }
            else
            {
                ilFaceSir(expresie[i], numar);
                puneInVectorSir(numar, numarElemente, vectorExpresie);
                i++;
            }
        }
        else if(esteX(expresie[i])==1 || expresie[i]=='e')
        {
            ilFaceSir(expresie[i], numar);
            puneInVectorSir(numar, numarElemente, vectorExpresie);
            i++;
        }
        else
        {
            if(expresie[i]=='c')
            {
                if(esteFunctia("cos", expresie, i)==1)
                {
                    puneInVectorSir("cos", numarElemente, vectorExpresie);
                    i=i+3;
                }
                else if(esteFunctia("ctg", expresie, i)==1)
                {
                    puneInVectorSir("ctg", numarElemente, vectorExpresie);
                    i=i+3;
                }
                else
                {
                    puneInVectorSir(greseala, numarElemente, vectorExpresie);
                    memoreazaGreseala(v, numarElemente, 3, "c");
                    i++;
                }
            }
            else if(expresie[i]=='s')
            {
                if(esteFunctia("sin", expresie, i)==1)
                {
                    puneInVectorSir("sin", numarElemente, vectorExpresie);
                    i=i+3;
                }
                else if(esteFunctia("sqrt", expresie, i)==1)
                {
                    puneInVectorSir("sqrt", numarElemente, vectorExpresie);
                    i=i+4;
                }
                else
                {
                    puneInVectorSir(greseala, numarElemente, vectorExpresie);
                    memoreazaGreseala(v, numarElemente, 3, "s");
                    i++;
                }
            }
            else if(expresie[i]=='a')
            {
                if(esteFunctia("arcsin", expresie, i)==1)
                {
                    puneInVectorSir("arcsin", numarElemente, vectorExpresie);
                    i=i+6;
                }
                else if(esteFunctia("arccos", expresie, i)==1)
                {
                    puneInVectorSir("arccos", numarElemente, vectorExpresie);
                    i=i+6;
                }
                else if(esteFunctia("arctg", expresie, i)==1)
                {
                    puneInVectorSir("arctg", numarElemente, vectorExpresie);
                    i=i+5;
                }
                else if(esteFunctia("arcctg", expresie, i)==1)
                {
                    puneInVectorSir("arcctg", numarElemente, vectorExpresie);
                    i=i+6;
                }
                else
                {
                    puneInVectorSir(greseala, numarElemente, vectorExpresie);
                    memoreazaGreseala(v, numarElemente, 3, "a");
                    i++;
                }
            }
            else if(expresie[i]=='l')
            {
                if(esteFunctia("ln", expresie, i)==1)
                {
                    puneInVectorSir("ln", numarElemente, vectorExpresie);
                    i=i+2;
                }
                else if(esteFunctia("log(", expresie, i)==1)
                {
                    puneInVectorSir("log", numarElemente, vectorExpresie);
                    puneInVectorSir("(", numarElemente, vectorExpresie);
                    numarVirgule++;
                    i=i+4;
                }
                else
                {
                    puneInVectorSir(greseala, numarElemente, vectorExpresie);
                    memoreazaGreseala(v, numarElemente, 3, "l");
                    i++;
                }
            }
            else if(expresie[i]=='t')
            {
                if(esteFunctia("tg", expresie, i)==1)
                {
                    puneInVectorSir("tg", numarElemente, vectorExpresie);
                    i=i+2;
                }
                else
                {
                    puneInVectorSir(greseala, numarElemente, vectorExpresie);
                    memoreazaGreseala(v, numarElemente, 3, "t");
                    i++;
                }
            }
            else
            {
                ilFaceSir(expresie[i], numar);
                puneInVectorSir(greseala, numarElemente, vectorExpresie);
                memoreazaGreseala(v, numarElemente, 3, numar);
                i++;
            }
        }
}


int suntGreseliDeScriere(char sir1[], char sir2[])
{
    if(sir1[0]=='(' && sir2[0]==')') return -2;
    /// atentie la scrierea parantezelor!

    if(esteOperator(sir1[0])==1 && esteOperator(sir2[0])==1) return -3;
    /// atentie la scrierea operatorilor!

    if(esteOperator(sir1[0])==1 && sir2[0]==')') return -4;
    /// lipsesc operanzi!

    if(sir1[0]=='(' && strchr("*^/+,",sir2[0])!=0) return -30;
    /// lipsesc operanzi!

    if(testFunctie(sir1[0])==1 && strlen(sir1)>1 && esteOperator(sir2[0])==1) return -5;
    /// atentie la scrierea functiilor si a operatorilor!

    if(testFunctie(sir1[0])==1 && strlen(sir1)>1 && sir2[0]==')') return -8;
    /// atentie la scrierea functiilor

    if(testFunctie(sir1[0])==1 && strlen(sir1)>1 && testFunctie(sir2[0])==1 && strlen(sir2)>1) return -20;
    ///functii scrise gresit

    return 0;
    /// nu sunt greseli
}

void pozitieInVector(int pozitieVecheInVector, int pozitieNouaInVector, structuraAuxiliar v[])
{
    v[pozitieNouaInVector].pozitieInVector=pozitieVecheInVector;
}

void puneSemnulInmultiriiZero(char vectorExpresie[][NN], int &numarElementeVector, structuraGreseli &v, structuraAuxiliar vectorPozitii[])
{
    char auxiliar[NN][NN];
    int i, greseala;
    int numarElementeAux;
    numarElementeAux=0;
    i=1;
    while(i<numarElementeVector && v.parantezareGresita==0)
    {
        greseala=suntGreseliDeScriere(vectorExpresie[i], vectorExpresie[i+1]);
        if(greseala!=0)
        {
            if(greseala==-2)
            {
                if(i>1 && testFunctie(vectorExpresie[i-1][0])==1)
                {
                    puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                    pozitieInVector(i, numarElementeAux, vectorPozitii);
                    puneInVectorSir("x", numarElementeAux, auxiliar);
                    pozitieInVector(0, numarElementeAux, vectorPozitii);

                    memoreazaGreseala(v, i, 7, vectorExpresie[i]);
                    memoreazaGreseala(v, i+1, 7, vectorExpresie[i+1]);
                }
                else
                    v.parantezareGresita=1;
            }
            else if(greseala==-8)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i, 11, vectorExpresie[i]);

            }
            else if(greseala==-3)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i, 4, vectorExpresie[i]);
                memoreazaGreseala(v, i+1, 4, vectorExpresie[i+1]);
            }
            else if(greseala==-4)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i, 5, vectorExpresie[i]);
            }
            else if(greseala==-30)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i+1, 5, vectorExpresie[i+1]);
            }
            else if(greseala==-5)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i, 6, vectorExpresie[i]);
                memoreazaGreseala(v, i+1, 6, vectorExpresie[i+1]);
            }
            else if(greseala==-20)
            {
                puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
                pozitieInVector(i, numarElementeAux, vectorPozitii);
                puneInVectorSir("x", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);
                puneInVectorSir("+", numarElementeAux, auxiliar); ///
                pozitieInVector(0, numarElementeAux, vectorPozitii);

                memoreazaGreseala(v, i, 7, vectorExpresie[i]);
            }
        }
        else
        {
            puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
            pozitieInVector(i, numarElementeAux, vectorPozitii);

            if(vectorExpresie[i][0]=='(' && vectorExpresie[i+1][0]=='-')
            {
                puneInVectorSir("0", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);
            }
            else if(esteOperator(vectorExpresie[i][0])==0 && esteOperator(vectorExpresie[i+1][0])==0 &&
                    vectorExpresie[i][0]!='(' && vectorExpresie[i+1][0]!=')'&&
                    testFunctie(vectorExpresie[i][0])==0)
            {
                puneInVectorSir("*", numarElementeAux, auxiliar);
                pozitieInVector(0, numarElementeAux, vectorPozitii);

            }

        }
        i++;
    }


    if(v.parantezareGresita==0)
    {
        puneInVectorSir(vectorExpresie[i], numarElementeAux, auxiliar);
        pozitieInVector(i, numarElementeAux, vectorPozitii);

        if(numarElementeVector<numarElementeAux)
        {
            numarElementeVector=numarElementeAux;
            mutaElementele(vectorExpresie, numarElementeVector, auxiliar);
        }
    }


}

int testParantezeleSuntPuseCorect(char vectorExpresie[][NN], int numarElemente)
{
    bool greseala;
    int i, numarParanteze;

    greseala=0;
    numarParanteze=0;

    for(i=1; i<=numarElemente && greseala==0; i++)
        if(vectorExpresie[i][0]=='(') numarParanteze++;
        else if(vectorExpresie[i][0]==')')
        {
            if(numarParanteze>0) numarParanteze--;
            else greseala=1;
        }

    if(greseala==1 || numarParanteze!=0) return 0;
    return 1;
}

/// ce tine de formarea arborelui
int prioritateOperatoriSiParanteze(char op)
{
    if(strchr("()", op)!=0) return 0;
    else if(strchr(",", op)!=0) return 1;
    else if(strchr("+-", op)!=0) return 2;
    else if(strchr("*/", op)!=0) return 3;
    else if(strchr("^", op)!=0) return 4;
    else if(strchr("cslat", op)!=0) return 5;
}

void transformaInArbore(char vectorExpresie[NN][NN], int &numarElemente, nod* &arbore, structuraGreseli &v, structuraAuxiliar pozitiiVector[])
{
    nod* operanzi[NN];
    char operatori[NN][NN];
    int varfOperanzi=0;
    int varfOperatori=0;
    int i;

    int indiceElementRadacinaArbore[NN];
    int indiceElementStivaOperatori[NN];

    strcpy(operatori[++varfOperatori], "(");

    i=1;
    while(i<numarElemente)
    {
        i++;

        if(esteNumar(vectorExpresie[i])==1 || esteX(vectorExpresie[i][0])==1 || esteE(vectorExpresie[i])==1)
        {
            arbore=new nod;
            strcpy(arbore->info, vectorExpresie[i]);
            arbore->st=NULL;
            arbore->dr=NULL;
            varfOperanzi++;
            operanzi[varfOperanzi]=arbore;

            indiceElementRadacinaArbore[varfOperanzi]=i;
        }
        else if(vectorExpresie[i][0]=='(')
        {
            varfOperatori++;
            strcpy(operatori[varfOperatori], "(");
        }
        else if(vectorExpresie[i][0]==')')
        {
            while(operatori[varfOperatori][0]!='(')
            {
                if(esteOperator(operatori[varfOperatori][0])==1)
                {
                    if(operanzi[varfOperanzi-1]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi-1]].pozitieInVector, 8, operanzi[varfOperanzi-1]->info);
                    }

                    if(operanzi[varfOperanzi]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi]].pozitieInVector, 8, operanzi[varfOperanzi]->info);
                    }

                    if(operatori[varfOperatori][0]==',' && operanzi[varfOperanzi-1]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi-1]].pozitieInVector, 8, operanzi[varfOperanzi-1]->info);
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 8, operatori[varfOperatori]);
                    }

                    arbore=new nod;
                    strcpy(arbore->info, operatori[varfOperatori]);
                    arbore->st=operanzi[varfOperanzi-1];
                    arbore->dr=operanzi[varfOperanzi];
                    varfOperanzi--;
                    operanzi[varfOperanzi]=arbore;
                }
                else if(testFunctie(operatori[varfOperatori][0])==1)
                {
                    if(operanzi[varfOperanzi]->info[0]==',' && esteLog(operatori[varfOperatori])==0)
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi]].pozitieInVector, 8, operanzi[varfOperanzi]->info);
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 9, operatori[varfOperatori]);
                    }


                    if(operanzi[varfOperanzi]->info[0]!=',' && esteLog(operatori[varfOperatori])==1)
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 9, operatori[varfOperatori]);
                    }

                    arbore=new nod;
                    strcpy(arbore->info, operatori[varfOperatori]);
                    arbore->st=operanzi[varfOperanzi];
                    arbore->dr=NULL;
                    operanzi[varfOperanzi]=arbore;

                }

                indiceElementRadacinaArbore[varfOperanzi]=indiceElementStivaOperatori[varfOperatori];

                varfOperatori--;
            }
            varfOperatori--;
        }
        else
        {
            while(varfOperatori>0 && operatori[varfOperatori][0]!='(' && operatori[varfOperatori][0]!=')' &&
                    prioritateOperatoriSiParanteze(operatori[varfOperatori][0])>=prioritateOperatoriSiParanteze(vectorExpresie[i][0]))
            {
                if(esteOperator(operatori[varfOperatori][0])==1)
                {
                    if(operanzi[varfOperanzi-1]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi-1]].pozitieInVector, 8, operanzi[varfOperanzi-1]->info);
                    }
                    if(operanzi[varfOperanzi]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi]].pozitieInVector, 8, operanzi[varfOperanzi]->info);
                    }

                    if(operatori[varfOperatori][0]==',' && operanzi[varfOperanzi-1]->info[0]==',')
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi-1]].pozitieInVector, 8, operanzi[varfOperanzi-1]->info);
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 8, operatori[varfOperatori]);
                    }

                    arbore=new nod;
                    strcpy(arbore->info, operatori[varfOperatori]);
                    arbore->st=operanzi[varfOperanzi-1];
                    arbore->dr=operanzi[varfOperanzi];
                    varfOperanzi--;
                    operanzi[varfOperanzi]=arbore;
                }
                else if(testFunctie(operatori[varfOperatori][0])==1)
                {

                    if(operanzi[varfOperanzi]->info[0]==',' && esteLog(operatori[varfOperatori])==0)
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi]].pozitieInVector, 8, operanzi[varfOperanzi]->info);
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 9, operatori[varfOperatori]);
                    }


                    if(operanzi[varfOperanzi]->info[0]!=',' && esteLog(operatori[varfOperatori])==1)
                    {
                        memoreazaGreseala(v, pozitiiVector[indiceElementStivaOperatori[varfOperatori]].pozitieInVector, 9, operatori[varfOperatori]);
                    }

                    arbore=new nod;
                    strcpy(arbore->info, operatori[varfOperatori]);
                    arbore->st=operanzi[varfOperanzi];
                    arbore->dr=NULL;
                    operanzi[varfOperanzi]=arbore;
                }

                indiceElementRadacinaArbore[varfOperanzi]=indiceElementStivaOperatori[varfOperatori];


                varfOperatori--;
            }

            varfOperatori++;
            strcpy(operatori[varfOperatori], vectorExpresie[i]);
            indiceElementStivaOperatori[varfOperatori]=i;
        }

    }

    if(i==numarElemente && varfOperatori==0)
    {
        arbore=new nod;
        arbore=operanzi[1];
        if(operanzi[varfOperanzi]->info[0]==',')
            memoreazaGreseala(v, pozitiiVector[indiceElementRadacinaArbore[varfOperanzi]].pozitieInVector, 8, operanzi[varfOperanzi]->info);
    }

}

/// ce tine de derivare
void derivare (nod * &arbore, nod * &arboreD)
{
    nod *arb1, *arb2, *arb3, *arb4, *arb5, *arb6, *arb7, *arb8;
    initializareArbore(arboreD);
    arboreD=new nod;
    strcpy(arboreD->info,"0");
    arboreD->dr=NULL;
    arboreD->st=NULL;
    if (esteCifra(arbore->info[0]))
    {
        strcpy(arboreD->info,"0");
    }
    else if (arbore->info[0]=='x')
    {
        strcpy(arboreD->info,"1");
    }
    else if (arbore->info[0]=='+')
    {
        derivare(arbore->st, arb3);
        arboreD->st=arb3;
        derivare(arbore->dr, arb4);
        arboreD->dr=arb4;
        strcpy(arboreD->info,"+");
    }
    else if (arbore->info[0]=='-')
    {
        derivare(arbore->st, arb3);
        arboreD->st=arb3;
        derivare(arbore->dr, arb4);
        arboreD->dr=arb4;
        strcpy(arboreD->info,"-");
    }
    else if (arbore->info[0]=='*')
    {
        arb1=new nod;
        arb2=new nod;
        derivare(arbore->st, arb3);
        derivare(arbore->dr, arb4);
        strcpy(arb1->info,"*");
        arb1->st=arb3;
        arb1->dr=arbore->dr;
        strcpy(arb2->info,"*");
        arb2->st=arbore->st;
        arb2->dr=arb4;
        strcpy(arboreD->info,"+");
        arboreD->st=arb1;
        arboreD->dr=arb2;
    }
    else if (arbore->info[0]=='/')
    {
        if (arbore->st->info[0]=='1')
        {
            arb1=new nod;
            arb2=new nod;
            arb3=new nod;
            arb5=new nod;
            arb6=new nod;
            derivare(arbore->dr, arb4);
            strcpy(arb1->info,"0");
            arb1->st=NULL;
            arb1->dr=NULL;
            strcpy(arb3->info,"2");
            arb3->st=NULL;
            arb3->dr=NULL;
            strcpy(arb5->info,"^");
            arb5->st=arbore->dr;
            arb5->dr=arb3;
            strcpy(arb6->info,"/");
            arb6->st=arb4;
            arb6->dr=arb5;
            strcpy(arboreD->info,"-");
            arboreD->st=arb1;
            arboreD->dr=arb6;

        }
        else
        {
            arb1=new nod;
            arb2=new nod;
            arb5=new nod;
            arb6=new nod;
            arb7=new nod;
            derivare(arbore->st, arb3);
            derivare(arbore->dr, arb4);
            strcpy(arb1->info,"*");
            arb1->st=arb3;
            arb1->dr=arbore->dr ;
            strcpy(arb2->info,"*");
            arb2->st=arbore->st;
            arb2->dr=arb4;
            strcpy(arb5->info,"-");
            arb5->st=arb1;
            arb5->dr=arb2;
            strcpy(arb6->info,"2");
            arb6->st=NULL;
            arb6->dr=NULL;
            strcpy(arb7->info,"^");
            arb7->st=arbore->dr;
            arb7->dr=arb6;
            strcpy(arboreD->info,"/");
            arboreD->st=arb5;
            arboreD->dr=arb7;
        }

    }
    else if (arbore->info[0]=='^')
    {
        if ((arbore->st->info[0]>='1') && (arbore->st->info[0]<='9'))
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            derivare(arbore->dr, arb1);
            strcpy(arb5->info,"^");
            arb5->st=arbore->st;
            arb5->dr=arbore->dr;
            strcpy(arb2->info,"ln");
            arb2->st=arbore->st;
            arb2->dr=NULL;
            strcpy(arb3->info,"*");
            arb3->st=arb2;
            arb3->dr=arb1;
            strcpy(arboreD->info,"*");
            arboreD->st=arb5;
            arboreD->dr=arb3;
        }
        else if (arbore->st->info[0]=='e')
        {
            arb2=new nod;
            derivare(arbore->dr, arb1);
            strcpy(arb2->info,arbore->info);
            arb2->st=arbore->st;
            arb2->dr=arbore->dr;
            strcpy(arboreD->info,"*");
            arboreD->st=arb2;
            arboreD->dr=arb1;
        }
        else
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb5->info,"1");
            arb5->st=NULL;
            arb5->dr=NULL;
            strcpy(arb2->info,"-");
            arb2->st=arbore->dr;
            arb2->dr=arb5;
            strcpy(arb3->info,"^");
            arb3->st=arbore->st;
            arb3->dr=arb2;
            strcpy(arb4->info,"*");
            arb4->st=arbore->dr;
            arb4->dr=arb3;
            strcpy(arboreD->info,"*");
            arboreD->st=arb4;
            arboreD->dr=arb1;
        }

    }
    else if (arbore->info[0]=='s')
    {
        if (arbore->info[1]=='q')
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb3->info,"sqrt");
            arb3->st=arbore->st;
            arb3->dr=NULL;
            strcpy(arb2->info,"2");
            arb2->st=NULL;
            arb2->dr=NULL;
            strcpy(arb4->info,"*");
            arb4->st=arb2;
            arb4->dr=arb3;
            strcpy(arboreD->info,"/");
            arboreD->st=arb1;
            arboreD->dr=arb4;
        }
        else
        {
            arb1=new nod;
            derivare(arbore->st, arb2);
            strcpy(arb1->info,"cos");
            arb1->st=arbore->st;
            arb1->dr=NULL;
            strcpy(arboreD->info,"*");
            arboreD->st=arb1;
            arboreD->dr=arb2;
        }

    }
    else if (arbore->info[0]=='c')
    {
        if (arbore->info[1]=='t')
        {
            arb1=new nod;
            arb2=new nod;
            arb3=new nod;
            arb5=new nod;
            arb6=new nod;
            derivare(arbore->st, arb4);
            strcpy(arb1->info,"0");
            arb1->st=NULL;
            arb1->dr=NULL;
            strcpy(arb3->info,"2");
            arb3->st=NULL;
            arb3->dr=NULL;
            strcpy(arb2->info,"sin");
            arb2->st=arbore->st;
            arb2->dr=NULL;
            strcpy(arb5->info,"^");
            arb5->st=arb2;
            arb5->dr=arb3;
            strcpy(arb6->info,"/");
            arb6->st=arb4;
            arb6->dr=arb5;
            strcpy(arboreD->info,"-");
            arboreD->st=arb1;
            arboreD->dr=arb6;
        }
        else
        {
            arb1=new nod;
            arb2=new nod;
            arb3=new nod;
            derivare(arbore->st, arb4);
            strcpy(arb1->info,"0");
            arb1->st=NULL;
            arb1->dr=NULL;
            strcpy(arb2->info,"sin");
            arb2->st=arbore->st;
            arb2->dr=NULL;
            strcpy(arb3->info,"*");
            arb3->st=arb2;
            arb3->dr=arb4;
            strcpy(arboreD->info,"-");
            arboreD->st=arb1;
            arboreD->dr=arb3;
        }

    }
    else if (arbore->info[0]=='l')
    {
        if (arbore->st->info[0]==',') /// log
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb2=arbore->st;
            derivare(arb2->dr, arb1);
            strcpy(arb3->info,"ln");
            arb3->st=arb2->st;
            arb3->dr=NULL;
            strcpy(arb4->info,"*");
            arb4->st=arb2->dr;
            arb4->dr=arb3;
            strcpy(arboreD->info,"/");
            arboreD->st=arb1;
            arboreD->dr=arb4;
        }
        else
        {
            derivare(arbore->st, arb1);
            strcpy(arboreD->info,"/");
            arboreD->st=arb1;
            arboreD->dr=arbore->st;
        }

    }
    else if (arbore->info[0]=='t')
    {
        arb2=new nod;
        arb3=new nod;
        arb4=new nod;
        derivare(arbore->st, arb1);
        strcpy(arb3->info,"2");
        arb3->st=NULL;
        arb3->dr=NULL;
        strcpy(arb2->info,"cos");
        arb2->st=arbore->st;
        arb2->dr=NULL;
        strcpy(arb4->info,"^");
        arb4->st=arb2;
        arb4->dr=arb3;
        strcpy(arboreD->info,"/");
        arboreD->st=arb1;
        arboreD->dr=arb4;
    }
    else if (arbore->info[0]=='a')
    {
        if (arbore->info[3]=='s') ///arcsin
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            arb6=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb2->info,"2");
            arb2->st=NULL;
            arb2->dr=NULL;
            strcpy(arb3->info,"^");
            arb3->st=arbore->st;
            arb3->dr=arb2;
            strcpy(arb4->info,"1");
            arb4->st=NULL;
            arb4->dr=NULL;
            strcpy(arb5->info,"-");
            arb5->st=arb4;
            arb5->dr=arb3;
            strcpy(arb6->info,"sqrt");
            arb6->st=arb5;
            arb6->dr=NULL;
            strcpy(arboreD->info,"/");
            arboreD->st=arb1;
            arboreD->dr=arb6;

        }
        else if (arbore->info[3]=='t') ///arctg
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb2->info,"2");
            arb2->st=NULL;
            arb2->dr=NULL;
            strcpy(arb3->info,"^");
            arb3->st=arbore->st;
            arb3->dr=arb2;
            strcpy(arb4->info,"1");
            arb4->st=NULL;
            arb4->dr=NULL;
            strcpy(arb5->info,"+");
            arb5->st=arb4;
            arb5->dr=arb3;
            strcpy(arboreD->info,"/");
            arboreD->st=arb1;
            arboreD->dr=arb5;
        }
        else if (arbore->info[4]=='o') ///arccos
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            arb6=new nod;
            arb7=new nod;
            arb8=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb2->info,"0");
            arb2->st=NULL;
            arb2->dr=NULL;
            strcpy(arb3->info,"2");
            arb3->st=NULL;
            arb3->dr=NULL;
            strcpy(arb4->info,"^");
            arb4->st=arbore->st;
            arb4->dr=arb3;
            strcpy(arb5->info,"1");
            arb5->st=NULL;
            arb5->dr=NULL;
            strcpy(arb6->info,"-");
            arb6->st=arb5;
            arb6->dr=arb4;
            strcpy(arb7->info,"sqrt");
            arb7->st=arb6;
            arb7->dr=NULL;
            strcpy(arb8->info,"/");
            arb8->st=arb1;
            arb8->dr=arb7;
            strcpy(arboreD->info,"-");
            arboreD->st=arb2;
            arboreD->dr=arb8;
        }
        else if (arbore->info[4]=='t') ///arcctg
        {
            arb2=new nod;
            arb3=new nod;
            arb4=new nod;
            arb5=new nod;
            arb6=new nod;
            arb7=new nod;
            derivare(arbore->st, arb1);
            strcpy(arb2->info,"2");
            arb2->st=NULL;
            arb2->dr=NULL;
            strcpy(arb3->info,"^");
            arb3->st=arbore->st;
            arb3->dr=arb2;
            strcpy(arb4->info,"1");
            arb4->st=NULL;
            arb4->dr=NULL;
            strcpy(arb5->info,"+");
            arb5->st=arb4;
            arb5->dr=arb3;
            strcpy(arb6->info,"/");
            arb6->st=arb1;
            arb6->dr=arb5;
            strcpy(arb7->info,"0");
            arb7->st=NULL;
            arb7->dr=NULL;
            strcpy(arboreD->info,"-");
            arboreD->st=arb7;
            arboreD->dr=arb6;
        }
    }
}

/// ce tine de simplificarea arborelui derivat
int nrCifre (int a)
{
    int nr=0;
    int aux = abs(a);
    while (aux!=0)
    {
        nr++;
        aux=aux/10;
    }
    return nr;
}

int cifraPozitiaK (int numar, int poz)
{
    numar=abs(numar);
    int cifre = nrCifre(numar)-1;
    for (int i=cifre; i>poz; i--)
    {
        numar=numar/10;
    }
    return numar%10;
}

void operatorIntre2CaractereNumere (nod *&arboreD, nod *arb)
{
    int lungime1 = strlen(arboreD->st->info);
    int lungime2 = strlen(arboreD->dr->info);
    int numar1 = 0, numar2 = 0, oper = 0, operPutere = 1, cifrapoz = 0;
    arb=new nod;
    for (int i=0; i<lungime1; i++)
    {
        numar1 = numar1*10 + (int)arboreD->st->info[i] - 48;
    }
    for (int i=0; i<lungime2; i++)
    {
        numar2 = numar2*10 + (int)arboreD->dr->info[i] - 48;
    }
    if (arboreD->info[0]=='+')
    {
        oper = numar1 + numar2;
    }
    else if (arboreD->info[0]=='*')
    {
        oper = numar1 * numar2;
    }
    else if (arboreD->info[0]=='-')
    {
        oper = numar1 - numar2;
    }
    else if (arboreD->info[0]=='^')
    {
        for (int i=0; i<numar2; i++)
        {
            operPutere=operPutere*numar1;
        }
    }
    arboreD->info[0]='\0';
    arb->st=new nod;
    arb->dr=new nod;
    if (operPutere>1)
    {
        for (int i=0; i<nrCifre(operPutere); i++)
        {
            cifrapoz=cifraPozitiaK(operPutere,i);
            arb->info[i] = (char)(cifrapoz + 48);
            arb->st=NULL;
            arb->dr=NULL;
        }
    }
    else
    {
        for (int i=0; i<nrCifre(oper); i++)
        {
            if (oper<0)
            {
                arb->info[0] = '-';
                cifrapoz=cifraPozitiaK(oper,i);
                strcpy(arb->st->info,"0");
                arb->dr->info[i] = (char)(cifrapoz + 48);
            }
            else
            {
                cifrapoz=cifraPozitiaK(oper,i);
                arb->info[i] = (char)(cifrapoz + 48);
                arb->st=NULL;
                arb->dr=NULL;
            }
        }
    }
    arboreD = arb;
}

int catiX (nod *arboreD)
{
    int nrX1=0, nrX2=0, nrX=0;
    if (esteArboreNul(arboreD))
    {
        return 0;
    }
    else
    {
        if(arboreD->info[0]=='*')
        {
            if (esteCifra(arboreD->st->info[0]) && arboreD->dr->info[0]=='x')
            {
                int lungime1 = strlen(arboreD->st->info);
                for (int i=0; i<lungime1; i++)
                {
                    nrX1 = nrX1*10 + (int)arboreD->st->info[i] - 48;
                }
            }
            else if(esteCifra(arboreD->dr->info[0]) && arboreD->st->info[0]=='x')
            {
                int lungime2 = strlen(arboreD->dr->info);
                for (int i=0; i<lungime2; i++)
                {
                    nrX2 = nrX2*10 + (int)arboreD->dr->info[i] - 48;
                }
            }
        }
        return nrX1 + nrX2 + catiX (arboreD->st) + catiX (arboreD->dr);
        nrX1 = 0;
        nrX2 = 0;
    }
}

void simplificaArbore (nod *&arboreD)
{
    nod *arb1, *arb2, *arb3, *arb4, *arb5, *arb6, *arb7, *arb8;
    if (!esteArboreNul(arboreD))
    {
        simplificaArbore (arboreD->st);
        simplificaArbore (arboreD->dr);
        if (arboreD->info[0]=='+')
        {
            if (arboreD->st->info[0]=='0')
            {
                arboreD=arboreD->dr;
            }
            else if (arboreD->dr->info[0]=='0')
            {
                arboreD=arboreD->st;
            }
            else if (esteCifra(arboreD->st->info[0])&& esteCifra(arboreD->dr->info[0]))
            {
                operatorIntre2CaractereNumere(arboreD, arb4);
            }
            else if (arboreD->dr->info[0]=='-' && arboreD->st != NULL)
            {
                arb1=new nod;
                arb2=new nod;
                arb3=new nod;
                strcpy(arb1->info,"-");
                arb1->st=arboreD->st;
                arb2=arboreD->dr;
                if (arb2->st->info[0]=='0' && arb2->dr != NULL)
                {
                    arb3=arb2->dr;
                    arb1->dr=arb3;
                    arboreD=arb1;
                }
            }
            else if (arboreD->st->info[0]=='*' && arboreD->dr->info[0]=='*')
            {
                arb1=new nod;
                arb1=arboreD->st;
                arb2=new nod;
                arb2=arboreD->dr;
                arb3=new nod;
                arb3->dr=new nod;
                arb3->st=new nod;
                if((esteCifra(arb1->st->info[0]) && esteX(arb1->dr->info[0])|| esteCifra(arb1->dr->info[0]) && esteX(arb1->st->info[0]))
                        && (esteCifra(arb2->st->info[0]) && esteX(arb2->dr->info[0])|| esteCifra(arb2->dr->info[0]) && esteX(arb2->st->info[0])))
                {
                    strcpy(arb3->info,"*");
                    strcpy(arb3->dr->info,"x");
                    int nrX=catiX(arb1)+catiX(arb2);
                    for (int i=0; i<nrCifre(nrX); i++)
                    {
                        int cifrapoz=cifraPozitiaK(nrX,i);
                        arb3->st->info[i] = (char)(cifrapoz + 48);
                    }
                    arboreD=arb3;
                }
            }
            else if (arboreD->st->info[0]=='+' && arboreD->dr->info[0]=='*')
            {
                arb1=new nod;
                arb2=new nod;
                arb3=new nod;
                arb1=arboreD->st;
                arb2=arboreD->dr;
                arb6=new nod;
                if (arb1->st->info[0]=='*')
                {
                    arb6=arb1->dr;
                    if(esteCifra(arb6->st->info[0]) && esteX(arb6->dr->info[0]) && esteCifra(arb2->st->info[0]) && esteX(arb2->dr->info[0]))
                    {
                        strcpy(arb3->info,"+");
                        if (esteCifra(arb6->st->info[0]))
                        {
                            arb3->st=arb6->st;
                        }
                        else if(esteCifra(arb6->dr->info[0]))
                        {
                            arb3->st=arb6->dr;
                        }
                        if (esteCifra(arb2->st->info[0]))
                        {
                            arb3->dr=arb2->st;
                        }
                        else if(esteCifra(arb2->dr->info[0]))
                        {
                            arb3->dr=arb2->dr;
                        }
                        operatorIntre2CaractereNumere(arb3,arb4);
                        arb5=new nod;
                        strcpy(arb5->info,"*");
                        arb5->dr=arb6->dr;
                        arb5->st=arb3;
                        arb4=new nod;
                        strcpy(arb4->info,"+");
                        arb4->st=arb1->st;
                        arb4->dr=arb5;
                        arboreD=arb4;
                    }
                }

            }
            else if(esteX(arboreD->st->info[0])&& esteX(arboreD->dr->info[0]))
            {
                arb1=new nod;
                arb2=new nod;
                arb3=new nod;
                strcpy(arb1->info, "2");
                arb1->st=NULL;
                arb2->dr=NULL;
                strcpy(arb2->info, "*");
                arb2->st=arb1;
                arb2->dr=arboreD->dr;
                arboreD=arb2;
            }
            else if (esteCifra(arboreD->dr->info[0])&& arboreD->st->info[0]=='+')
            {
                arb2=new nod;
                arb2=arboreD->st;
                if(esteCifra(arb2->dr->info[0]))
                {
                    arb3=new nod;
                    strcpy(arb3->info,"+");
                    arb3->st=arb2->dr;
                    arb3->dr=arboreD->dr;
                    operatorIntre2CaractereNumere(arb3,arb4);
                    arb5=new nod;
                    strcpy(arb5->info,"+");
                    arb5->st=arb2->st;
                    arb5->dr=arb3;
                    arboreD=arb5;
                }
            }
        }
        else if (arboreD->info[0]=='-')
        {
            if (arboreD->dr->info[0]=='0' && arboreD->st->info[0]=='0')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->dr->info[0]=='0' && arboreD->st->info[0]!='0')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->dr->info[0]=='-')
            {
                arb1=new nod;
                arb2=new nod;
                arb3=new nod;
                strcpy(arb1->info,"+");
                arb1->st=arboreD->st;
                arb2=arboreD->dr;
                if (arb2->st->info[0]=='0' && arb2->dr != NULL)
                {
                    arb3=arb2->dr;
                    arb1->dr=arb3;
                    arboreD=arb1;
                }
            }
            else if (esteCifra(arboreD->st->info[0])&& esteCifra(arboreD->dr->info[0]))
            {
                if(!((arboreD->st->info[0]==arboreD->dr->info[0] )&& strlen(arboreD->st->info)==strlen(arboreD->dr->info)))
                {
                    operatorIntre2CaractereNumere(arboreD, arb4);
                }
                else
                {
                    arb1=new nod;
                    strcpy(arb1->info,"0");
                    arb1->st=NULL;
                    arb1->dr=NULL;
                    arboreD=arb1;
                }
            }
            else if(arboreD->dr->info[0]=='/' && arboreD->st->info[0]=='0')
            {
                arb2=new nod;
                arb2=arboreD->dr;
                if(arb2->st->info[0]=='-')
                {
                    arb3=new nod;
                    arb3=arb2->st;
                    if(arb3->st->info[0]=='0')
                    {
                        arb4=new nod;
                        strcpy(arb4->info, "/");
                        arb4->st=arb3->dr;
                        arb4->dr=arb2->st;
                        arboreD=arb4;
                    }
                }

            }
        }
        else if (arboreD->info[0]=='*')
        {

            if (arboreD->st->info[0]=='0')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->dr->info[0]=='0')
            {
                arboreD=arboreD->dr;
            }
            else if (arboreD->st->info[0]=='1' && strlen(arboreD->st->info)== 1 )
            {
                arboreD=arboreD->dr;
            }
            else if (arboreD->dr->info[0]=='1' && strlen(arboreD->dr->info)== 1 )
            {
                arboreD=arboreD->st;
            }
            else if (esteCifra(arboreD->st->info[0])&& esteCifra(arboreD->dr->info[0]))
            {
                operatorIntre2CaractereNumere(arboreD, arb1);
            }
            else if (esteCifra(arboreD->st->info[0])&& arboreD->dr->info[0]=='/')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb2=arboreD->dr;
                strcpy(arb3->info,"*");
                if (esteCifra(arb2->st->info[0]))
                {
                    arb3->st=arb2->st;
                    arb3->dr=arboreD->st;
                    operatorIntre2CaractereNumere(arb3, arb4);
                    strcpy(arboreD->info,"/");
                    arboreD->st=arb3;
                    arboreD->dr=arb2->dr;
                }

            }
            else if (esteCifra(arboreD->st->info[0])&& arboreD->dr->info[0]=='*')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb2=arboreD->dr;
                if (arb2->st->info[0]!= '*' && arb2->dr->info[0]!= '*')
                {
                    strcpy(arb3->info,"*");
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arb3->st=arb2->st;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arb3->st=arb2->dr;
                    }
                    arb3->dr=arboreD->st;
                    operatorIntre2CaractereNumere(arb3, arb4);
                    strcpy(arboreD->info,"*");
                    arboreD->st=arb3;
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arboreD->dr=arb2->dr;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arboreD->dr=arb2->st;
                    }
                }
            }
            else if (esteCifra(arboreD->dr->info[0])&& arboreD->st->info[0]=='*')
            {
                arb2=new nod;
                arb3=new nod;
                arb3->st=new nod;
                arb3->dr=new nod;
                arb4=new nod;
                arb2=arboreD->st;
                if (arb2->st->info[0]!= '*' && arb2->dr->info[0]!= '*')
                {
                    strcpy(arb3->info,"*");
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arb3->st=arb2->st;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arb3->st=arb2->dr;
                    }
                    arb3->dr=arboreD->dr;
                    operatorIntre2CaractereNumere(arb3, arb4);
                    strcpy(arboreD->info,"*");
                    arboreD->st=arb3;
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arboreD->dr=arb2->dr;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arboreD->dr=arb2->st;
                    }
                }
            }
            else if (esteCifra(arboreD->st->info[0]) && arboreD->dr->info[0]=='+')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb2=arboreD->dr;
                strcpy(arb3->info,"*");
                arb3->st=arboreD->st;
                arb3->dr=arb2->st;
                strcpy(arb4->info,"*");
                arb4->st=arboreD->st;
                arb4->dr=arb2->dr;
                strcpy(arboreD->info,"+");
                arboreD->st=arb3;
                arboreD->dr=arb4;
            }
            else if (esteCifra(arboreD->dr->info[0]) && arboreD->st->info[0]=='+')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb2=arboreD->st;
                strcpy(arb3->info,"*");
                arb3->st=arb2->st;
                arb3->dr=arboreD->dr;
                strcpy(arb4->info,"*");
                arb4->st=arb2->dr;
                arb4->dr=arboreD->dr;
                strcpy(arboreD->info,"+");
                arboreD->st=arb3;
                arboreD->dr=arb4;
            }
            else if (arboreD->dr->info[0]=='*' && arboreD->st->info[0]=='*')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb6=new nod;
                arb7=new nod;
                arb8=new nod;
                arb2=arboreD->st;
                arb3=arboreD->dr;

                if ( ((esteCifra(arb2->st->info[0]) && arb2->dr->info[0]=='^')||(esteCifra(arb2->dr->info[0]) && arb2->st->info[0]=='^'))
                        && ((esteCifra(arb3->st->info[0]) && esteX(arb3->dr->info[0]))||(esteCifra(arb3->dr->info[0]) && esteX(arb3->st->info[0]))))
                {
                    arb1=new nod;
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arb1=arb2->dr;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arb1=arb2->st;
                    }

                    if (esteX(arb1->st->info[0]))
                    {

                        strcpy(arb4->info,"*");
                        if (esteCifra(arb2->st->info[0]))
                        {
                            arb4->st=arb2->st;
                        }
                        else if (esteCifra(arb2->dr->info[0]))
                        {
                            arb4->st=arb2->dr;
                        }
                        if (esteCifra(arb3->st->info[0]))
                        {
                            arb4->dr=arb3->st;
                        }
                        else if (esteCifra(arb3->dr->info[0]))
                        {
                            arb4->dr=arb3->dr;
                        }
                        operatorIntre2CaractereNumere(arb4, arb5);
                        arb5=new nod;
                        strcpy(arb6->info,"+");
                        if (arb2->dr->info[0]=='^')
                        {
                            arb5=arb2->dr;
                        }
                        else if (arb2->st->info[0]=='^')
                        {
                            arb5=arb2->st;
                        }
                        arb6->st=arb5->dr;
                        strcpy(arb7->info,"1");
                        arb7->st=NULL;
                        arb7->dr=NULL;
                        arb6->dr=arb7;
                        operatorIntre2CaractereNumere(arb6, arb8);
                        arb8=new nod;
                        strcpy(arb8->info,"^");
                        if (esteX(arb3->dr->info[0]))
                        {
                            arb8->st=arb3->dr;
                        }
                        else if (esteX(arb3->st->info[0]))
                        {
                            arb8->st=arb3->st;
                        }
                        arb8->dr=arb6;
                        arboreD->st=arb4;
                        arboreD->dr=arb8;
                    }

                }
                else if (((esteCifra(arb3->st->info[0]) && arb3->dr->info[0]=='^')||(esteCifra(arb3->dr->info[0]) && arb3->st->info[0]=='^'))
                         && ((esteCifra(arb2->st->info[0]) && esteX(arb2->dr->info[0]))||(esteCifra(arb2->dr->info[0]) && esteX(arb2->st->info[0]))))
                {

                    arb1=new nod;
                    if (esteCifra(arb3->st->info[0]))
                    {
                        arb1=arb3->dr;
                    }
                    else if (esteCifra(arb3->dr->info[0]))
                    {
                        arb1=arb3->st;
                    }

                    if (esteX(arb1->st->info[0]))
                    {

                        strcpy(arb4->info,"*");
                        if (esteCifra(arb2->st->info[0]))
                        {
                            arb4->st=arb2->st;
                        }
                        else if (esteCifra(arb2->dr->info[0]))
                        {
                            arb4->st=arb2->dr;
                        }
                        if (esteCifra(arb3->st->info[0]))
                        {
                            arb4->dr=arb3->st;
                        }
                        else if (esteCifra(arb3->dr->info[0]))
                        {
                            arb4->dr=arb3->dr;
                        }
                        operatorIntre2CaractereNumere(arb4, arb5);
                        arb5=new nod;
                        strcpy(arb6->info,"+");
                        if (arb3->dr->info[0]=='^')
                        {
                            arb5=arb3->dr;
                        }
                        else if (arb3->st->info[0]=='^')
                        {
                            arb5=arb3->st;
                        }
                        arb6->st=arb5->dr;
                        strcpy(arb7->info,"1");
                        arb7->st=NULL;
                        arb7->dr=NULL;
                        arb6->dr=arb7;
                        operatorIntre2CaractereNumere(arb6, arb8);
                        arb8=new nod;
                        strcpy(arb8->info,"^");
                        if (esteX(arb2->dr->info[0]))
                        {
                            arb8->st=arb2->dr;
                        }
                        else if (esteX(arb2->st->info[0]))
                        {
                            arb8->st=arb2->st;
                        }
                        arb8->dr=arb6;
                        arboreD->st=arb4;
                        arboreD->dr=arb8;
                    }

                }
                else if (((esteCifra(arb2->st->info[0]) && arb2->dr->info[0]=='x')||(esteCifra(arb2->dr->info[0]) && arb2->st->info[0]=='x'))
                         && ((esteCifra(arb3->st->info[0]) && esteX(arb3->dr->info[0]))||(esteCifra(arb3->dr->info[0]) && esteX(arb3->st->info[0]))) )
                {
                    strcpy(arb4->info,"*");
                    if (esteCifra(arb2->st->info[0]))
                    {
                        arb4->st=arb2->st;
                    }
                    else if (esteCifra(arb2->dr->info[0]))
                    {
                        arb4->st=arb2->dr;
                    }
                    if (esteCifra(arb3->st->info[0]))
                    {
                        arb4->dr=arb3->st;
                    }
                    else if (esteCifra(arb3->dr->info[0]))
                    {
                        arb4->dr=arb3->dr;
                    }
                    operatorIntre2CaractereNumere(arb4, arb5);
                    strcpy(arb6->info,"2");
                    arb6->st=NULL;
                    arb6->dr=NULL;
                    arb7=new nod;
                    strcpy(arb7->info,"^");
                    if (esteX(arb2->dr->info[0]))
                    {
                        arb7->st=arb2->dr;
                    }
                    else if (esteX(arb2->st->info[0]))
                    {
                        arb7->st=arb2->st;
                    }
                    arb7->dr=arb6;
                    arboreD->st=arb4;
                    arboreD->dr=arb7;
                }
            }
            else if (arboreD->dr->info[0]=='*'&& arboreD->st->info[0]=='x' || arboreD->st->info[0]=='*'&& arboreD->dr->info[0]=='x')
            {
                arb2=new nod;
                arb6=new nod;
                arb5=new nod;
                arb7=new nod;
                if (arboreD->dr->info[0]=='*')
                {
                    arb2=arboreD->dr;
                }
                else if (arboreD->st->info[0]=='*')
                {
                    arb2=arboreD->st;
                }
                strcpy(arb6->info,"2");
                arb6->st=NULL;
                arb6->dr=NULL;
                strcpy(arb5->info,"x");
                arb5->st=NULL;
                arb5->dr=NULL;
                strcpy(arb7->info,"^");
                arb7->st=arb5;
                arb7->dr=arb6;
                if (esteCifra(arb2->st->info[0]))
                {
                    arboreD->st=arb2->st;
                }
                else if (esteCifra(arb2->dr->info[0]))
                {
                    arboreD->st=arb2->dr;
                }
                arboreD->dr=arb7;
            }
            else if (arboreD->dr->info[0]=='^'&& arboreD->st->info[0]=='^')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb2=arboreD->st;
                arb3=arboreD->dr;
                if (esteX(arb2->st->info[0])&& esteCifra(arb2->dr->info[0]) && esteX(arb3->st->info[0])&& esteCifra(arb3->dr->info[0]))
                {
                    arb4->st=arb2->dr;
                    arb4->dr=arb3->dr;
                    strcpy(arb4->info,"+");
                    operatorIntre2CaractereNumere(arb4, arb1);
                    strcpy(arb5->info,"^");
                    arb5->st=arb2->st;
                    arb5->dr=arb4;
                    arboreD=arb5;
                }
            }
            else if (arboreD->st->info[0]=='*'&& arboreD->dr->info[0]=='^')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb6=new nod;
                arb7=new nod;
                arb2=arboreD->st;
                arb3=arboreD->dr;
                if (arb2->dr->info[0]=='^'&& esteX(arb3->st->info[0])&& esteCifra(arb3->dr->info[0]))
                {
                    arb4=arb2->dr;
                    if(esteX(arb4->st->info[0])&& esteCifra(arb4->dr->info[0]))
                    {
                        arb6->st=arb4->dr;
                        arb6->dr=arb3->dr;
                        strcpy(arb6->info,"+");
                        operatorIntre2CaractereNumere(arb6, arb1);
                        strcpy(arb5->info,"^");
                        arb5->st=arb3->st;
                        arb5->dr=arb6;
                        strcpy(arb7->info,"*");
                        arb7->dr=arb5;
                        arb7->st=arb2->st;
                        arboreD=arb7;
                    }

                }
            }
            else if (arboreD->st->info[0]=='*' && esteCifra(arboreD->dr->info[0]))
            {
                arb1=new nod;
                arb1=arboreD->st;
                if (esteCifra(arb1->st->info[0]))
                {
                    arb2=new nod;
                    strcpy(arb2->info,"*");
                    arb2->st=arboreD->dr;
                    arb2->dr=arb1->st;
                    operatorIntre2CaractereNumere(arb2, arb3);
                    arb3=new nod;
                    strcpy(arb3->info,"*");
                    arb3->st=arb2;
                    arb3->dr=arb1->dr;
                    arboreD=arb3;
                }
            }
        }
        else if (arboreD->info[0]=='^'&& arboreD->st->info[0] !='e')
        {
            if (arboreD->dr->info[0]=='0')
            {
                arb2=new nod;
                strcpy(arb2->info,"1");
                arb2->st=NULL;
                arb2->st=NULL;
                arboreD=arb2;
            }
            else if (arboreD->st->info[0]=='1')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->dr->info[0]=='1')
            {
                arboreD=arboreD->st;
            }
            else if (esteCifra(arboreD->st->info[0])&& esteCifra(arboreD->dr->info[0]))
            {
                operatorIntre2CaractereNumere(arboreD, arb1);
            }
            else if (arboreD->st->info[0]=='^'&& esteCifra(arboreD->dr->info[0]))
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb2=arboreD->st;
                arb3->st=arb2->dr;
                arb3->dr=arboreD->dr;
                strcpy(arb3->info,"*");
                operatorIntre2CaractereNumere(arb3, arb4);
                strcpy(arboreD->info,"^");
                arboreD->st=arb2->st;
                arboreD->dr=arb3;
            }
            else if (esteCifra(arboreD->dr->info[0]) && arboreD->st->info[0]=='*')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb6=new nod;
                arb2=arboreD->st;
                if (esteCifra(arb2->st->info[0]) && arb2->dr->info[0]=='^')
                {
                    arb5=arb2->dr;
                    arb3->st=arb2->st;
                    arb3->dr=arboreD->dr;
                    strcpy(arb3->info,"^");
                    operatorIntre2CaractereNumere(arb3, arb4);
                    arb4=new nod;
                    arb4->st=arb5->dr;
                    arb4->dr=arboreD->dr;
                    strcpy(arb4->info,"*");
                    operatorIntre2CaractereNumere(arb4, arb6);
                    arb6=new nod;
                    strcpy(arb6->info, "^");
                    arb6->st = arb5->st;
                    arb6->dr = arb4;
                    strcpy(arboreD->info,"*");
                    arboreD->st=arb3;
                    arboreD->dr=arb6;
                }
            }
        }
        else if (arboreD->info[0]=='/')
        {
            if (arboreD->st->info[0]=='0')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->dr->info[0]=='1')
            {
                arboreD=arboreD->st;
            }
            else if (arboreD->st->info[0]=='^' && arboreD->dr->info[0]=='x')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb2=arboreD->st;
                strcpy(arb5->info,"1");
                arb5->st=NULL;
                arb5->dr=NULL;
                arb3->st=arb2->dr;
                arb3->dr=arb5;
                strcpy(arb3->info,"-");
                operatorIntre2CaractereNumere(arb3, arb4);
                strcpy(arboreD->info,"^");
                arboreD->st=arb2->st;
                arboreD->dr=arb3;
            }
            else if (arboreD->dr->info[0]=='^' && arboreD->st->info[0]=='x')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb6=new nod;
                arb2=arboreD->dr;
                strcpy(arb5->info,"1");
                arb5->st=NULL;
                arb5->dr=NULL;
                arb3->st=arb2->dr;
                arb3->dr=arb5;
                strcpy(arb3->info,"-");
                operatorIntre2CaractereNumere(arb3, arb4);
                strcpy(arb6->info,"^");
                arb6->st=arb2->st;
                arb6->dr=arb3;
                strcpy(arboreD->info,"/");
                arboreD->st=arb5;
                arboreD->dr=arb6;
            }
            else if (arboreD->st->info[0]=='*' && arboreD->dr->info[0]=='x')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb5=new nod;
                arb2=arboreD->st;
                if (arb2->st->info[0]=='^' || arb2->dr->info[0]=='^' )
                {
                    if (arb2->st->info[0]=='^')
                    {
                        arb4=arb2->st;
                    }
                    if (arb2->dr->info[0]=='^')
                    {
                        arb4=arb2->dr;
                    }
                    strcpy(arb5->info,"1");
                    arb5->st=NULL;
                    arb5->dr=NULL;
                    arb3->st=arb4->dr;
                    arb3->dr=arb5;
                    strcpy(arb3->info,"-");
                    arb4=new nod;
                    operatorIntre2CaractereNumere(arb3, arb4);
                    strcpy(arboreD->info,"*");
                    arboreD->st=arboreD->st;
                    arboreD->dr=arb3;
                }

            }
            else if (arboreD->dr->info[0]=='^'&& arboreD->st->info[0]=='^')
            {
                arb2=new nod;
                arb3=new nod;
                arb4=new nod;
                arb6=new nod;
                arb5=new nod;
                arb7=new nod;
                arb2=arboreD->st;
                arb3=arboreD->dr;
                if (esteX(arb2->st->info[0])&& esteCifra(arb2->dr->info[0]) && esteX(arb3->st->info[0])&& esteCifra(arb3->dr->info[0]))
                {
                    arb4->st=arb2->dr;
                    arb4->dr=arb3->dr;
                    strcpy(arb4->info,"-");
                    operatorIntre2CaractereNumere(arb4, arb1);
                    strcpy(arb5->info,"^");
                    arb5->st=arb2->st;
                    arb5->dr=arb4;
                    arboreD=arb5;
                }
            }
        }
    }
}

void simplificaZero(nod *&arboreD)
{
    nod *arb1, *arb2, *arb3, *arb4, *arb5, *arb6, *arb7, *arb8;
    arb1=new nod;
    arb2=new nod;
    arb3=new nod;
    if (!esteArboreNul(arboreD))
    {
        if (arboreD->info[0]=='-')
        {
            if (arboreD->st!=NULL && arboreD->st->info[0]=='0')
            {
                //stergeArbore(arboreD->st);
                arboreD->st=NULL;
            }
        }
        simplificaZero (arboreD->st);
        simplificaZero (arboreD->dr);
    }

}

///derivarea expresiei de ordin dat
void derivareOrdin(nod* &arbore, nod *&arboreD, int ordin)
{
    nod *arboreAux;
    initializareArbore(arboreAux);

    if (ordin==1)
    {
        initializareArbore(arboreD);
        derivare(arbore, arboreD);
        simplificaArbore(arboreD);
    }
    else if (ordin==2)
    {
        initializareArbore(arboreD);
        derivare(arbore, arboreD);
        simplificaArbore(arboreD);

        initializareArbore(arboreAux);
        derivare(arboreD, arboreAux);
        copiazaArbore(arboreD, arboreAux);
        simplificaArbore(arboreD);
    }
    else if (ordin==3)
    {
        initializareArbore(arboreD);
        derivare(arbore, arboreD);
        simplificaArbore(arboreD);

        initializareArbore(arboreAux);
        derivare(arboreD, arboreAux);
        copiazaArbore(arboreD, arboreAux);
        simplificaArbore(arboreD);

        copiazaArbore(arboreAux, arboreD);
        initializareArbore(arboreD);
        derivare(arboreAux, arboreD);
        simplificaArbore(arboreD);

    }
    else if (ordin==4)
    {
        initializareArbore(arboreD);
        derivare(arbore, arboreD);
        simplificaArbore(arboreD);

        initializareArbore(arboreAux);
        derivare(arboreD, arboreAux);
        copiazaArbore(arboreD, arboreAux);
        simplificaArbore(arboreD);

        copiazaArbore(arboreAux, arboreD);
        initializareArbore(arboreD);
        derivare(arboreAux, arboreD);
        simplificaArbore(arboreD);

        initializareArbore(arboreAux);
        derivare(arboreD, arboreAux);
        copiazaArbore(arboreD,arboreAux);
        simplificaArbore(arboreD);
    }
}

int nrNiveluri(nod *arbore)
{
    if(arbore==NULL)
        return 0;
    else
    {
        int n1=nrNiveluri(arbore->st);
        int n2=nrNiveluri(arbore->dr);
        return 1+max(n1, n2);
    }
}

int nrDeNoduri(nod *arbore)
{
    if(arbore==NULL)
        return 0;
    else
    {
        int n1=nrDeNoduri(arbore->st);
        int n2=nrDeNoduri(arbore->dr);
        return 1+n1+n2;
    }
}

int nrColoane(nod *arbore)
{
    if(arbore==NULL) return 0;
    else
    {
        int n1=nrColoane(arbore->st);
        int n2=nrColoane(arbore->dr);

        return 1+n1+n2;
    }
}


bool esteFrunza(nod *arbore)
{
    if(nrNiveluri(arbore)==1) return 1;
    return 0;
}

bool contineDoarUnNumarPozitiv(char sir[])
{
    int i;
    for(i=0; i<strlen(sir); i++)
        if(esteCifra(sir[i])==0)
            if(sir[i]!='.')
                return 0;
    return 1;
}

void adaugaParanteze(char sir[])
{
    char aux[NN];
    strcpy(aux,sir);
    strcpy(sir,"(");
    strcpy(sir+1,aux);
    strcat(sir,")");
}


bool existaDejaParantezeLaCapete(char sir[])
{
    if(sir[0]!='(') return 0;

    int numarParanteze, i;
    numarParanteze=0;

    for(i=0; i<strlen(sir); i++)
        if(sir[i]=='(') numarParanteze++;
        else if(sir[i]==')')
        {
            numarParanteze--;
            if(numarParanteze==0 && i!=strlen(sir)-1) return 0;
        }

    return 1;
}

bool adunaNumarCaractere (nod *arbore)
{
    if(arbore!=NULL)
    {
        return strlen(arbore->info)+ adunaNumarCaractere(arbore->st) + adunaNumarCaractere(arbore->dr);
    }
    else return 0;
}


void expresieDerivata(nod *&arbore, char rezultat[], int &maxim)
{
    if(esteArboreNul(arbore)==0)
    {
        if(esteFrunza(arbore)==1)
        {
            strcpy(rezultat, arbore->info);
        }
        else
        {

            char infoStanga[MM]="", infoDreapta[MM]="", operatori[MM]="";

            strcpy(operatori, arbore->info);

            expresieDerivata(arbore->st, rezultat, maxim);

            if(strlen(rezultat)+strlen(infoStanga)<=400 && maxim==0)
                strcat(infoStanga, rezultat);
            else
            {
                maxim=1;
                stergeSir(infoStanga);
                infoStanga[0]='x';
            }

            expresieDerivata(arbore->dr, rezultat, maxim);

            if(strlen(rezultat)+strlen(infoDreapta)<=400 && maxim==0)
                strcat(infoDreapta, rezultat);
            else
            {
                maxim=1;
                stergeSir(infoDreapta);
                infoDreapta[0]='x';
            }

            if(esteOperator(operatori[0])==1)
            {
                char auxiliar[MM]="";
                if(operatori[0]=='/')
                {
                    if(infoStanga!=NULL && esteFrunza(arbore->st)==0 && existaDejaParantezeLaCapete(infoStanga)==0  &&  testFunctie(arbore->st->info[0])==0 && arbore->st->info[0]!='^' && arbore->st->info[0]!='*' || infoStanga[0]=='-')
                        adaugaParanteze(infoStanga);
                    if(infoDreapta!=NULL && esteFrunza(arbore->dr)==0 && existaDejaParantezeLaCapete(infoDreapta)==0 &&  testFunctie(arbore->dr->info[0])==0 && arbore->dr->info[0]!='^' || infoDreapta[0]=='-')
                        adaugaParanteze(infoDreapta);
                }
                else if(operatori[0]=='*')
                {
                    if(infoStanga!=NULL && esteFrunza(arbore->st)==0 && existaDejaParantezeLaCapete(infoStanga)==0 && arbore->st->info[0]!='*'  && arbore->st->info[0]!='/'&&arbore->st->info!=NULL && testFunctie(arbore->st->info[0])==0 || infoStanga[0]=='-')
                        adaugaParanteze(infoStanga);
                    if(infoDreapta!=NULL && esteFrunza(arbore->dr)==0 && existaDejaParantezeLaCapete(infoDreapta)==0 && arbore->dr->info[0]!='*' && arbore->dr->info!=NULL && arbore->dr->info[0]!='/'&& testFunctie(arbore->dr->info[0])==0 && arbore->dr->info[0]!='^'|| infoDreapta[0]=='-')
                        adaugaParanteze(infoDreapta);
                }
                else if(operatori[0]=='^')
                {
                    if(infoStanga!=NULL && esteFrunza(arbore->st)==0 && existaDejaParantezeLaCapete(infoStanga)==0 && testFunctie(arbore->st->info[0])==0|| infoStanga[0]=='-')
                        adaugaParanteze(infoStanga);
                    if(infoDreapta!=NULL && esteFrunza(arbore->dr)==0 && existaDejaParantezeLaCapete(infoDreapta)==0 && testFunctie(arbore->dr->info[0])==0 || infoDreapta[0]=='-')
                        adaugaParanteze(infoDreapta);
                }

                if(infoStanga!=NULL)
                    strcpy(auxiliar, infoStanga);

                strcat(auxiliar, operatori);

                if(infoDreapta!=NULL)
                    strcat(auxiliar, infoDreapta);

                if(auxiliar[0]=='-')
                    adaugaParanteze(auxiliar);

                if(strlen(rezultat)+strlen(auxiliar)<=400 && maxim==0) strcpy(rezultat, auxiliar);
                else
                {
                    maxim=1;
                    stergeSir(rezultat);
                    rezultat[0]='x';

                }

            }
            else if(testFunctie(operatori[0])==1)
            {
                char auxiliar[MM]="";

                if(esteFrunza(arbore->st)==0 && existaDejaParantezeLaCapete(infoStanga)==0)
                    adaugaParanteze(infoStanga);

                strcat(auxiliar, operatori);

                if(infoStanga!=NULL)
                    strcat(auxiliar, infoStanga);

                if(strlen(rezultat)+strlen(auxiliar)<=400 && maxim==0)
                    strcpy(rezultat, auxiliar);
                else
                {
                    maxim=1;
                    stergeSir(rezultat);
                    rezultat[0]='x';

                }
            }
        }
    }
    else
    {
        strcpy(rezultat, "");
    }

}

///ce tine de desenarea arborelui


int nrFii(nod *arbore)
{
    if(arbore->st!=NULL && arbore->dr!=NULL) return 2;
    if(arbore->st!=NULL || arbore->dr!=NULL) return 1;
    return 0;
}

int numarColoane(nod *a)
{
    if(a!=NULL)
    {
        if(nrFii(a)!=1) ///cazuri 2 si 0
        {
            if(a->st!=NULL && a->dr!=NULL)
            {
                int n1=numarColoane(a->st);
                int n2=numarColoane(a->dr);

                return max(n1,n2)*2+1;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if(a->st!=NULL) numarColoane(a->st);
            else numarColoane(a->dr);
        }
    }
    else return 0;

}


int numarColoaneCazUnFiu(nod *a, int tipArbore) ///directie=1 la stanga directie=0 la dreapta
{
    if(a!=NULL)
    {
        if(nrFii(a)!=1) ///cazuri 2 si 0
        {
            if(a->st!=NULL && a->dr!=NULL)
            {
                if(tipArbore==1) return numarColoane(a->st)+1;
                else return numarColoane(a->dr)+1;
            }
            else return 1;
        }
        else
        {
            if(a->st!=NULL) numarColoaneCazUnFiu(a->st, tipArbore);
            else numarColoaneCazUnFiu(a->dr, tipArbore);
        }
    }
    else return 0;

}


void calculeazaColoane(nod *arbore, int &numarColoane)
{
    if(arbore!=NULL)
    {
        calculeazaColoane(arbore->st, numarColoane);
        calculeazaColoane(arbore->dr, numarColoane);
        if(nrFii(arbore)==2) numarColoane=numarColoane+2;
    }

}

int numarColoane2(nod *arbore)
{
    if(arbore==NULL) return 0;
    else
    {
        int coloane=1;
        calculeazaColoane(arbore, coloane);
        return coloane;
    }
}

int numarColoaneCazUnFiuVarianta2(nod *a, int tipArbore) ///directie=1 la stanga directie=0 la dreapta
{
    if(a!=NULL)
    {
        if(nrFii(a)!=1) ///cazuri 2 si 0
        {
            if(a->st!=NULL && a->dr!=NULL)
            {
                if(tipArbore==1) return numarColoane2(a->st)+1;
                else return numarColoane2(a->dr)+1;
            }
            else return 1;
        }
        else
        {
            if(a->st!=NULL) numarColoaneCazUnFiu(a->st, tipArbore);
            else numarColoaneCazUnFiu(a->dr, tipArbore);
        }
    }
    else return 0;
}

void text(int coloana, int nivel, char informatie[], double C, int H, int R, int N, char r[])
{

    settextjustify(1,1);

    outtextxy(coloana*C, nivel*H+int(textheight(r)/4), informatie);
}


void cerc(int col, int niv, double C, int H, int R, char r[])
{
    setcolor(RED);


    circle(col*C, niv*H, R);

    if(R>=5)
    {
        setfillstyle(1, WHITE);
        floodfill(col*C,niv*H, RED);
    }

}

void linii2(nod *a, int niv, int col, double C, int H, int R, int N)
{

    if(nrNiveluri(a)!=1)
    {
        setcolor(BLUE);
        int n1,n2;
        int s,d;
        bool ok;
        if(nrFii(a)==2)
        {
            if(nrFii(a->st)==1)
            {
                if(a->st->st!=NULL)
                    n1=numarColoaneCazUnFiuVarianta2(a->st->st, 0);
                else
                    n1=numarColoaneCazUnFiuVarianta2(a->st->dr, 0);

            }
            else n1=numarColoane2(a->st->dr)+1;

            if(nrFii(a->dr)==1)
            {
                if(a->dr->st!=NULL)
                    n2=numarColoaneCazUnFiuVarianta2(a->dr->st, 1);
                else
                    n2=numarColoaneCazUnFiuVarianta2(a->dr->dr, 1);

            }
            else n2=numarColoane2(a->dr->st)+1;

            line(col*C, niv*H, (col-n1)*C, (niv+1)*H);
            line(col*C, niv*H, (col+n2)*C, (niv+1)*H);
        }
        else if(nrFii(a)==1)
        {
            line(col*C, niv*H, col*C, (niv+1)*H);
        }
    }


}

void desenezVarianta2(nod *a, char info[], int niv, int col, double C, int H, int R, int N, char r[])
{
    settextstyle(8, 0, 1);

    int ct=2;
    bool gasit=0;
    while(textwidth(r)<R && gasit==0 && ct!=10)
    {

        settextstyle(8, 0, ct);
        if(textwidth(r)>=R)
        {
            settextstyle(8, 0, max(ct-1, 1));

            if(textwidth(r)>=R)
                settextstyle(8, 0, max(ct-2, 1));

            gasit=1;

        }
        else

            ct++;
    }

    R=(max(textwidth(r)/2+2, textheight(r)/2+2));

    if(R<=5) R=12;

    settextstyle(8, 0, max(ct-2, 1));

    linii2(a, niv, col, C, H, R, N);
    cerc(col, niv, C, H, R, r);
    text(col, niv, info, C, H, R, N, r);
}


void deseneazaVarianta2(nod *a, int niv, int col, double C, int H, int R, int N, char r[])
{
    if(a!=NULL)
    {
        int s,d;
        desenezVarianta2(a, a->info, niv, col, C, H, R, N, r);
        int n1,n2,n3,n4;

        bool ok;
        if(nrFii(a)==2)
        {
            if(nrFii(a->st)==1)
            {
                if(a->st->st!=NULL)
                    n1=numarColoaneCazUnFiuVarianta2(a->st->st, 0);
                else
                    n1=numarColoaneCazUnFiuVarianta2(a->st->dr, 0);

            }
            else n1=numarColoane2(a->st->dr)+1;

            if(nrFii(a->dr)==1)
            {
                if(a->dr->st!=NULL)
                    n2=numarColoaneCazUnFiuVarianta2(a->dr->st, 1);
                else
                    n2=numarColoaneCazUnFiuVarianta2(a->dr->dr, 1);

            }
            else n2=numarColoane2(a->dr->st)+1;

            deseneazaVarianta2(a->st, niv+1, col-n1, C, H, R, N, r);
            deseneazaVarianta2(a->dr, niv+1, col+n2, C, H, R, N, r);
        }
        else if(nrFii(a)==1)
        {
            deseneazaVarianta2(a->st, niv+1, col, C, H, R, N, r);
            deseneazaVarianta2(a->dr, niv+1, col, C, H, R, N, r);
        }

    }
}

void afiseazaText(char text[])
{
    settextstyle(8, 0, 2);
    setcolor(BLUE);
    outtextxy(10, 10, text);
}


void afiseazaGreseli(structuraGreseli v, int numarElemente, int x, int y, int *limba)
{
    if(*limba==1)
    {
        x=189;
        y=72;
        setcolor(BLACK);
        settextstyle(8, 0, 4);
        if(v.numarGreseli!=0 || v.parantezareGresita!=0)
        {
            if(v.parantezareGresita==1)
            {
                outtextxy(x, y, "Atentie la scrierea parantezelor");
            }
            else
            {
                outtextxy(x, y,"Functie gresita");
            }
        }
    }
    else
    {
        x=189;
        y=72;
        setcolor(BLACK);
        settextstyle(8, 0, 4);
        if(v.numarGreseli!=0 || v.parantezareGresita!=0)
        {
            if(v.parantezareGresita==1)
            {
                outtextxy(x, y, "Pay attention to the brackets");
            }
            else
            {
                outtextxy(x, y,"Wrong function");
            }
        }
    }

}

void vectorizareSiGreseli(char expresie[], char vectorExpresie[][NN], int &numarElemente, structuraGreseli &v, structuraAuxiliar vectorPozitii[])
{
    scrieExpresieInVector(expresie, vectorExpresie, numarElemente, v);

    if(testParantezeleSuntPuseCorect(vectorExpresie, numarElemente)==0)
        v.parantezareGresita=1;

    if(v.parantezareGresita==0)
        puneSemnulInmultiriiZero(vectorExpresie, numarElemente, v, vectorPozitii);
}


void deseneazaButon(int x1, int y1, int x2, int y2, char text[])
{
    setcolor(15);
    bar(x1, y1, x2, y2);
    setcolor(7);
    rectangle(x1, y1, x2, y2);
    setbkcolor(15);
    setcolor(0);
    if (strlen(text)>1)
    {
        if (strlen(text)>=5)
        {
            settextstyle(8, 0, 5/strlen(text)+2);
            outtextxy((x1+x2)/2 - 37, (y1+y2)/2 - 12, text);

        }
        else if (strlen(text)==2)
        {
            settextstyle(8, 0, 5/strlen(text)+1);
            outtextxy((x1+x2)/2 - 16, (y1+y2)/2 - 10, text);
        }
        else if (strlen(text)==4)
        {
            settextstyle(8, 0, 5/strlen(text)+2);
            outtextxy((x1+x2)/2 - 27, (y1+y2)/2 - 10, text);
        }
        else
        {
            settextstyle(8, 0, 5/strlen(text)+2);
            outtextxy((x1+x2)/2 - 20, (y1+y2)/2 - 12, text);
        }


    }
    else
    {
        settextstyle(8, 0, 5);
        outtextxy((x1+x2)/2-12, (y1+y2)/2 - 18, text);
    }
}

void deseneazaButoaneTastatura ()
{
    int x=315;
    deseneazaButon(x, 710, x+100, 760, "0");
    deseneazaButon(x, 655, x+100, 705, "1");
    deseneazaButon(x, 600, x+100, 650, "4");
    deseneazaButon(x, 545, x+100, 595, "7");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, "(");
    deseneazaButon(x, 655, x+100, 705, "2");
    deseneazaButon(x, 600, x+100, 650, "5");
    deseneazaButon(x, 545, x+100, 595, "8");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, ")");
    deseneazaButon(x, 655, x+100, 705, "3");
    deseneazaButon(x, 600, x+100, 650, "6");
    deseneazaButon(x, 545, x+100, 595, "9");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, "<-");
    deseneazaButon(x, 655, x+100, 705, "-");
    deseneazaButon(x, 600, x+100, 650, "+");
    deseneazaButon(x, 545, x+100, 595, "*");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, ",");
    deseneazaButon(x, 655, x+100, 705, "^");
    deseneazaButon(x, 600, x+100, 650, "e");
    deseneazaButon(x, 545, x+100, 595, "/");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, "ctg");
    deseneazaButon(x, 655, x+100, 705, "tg");
    deseneazaButon(x, 600, x+100, 650, "cos");
    deseneazaButon(x, 545, x+100, 595, "sin");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, "arcctg");
    deseneazaButon(x, 655, x+100, 705, "arctg");
    deseneazaButon(x, 600, x+100, 650, "arccos");
    deseneazaButon(x, 545, x+100, 595, "arcsin");
    x+=105;
    deseneazaButon(x, 710, x+100, 760, "x");
    deseneazaButon(x, 655, x+100, 705, "sqrt");
    deseneazaButon(x, 600, x+100, 650, "log");
    deseneazaButon(x, 545, x+100, 595, "ln");
}



void deseneazaButonStergere(int color)
{
    setcolor(color);
    ellipse(1496, 486, 0, 90, 4, 4);
    ellipse(1442, 486, 90, 180, 4, 4);
    ellipse(1496, 506, 270, 360, 4, 4);
    ellipse(1442, 506, 180, 270, 4, 4);
    line(1442,482,1496,482); //sus
    line(1442,509,1496,509); //jos
    line(1438,487,1438,506); //stanga
    line(1499,486,1499,506); //dreapta
}

void deseneazaButonDeriva(int color)
{
    setcolor(color);
    ellipse(1268, 495, 90, 270, 19, 19);
    ellipse(1381, 495, 270, 450, 19, 19);
    line(1268, 476, 1383, 476); //sus
    line(1268, 513, 1383, 513); //jos
}

void animatieButonDeivata()
{
    deseneazaButonDeriva(0);
    delay(100);
    deseneazaButonDeriva(7);
}

void deseneazaSimbolFoaie(int x1, int x2, int x3, int x4, int x5, int x6, int y1, int y2, int y3, int y4, int y5, int y6)
{
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x4, y4, x5, y5);
    line(x5, y5, x1, y1);
    line(x6, y6, x4, y4);
    line(x6, y6, x5, y5);
}

void deseneazaPatrat(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4)
{
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x4, y4, x1, y1);
}

void deseneazaButoaneSageti(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int y1, int y2, int y3, int y4, int y5, int y6, int y7, int y8)
{
    setbkcolor(15);
    settextstyle(8, 0, 3);
    settextjustify(0,0);
    outtextxy(x1+2, y1-2, "<<");
    outtextxy(x5+2, y5-2, ">>");
    deseneazaPatrat(x1, x2, x3, x4, y1, y2, y3, y4);
    deseneazaPatrat(x5, x6, x7, x8, y5, y6, y7, y8);
    settextjustify(0,2);
}

void animatieButonSageata(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, int tipButon)
{
    setcolor(0);
    setbkcolor(15);
    settextstyle(8, 0, 3);
    settextjustify(0,0);
    if(tipButon==1) ///buton stanga
        outtextxy(x1+2, y1-2, "<<");
    else outtextxy(x1+2, y1-2, ">>");
    deseneazaPatrat(x1, x2, x3, x4, y1, y2, y3, y4);

    delay(100);

    setcolor(8);
    setbkcolor(15);
    settextstyle(8, 0, 3);
    settextjustify(0,0);
    if(tipButon==1) ///buton stanga
        outtextxy(x1+2, y1-2, "<<");
    else outtextxy(x1+2, y1-2, ">>");
    deseneazaPatrat(x1, x2, x3, x4, y1, y2, y3, y4);
    settextjustify(0,2);

}

void animatieClick (int x1, int y1, int x2, int y2)
{
    setcolor(0);
    rectangle(x1, y1, x2, y2);
    delay(100);
    setcolor(7);
    rectangle(x1, y1, x2, y2);
}

void animatieButonStergere()
{
    deseneazaButonStergere(0);
    delay(100);
    deseneazaButonStergere(7);
}

void animatieSimbolFoaie(int x1, int x2, int x3, int x4, int x5, int x6, int y1, int y2, int y3, int y4, int y5, int y6)
{
    setcolor(0);
    deseneazaSimbolFoaie(x1, x2, x3, x4, x5, x6, y1, y2, y3, y4, y5, y6);
    delay(100);
    setcolor(8);
    deseneazaSimbolFoaie(x1, x2, x3, x4, x5, x6, y1, y2, y3, y4, y5, y6);
}

bool esteBackSpace(int caracter)
{
    return int(caracter)==8;
}

bool esteSageata(char caracter)
{
    return int(caracter)==77 || int(caracter)==75;
}

void cursor(char intrare[], int &pozitieCursor, char caracter)
{
    if(int(caracter)==77)
    {
        if(intrare[pozitieCursor]!=NULL)
            pozitieCursor++;
    }
    else
    {
        if(pozitieCursor!=0)
            pozitieCursor--;
    }
}

void memoreazaCaracterIntrodus(char intrare[], char caracter, int &pozitieCursor)
{
    if(esteBackSpace(caracter)==0)
    {
        char sir[NN]="", auxiliar[500]="";
        sir[0]=0;
        sir[0]=caracter;
        sir[1]=0;

        strcpy(auxiliar, intrare+pozitieCursor);
        strcpy(intrare+pozitieCursor, sir);
        strcat(intrare, auxiliar);
        pozitieCursor++;
    }
    else
    {
        if(pozitieCursor!=0)
        {
            char auxiliar[NN]="";
            strcpy(auxiliar, intrare+pozitieCursor);
            strcpy(intrare+pozitieCursor-1, auxiliar);
            pozitieCursor--;
        }
        else cout<<char(7);
    }
}

void deseneazaCursor(int pozitieCursor, int culoare)
{
    int spatiu=20;
    settextstyle(8, 0, 4);

    setcolor(culoare);
    line(100+spatiu*pozitieCursor, 480, 100+spatiu*pozitieCursor, 510);

}

void afisareFunctieIntrodusaInFereastra(char intrare[], char vectorFunctie[][NN], int numarElemente, structuraGreseli v, structuraAuxiliar pozitiiVector[],int x, int y, int numarDeClickuri, int *limba)
{
    y=130;
    setbkcolor(15);
    settextstyle(8, 0, 4);
    outtextxy(x, y, "                                                                             ");
    int i, lungimeCaracter=20;
    char sir[NN]="";
    if(v.parantezareGresita==1)
    {
        for(i=0; i<strlen(intrare); i++)
        {
            if(esteParanteza(intrare[i])==1)
            {
                setcolor(BLUE);
            }
            else
            {
                setcolor(BLACK);
            }

            char aux[NN]="";
            ilFaceSir(intrare[i], aux);
            outtextxy(x, y, aux);
            x=x+lungimeCaracter;
        }

    }
    else
    {
        int numarCaractere=0;
        for(i=2; i<numarElemente && numarCaractere<68; i++)
        {
            int j=pozitiiVector[i].pozitieInVector;
            if(v.vectorGreseli[j].pozitieInVector!=-1 && j>0)
            {
                setcolor(RED);
                outtextxy(x, y, v.vectorGreseli[j].sirDinFunctie);
                x=x+lungimeCaracter*strlen(v.vectorGreseli[j].sirDinFunctie);
                numarCaractere=numarCaractere+strlen(v.vectorGreseli[j].sirDinFunctie);

            }
            else if(j>0)
            {
                setcolor(BLACK);
                outtextxy(x, y, vectorFunctie[i]);
                x=x+lungimeCaracter*strlen(vectorFunctie[i]);
                numarCaractere=numarCaractere+strlen(vectorFunctie[i]);
            }
        }

        outtextxy(85+68*20, y, "      ");

    }

}

void arborizeazaRezultat (char rezultat[], nod *&arbore)
{
    char copie[NN]="";
    strcpy(copie, rezultat);
    adaugaParanteze(copie);
    int numarElemente;
    char vectorFunctie[NN][NN];
    structuraGreseli v;
    v.numarGreseli=0;
    v.parantezareGresita=0;

    structuraAuxiliar vectorPozitii[NN];
    vectorizareSiGreseli(copie, vectorFunctie, numarElemente, v, vectorPozitii);

    if (arbore!=NULL)
    {
        stergeArbore(arbore);
    }
    else initializareArbore(arbore);

    if(v.parantezareGresita==0)
        transformaInArbore(vectorFunctie, numarElemente, arbore, v, vectorPozitii);
}


void prelucrareFunctieIntrodusa(char intrare[], bool &functiaPoateFiDerivata, int numarDeClickuri, int *limba)
{
    int x=85, y=130;

    char functie[NN];
    strcpy(functie, intrare);
    adaugaParanteze(functie);
    outtextxy(189, 25, "                               ");
    outtextxy(189, 72, "                                                         ");
    int numarElemente;
    char vectorFunctie[NN][NN];
    structuraGreseli v;
    v.numarGreseli=0;
    v.parantezareGresita=0;

    structuraAuxiliar vectorPozitii[NN];
    vectorizareSiGreseli(functie, vectorFunctie, numarElemente, v, vectorPozitii);

    nod *arbore;
    initializareArbore(arbore);

    if(v.parantezareGresita==0)
        transformaInArbore(vectorFunctie, numarElemente, arbore, v, vectorPozitii);
///

    if(v.numarGreseli!=0 || v.parantezareGresita!=0)
    {
        afiseazaGreseli(v, numarElemente, 189, 72, limba);
        afisareFunctieIntrodusaInFereastra(intrare, vectorFunctie, numarElemente, v, vectorPozitii,x, y, numarDeClickuri, limba);
        functiaPoateFiDerivata=0;

        setcolor(15);
        deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 162, 130,  130, 162, 162, 130, 130, 162);

    }
    else
    {
        setbkcolor(15);
        settextstyle(8, 0, 4);
        setcolor(BLACK);

        outtextxy(189, 72, "                                                         ");
        if (*limba==1)
        {
            outtextxy(189, 72, "Functie corecta");

        }
        else
        {
            outtextxy(189, 72, "Correct function");

        }

        char ceSeAfiseaza[NN]="";
        strcpy(ceSeAfiseaza, intrare+numarDeClickuri);
        ceSeAfiseaza[68]=0;
        outtextxy(85, 130, "                                                                             ");
        outtextxy(85, 130, ceSeAfiseaza);
        functiaPoateFiDerivata=1;


        if(strlen(intrare)>68)
        {
            setcolor(7);
            deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 162, 130,  130, 162, 162, 130, 130, 162);

        }
        else
        {
            setcolor(15);
            deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 162, 130,  130, 162, 162, 130, 130, 162);
        }
    }

    stergeArbore(arbore);
}

struct structuraCulori
{
    int xInceputDeElement;
    int xSfarsitDeElement;
    int culoareElement;
    char mesajGreseli[NN]="";
};

void memoreazaCoordonateInStructuraCulori(int &indice, int xCurent, int xUrmator, int culoare, structuraCulori vectorCulori[], char text[])
{
    indice++;
    vectorCulori[indice].xInceputDeElement=xCurent;
    vectorCulori[indice].xSfarsitDeElement=xUrmator;
    vectorCulori[indice].culoareElement=culoare;
    strcpy(vectorCulori[indice].mesajGreseli, text);
}

void mesajGreseala(int cod, int *limba, char sir[])
{
    char aux[NN]="";

    if(*limba==1)
    {
        if(cod==1) strcpy(aux, "Exista un numar scris gresit");
        else if(cod==2) strcpy(aux,"Virgula plasata necorespunzator");
        else if(cod==3) strcpy(aux, "Fara semnificatie");
        else if(cod==4) strcpy(aux, "Atentie la scrierea operatorului");
        else if(cod==5) strcpy(aux, "Lipsesc operanzi");
        else if(cod==6) strcpy(aux, "Atentie la scrierea functiei si a operatorului");
        else if(cod==7 || cod==11 || cod==9 || cod==10)
        {
            strcpy(aux, "Atentie la scrierea functiei");
        }
        else if(cod==8) strcpy(aux, "Virgula plasata necorespunzator");

    }
    else
    {
        if(cod==1) strcpy(aux, "Misspelled number");
        else if(cod==2) strcpy(aux,"Inappropriate placed comma");
        else if(cod==3) strcpy(aux, "Meaningless data");
        else if(cod==4) strcpy(aux, "Pay attention to writing operators");
        else if(cod==5) strcpy(aux, "Operands are missing");
        else if(cod==6) strcpy(aux, "Pay attention to the function's and operator's writing ");
        else if(cod==7 || cod==11 || cod==9 || cod==10)
        {
            strcpy(aux, "Pay attention to the function's writing");
        }
        else if(cod==8) strcpy(aux, "Virgula plasata necorespunzator");
    }


    strcpy(sir, aux);
}


void greseliClick(int x, int y, char intrare[], int nrClick, int *limba)
{

    int ySus=157, yJos=174-20;
    if(x>=85 && x<=1534 && y>=157-20 && y<=174-20)
    {

        char functie[NN];
        strcpy(functie, intrare);
        adaugaParanteze(functie);
        int numarElemente;
        char vectorFunctie[NN][NN];
        structuraGreseli v;
        v.numarGreseli=0;
        v.parantezareGresita=0;

        structuraAuxiliar vectorPozitii[NN];
        vectorizareSiGreseli(functie, vectorFunctie, numarElemente, v, vectorPozitii);

        nod *arbore;
        initializareArbore(arbore);

        if(v.parantezareGresita==0)
            transformaInArbore(vectorFunctie, numarElemente, arbore, v, vectorPozitii);

        if(v.numarGreseli!=0 && v.parantezareGresita==0)
        {
            int i, lungimeCaracter=20;
            int culoare; ///rosu cu 1  si negru cu 0
            structuraCulori vectorCulori[NN];
            int xCurent, xUrmator;
            xCurent=xUrmator=85;
            int indice=0;

            for(i=2; i<numarElemente; i++)
            {
                int j=vectorPozitii[i].pozitieInVector;
                if(v.vectorGreseli[j].pozitieInVector!=-1 && j>0)
                {
                    culoare=1;
                    xCurent=xUrmator;
                    xUrmator=xUrmator+lungimeCaracter*strlen(v.vectorGreseli[j].sirDinFunctie);

                    char aux[NN]="";
                    mesajGreseala(v.vectorGreseli[j].codGreseala, limba, aux);


                    memoreazaCoordonateInStructuraCulori(indice, xCurent, xUrmator, culoare, vectorCulori, aux);

                }
                else if(j>0)
                {
                    culoare=0;
                    xCurent=xUrmator;
                    xUrmator=xUrmator+lungimeCaracter*strlen(vectorFunctie[i]);
                    if(*limba==1)
                    {
                        memoreazaCoordonateInStructuraCulori(indice, xCurent, xUrmator, culoare, vectorCulori, "Nu este greseala");

                    }
                    else memoreazaCoordonateInStructuraCulori(indice, xCurent, xUrmator, culoare, vectorCulori, "There's no error");
                }
            }

            int xLimitaInferioara=85;
            int xLimitaSuperioara=xUrmator;
            int numarElementeAfisate=indice;
            if(x>=xLimitaInferioara && x<=xLimitaSuperioara)
            {
                for(i=1; i<=numarElementeAfisate; i++)
                {

                    if(x>=vectorCulori[i].xInceputDeElement && x<=vectorCulori[i].xSfarsitDeElement)
                    {
                        setbkcolor(15);
                        settextstyle(8, 0, 4);
                        outtextxy(189, 72, "                                                         ");
                        outtextxy(189, 72, vectorCulori[i].mesajGreseli);
                        break;
                    }

                }
            }

        }

    }

}



void textTastatura (char intrare[], int &pozitieCursor, int &pozitiePAnt, int &anteriorCursor, bool &functiaPoateFiDerivata, int &ordin, bool &functiaEsteDerivata, int &numarClickuri, int &numarClickuriDerivata, int *limba)
{
    char tasta, urmator;
    int spatiuY=480, spatiuX=100, spatiu=20;
    setcolor(0);
    settextstyle(8, 0, 3);

    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        if (kbhit())
        {
            tasta = getch();
            int anterior=pozitieCursor;
            if(int(tasta)==32 || int(tasta)==13 || int(tasta)==10)
            {
                ///ignora
            }
            else if(int(tasta)==27)
            {
                ///ignora
            }
            else if(int(tasta)==0 || int(tasta)==224)
            {
                urmator=getch();
                if(esteSageata(urmator)==1)
                {
                    cursor(intrare, pozitieCursor, urmator);
                }
                else if(int(urmator)==83)
                {
                    if(pozitieCursor==0) cout<<char(7);

                    pozitieCursor=0;
                    pozitiePAnt=1;
                    anteriorCursor=0;
                    anterior=0;
                    stergeSir(intrare);
                    functiaEsteDerivata=0;
                    int spatiuXORD=1155, spatiuYORD=483;
                    setcolor(0);
                    settextstyle(8, 0, 3);
                    ordin=1;
                    outtextxy(spatiuXORD, spatiuYORD, "1");
                    numarClickuri=0;
                    numarClickuriDerivata=0;
                    setcolor(15);
                    deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 162, 130,  130, 162, 162, 130, 130, 162);
                    settextstyle(8, 0, 4);
                    outtextxy(85, 370, "                                                                    ");
                }

            }
            else
            {
                memoreazaCaracterIntrodus(intrare, tasta, pozitieCursor);
                numarClickuri=0;
            }

            char aux[NN]="";
            setbkcolor(15);
            setcolor(0);
            settextstyle(8, 0, 4);
            outtextxy(100, 480, "                                            ");

            {
                if(anterior>pozitieCursor)
                {
                    if(anteriorCursor!=0)
                    {
                        anteriorCursor--;
                    }
                    else
                    {
                        pozitiePAnt--;
                    }

                    strcpy(aux, intrare+pozitiePAnt);
                    int numereCaractereDupaBara=strlen(aux+42);
                    aux[0]=0;

                    if(int(tasta)==8)
                    {

                        if(numereCaractereDupaBara>0)
                        {
                            strcpy(aux, intrare+pozitiePAnt-1);
                        }
                        else
                        {
                            strcpy(aux, intrare+max(0,pozitiePAnt-2));
                            if(max(0,pozitiePAnt-2)==0) pozitiePAnt=1;
                            else pozitiePAnt--;
                        }

                    }
                    else strcpy(aux, intrare+pozitiePAnt-1);

                    aux[44]=0;
                    outtextxy(100, 480, aux);

                    if(int(tasta)==8)
                    {

                        if(numereCaractereDupaBara>0)
                        {
                            deseneazaCursor(anteriorCursor, 4);
                        }
                        else
                        {
                            if(strlen(intrare)>44)
                            {
                                deseneazaCursor(anteriorCursor+1, 4);
                                anteriorCursor++;
                            }
                            else
                            {
                                deseneazaCursor(pozitieCursor, 4);
                                anteriorCursor=pozitieCursor;
                            }

                        }

                    }
                    else deseneazaCursor(anteriorCursor, 4);


                }
                else if(anterior<pozitieCursor)
                {
                    if(anteriorCursor!=44)
                    {
                        anteriorCursor++;
                    }
                    else
                    {
                        pozitiePAnt++;
                    }
                    strcpy(aux, intrare+pozitiePAnt-1);
                    aux[44]=0;
                    outtextxy(100, 480, aux);
                    deseneazaCursor(anteriorCursor, 4);
                }
                else if(anterior==pozitieCursor)
                {
                    strcpy(aux, intrare+pozitiePAnt-1);
                    aux[44]=0;
                    outtextxy(100, 480, aux);
                    deseneazaCursor(anteriorCursor, 4);
                }
            }

            if(strlen(intrare)>0)
            {
                prelucrareFunctieIntrodusa(intrare, functiaPoateFiDerivata, numarClickuri, limba);
            }
            else
            {
                settextstyle(8, 0, 4);
                outtextxy(85, 130, "                                                                    ");
                outtextxy(189, 25, "                               ");
                outtextxy(189, 72, "                                                         ");
                functiaPoateFiDerivata=0;
            }

        }
    }

}

void fileDinCalculator(char memoreazaDinFisier[])
{
    int x, y;
    int j=0;
    char ch;
    char s[NN]="";
    FILE *fsr;

    OPENFILENAME fisier;

    char numeFisier[NN]="";
    char *filtru = "TEXT\0*.TXT\0";

    HWND owner = NULL;

    ZeroMemory(&fisier, sizeof(fisier));

    fisier.lStructSize = sizeof(OPENFILENAME);
    fisier.hwndOwner = owner;
    fisier.lpstrFilter = filtru;
    fisier.lpstrFile = numeFisier;
    fisier.nMaxFile = NN;

    if (GetOpenFileName(&fisier))
    {
        fsr = fopen(numeFisier,"r");
        while(ch!=EOF)
        {
            ch=getc(fsr);
            if (ch==EOF)
                break;
            s[j]=ch;
            strcpy(memoreazaDinFisier, s);
            j++;
        }
    }
    fclose(fsr);
}

void salveazaFileInCalculator(char salveazaInFisier[], int ordin, int *limba, char intrare[])
{
    int x, y;
    int j=0;
    char ch;
    char s[NN]="";
    char salvatRO[]="Derivata de ordinul ";
    char salvatRO2[]=" a functiei ";
    char salvatEN[]=" order derivative";
    char salvatEN2[]=" of function ";
    FILE *fsr;

    OPENFILENAME fisier;

    char numeFisier[NN]="";
    char *filtru = "Text\0*.TXT\0";

    HWND owner = NULL;

    ZeroMemory(&fisier, sizeof(fisier));

    fisier.lStructSize = sizeof(OPENFILENAME);
    fisier.hwndOwner = owner;
    fisier.lpstrFilter = filtru;
    fisier.lpstrFile = numeFisier;
    fisier.nMaxFile = NN;

    if (GetSaveFileNameA(&fisier))
    {
        fsr = fopen(numeFisier,"w");
        if (*limba==1)
        {
            fprintf(fsr,"%s",salvatRO);
            fprintf(fsr,"%d",ordin);
            fprintf(fsr,"%s",salvatRO2);
            fprintf(fsr,"%s",intrare);
            fprintf(fsr,"%s \n",":");
        }
        else
        {
            fprintf(fsr,"%d",ordin);
            fprintf(fsr,"%s",salvatEN);
            fprintf(fsr,"%s",salvatEN2);
            fprintf(fsr,"%s",intrare);
            fprintf(fsr,"%s \n",":");
        }
        fprintf(fsr,"%s",salveazaInFisier);
    }
    fclose(fsr);
}

void setariLimba(int *limba)
{
    int x,y;
    initwindow(350, 400, "Setari", 520, 200);
    if (*limba==1)
    {
        readimagefile("SetariRO.jpg", 0, 0, 350, 400);
    }
    else
    {
        readimagefile("SetariEN.jpg", 0, 0, 350, 400);
    }

    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(305, 0, 350, 25);
    setbkcolor(LIGHTRED);
    setcolor(15);
    settextstyle(8, 0, 3);
    outtextxy(320, -1, "X");

    while (!(x>=305 && x<=350 && y>=0 && y<=22))
    {
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(50);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x>=88 && x<=169 && y>=102 && y<=126)
        {
            *limba=1;
            readimagefile("SetariRO.jpg", 0, 0, 350, 400);
        }
        else if (x>=90 && x<=162 && y>=200 && y<=225)
        {
            *limba=2;
            readimagefile("SetariEN.jpg", 0, 0, 350, 400);
        }

        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(305, 0, 350, 25);
        setbkcolor(LIGHTRED);
        setcolor(15);
        settextstyle(8, 0, 3);
        outtextxy(320, -1, "X");
    }

    getcurrentwindow();
    closegraph(CURRENT_WINDOW);
    setcurrentwindow(0);
}

void informatii(int *limba)
{
    int x,y;
    initwindow(450, 500, "", 500, 160);

    if (*limba==1)
    {
        readimagefile("InfoRO.jpg", 0, 0, 450, 500);
    }
    else
    {
        readimagefile("InfoEN.jpg", 0, 0, 450, 500);
    }

    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(405, 0, 450, 25);
    setbkcolor(LIGHTRED);
    setcolor(15);
    settextstyle(8, 0, 3);
    outtextxy(420, -1, "X");
    bool gata=false;
    do
    {

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if (x>=405 && x<=450 && y>=0 && y<=22)
            {
                gata=true;
            }
        }

    }
    while (!gata);

    getcurrentwindow();
    closegraph(CURRENT_WINDOW);
    setcurrentwindow(0);

}

void limbaFundal(char intrare[], int *limba, int ordin)
{
    int spatiuXORD=1155, spatiuYORD=483;
    char b[]="1";
    char* i;
    b[0] = (char)(ordin + 48);
    i = &b[0];

    if (*limba==1)
    {
        readimagefile("FundalRO.jpg", 0, 0, 1535, 800);
        deseneazaButoaneTastatura ();
        setcolor(0);
        settextstyle(8, 0, 3);

        outtextxy(spatiuXORD, spatiuYORD, i);
    }
    else
    {
        readimagefile("FundalEN.jpg", 0, 0, 1535, 800);
        deseneazaButoaneTastatura ();
        setcolor(0);
        settextstyle(8, 0, 3);
        ordin=1;
        outtextxy(spatiuXORD, spatiuYORD, i);
    }
}

void lungimeMax(nod *a, char sir[])
{
    if(a!=NULL)
    {
        lungimeMax(a->st, sir);
        lungimeMax(a->dr, sir);

        if(strlen(a->info)>strlen(sir)) strcpy(sir, a->info);
    }

}

void fereastraArbore(nod *arbore, char text[])
{
    int H, R, N;
    double C;
    N=nrNiveluri(arbore);
    H=800/(nrNiveluri(arbore)+1);

    initwindow(1000, 800, "", 250, 10);

    setbkcolor(WHITE);
    cleardevice();

    afiseazaText(text);

    int coloanaDeInceput=1;

    if(nrFii(arbore)==2)
    {

        coloanaDeInceput=numarColoane2(arbore->st)+1;

    }
    else if(nrFii(arbore)==1)
    {

        if(arbore->st!=NULL)
        {
            coloanaDeInceput=numarColoaneCazUnFiuVarianta2(arbore->st, 1);
        }
        else
        {
            coloanaDeInceput=numarColoaneCazUnFiuVarianta2(arbore->dr, 1);
        }
    }

    C=1000/double(numarColoane2(arbore)+1);
    R=min(H/2, int(C/2))-1;

    char elemLungMax[NN]="";
    lungimeMax(arbore, elemLungMax);
    deseneazaVarianta2(arbore, 1, coloanaDeInceput, C, H, R, N, elemLungMax);


    settextjustify(0,2);
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(975, 0, 999, 25);
    setbkcolor(LIGHTRED);
    setcolor(15);
    settextstyle(8, 0, 3);
    outtextxy(980, 0, "X");

    int x, y;
    bool apasat=false;
    do
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if (x>=975 && x<=1000 && y>=0 && y<=25)
            {
                apasat=true;
            }

        }

    }
    while (!apasat);

    getcurrentwindow();
    closegraph(CURRENT_WINDOW);
    setcurrentwindow(0);
}

int numarParanteze(char sir[])
{
    int i, contor=0;
    for(i=0; i<strlen(sir); i++)
        if(esteParanteza(sir[i])==1) contor++;
    return contor;
}

int parantezePuseCorect(char sir[])
{
    bool greseala;
    int i, numarParanteze;

    greseala=0;
    numarParanteze=0;

    for(i=0; i<strlen(sir) && greseala==0; i++)
        if(sir[i]=='(') numarParanteze++;
        else if(sir[i]==')')
        {
            if(numarParanteze>0) numarParanteze--;
            else greseala=1;
        }

    if(greseala==1 || numarParanteze!=0) return 0;
    return 1;
}

void afisareFunctieDerivata(nod *&arboreD, char intrare[], char rezultat[], int ordin, bool& functiaEsteDerivata)
{
    stergeSir(rezultat);
    rezultat[0]=0;
    int numarElemente;
    char vectorFunctie[NN][NN];
    char functie[NN];
    strcpy(functie, intrare);
    adaugaParanteze(functie);

    structuraGreseli v;
    v.numarGreseli=0;
    v.parantezareGresita=0;

    structuraAuxiliar vectorPozitii[NN];
    vectorizareSiGreseli(functie, vectorFunctie, numarElemente, v, vectorPozitii);

    nod *arbore;
    initializareArbore(arbore);
    transformaInArbore(vectorFunctie, numarElemente, arbore, v, vectorPozitii);

    nod *arboreCopie;
    initializareArbore(arboreCopie);
    copiazaArbore(arboreCopie, arbore);

    initializareArbore(arboreD);
    derivareOrdin(arboreCopie, arboreD, ordin);
    simplificaZero(arboreD);

    int maxim=0;
    expresieDerivata(arboreD, rezultat, maxim);


    if(maxim==0)
    {
        if(rezultat[0]=='(' && rezultat[strlen(rezultat)-1]==')')
        {
            char auxiliar[NN]="";
            strcpy(auxiliar, rezultat);
            strcpy(auxiliar, auxiliar+1);
            auxiliar[strlen(auxiliar)-1]=0;
            if(parantezePuseCorect(auxiliar)==1) strcpy(rezultat, auxiliar);
        }

        functiaEsteDerivata=1;
    }
    else
    {
        functiaEsteDerivata=0;
        cout<<char(7);
    }

}

void afiseazaTextButoane(int *limba)
{
    char intrare[NN]="";
    int x,y;
    int spatiuXORD=1155, spatiuYORD=483;
    char b[] = "1";
    char tasta;
    int ordin=1;
    char* i = &b[0];
    char rezultat[MM]="";

    int pozitieCursor=0;
    int pozitiePAnt=1, anteriorCursor=0;
    int anterior;
    int numarCaractereButon=0;
    int scade;

    nod *arboreD;
    initializareArbore(arboreD);

    nod *arboreDesenat;
    initializareArbore(arboreDesenat);

    bool functiaEsteDerivata=0;
    bool functiaPoateFiDerivata=0;
    bool esteClickPeFunctie;

    setcolor(0);
    settextstyle(8, 0, 3);
    outtextxy(spatiuXORD, spatiuYORD, "1");


    int numarClickuriPeSageataFunctieIntrodusa=0;
    int numarClickuriPeSageataFunctieDerivata=0;

    while (1)
    {
        textTastatura(intrare, pozitieCursor, pozitiePAnt, anteriorCursor, functiaPoateFiDerivata, ordin, functiaEsteDerivata, numarClickuriPeSageataFunctieIntrodusa, numarClickuriPeSageataFunctieDerivata, limba);

        anterior=pozitieCursor;

        scade=0;
        esteClickPeFunctie=0;
        x=-1;
        y=-1;
        getmouseclick(WM_LBUTTONDOWN, x, y);

        setcolor(0);
        settextstyle(8, 0, 4);
        if ((x>=315 && x<=415 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, '0', pozitieCursor);
            animatieClick(315, 710, 415, 760);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=315 && x<=415 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, '1', pozitieCursor);
            animatieClick(315, 655, 415, 705);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=315 && x<=415 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, '4', pozitieCursor);
            animatieClick(315, 600, 415, 650);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=315 && x<=415 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, '7', pozitieCursor);
            animatieClick(315, 545, 415, 595);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        ///////////////////////////////////////////////////////////
        else if ((x>=420 && x<=520 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            animatieClick(420, 710, 520, 760);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=420 && x<=520 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, '2', pozitieCursor);
            animatieClick(420, 655, 520, 705);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=420 && x<=520 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, '5', pozitieCursor);
            animatieClick(420, 600, 520, 650);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=420 && x<=520 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, '8', pozitieCursor);
            animatieClick(420, 545, 520, 595);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        ///////////////////////////////////////////////////////
        else if ((x>=525 && x<=625 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            animatieClick(525, 710, 625, 760);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=525 && x<=625 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, '3', pozitieCursor);
            animatieClick(525, 655, 625, 705);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=525 && x<=625 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, '6', pozitieCursor);
            animatieClick(525, 600, 625, 650);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=525 && x<=625 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, '9', pozitieCursor);
            animatieClick(525, 545, 625, 595);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        /////////////////////////////////////////////////////////
        else if ((x>=630 && x<=730 && y>=710 && y<=760))
        {
            animatieClick(630, 710, 730, 760);
            memoreazaCaracterIntrodus(intrare, char(8), pozitieCursor);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=630 && x<=730 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, '-', pozitieCursor);
            animatieClick(630, 655, 730, 705);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=630 && x<=730 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, '+', pozitieCursor);
            animatieClick(630, 600, 730, 650);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=630 && x<=730 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, '*', pozitieCursor);
            animatieClick(630, 545, 730, 595);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        /////////////////////////////////////////////////
        else if ((x>=735 && x<=835 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, ',', pozitieCursor);
            animatieClick(735, 710, 835, 760);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=735 && x<=835 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, '^', pozitieCursor);
            animatieClick(735, 655, 835, 705);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=735 && x<=835 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, 'e', pozitieCursor);
            animatieClick(735, 600, 835, 650);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=735 && x<=835 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, '/', pozitieCursor);
            animatieClick(735, 545, 835, 595);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        //////////////////////////////////////////////
        else if ((x>=840 && x<=940 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 't', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'g', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);

            animatieClick(840, 710, 940, 760);
            numarCaractereButon=3+2;
            scade=1;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=840 && x<=940 && y>=655 && y<=705))
        {
            memoreazaCaracterIntrodus(intrare, 't', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'g', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;
            animatieClick(840, 655, 940, 705);
            numarCaractereButon=4;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=840 && x<=940 && y>=600 && y<=650))
        {
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'o', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 's', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;
            animatieClick(840, 600, 940, 650);
            numarCaractereButon=3+2;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=840 && x<=940 && y>=545 && y<=595))
        {
            memoreazaCaracterIntrodus(intrare, 's', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'i', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'n', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;
            animatieClick(840, 545, 940, 595);
            numarCaractereButon=3+2;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        ////////////////////////////////////////////
        else if ((x>=945 && x<=1045 && y>=710 && y<=760))
        {
            memoreazaCaracterIntrodus(intrare, 'a', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'r', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 't', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'g', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;
            animatieClick(945, 710, 1045, 760);
            numarCaractereButon=6+2;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=945 && x<=1045 && y>=655 && y<=705))
        {
            animatieClick(945, 655, 1045, 705);
            memoreazaCaracterIntrodus(intrare, 'a', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'r', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 't', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'g', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;

            numarCaractereButon=5+2;
            numarClickuriPeSageataFunctieIntrodusa=0;

        }
        else if ((x>=945 && x<=1045 && y>=600 && y<=650))
        {
            animatieClick(945, 600, 1045, 650);
            memoreazaCaracterIntrodus(intrare, 'a', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'r', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'o', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 's', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;

            numarCaractereButon=6+2;
            numarClickuriPeSageataFunctieIntrodusa=0;

        }
        else if ((x>=945 && x<=1045 && y>=545 && y<=595))
        {
            animatieClick(945, 545, 1045, 595);
            memoreazaCaracterIntrodus(intrare, 'a', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'r', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'c', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 's', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'i', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'n', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;

            numarCaractereButon=6+2;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        ////////////////////////////////////////////////
        else if ((x>=1050 && x<=1150 && y>=710 && y<=760))
        {
            animatieClick(1050, 710, 1150, 760);
            memoreazaCaracterIntrodus(intrare, 'x', pozitieCursor);
            numarCaractereButon=1;
            numarClickuriPeSageataFunctieIntrodusa=0;

        }
        else if ((x>=1050 && x<=1150 && y>=655 && y<=705))
        {
            animatieClick(1050, 655, 1150, 705);
            memoreazaCaracterIntrodus(intrare, 's', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'q', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'r', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 't', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;


            numarCaractereButon=4+2;
            numarClickuriPeSageataFunctieIntrodusa=0;

        }
        else if ((x>=1050 && x<=1150 && y>=600 && y<=650))
        {
            animatieClick(1050, 600, 1150, 650);
            memoreazaCaracterIntrodus(intrare, 'l', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'o', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'g', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ',', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=2;


            numarCaractereButon=3+3;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        else if ((x>=1050 && x<=1150 && y>=545 && y<=595))
        {
            animatieClick(1050, 545, 1150, 595);
            memoreazaCaracterIntrodus(intrare, 'l', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, 'n', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, '(', pozitieCursor);
            memoreazaCaracterIntrodus(intrare, ')', pozitieCursor);
            scade=1;
            numarCaractereButon=2+2;
            numarClickuriPeSageataFunctieIntrodusa=0;
        }
        /// butoanele de la ordinul derivatei
        else if ((x>=1203 && x<=1224 && y>=482 && y<=494))
        {
            setcolor(0);
            settextstyle(8, 0, 3);
            if (ordin<4)
            {
                ordin++;
                b[0] = (char)(ordin + 48);
                i = &b[0];

            }
            outtextxy(spatiuXORD, spatiuYORD, i);
        }
        else if ((x>=1203 && x<=1224 && y>=496 && y<=508))
        {
            setcolor(0);
            settextstyle(8, 0, 3);
            if (ordin>1)
            {
                ordin--;
                b[0] = (char)(ordin + 48);
                i = &b[0];
            }
            outtextxy(spatiuXORD, spatiuYORD, i);
        }
        /// cursor
        else if(x>=90 && x<=990 && y>=480 && y<=510)
        {
            int j;
            for(j=90; j<=990 && numarCaractereButon==0; j=j+20)
                if(x>=j && x<=j+20)
                {
                    if(anteriorCursor*20+100<j || anteriorCursor*20+100>j+20)
                    {
                        if(anteriorCursor*20+100<x)
                        {

                            int c1=pozitieCursor, c2=anteriorCursor;

                            pozitieCursor=pozitieCursor+abs(anteriorCursor-(j-90)/20);
                            anteriorCursor=(j-90)/20-1;

                            if(intrare[pozitieCursor-1]!=NULL) numarCaractereButon=1;
                            else
                            {
                                ///cazul pentru click in spatiul neocupat de un caracter
                                if(c1==c2 && c1==strlen(intrare)) ///daca cele doua sunt egale si cursorul deja se afla la finalul sirului
                                {
                                    pozitieCursor=anteriorCursor=strlen(intrare); /// sau=c1;
                                }
                                else
                                {
                                    pozitieCursor=strlen(intrare);
                                    anteriorCursor=strlen(intrare)-1;
                                }

                                numarCaractereButon=1;
                            }
                        }
                        else
                        {
                            pozitieCursor=pozitieCursor-abs(anteriorCursor-(j-90)/20);
                            anteriorCursor=(j-90)/20+1;
                            numarCaractereButon=1;
                        }

                    }
                    else break;

                }

        }
        /// sterge tot sirul
        else if(x>=1439 && x<=1501 && y>=484 && y<=509)
        {
            if(pozitieCursor==0) cout<<char(7);

            pozitieCursor=0;
            pozitiePAnt=1;
            anteriorCursor=0;
            anterior=0;
            numarCaractereButon=1;
            stergeSir(intrare);
            setcolor(15);

            animatieButonStergere();
            functiaEsteDerivata=0;

            setcolor(0);
            settextstyle(8, 0, 3);
            ordin=1;
            b[0] = (char)(ordin + 48);
            i = &b[0];
            outtextxy(spatiuXORD, spatiuYORD, i);
            numarClickuriPeSageataFunctieIntrodusa=0;
            numarClickuriPeSageataFunctieDerivata=0;
            setcolor(15);
            deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 162, 130,  130, 162, 162, 130, 130, 162);
            setcolor(0);
            settextstyle(8, 0, 4);
            outtextxy(85, 370, "                                                                    ");

        }
        else if (x>=1443 && x<=1487 && y>=618 && y<=657) /// informatii aplicatie
        {
            informatii(limba);
        }
        else if (x>=1444 && x<=1486 && y>=568 && y<=605) ///setari
        {
            setariLimba(limba);
            limbaFundal(intrare,limba,ordin);
            numarCaractereButon=1;
        }
        else if (x>=34 && x<=68 && y>=476 && y<=512) ///citirea din fisiere
        {
            animatieSimbolFoaie(35, 35, 61, 61,52, 52, 476, 512, 512, 484, 476, 484);
            setcolor(WHITE);
            line(61, 501, 61, 497);
            fileDinCalculator(intrare);
            numarCaractereButon=1;
        }
        else if (x>=1474 && x<=1504 && y>=292 && y<=332) ///salvare in fisiere
        {
            animatieSimbolFoaie(1474, 1474, 1504, 1504, 1494, 1494, 294, 333, 333, 303, 294, 303); ///salvare
            setcolor(WHITE);
            line(1474, 323, 1474, 321);
            line(1474, 318, 1474, 316);
            salveazaFileInCalculator(rezultat, ordin, limba, intrare); ///cand salvez fisierul trebuie neaparat pusa extensia .txt la numele fisierului
        }
        ///buton fereastra arbore
        else if(x>=1427 && x<=1459 && y>=293&& y<=332)
        {
            animatieSimbolFoaie(1428, 1428, 1458, 1458, 1448, 1448, 294, 333, 333, 303, 294, 303);


            if(functiaEsteDerivata==1)
            {
                arborizeazaRezultat(rezultat, arboreD);
                simplificaZero(arboreD);

                if(*limba==1)
                    fereastraArbore(arboreD, "Arborele asociat functiei derivate");
                else
                    fereastraArbore(arboreD, "The tree of the derivated function");
            }
            else cout<<char(7); ///sunet
        }
        else if (x >=1254 && x<=1375 && y>=475 && y<=514) ///deriveaza
        {
            if(functiaPoateFiDerivata==1)
            {
                setcolor(15);
                settextstyle(8, 0, 4);
                outtextxy(85, 370, "                                                                                   ");
                deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 402, 370,  370, 402, 402, 370, 370, 402);
                animatieButonDeivata();
                afisareFunctieDerivata(arboreD, intrare, rezultat, ordin, functiaEsteDerivata);
                numarClickuriPeSageataFunctieDerivata=0;
            }
            else cout<<char(7);///sunet
        }
        else if(x>=1449 && x<=1482 && y>=130 && y<=162 && strlen(intrare)>68) ///click pe sageata din dreapta de la functia introdusa
        {

            if(strlen(intrare+numarClickuriPeSageataFunctieIntrodusa)-68>0)
            {
                numarClickuriPeSageataFunctieIntrodusa++;
                animatieButonSageata(1449, 1449, 1482, 1482, 162, 130, 130, 162, 0);

            }
            else cout<<char(7);///sunet

        }
        else if(x>=44 && x<=77 && y>=130 && y<=162 && strlen(intrare)>68) ///click pe sageata din stanga de la functia introdusa
        {
            if(numarClickuriPeSageataFunctieIntrodusa>0)
            {
                numarClickuriPeSageataFunctieIntrodusa--;
                animatieButonSageata(44, 44, 77, 77, 162, 130, 130, 162, 1);

            }
            else cout<<char(7);

        }

        else if(x>=44 && x<=77 && y>=370 && y<=402 && strlen(rezultat)>68 && functiaEsteDerivata==1) ///buton click derivata derivata  stanga
        {

            if(numarClickuriPeSageataFunctieDerivata>0)
            {
                numarClickuriPeSageataFunctieDerivata--;
                animatieButonSageata(44, 44, 77, 77, 402, 370, 370, 402, 1);

            }
            else cout<<char(7);

        }
        else if(x>=1449 && x<=1482 && y>=370 && y<=402 && strlen(rezultat)>68 && functiaEsteDerivata==1) ///click pe sageata din dreapta de la functia introdusa
        {

            if(strlen(rezultat+numarClickuriPeSageataFunctieDerivata)-68>0)
            {
                numarClickuriPeSageataFunctieDerivata++;
                animatieButonSageata(1449, 1449, 1482, 1482, 402, 370, 370, 402, 0);
            }
            else cout<<char(7);
        }
        else if(x>=1 && x<=1534 && y>=77 && y<=226) ///click pe greseli
        {
            greseliClick(x, y, intrare, numarClickuriPeSageataFunctieIntrodusa, limba);
            esteClickPeFunctie=1;
        }

        while(numarCaractereButon>0)
        {
            char aux[NN]="";
            setbkcolor(15);
            setcolor(0);
            settextstyle(8, 0, 4);
            outtextxy(100, 480, "                                            ");

            if(anterior>pozitieCursor)
            {
                if(anteriorCursor!=0)
                {
                    anteriorCursor--;
                }
                else
                {
                    pozitiePAnt--;
                }

                strcpy(aux, intrare+pozitiePAnt);
                int numereCaractereDupaBara=strlen(aux+42);
                aux[0]=0;

                if(int(tasta)==8 && strlen(intrare)>=1)
                {

                    if(numereCaractereDupaBara>0)
                    {
                        strcpy(aux, intrare+pozitiePAnt-1);
                    }
                    else
                    {
                        strcpy(aux, intrare+max(0,pozitiePAnt-2));
                        if(max(0,pozitiePAnt-2)==0) pozitiePAnt=1;
                        else pozitiePAnt--;
                    }

                }

                else strcpy(aux, intrare+pozitiePAnt-1);

                aux[44]=0;
                outtextxy(100, 480, aux);

                if(int(tasta)==8 && strlen(intrare)>=1)
                {

                    if(numereCaractereDupaBara>0)
                    {
                        deseneazaCursor(anteriorCursor, 4);
                    }
                    else
                    {
                        if(strlen(intrare)>44)
                        {
                            deseneazaCursor(anteriorCursor+1, 4);
                            anteriorCursor++;
                        }
                        else
                        {
                            deseneazaCursor(pozitieCursor, 4);
                            anteriorCursor=pozitieCursor;
                        }

                    }


                }
                else deseneazaCursor(anteriorCursor, 4);


            }
            else if(anterior<pozitieCursor)
            {
                if(anteriorCursor!=44)
                {
                    anteriorCursor++;
                }
                else
                {
                    pozitiePAnt++;
                }
                strcpy(aux, intrare+pozitiePAnt-1);
                aux[44]=0;
                outtextxy(100, 480, aux);
                deseneazaCursor(anteriorCursor, 4);
            }
            else if(anterior==pozitieCursor)
            {
                strcpy(aux, intrare+pozitiePAnt-1);
                aux[44]=0;
                outtextxy(100, 480, aux);
                deseneazaCursor(anteriorCursor, 4);
            }

            numarCaractereButon--;
        }

        if(scade>0)
        {
            char aux[NN]="";
            setbkcolor(15);
            setcolor(0);
            settextstyle(8, 0, 4);
            outtextxy(100, 480, "                                            ");
            pozitieCursor-=scade;
            anteriorCursor-=scade;
            strcpy(aux, intrare+pozitiePAnt-1);
            aux[44]=0;
            outtextxy(100, 480, aux);
            deseneazaCursor(anteriorCursor, 4);
        }


        if(esteClickPeFunctie==0)
        {
            if(strlen(intrare)>0)
            {
                prelucrareFunctieIntrodusa(intrare, functiaPoateFiDerivata, numarClickuriPeSageataFunctieIntrodusa, limba);
            }
            else if(strlen(intrare)==0)
            {
                settextstyle(8, 0, 4);
                outtextxy(85, 130, "                                                                    ");
                outtextxy(189, 25, "                               ");
                outtextxy(189, 72, "                                                         ");
                functiaPoateFiDerivata=0;
            }
        }

        if(functiaEsteDerivata==1)
        {
            setcolor(0);
            settextstyle(8, 0, 4);
            outtextxy(85, 370, "                                                                    ");

            if(strlen(rezultat)>68)
            {
                char ceSeAfiseaza[NN]="";
                strcpy(ceSeAfiseaza, rezultat+numarClickuriPeSageataFunctieDerivata);
                ceSeAfiseaza[68]=0;
                outtextxy(85, 370, ceSeAfiseaza);
                setcolor(7);
                deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 402, 370,  370, 402, 402, 370, 370, 402);
            }
            else
            {
                outtextxy(85, 370, rezultat);
            }

        }
        else
        {
            setcolor(15);
            settextstyle(8, 0, 4);
            outtextxy(85, 370, "                                                                    ");
            deseneazaButoaneSageti(44, 44, 77, 77, 1449, 1449, 1482, 1482, 402, 370,  370, 402, 402, 370, 370, 402);

        }

    }
}


int main()
{
    initwindow(1535,800, "Deriv");

    int x, y;
    int l=1;
    int *limba=&l;
    readimagefile("FundalRO.jpg", 0, 0, 1535, 800);

    deseneazaButoaneTastatura();
    afiseazaTextButoane(limba);

    getch();
    closegraph();
    return 0;
}
