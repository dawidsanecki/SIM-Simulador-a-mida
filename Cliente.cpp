
#include "Cliente.h"

Cliente::Cliente()
    :TiempoEntrada(0),TiempoSalida(0)
{}
void Cliente::SetTiempoEntrada(int ticks){
    TiempoEntrada = ticks;
}
void Cliente::GuardarTiempoSalida(int ticks) {
    TiempoSalida = ticks - TiempoEntrada;
}
int Cliente::GetTiempoSalida(){
    return TiempoSalida;
}
bool Cliente::WantsChange(int ticks,int tiempoEspera){
    if(ticks - TiempoEntrada >= tiempoEspera) return true;
    else return false;
}
