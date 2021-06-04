#include "iostream"
#include "vector"
#include "list"
using namespace std;


//Clase cliente
class Cliente {

    int TiempoSalida;
public:
    int TiempoEntrada;
    void SetTiempoEntrada(int ticks){
        TiempoEntrada = ticks;
    }
    void GuardarTiempoSalida(int ticks) {
        TiempoSalida = ticks - TiempoEntrada;
    }
    int GetTiempoSalida(){
        return TiempoSalida;
    }
    bool WantsChange(int ticks,int tiempoEspera){
        if(ticks - TiempoEntrada >= tiempoEspera) return true;
        else return false;
    }
};

class Cajero {

public:
    vector<Cliente> cola;
    Cliente actual;
    bool ocupado = false;
    int TiempoRestante = 0;

    bool GetOcupado(){
        return ocupado;
    }
    void switchOcupado(){
        if(!ocupado) ocupado = true;
        else ocupado = false;
    }

    void setTiempoRestante(int tiempo){
        TiempoRestante = tiempo;
    }
    int getTiempoRestante(){
        return TiempoRestante;
    }

    void setClienteActual(Cliente c){
        actual = c;
    }
    Cliente getClienteActual(){
        return actual;
    }

    Cliente getClienteI(int i){
        return cola[i];
    }

    void restarTiempoRestante(){
        --TiempoRestante;
    }

    void EntrarCola(Cliente c){
        cola.push_back(c);
    }

    void SalirCola(){
        cout << cola.size() << endl;
        cola.erase(cola.begin());

    }

    Cliente getPrimero(){
        return cola[0];
    }

    void CambiarCola(Cajero &CajeroDestino,int PosCliente){
        Cliente c = cola[PosCliente];
        cola.erase(cola.begin()+PosCliente);
        CajeroDestino.EntrarCola(c);
    }

    int GetLength(){
        return cola.size();
    }
};
//Si offset es igual a 0 es el caso de que se escoge la cola sin estar en una, si offset es diferente se hace el caso de cambiar de cola
int CompararColas(Cajero &c1, Cajero &c2, Cajero &c3,int offset){
    cout << "im here" << endl;
    int cl1 = c1.GetLength();
    int cl2 = c2.GetLength();
    int cl3 = c3.GetLength();
    cout << cl1 << " " << cl2 << " " << cl3 << " " << offset << endl;
    //3 colas iguales

    if(cl1-offset == cl2 and cl2 == cl3 and offset == 0){
        int numr = rand() % 3;
        if(numr == 0) return 1;
        else if(numr == 1) return 2;
        else return 3;
    }
    //2 colas iguales
    else if(cl1-offset == cl2 && cl1-offset < cl3 and offset == 0){
        int numr = rand() % 2;
        if(numr == 0) return 1;
        else return 2;
    }

    else if(cl1-offset == cl2 && cl1-offset < cl3 and offset != 0){
        return 1;
    }
    else if(cl1-offset == cl2 && cl1-offset > cl3) return 3;

    else if(cl1-offset == cl3 && cl1-offset < cl2 and offset == 0){
        int numr = rand() % 2;
        if(numr == 0) return 1;
        else return 3;
    }

    else if(cl1-offset == cl3 && cl1-offset < cl2 and offset != 0){
        return 1;
    }
    else if(cl1-offset == cl3 && cl1-offset > cl2) return 2;

    else if(cl2 == cl3 && cl1-offset > cl2){
        int numr = rand() % 2;
        if(numr == 0) return 2;
        else return 3;
    }
    else if(cl2 == cl3 && cl1-offset < cl2) return 1;

    //3 cola diferentes
    else if(cl1-offset < cl2 && cl1-offset < cl3) return 1;
    else if(cl2 < cl3 && cl2 < cl1-offset) return 2;
    else if(cl3 < cl1-offset && cl3 < cl2) return 3;
    return 1;

}



