class Cliente {
    private:
    int TiempoSalida;
    int TiempoEntrada;
public:
    Cliente();

    void SetTiempoEntrada(int ticks);
    void GuardarTiempoSalida(int ticks);
    int GetTiempoSalida();
    bool WantsChange(int ticks,int tiempoEspera);
};



