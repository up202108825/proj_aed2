#include <list>
#include <string>
#include "airport.h"
#include <iostream>
#include "graph.cpp"
using namespace std;

//lista de aeroportos numa cidade

list<Airport> citySearch(const string& city, unordered_map<string,Airport>& airports){
    list<Airport> a;
    for(auto &i:airports)
        if(i.second.getCity()==city)
            a.push_back(i.second);
    return a;
}

//lista de aeroportos por pais
list<Airport> countrySearch(const string& country, unordered_map<string,Airport>& airports){
    list<Airport> a;
    for(auto &i:airports)
        if(i.second.getCountry()==country)
            a.push_back(i.second);
    return a;
}

//lista de aeroportos dentro de um raio x, a partir de uma coordenada fixa

list<Airport> coordinateSearch(const float& lat, const float& lon, const float& radius, unordered_map<string,Airport>& airports){
    list<Airport> a;
    for(auto &i:airports)
        if(d(lat, i.second.getLatitude(), lon, i.second.getLongitude()) <= radius)
            a.push_back(i.second);
    return a;
}

//criar um vetor de voos com restricao de companhias

vector<Flight> createFlights(vector<Flight>& flights, list<Airline>& airlines){
    vector<Flight> newflights;
    if(airlines.empty()) newflights = flights;
    else for(auto &i: flights)
        for(auto &a : airlines)
            if(i.getAirline().getCode()==a.getCode()) newflights.push_back(i);
    return newflights;
}

void setAirport(int escolha, Flight& f, unordered_map<string, Airport>& airports){
    int n, temp;
    string city, city1;
    float lat,lon,r;
    list<Airport> newairports;
    while(true){
        system("cls");
        cout<< "\n\n---- Pesquisar aeroporto ----";
        //----- pesquisar por cidade -----
        cout << "\n\n1) Pesquisar por cidade";

        //----- pesquisar por pais -----
        cout << "\n\n2) Pesquisar por pais";

        //----- introduzir localizacao
        cout << "\n\n3) Introduzir localizacao e raio maximo";

        cout << "\n\n-------------------\n\n0) Sair\n\n--> ";

        cin >> n;
        if(n==0) break;

        if(n==1){
            system("cls");
            cout << "\n\nCidade: ";

            cin >> city;
            getline(cin,city1,'\n');
            city += city1;

            newairports = citySearch(city, airports);
            int count = 1;
            if(!newairports.empty()) for(auto &i: newairports){
                cout << "\n\n" + to_string(count) + ") " + i.getName() + " (" + i.getCode() + ") - " + i.getCountry();
                count++;
            }
            else cout << "\n\nNao ha aeroportos nessa cidade";
            cout << "\n\n-------------------\n\n0) Sair\n\n--> ";
            cin >> n;
            if(n>0){
                auto it = newairports.begin();
                for(int i = 1; i<n; i++){it++;}
                if(escolha==0) {
                    if(it->getCode()==f.getTarget().getCode()){
                        cout << "\n\nO aeroporto de partida nao pode ser igual ao de destino, prima qualquer tecla para voltar\n-->";
                        cin >> temp;
                    }
                    else f.setSource(*it);
                }
                else {
                    if(it->getCode()==f.getSource().getCode()){
                        cout << "\n\nO aeroporto de destino nao pode ser igual ao de destino, prima qualquer tecla para voltar\n-->";
                        cin >> temp;
                    }
                    else f.setTarget(*it);
                }
            }
            break;
        }

        if(n==2){
            system("cls");
            cout << "\n\nPais: ";

            cin >> city;
            getline(cin,city1,'\n');
            city += city1;

            newairports = countrySearch(city, airports);
            int count = 1;
            if(!newairports.empty()) for(auto &i: newairports){
                    cout << "\n\n" + to_string(count) + ") " + i.getName() + " (" + i.getCode() + ") - " + i.getCountry();
                    count++;
                }
            else cout << "\n\nNao ha aeroportos nesse pais";
            cout << "\n\n-------------------\n\n0) Sair\n\n--> ";
            cin >> n;
            if(n>0){
                auto it = newairports.begin();
                for(int i = 1; i<n; i++){it++;}
                if(escolha==0) {
                    if(it->getCode()==f.getTarget().getCode()){
                        cout << "\n\nO aeroporto de partida nao pode ser igual ao de destino, prima qualquer tecla para voltar\n-->";
                        cin >> temp;
                    }
                    else f.setSource(*it);
                }
                else {
                    if(it->getCode()==f.getSource().getCode()){
                        cout << "\n\nO aeroporto de destino nao pode ser igual ao de destino, prima qualquer tecla para voltar\n-->";
                        cin >> temp;
                    }
                    else f.setTarget(*it);
                }
            }
            break;
        }

        if(n==3){
            system("cls");
            cout << "\n\nLatitude: ";
            cin >> lat;
            cout << "\n\nLongitude: ";
            cin >> lon;
            cout << "\n\nRaio maximo: ";
            cin >> r;
            newairports = coordinateSearch(lat,lon,r,airports);
            int count = 1;
            if(!newairports.empty()) for(auto &i: newairports){
                cout << "\n\n" + to_string(count) + ") " + i.getName() + " (" + i.getCode() + ") - " + i.getCountry();
                count++;
            }
            else cout << "\n\nNao ha aeroportos no raio indicado";
            cout << "\n\n-------------------\n\n0) Sair\n\n--> ";
            cin >> n;
            if(n>0){
                auto it = newairports.begin();
                for(int i = 1; i<n; i++){it++;}
                if(escolha==0) {
                    if(it->getCode()==f.getTarget().getCode()){
                        cout << "\n\nO aeroporto de partida nao pode ser igual ao de destino\n\n0) Sair\n\n-->";
                        cin >> temp;
                    }
                    else f.setSource(*it);
                }
                else {
                    if(it->getCode()==f.getSource().getCode()){
                        cout << "\n\nO aeroporto de destino nao pode ser igual ao de partida\n\n0) Sair\n\n-->";
                        cin >> temp;
                    }
                    else f.setTarget(*it);
                }
            }
            break;
        }
    }
}

