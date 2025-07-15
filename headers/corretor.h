#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>
#include <vector>
#include "imovel.h"

class Corretor{
private: 
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;
    bool avaliador;
    double lat, lng;
    std::vector<Imovel*> imoveisAtribuidos;


public:
    Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome);

    int getId() const;
    std::string getNome() const;
    bool isAvaliador() const;
    double getLat() const;
    double getLng() const;
    std::vector<Imovel*>& getImoveis();

    void adicionarImovel(Imovel* imovel);
};

#endif