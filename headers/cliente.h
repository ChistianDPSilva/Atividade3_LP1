#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente{
private:
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;

public:
    Cliente(const std::string& nome, const std::string& telefone);

    int getId() const;
    std::string getNome() const;   
};

#endif