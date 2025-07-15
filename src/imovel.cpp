#include "imovel.h"

int Imovel::nextId = 1;

Imovel::Imovel(const std::string& tipoStr, int proprietarioId, double lat, double lng, double preco, const std::string& endereco)
    : proprietarioId(proprietarioId), lat(lat), lng(lng), preco(preco), endereco(endereco) {
    this->id = nextId++;

    if (tipoStr == "Casa")
        tipo = TipoImovel::Casa;
    else if (tipoStr == "Apartamento")
        tipo = TipoImovel::Apartamento;
    else
        tipo = TipoImovel::Terreno;
}

int Imovel::getId() const {
    return id;
}

TipoImovel Imovel::getTipo() const {
    return tipo;
}

double Imovel::getLat() const {
    return lat;
}

double Imovel::getLng() const {
    return lng;
}

std::string Imovel::getEndereco() const {
    return endereco;
}