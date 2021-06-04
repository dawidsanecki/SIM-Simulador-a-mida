#include "iostream"
#include "vector"
#include <iterator>
#include <random>
#include <fstream>
#include "Cajero.h"
using namespace std;

//Si offset es igual a 0 es el caso de que se escoge la cola sin estar en una, si offset es diferente se hace el caso de cambiar de cola
int CompararColas(Cajero &c1, Cajero &c2, Cajero &c3,int offset,int seed){
    srand(seed);
    int cl1 = c1.GetLength();
    int cl2 = c2.GetLength();
    int cl3 = c3.GetLength();
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

vector<bool> ArrivalTime(int IntervalLlegada,int Seed,int ticks_max){
    random_device rd;

    mt19937 randomN (Seed);
    double lamda = 1 / double(IntervalLlegada);
    exponential_distribution<double> exp (lamda);

    int sumTimes=0;
    double newTime;
    vector<bool> ArrivalInterval(ticks_max,false);
    bool primera_vez = true;

    for(int i = 0; sumTimes < ticks_max; ++i){

        if(!primera_vez){
            ArrivalInterval[sumTimes] = true;
        }

        newTime = exp.operator() (randomN); //Genera el siguiente numero de la distribución
        int IntTime = newTime;

        sumTimes = sumTimes + IntTime;
        primera_vez = false;
    }



    return ArrivalInterval;
}

void SimulationWithoutChange(int IntervalLLegada, int Seed,int tick_max, double AverageServiceTime){
    srand(Seed);
    vector<bool> Arrival = ArrivalTime(IntervalLLegada,Seed,tick_max);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    mt19937 randomN (Seed);
    double lamda = 1/AverageServiceTime;
    exponential_distribution<double> exp (lamda);

    vector<int> nivelCola(tick_max,0);

    while(ticks < tick_max){
        if(ticks > 0)nivelCola[ticks] = nivelCola[ticks-1];
        //Entrada nuevo cliente cada intervalo
        if(Arrival[ticks]){
            nivelCola[ticks]++;
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = CompararColas(c1,c2,c3,0,Seed);
            if(colaD == 1){
                c1.EntrarCola(c);
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
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
                nivelCola[ticks]--;
                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;

                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;

                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    int sum = 0;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        sum+= ClientesSalida[i].GetTiempoSalida();
    }

    ofstream myfile;
    myfile.open ("outNoChange.txt");
    myfile << "tick - personas en la cola" << endl;
    for (int i = 0; i < tick_max;++i) myfile << nivelCola[i] << endl;
    myfile << "Media del tiempo pasado en la cola: " << sum/ClientesSalida.size() << endl;
    myfile.close();
}

void SimulationWithChange(int IntervalLLegada,int MinutosHastaCambio, int Seed,int tick_max, double AverageServiceTime){
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<int> nivelCola(tick_max,0);
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int sumCambios = 0;
    mt19937 randomN (Seed);
    double lamda = 1/AverageServiceTime;
    exponential_distribution<double> exp (lamda);
    vector<bool> Arrival = ArrivalTime(IntervalLLegada,Seed,tick_max);

    while(ticks < tick_max){
        if(ticks > 0)nivelCola[ticks] = nivelCola[ticks-1];
        //Mirar el resto de la cua
        //Cola 1

        if(c1.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c1.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c1.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c1.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c1,c2,c3,c1.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c1.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c1.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 2

        if(c2.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c2.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c2.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c2.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c2,c1,c3,c2.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c2.CambiarCola(c1,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c2.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 3
        if(c3.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c3.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c3.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c3.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c3,c2,c1,c3.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c3.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c3.CambiarCola(c1,i);
                        }
                    }
                }
            }
        }
        //Entrada nuevo cliente cada intervalo
        if(Arrival[ticks]){
            nivelCola[ticks]++;
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = CompararColas(c1,c2,c3,0,Seed);
            if(colaD == 1){
                c1.EntrarCola(c);
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
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
                nivelCola[ticks]--;

                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;
                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;
                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    ofstream myfile;
    myfile.open ("outChange.txt");
    int sum = 0;
    for (int i = 0; i < ClientesSalida.size(); ++i){
       sum+= ClientesSalida[i].GetTiempoSalida();
       //cout << "Cliente " << i << " ha tardado " << ClientesSalida[i].GetTiempoSalida() << endl;
    }

    myfile << "tick - personas en la cola" << endl;
    for (int i = 0; i < tick_max;++i) myfile << nivelCola[i] << endl;
    myfile << "Media del tiempo pasado en la cola: " << sum/ClientesSalida.size() << endl;
    myfile  << "El numero de cambios de fila hechos en total: " << sumCambios << endl;
    myfile.close();
}



void SimulationWithoutChangeRANDOM(int IntervalLLegada, int Seed,int tick_max, double AverageServiceTime){
    srand(Seed);
    vector<bool> Arrival = ArrivalTime(IntervalLLegada,Seed,tick_max);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    mt19937 randomN (Seed);
    double lamda = 1/AverageServiceTime;
    exponential_distribution<double> exp (lamda);
    vector<int> nivelCola(tick_max,0);

    while(ticks < tick_max){
        if(ticks > 0)nivelCola[ticks] = nivelCola[ticks-1];

        //Entrada nuevo cliente cada intervalo
        if(Arrival[ticks]){
            Cliente c;
            nivelCola[ticks]++;
            c.SetTiempoEntrada(ticks);
            int colaD = rand() % 3 + 1;
            if(colaD == 1){
                c1.EntrarCola(c);
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
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
                nivelCola[ticks]--;
                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;

                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;

                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        else if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    int sum = 0;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        sum+= ClientesSalida[i].GetTiempoSalida();
    }

    ofstream myfile;
    myfile.open ("outNoChangeRANDOM.txt");
    myfile << "tick - personas en la cola" << endl;
    for (int i = 0; i < tick_max;++i) myfile << nivelCola[i] << endl;
    myfile << "Media del tiempo pasado en la cola: " << sum/ClientesSalida.size() << endl;
    myfile.close();
}

void SimulationWithChangeRANDOM(int IntervalLLegada,int MinutosHastaCambio, int Seed,int tick_max, double AverageServiceTime){
    srand(Seed);
    int ticks = 0; //Ticks son nuestro metodo de medir el tiempo, cada tick representa un minuto
    vector<int> nivelCola(tick_max,0);
    vector<Cliente> ClientesSalida; //Clientes que salen de la simulacion
    Cajero c1;
    Cajero c2;
    Cajero c3;
    int sumCambios = 0;
    mt19937 randomN (Seed);
    double lamda = 1/AverageServiceTime;
    exponential_distribution<double> exp (lamda);
    vector<bool> Arrival = ArrivalTime(IntervalLLegada,Seed,tick_max);

    while(ticks < tick_max){
        if(ticks > 0)nivelCola[ticks] = nivelCola[ticks-1];
        //Mirar el resto de la cua
        //Cola 1

        if(c1.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c1.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c1.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c1.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c1,c2,c3,c1.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c1.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c1.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 2

        if(c2.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c2.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c2.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c2.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c2,c1,c3,c2.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c2.CambiarCola(c1,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c2.CambiarCola(c3,i);
                        }
                    }
                }
            }
        }

        //Mirar el resto de la cua
        //Cola 3
        if(c3.GetLength() > 1){ //ignoro el primero que ya debe estar atendido
            vector<bool> clientesCambiar;
            for(int i = 1; i < c3.GetLength();++i ){ //empezamos por el final que deben salir primeros
                Cliente aux = c3.getClienteI(i);
                if(aux.WantsChange(ticks,MinutosHastaCambio)) clientesCambiar.push_back(true);
                else clientesCambiar.push_back(false);
            }
            for(int i = c3.GetLength()-1; i > 0;--i){
                if(clientesCambiar[i]){ //si quiere cambiarse
                    int colaD = CompararColas(c3,c2,c1,c3.GetLength()-i,Seed);
                    if(colaD != 1){
                        if(colaD == 2){
                            ++sumCambios;
                            c3.CambiarCola(c2,i);
                        }
                        else if(colaD == 3){
                            ++sumCambios;
                            c3.CambiarCola(c1,i);
                        }
                    }
                }
            }
        }
        //Entrada nuevo cliente cada intervalo
        if(Arrival[ticks]){
            nivelCola[ticks]++;
            Cliente c;
            c.SetTiempoEntrada(ticks);
            int colaD = rand() % 3 + 1;
            if(colaD == 1){
                c1.EntrarCola(c);
            }
            if(colaD == 2) {
                c2.EntrarCola(c);
            }
            if(colaD == 3) {
                c3.EntrarCola(c);
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
                nivelCola[ticks]--;

                if(c1.GetLength() > 0) {
                    c1.setClienteActual(c1.getPrimero());
                    c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        if(!c1.GetOcupado() && c1.GetLength() > 0){
            c1.setClienteActual(c1.getPrimero());
            c1.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;
                if(c2.GetLength() > 0) {
                    c2.setClienteActual(c2.getPrimero());
                    c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        if(!c2.GetOcupado() && c2.GetLength() > 0){
            c2.setClienteActual(c2.getPrimero());
            c2.setTiempoRestante((int(exp.operator() (randomN)))+1);
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
                nivelCola[ticks]--;
                if(c3.GetLength() > 0) {
                    c3.setClienteActual(c3.getPrimero());
                    c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
                }

            }
        }
            //El cajero no esta ocupado
        if(!c3.GetOcupado() && c3.GetLength() > 0){
            c3.setClienteActual(c3.getPrimero());
            c3.setTiempoRestante((int(exp.operator() (randomN)))+1);
            c3.switchOcupado();
        }
        c3.restarTiempoRestante();

        ticks++;
    }
    ofstream myfile;
    myfile.open ("outChangeRANDOM.txt");
    int sum = 0;
    for (int i = 0; i < ClientesSalida.size(); ++i){
        sum+= ClientesSalida[i].GetTiempoSalida();
        //cout << "Cliente " << i << " ha tardado " << ClientesSalida[i].GetTiempoSalida() << endl;
    }

    myfile << "tick - personas en la cola" << endl;
    for (int i = 0; i < tick_max;++i) myfile << nivelCola[i] << endl;
    myfile << "Media del tiempo pasado en la cola: " << sum/ClientesSalida.size() << endl;
    myfile  << "El numero de cambios de fila hechos en total: " << sumCambios << endl;
    myfile.close();
}

void ScenarioExecute(int escenario){
    int IntervalLLegada = 8;
    int Seed = 39;
    int tick_max = 720;

    if(escenario == 1){
        SimulationWithoutChange(IntervalLLegada,Seed,tick_max,15);
    }
    else if(escenario == 2){
        SimulationWithChange(IntervalLLegada,1,Seed,tick_max,15);
    }
    else if(escenario == 4){
        SimulationWithChangeRANDOM(IntervalLLegada,1,Seed,tick_max,15);
    }
    else if(escenario == 3){
        SimulationWithoutChangeRANDOM(IntervalLLegada,Seed,1000,15);
    }
    else if(escenario == 5){
        for(int i = 1; i < 5;++i){
            ScenarioExecute(i);
        }
    }
}

void DataImport(){
    cout << "Quieres ejecutar todos los escenarios de una?" << endl << "[y/n]" << endl;
    string ans;
    cin >> ans;
    if (ans == "n"){
        cout << "Introduce los siguientes datos para tu simulación" << endl;
        cout << "Quieres que los clientes puedan cambiar de cola despues de un tiempo?" << endl << "[y/n]" << endl;
        string ans;
        cin >> ans;
        if (ans == "y") {
            cout << "Quieres que los clientes escogan el cajero inicial aleatoriamente?" << endl << "[y/n]" << endl;
            string ans;
            cin >> ans;
            if (ans == "n") {
                cout << "Cuantos minutos quieres que los clientes se esperan antes de cambiar de cola?" << endl;
                int TiempoCambio;
                cin >> TiempoCambio;
                cout << "Cada cuantos minutos llega una persona" << endl;
                int IntervalLlegada;
                cin >> IntervalLlegada;
                cout << "Indica un seed para la simulación" << endl;
                int s;
                cin >> s;
                cout << "Indica el tiempo maximo de la simulacion" << endl;
                int tickmax;
                cin >> tickmax;
                cout << "Indica tiempo medio del servicio" << endl;
                double avgstime;
                cin >> avgstime;

                SimulationWithChange(IntervalLlegada, TiempoCambio, s, tickmax, avgstime);
            } else if (ans == "y") {
                cout << "Quieres que los clientes escogan el cajero inicial aleatoriamente?" << endl << "[y/n]" << endl;
                string ans;
                cin >> ans;
                if (ans == "n") {}
                cout << "Cuantos minutos quieres que los clientes se esperan antes de cambiar de cola?" << endl;
                int TiempoCambio;
                cin >> TiempoCambio;
                cout << "Cada cuantos minutos llega una persona" << endl;
                int IntervalLlegada;
                cin >> IntervalLlegada;
                cout << "Indica un seed para la simulación" << endl;
                int s;
                cin >> s;
                cout << "Indica el tiempo maximo de la simulacion" << endl;
                int tickmax;
                cin >> tickmax;
                cout << "Indica tiempo medio del servicio" << endl;
                double avgstime;
                cin >> avgstime;

                SimulationWithChangeRANDOM(IntervalLlegada, TiempoCambio, s, tickmax, avgstime);
            }
        } else if (ans == "n") {
            cout << "Quieres que los clientes escogan el cajero inicial aleatoriamente?" << endl << "[y/n]" << endl;
            string ans;
            cin >> ans;
            if (ans == "n") {
                cout << "Cada cuantos minutos llega una persona" << endl;
                int IntervalLlegada;
                cin >> IntervalLlegada;
                cout << "Indica un seed para la simulación" << endl;
                int s;
                cout << "Indica tiempo maximo" << endl;
                int tm;
                cin >> tm;
                cout << "Indica tiempo medio del servicio" << endl;
                double avgstime;
                cin >> avgstime;
                SimulationWithoutChange(IntervalLlegada, s, tm, avgstime);
            } else if (ans == "y") {
                cout << "Cada cuantos minutos llega una persona" << endl;
                int IntervalLlegada;
                cin >> IntervalLlegada;
                cout << "Indica un seed para la simulación" << endl;
                int s;
                cout << "Indica tiempo maximo" << endl;
                int tm;
                cin >> tm;
                cout << "Indica tiempo medio del servicio" << endl;
                double avgstime;
                cin >> avgstime;
                SimulationWithoutChangeRANDOM(IntervalLlegada, s, tm, avgstime);

            }
        }
    }
    else if(ans == "y"){

        cout << "Cuantos minutos quieres que los clientes se esperan antes de cambiar de cola?" << endl;
        int TiempoCambio;
        cin >> TiempoCambio;
        cout << "Cada cuantos minutos llega una persona" << endl;
        int IntervalLlegada;
        cin >> IntervalLlegada;
        cout << "Indica un seed para la simulación" << endl;
        int s;
        cin >> s;
        cout << "Indica el tiempo maximo de la simulacion" << endl;
        int tickmax;
        cin >> tickmax;
        cout << "Indica tiempo medio del servicio" << endl;
        double avgstime;
        cin >> avgstime;

        SimulationWithChange(IntervalLlegada, TiempoCambio, s, tickmax, avgstime);
        SimulationWithChangeRANDOM(IntervalLlegada, TiempoCambio, s, tickmax, avgstime);
        SimulationWithoutChangeRANDOM(IntervalLlegada, s, tickmax, avgstime);
        SimulationWithoutChange(IntervalLlegada, s, tickmax, avgstime);



    }
}

int main(){
    cout << "Para escoger el escenario escribe 1, para importar tus propios datos escribe 2" << endl;
    int res;
    cin >> res;
    if(res == 1){
        int escenario;
        cout << "Escoge uno de los 5 escenarios" << endl << "1.3 cajeros con colas individuales" << endl << "2.3 cajeros con colas individuales pero los clientes pueden cambiar de cola despues de estar 15 minutos en una" << endl;
        cout << "3. Escenario igual que 1 pero escogiendo el cajero inicial aleatoriamente" << endl << "4.Escenario igual al 2 pero escogiendo el cajero incial aleatoriamente" << endl << "5.Cada de los 4 escenarios sequencialmente" << endl;
        cin >> escenario;
        ScenarioExecute(escenario);
    }
    else if(res == 2){
        DataImport();
    }
}

