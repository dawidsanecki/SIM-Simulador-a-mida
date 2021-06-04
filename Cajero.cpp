//
// Created by user on 05.06.2021.
//

#include "Cajero.h"

Cajero::Cajero()
    :ocupado(false),TiempoRestante(0)
{}
bool Cajero::GetOcupado(){
    return ocupado;
}
void Cajero::switchOcupado(){
    if(!ocupado) ocupado = true;
    else ocupado = false;
}

void Cajero::setTiempoRestante(int tiempo){
    TiempoRestante = tiempo;
}
int Cajero::getTiempoRestante(){
    return TiempoRestante;
}

void Cajero::setClienteActual(Cliente c){
    actual = c;
}
Cliente Cajero::getClienteActual(){
    return actual;
}

Cliente Cajero::getClienteI(int i){
    return cola[i];
}

void Cajero::restarTiempoRestante(){
    --TiempoRestante;
}

void Cajero::EntrarCola(Cliente c){
    cola.push_back(c);
}

void Cajero::SalirCola(){
    cola.erase(cola.begin());

}

Cliente Cajero::getPrimero(){
    return cola[0];
}

void Cajero::CambiarCola(Cajero &CajeroDestino,int PosCliente){
    Cliente c = cola[PosCliente];
    cola.erase(cola.begin()+PosCliente);
    CajeroDestino.EntrarCola(c);
}

int Cajero::GetLength(){
    return cola.size();
}