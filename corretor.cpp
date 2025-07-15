#include "corretor.h"

int Corretor::nextId = 1;

Corretor::Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome)
    : telefone(telefone), avaliador(avaliador), lat(lat), lng(lng), nome(nome) {
    this->id = nextId++;
}

int Corretor::getId() const {
    return id;
}

std::string Corretor::getNome() const {
    return nome;
}

bool Corretor::isAvaliador() const {
    return avaliador;
}

double Corretor::getLat() const {
    return lat;
}

double Corretor::getLng() const {
    return lng;
}

std::vector<Imovel*>& Corretor::getImoveis() {
    return imoveisAtribuidos;
}

void Corretor::adicionarImovel(Imovel* imovel) {
    imoveisAtribuidos.push_back(imovel);
}