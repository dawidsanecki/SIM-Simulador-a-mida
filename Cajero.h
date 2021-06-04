
#include "Cliente.h"
#include "vector"
using namespace std;

class Cajero {

public:
    vector<Cliente> cola;
    Cliente actual;
    bool ocupado;
    int TiempoRestante;

    Cajero();
    bool GetOcupado();
    void switchOcupado();
    void setTiempoRestante(int tiempo);
    int getTiempoRestante();

    void setClienteActual(Cliente c);
    Cliente getClienteActual();

    Cliente getClienteI(int i);

    void restarTiempoRestante();

    void EntrarCola(Cliente c);

    void SalirCola();

    Cliente getPrimero();

    void CambiarCola(Cajero &CajeroDestino,int PosCliente);

    int GetLength();
};


