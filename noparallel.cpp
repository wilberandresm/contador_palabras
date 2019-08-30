#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  char palabra[128];
  int count=0;
  ifstream file1;
  file1.open("text.txt");

  if(file1.fail())
    cout << "Error al abrir el archivo" << endl;

  while(!file1.eof())
  {
   file1>>palabra;
   count+=1;
  }

  cout << "Cantidad de palabras " << count;
}
