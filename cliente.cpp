#include "cliente.h"

int Cliente::nextId = 1;

Cliente::Cliente(const std::string& telefone, const std::string& nome)
    : telefone(telefone), nome(nome) {
    this->id = nextId++;
}

int Cliente::getId() const {
    return id;
}

std::string Cliente::getNome() const {
    return nome;
}