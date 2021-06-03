#include "iostream"
using namespace std;

void SimulationWithoutChange(){

    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    while(ticks < 720){
        ticks++;

    }

}

void SimulationWithChange(int MinutosHastaCambio, double ProbabilidadDeCambio){

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
        SimulationWithoutChange();
    }
    else if(escenario == 2){
        SimulationWithChange();
    }
}

void DataImport(){
    cout << "Introduce los siguientes datos para tu simulación" << endl;
    cout << "Quieres que los clientes puedan cambiar de cola despues de un tiempo?" << endl << "[y/n]" << endl;
    string ans;
    if(ans == "y"){
        cout << "Cuantos minutos quieres que los clientes se esperan antes de cambiar de cola?" << endl;
        int TiempoCambio;
        cin >> TiempoCambio;
        cout << "Que probabilidad de cambio quieres asignar? (0 - 1)" << endl;
        double ProbabilidadCambio;
        cin >> ProbabilidadCambio;
        SimulationWithChange(TiempoCambio, ProbabilidadCambio);
    }
    else if(ans == "n"){
        SimulationWithoutChange();
    }
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

