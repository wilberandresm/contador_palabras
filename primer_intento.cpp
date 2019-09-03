#include <omp.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>

//Wilber Cajamarca
//GIOVANNI LUIS PALENCIA
using namespace std;

int main()
{
    ifstream ifs;
    ifs.open("texto.txt");
    int lineas=0; //contador de lineas inicializado en cero
    string aux;
    vector<string> vector; //el texto lo manejaremos por vectores para utilizar las lineas
                            //y distribuirlas a cada hilo
    while(getline(ifs,aux)){
        lineas=lineas+1;
        vector.push_back(aux);

    }
    int tid; //id del hilo
    int palabras=0;//contador de las palabras


    #pragma omp parallel private(tid) reduction(+:palabras)
    {
        int nucleos=omp_get_num_threads();
        int x;//variable que almcenara la cantidad de lineas que tomará cada hilo
        x=lineas/nucleos;//funcion que me retorna el numero de nucleo que maneja mi dispositivo
        tid=omp_get_thread_num();//identificador del hilo
        int partes=x*(tid+1);//delimitación de las partes para cada hilo

        if(tid==(nucleos-1)){
            partes=lineas;
        }
        bool espacio=true; //verificacion de que despues de un espacio halla una palabra y no otro espacio
        for (int i=x*tid;i<partes;i++){
            espacio=true;
            for(int j=0;j<vector[i].size();j++){
                if(vector[i][j]== ' '){ //verificacion de los espacios
                    espacio=true;
                }else{
                    if(espacio){
                        palabras=palabras+1;
                    }
                    espacio=false;
                }
            }
        }
    }
    cout<<"la cantidad de palabras en el texto es : "<<palabras<<endl;
}
