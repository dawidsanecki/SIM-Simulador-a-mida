#include "iostream"
#include "vector"
#include "list"
using namespace std;


//Clase cliente
class Cliente {
    int TiempoEntrada;
    int TiempoSalida;
public:

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

    void restarTiempoRestante(){
        --TiempoRestante;
    }

    void EntrarCola(Cliente c){
        cola.push_back(c);
    }

    void SalirCola(){
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

int CompararColas(Cajero &c1, Cajero &c2, Cajero &c3){
    int cl1 = c1.GetLength();
    int cl2 = c2.GetLength();
    int cl3 = c3.GetLength();
    cout << cl1 << " " << cl2 << " " << cl3 << endl;
    //3 colas iguales
    if(cl1 == cl2 and cl2 == cl3){
        int numr = rand() % 3;
        if(numr == 0) return 1;
        else if(numr == 1) return 2;
        else return 3;
    }
    //2 colas iguales
    else if(cl1 == cl2 && cl1 < cl3){
        int numr = rand() % 2;
        if(numr == 0) return 1;
        else return 2;
    }
    else if(cl1 == cl2 && cl1 > cl3) return 3;

    else if(cl1 == cl3 && cl1 < cl2){
        int numr = rand() % 2;
        if(numr == 0) return 1;
        else return 3;
    }
    else if(cl1 == cl3 && cl1 > cl2) return 2;

    else if(cl2 == cl3 && cl1 > cl2){
        int numr = rand() % 2;
        if(numr == 0) return 2;
        else return 3;
    }
    else if(cl2 == cl3 && cl1 < cl2) return 1;

    //3 cola diferentes
    else if(cl1 < cl2 && cl1 < cl3) return 1;
    else if(cl2 < cl3 && cl2 < cl1) return 2;
    else if(cl3 < cl1 && cl3 < cl2) return 3;
    return 1;

}

void SimulationWithoutChange(int IntervalLLegada, int SeedCajero1, int SeedCajero2, int SeedCajero3){

    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int offset = 20;
    while(ticks < 60){
        //Entrada nuevo cliente cada intervalo
        if(ticks % IntervalLLegada == 0){
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = CompararColas(c1,c2,c3);
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
            if(c1.getTiempoRestante() == 0) {
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
            c1.setTiempoRestante((rand() % 5) + offset);
            c1.switchOcupado();
        }
        c1.restarTiempoRestante();

        //Cola 2
        if(c2.GetOcupado()){
            if(c2.getTiempoRestante() == 0) {
                c2.switchOcupado();
                Cliente caux = c2.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c1.SalirCola();
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
            if(c3.getTiempoRestante() == 0) {
                c3.switchOcupado();
                Cliente caux = c3.getClienteActual();
                caux.GuardarTiempoSalida(ticks);
                ClientesSalida.push_back(caux);
                c1.SalirCola();
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

    for (int i = 0; i < ClientesSalida.size(); ++i){
        cout << ClientesSalida[i].GetTiempoSalida() << endl;
    }

}

void SimulationWithChange(int IntervalLLegada,int MinutosHastaCambio, double ProbabilidadDeCambio, int SeedCajero1, int SeedCajero2, int SeedCajero3){

    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    while(ticks < 720){
        ticks++;

    }

}

void ScenarioExecute(){
    int escenario;
    cout << "Escoge uno de los 2 escenarios" << endl << "1.3 cajeros con colas individuales" << endl << "2.3 cajeros con colas individuales pero los clientes pueden cambiar de cola despues de estar 15 minutos en una" << endl;
    cin >> escenario;
    if(escenario == 1){
        SimulationWithoutChange(3,5234,234234,25332);
    }
    else if(escenario == 2){
        SimulationWithChange(8,15,0.15,23423,9035,8394);
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
        cout << "Cada cuantos minutos llega una persona" << endl;
        int IntervalLlegada;
        cin >> IntervalLlegada;
        cout << "Indica un seed para el cajero 1 (numero entero)" << endl;
        int s1;
        cin >> s1;
        cout << "Indica un seed para el cajero 2 (numero entero)" << endl;
        int s2;
        cin >> s2;
        cout << "Indica un seed para el cajero 3 (numero entero)" << endl;
        int s3;
        cin >> s3;
        SimulationWithChange( IntervalLlegada,TiempoCambio, ProbabilidadCambio,s1,s2,s3);
    }
    else if(ans == "n"){
        cout << "Cada cuantos minutos llega una persona" << endl;
        int IntervalLlegada;
        cin >> IntervalLlegada;
        cout << "Indica un seed para el cajero 1 (numero entero)" << endl;
        int s1;
        cin >> s1;
        cout << "Indica un seed para el cajero 2 (numero entero)" << endl;
        int s2;
        cin >> s2;
        cout << "Indica un seed para el cajero 3 (numero entero)" << endl;
        int s3;
        cin >> s3;


        SimulationWithoutChange(IntervalLlegada,s1,s2,s3);
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

