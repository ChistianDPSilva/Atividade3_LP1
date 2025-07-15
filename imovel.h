#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>

enum class TipoImovel{
    Casa,
    Apartamento,
    Terreno
};

class Imovel{
private:
    static int nextId;
    int id;
    TipoImovel tipo;
    int proprietarioId;
    double lat, lng;
    double preco;
    std::string endereco;

public:
    Imovel(const std::string& tipoStr, int proprietarioId, double lat, double lng, double preco, const std::string& endereco);

    int getId() const;
    TipoImovel getTipo() const;
    double getLat() const;
    double getLng() const;
    std::string getEndereco() const;
};

#endif