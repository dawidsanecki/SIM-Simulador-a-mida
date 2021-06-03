#include "iostream"
using namespace std;

void Simulation(){

    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    while(ticks < 720){
        ticks++;

    }

}

void ScenarioExecute(){
    int escenario;
    cout << "Escoge uno de los 2 escenarios" << endl << "1.3 cajeros con colas individuales" << endl << "2.3 cajeros con colas individuales pero los clientes pueden cambiar de cola despues de estar 15 minutos en una" << endl;
    cin >> escenario;
    if(escenario == 1){
        Simulation();
    }
    else if(escenario == 2){
        Simulation();
    }
}

void DataImport(){
    cout << "Introduce los siguientes datos para tu simulación" << endl;
    cout << "El valor de la X" << endl;
    int X;
    cin >> X;
    cout << "El valor de la Y" << endl;
    int Y;
    cin >> Y;
}

int main(){
    cout << "Para escoger el escenario escribe 1, para importar tus propios datos escribe 2" << endl;
    int res;
    cin >> res;
    if(res == 1){
        ScenarioExecute();
    }
    else if(res == 2){
        DataImport();
    }
}

