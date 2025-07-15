#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "corretor.h" 
#include "imovel.h" 
#include "cliente.h" 
#include "haversine.h"


int main() {
    std::vector<Corretor> corretores;
    std::vector<Cliente> clientes;
    std::vector<Imovel> imoveis;


    // Ler corretores
    int numCorretores;
    std::cin >> numCorretores;

    for (int i = 0; i < numCorretores; ++i) {
        // criação das variaveis
        std::string telefone;
        int avaliadorInt;
        double lat, lng;
        std::string nome;

        // pegando com o 'cin' os dados do corretor
        std::cin >> telefone >> avaliadorInt >> lat >>lng;
        std::getline(std::cin >> std::ws, nome);

        // criando o corretor com os dados recebidos
        Corretor c(telefone, avaliadorInt == 1, lat, lng, nome);
        corretores.push_back(c);
    }
    

    // Se repete a mesma coisa, só adaptando para cada tipo
    // Ler clientes     
    int numClientes;
    std::cin >> numClientes;

    for (int i = 0; i < numClientes; ++i) {
        // Aqui só teremos telefone e nome, nessa ordem
        std::string telefone;
        std::string nome;

        // recebendo ambos
        std::cin >> telefone;
        std::getline(std::cin >> std::ws, nome);

        // criação dos clientes recebidos
        Cliente cli(telefone, nome);
        clientes.push_back(cli);
    }


    // Agora para os imoveis
    int numImoveis;
    std::cin >> numImoveis;

    for (int i = 0; i < numImoveis; ++i) {
        // Aqui teremos o tipo da casa, Id do proprietario, localização geografica, preço e nome da rua
        std::string tipo;
        int proprietarioId;
        double lat, lng, preco;
        std::string endereco;

        // recebendo 
        std::cin >> tipo >> proprietarioId >> lat >> lng >> preco;
        std::getline(std::cin >> std::ws, endereco);

        // Criando imoveis
        Imovel imv(tipo, proprietarioId, lat, lng, preco, endereco);
        imoveis.push_back(imv);
    }
    


    // Round-Robin

    // Filtrar avaliadores

    std::vector<Corretor*> avaliadores;
    for (auto& corretor : corretores) {
        if (corretor.isAvaliador()) {
            avaliadores.push_back(&corretor);
        }
    }

    // para caso não tenha nenhum avaliador entre os corretores
    if(avaliadores.empty()){
        std::cerr << "Nenhum corretor avaliador cadastrado.\n";
        return 1;
    }

    // ordenar os imoveis por ID com selection sort
    for(int i = 0; i <imoveis.size(); ++i){
        auto menor = i;
        for(int j = i + 1; j < imoveis.size(); ++j){
            if(imoveis[j].getId() < imoveis[menor].getId()){
                menor = j;
            }
        }
        if(menor != i){
            std::swap(imoveis[i], imoveis[menor]);
        }

    }

    // distruibuir imoveis entre os avaliadores
    int i_corretor = 0;
    for(auto& imovel : imoveis){
        // a parte "i_corretor % avaliadores.size()" faz com que fique rotativo entre os avaliadores
        Corretor* corretorAtual = avaliadores[i_corretor % avaliadores.size()];
        corretorAtual->adicionarImovel(&imovel);
        i_corretor++;
    }



    // agendamentos
    for(int i = 0; i < avaliadores.size(); ++i){
        auto* corretor = avaliadores[i];

        std::vector<Imovel*> imoveis = corretor->getImoveis();
        std::vector<bool> visitado(imoveis.size(), false);

        //loc atual do caba
        double atualLat = corretor->getLat();
        double atualLng = corretor->getLng();

        int hora = 9, minuto = 0;

        std::cout << "Corretor " << corretor->getId() << std::endl;

        //encontrar o imovel mais próx do caba
        for(int visitasFeitas = 0; visitasFeitas < imoveis.size(); visitasFeitas++){
            int i_MaisProx = -1;
            double menorDistancia = 1000000000.0; //um numero muito grande

            for(int i = 0; i < imoveis.size(); i++){
                if(!visitado[i]){
                    double distancia = haversine(atualLat, atualLng, imoveis[i]->getLat(), imoveis[i]->getLng());

                    if(distancia < menorDistancia){
                        menorDistancia = distancia;
                        i_MaisProx = i;
                    }
                }
            }
            // marca como visitado
            visitado[i_MaisProx] = true;

            //calcular o tempo de deslocamento
            int minutosDeslocamento = static_cast<int>((menorDistancia * 2));

            minuto += minutosDeslocamento;
            if(minuto >= 60){
                hora += minuto / 60;
                minuto %= 60;
            }

            //imprime agendamento
            // setw define a largura da saída (2) e setfill define que oq seria 'espaço' vire '0'
            std::cout << std::setfill('0') << std::setw(2) << hora << ":" << std::setfill('0') << std::setw(2) << minuto << " Imóvel " << imoveis[i_MaisProx]->getId() << std::endl;

            //adiciona mais uma hora
            hora += 1;

            //atualiza ponto de partida
            atualLat = imoveis[i_MaisProx]->getLat();
            atualLng = imoveis[i_MaisProx]->getLng();
        }
        //pula linha para separar os corretores SE NAO FOR O ULTIMO
        if(i < avaliadores.size() - 1){
            std::cout << std::endl;
        }
    }
    
    return 0;
}