void addAirline(list<Airline>& newairlines, unordered_map<string, Airline>& airlines){
    int n = 1;
    system("cls");
    cout << "\n\n---- Adicionar companhia ----";
    string code, code1;
    cout << "\n\nCodigo: ";
    cin >> code;
    getline(cin,code1,'\n');
    code1 += code1;
    if(airlines.find(code)!=airlines.end()) {
        auto a = airlines[code];
        int existe = 0;
        for(auto &i : newairlines) if(i.getCode()==code) existe = 1;
        if(existe==0) newairlines.push_back(a);
        cout << "\n - " + a.getName() + " (" + a.getCountry() + ")\n\n-------------------\n\n0) Sair\n\n--> ";
        while(n!=0) cin>>n;
    }
    else {
        cout << "\n\nNao existe nenhuma companhia com esse codigo\n\n-------------------\n\n0) Sair\n\n--> ";
        while(n!=0) cin>>n;
    }
}

void removeAirline(list<Airline>& newairlines){
    system("cls");
    cout << "\n\n---- Remover companhia ----";
    int x=1, n;
    list<Airline> temp;
    for(auto &i : newairlines){
        cout<< "\n\n" << x << ") " + i.getName() + " (" + i.getCountry() + ")";
        x++;
    }
    cout << "\n\n-------------------\n\n0) Sair\n\n--> ";
    cin >> n;
    if(n>0){
        auto it = newairlines.begin();
        for(int i = 1; i<n; i++){temp.push_back(*it); it++;}
        it++;
        while(it!=newairlines.end()) {temp.push_back(*it);it++;}
        newairlines = temp;
    }
}

//menu de planeamento de viagem

void planTripMenu(unordered_map<string, Airline>& airlines, unordered_map<string, Airport>& airports, vector<Flight>& flights){
    Flight f = Flight();
    list<Airline> newairlines;
    vector<Flight> currentflights;
    list<pair<string,string>> shortestTrip;
    int temp = 1;
    int n;
    while(true){
        //--------------- cabeçalho ---------------//
        system("cls");
        cout << "\n\n---- Planear Viagem ----";


        //---- partida ----
        cout << "\n\nPartida: ";
        if (f.getSource().getCode() != "") cout << f.getSource().getCity() + " (" + f.getSource().getCountry() + ") - " + f.getSource().getName();


        //---- destino ----
        cout << "\n\nDestino: ";
        if (f.getTarget().getCode() != "") cout << f.getTarget().getCity() + " (" + f.getTarget().getCountry() + ") - " + f.getTarget().getName();


        //---- percurso ----
        cout << "\n\nPercurso: ";
        if(validTrip(shortestTrip)) displayTrip(shortestTrip, airports);

        //---- companhias ----
        if(newairlines.empty()) cout << "\n\nSem restricao nas companhias de aviacao";
        else{
            cout << "\n\nCompanhias de aviacao escolhidas: ";
            auto it = newairlines.begin();
            cout << it->getName();
            it++;
            while(it!=newairlines.end()) { cout << ", " + it->getName(); it++;}
        }

        //--------------- filtros ---------------//
        cout << "\n\n---- Filtros ----";
        //---- definir partida ----
        cout << "\n\n1) Definir partida";


        //---- definir destino ----
        cout << "\n\n2) Definir destino";


        //---- escolher companhia(s) de aviação ----
        cout << "\n\n3) Adicionar companhia de aviacao\n\n4) Remover companhia de aviacao";

        //---- confirmar ----
        cout << "\n\n5) Confirmar - processar viagem";


        cout << "\n\n-------------------\n\n0) Sair\n\n--> ";
        //--------------- input ---------------//
        cin >> n;
        if (n == 0) break;

        //definir partida
        if(n==1) setAirport(0,f,airports);

        //definir destino
        if(n==2) setAirport(1,f,airports);

        //adicionar companhia
        if(n==3) addAirline(newairlines, airlines);

        //remover companhia
        if(n==4) removeAirline(newairlines);

        //confirmar viagem
        if(n==5){
            temp = 1;
            Graph g;
            currentflights = createFlights(flights, newairlines);
            cout << "...";
            for(auto &i : currentflights) {
                g.addEdge(i);
            }
            g.bfs(f.getSource().getCode(), f.getTarget().getCode());
            if(f.getSource().getCode()!="" && f.getTarget().getCode()!=""){
                shortestTrip = shortestFlight(f.getSource().getCode(), f.getTarget().getCode(),g);
                if(shortestTrip.empty()){
                    cout << "\nNao existe trajeto possivel para esta viagem, experimenta remover restricao de companhia e tenta novamente\n0) Voltar\n\n--> ";
                    while(temp!=0) cin >> temp;
                }
            }
            else {
                cout << "\nTens de definir partida e destino para a viagem ser processada\n0) Voltar\n\n--> ";
                while(temp!=0) cin >> temp;
            }
        }
    }
}