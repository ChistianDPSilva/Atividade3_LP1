CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Iheaders

# Adicione todos os seus arquivos .cpp aqui
SRCS = src/main.cpp src/corretor.cpp src/imovel.cpp src/cliente.cpp src/haversine.cpp

imobiliaria: $(SRCS)
	$(CXX) $(CXXFLAGS) -o imobiliaria $(SRCS)

clean:
	rm -f imobiliaria