void SimulationWithoutChange(int IntervalLLegada, int Seed){
    srand(Seed);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int offset = 8;
    cout << "entrada while" << endl;
    while(ticks < 60){
        //Entrada nuevo cliente cada intervalo
        if(ticks % IntervalLLegada == 0){
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = CompararColas(c1,c2,c3,0);
            if(colaD == 1){
                c1.EntrarCola(c);
                cout << "entrado a 1" << endl;
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
                cout << "entrado a 2" << endl;
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
                cout << "entrado a 3" << endl;
            }

        }
        //Scan colas
        //Cola 1
        //Si el cajero esta ocupado restamos el tiempo restante
        if(c1.GetOcupado()){
            if(c1.getTiempoRestante() == 0 && c1.GetLength() > 0) {
                c1.switchOcupado();
                Cliente caux = c1.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);

                c1.SalirCola();

                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((rand() % 5) + offset);
                }

            }
        }
        //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((rand() % 5) + 1);
            c1.switchOcupado();
        }
        c1.restarTiempoRestante();

        //Cola 2
        if(c2.GetOcupado()){
            if(c2.getTiempoRestante() == 0 && c2.GetLength() > 0) {
                c2.switchOcupado();
                Cliente caux = c2.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c2.SalirCola();

                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((rand() % 5) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((rand() % 5) + offset);
            c2.switchOcupado();
        }
        c2.restarTiempoRestante();
        //Cola 3
        if(c3.GetOcupado()){
            if(c3.getTiempoRestante() == 0 && c3.GetLength() > 0) {

                c3.switchOcupado();
                Cliente caux = c3.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c3.SalirCola();
                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((rand() % 5) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((rand() % 5) + offset);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    cout << "while finalizado" << endl;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        cout << ClientesSalida[i].GetTiempoSalida() << endl;
    }

}

void SimulationWithChange(int IntervalLLegada,int MinutosHastaCambio, double ProbabilidadDeCambio, int Seed){
    srand(Seed);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int offset = 30;
    int offset2 = 20;
    cout << "entrada while" << endl;
    while(ticks < 180){

        //Mirar el resto de la cua
        //Cola 1

        bool NoCambio = false;
        if(c1.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c1.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c1.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c1.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 1" << endl;
                    int colaD = CompararColas(c1,c2,c3,c1.GetLength()-i);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 2" << endl;
                            c1.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c1.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 2
        NoCambio = false;
        if(c2.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c2.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c2.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c2.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 2" << endl;
                    int colaD = CompararColas(c2,c1,c3,c2.GetLength()-i);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 1" << endl;
                            c2.CambiarCola(c1,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c2.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 3
        NoCambio = false;
        if(c3.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c3.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c3.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c3.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 3" << endl;
                    int colaD = CompararColas(c3,c2,c1,c3.GetLength()-i);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 2" << endl;
                            c3.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c3.CambiarCola(c1,i);
                        }
                    }
                }
            }
        }
        //Entrada nuevo cliente cada intervalo
        if(ticks % IntervalLLegada == 0){
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = CompararColas(c1,c2,c3,0);
            if(colaD == 1){
                c1.EntrarCola(c);
                cout << "entrado a 1" << endl;
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
                cout << "entrado a 2" << endl;
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
                cout << "entrado a 3" << endl;
            }

        }
        //Scan colas
        //Cola 1
        //Si el cajero esta ocupado restamos el tiempo restante
        if(c1.GetOcupado()){
            if(c1.getTiempoRestante() == 0 && c1.GetLength() > 0) {
                c1.switchOcupado();
                Cliente caux = c1.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);

                c1.SalirCola();

                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((rand() % 20) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((rand() % 20) + offset);
            c1.switchOcupado();
        }
        c1.restarTiempoRestante();

        //Cola 2
        if(c2.GetOcupado()){
            if(c2.getTiempoRestante() == 0 && c2.GetLength() > 0) {
                c2.switchOcupado();
                Cliente caux = c2.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c2.SalirCola();

                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((rand() % 20 + offset));
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((rand() % 20) + offset);
            c2.switchOcupado();
        }
        c2.restarTiempoRestante();
        //Cola 3
        if(c3.GetOcupado()){
            if(c3.getTiempoRestante() == 0 && c3.GetLength() > 0) {

                c3.switchOcupado();
                Cliente caux = c3.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c3.SalirCola();
                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((rand() % 20) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((rand() % 20) + offset);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    cout << "while finalizado" << endl;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        cout << ClientesSalida[i].GetTiempoSalida() << endl;
    }

}

void SimulationWithChangeAndRandomChoice(int IntervalLLegada,int MinutosHastaCambio, double ProbabilidadDeCambio, int Seed){
    srand(Seed);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int offset = 50;
    int offset2 = 20;
    cout << "entrada while" << endl;
    while(ticks < 180){

        //Mirar el resto de la cua
        //Cola 1

        bool NoCambio = false;
        if(c1.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c1.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c1.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c1.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 1" << endl;
                    int colaD = CompararColas(c1,c2,c3,c1.GetLength()-i);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 2" << endl;
                            c1.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c1.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 2
        NoCambio = false;
        if(c2.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c2.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c2.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c2.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 2" << endl;
                    int colaD = CompararColas(c2,c1,c3,c2.GetLength()-i);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 1" << endl;
                            c2.CambiarCola(c1,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c2.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 3
        NoCambio = false;
        if(c3.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c3.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c3.getClienteI(i);
                if(aux.WantsChange(ticks,IntervalLLegada)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c3.GetLength()-1; i > 0 and !NoCambio;--i){
                if(clientesCambiar[i] and rand() % 100 <= ProbabilidadDeCambio*100){ //si quiere cambiarse
                    cout << "Quiero cambiarme de la cola 3" << endl;
                    int colaD = CompararColas(c3,c2,c1,c3.GetLength()-i-1);
                    cout << colaD << endl;
                    if(colaD == 1) NoCambio = true;
                    if(colaD != 1){
                        if(colaD == 2){
                            cout << "Me cambio a cola 2" << endl;
                            c3.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            cout << "Me cambio a cola 3" << endl;
                            c3.CambiarCola(c1,i);
                        }
                    }
                }
            }
        }
        //Entrada nuevo cliente cada intervalo
        if(ticks % IntervalLLegada == 0){
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = rand() % 3 + 1;
            if(colaD == 1){
                c1.EntrarCola(c);
                cout << "entrado a 1" << endl;
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
                cout << "entrado a 2" << endl;
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
                cout << "entrado a 3" << endl;
            }

        }
        //Scan colas
        //Cola 1
        //Si el cajero esta ocupado restamos el tiempo restante
        if(c1.GetOcupado()){
            if(c1.getTiempoRestante() == 0 && c1.GetLength() > 0) {
                c1.switchOcupado();
                Cliente caux = c1.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);

                c1.SalirCola();

                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((rand() % 20) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((rand() % 20) + offset);
            c1.switchOcupado();
        }
        c1.restarTiempoRestante();

        //Cola 2
        if(c2.GetOcupado()){
            if(c2.getTiempoRestante() == 0 && c2.GetLength() > 0) {
                c2.switchOcupado();
                Cliente caux = c2.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c2.SalirCola();

                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((rand() % 20 + offset));
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((rand() % 20) + offset);
            c2.switchOcupado();
        }
        c2.restarTiempoRestante();
        //Cola 3
        if(c3.GetOcupado()){
            if(c3.getTiempoRestante() == 0 && c3.GetLength() > 0) {

                c3.switchOcupado();
                Cliente caux = c3.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c3.SalirCola();
                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((rand() % 20) + offset);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((rand() % 20) + offset);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    cout << "while finalizado" << endl;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        cout << ClientesSalida[i].GetTiempoSalida() << endl;
    }

}

void ScenarioExecute(){
    int escenario;
    cout << "Escoge uno de los 2 escenarios" << endl << "1.3 cajeros con colas individuales" << endl << "2.3 cajeros con colas individuales pero los clientes pueden cambiar de cola despues de estar 15 minutos en una" << endl;
    cout << "3.Los clientes se cambian de fila pero escogen el cajero aleatoriamente al inicio" << endl;

    cin >> escenario;
    if(escenario == 1){
        SimulationWithoutChange(4,123456);
    }
    else if(escenario == 2){
        SimulationWithChange(4,15,0.15,123421111);
    }

    else if(escenario == 3){
        SimulationWithChangeAndRandomChoice(4,15,0.15,696969);
    }

}

void DataImport(){
    cout << "Introduce los siguientes datos para tu simulación" << endl;
    cout << "Quieres que los clientes puedan cambiar de cola despues de un tiempo?" << endl << "[y/n]" << endl;
    string ans;
    cin >> ans;
    if(ans == "y"){
        cout << "Cuantos minutos quieres que los clientes se esperan antes de cambiar de cola?" << endl;
        int TiempoCambio;
        cin >> TiempoCambio;
        cout << "Que probabilidad de cambio quieres asignar? (0 - 1)" << endl;
        double ProbabilidadCambio;
        cin >> ProbabilidadCambio;
        cout << "Cada cuantos minutos llega una persona" << endl;
        int IntervalLlegada;
        cin >> IntervalLlegada;
        cout << "Indica un seed para la simulación" << endl;
        int s;
        cin >> s;

        SimulationWithChange( IntervalLlegada,TiempoCambio, ProbabilidadCambio,s);
    }
    else if(ans == "n"){
        cout << "Cada cuantos minutos llega una persona" << endl;
        int IntervalLlegada;
        cin >> IntervalLlegada;
        cout << "Indica un seed para la simulación" << endl;
        int s;
        cin >> s;
        SimulationWithoutChange(IntervalLlegada,s);
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

