#include "iostream"
using namespace std;

void ScenarioExecute( int escenario){
    if(escenario == 1){

    }
    else if(escenario == 2){
        
    }
}

void Simulation(){

    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    while(ticks < 720){
        ticks++;
        
    }

}

int main(){
    cout << "Para escoger el escenario escribe 1, para importar tus propios datos escribe 2" << endl;
    int res;
    cin >> res;
    if(res == 1){
        cout << "Escoge uno de los 2 escenarios" << endl << "1.3 cajeros con colas individuales" << endl << "2.3 cajeros con colas individuales pero los clientes pueden cambiar de cola despues de estar 15 minutos en una" << endl;
        int escenario;
        cin >> escenario;
        ScenarioExecute(escenario);
    }
    else if(res == 2){
        
    }
}

