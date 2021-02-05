#include "sala.h"

Sala::Sala(string nome, string textoInicial, vector<string> salasAnexasNomes, vector<string> objetoNomes) {
	this->nome = nome;
	this->codinome = nome;
	this->textoInicial = textoInicial;
	this->salasAnexasNomes = salasAnexasNomes;
	this->objetoNomes = objetoNomes;
}

Sala::Sala(string nome, string codinome, string textoInicial, vector<string> salasAnexasNomes, vector<string> objetoNomes) {
	this->nome = nome;
	this->codinome = codinome;
	this->textoInicial = textoInicial;
	this->salasAnexasNomes = salasAnexasNomes;
	this->objetoNomes = objetoNomes;
}


void Sala::removeObjeto(Objeto objeto) {
	bool found = false;
	for (int i = 0; i < objetos.size(); i++) {
		if (found) {
			objetos[i].setNotifyID(objetos[i].getNotifyID()-1);
			objetos[i-1] = objetos[i];
			objetoNomes[i - 1] = objetoNomes[i];

		} else if (objetos[i].getName().compare(objeto.getName()) == 0) {
			found = true;
		}
	}

	if (found) {
		objetos.resize(objetos.size() - 1);
		objetoNomes.resize(objetoNomes.size() - 1);
	}
}

bool Sala::isSalaAnexa(string salaAnexaNome) {
	for (int i = 0; i < salasAnexasNomes.size(); i++)
		if (salaAnexaNome == salasAnexasNomes[i])
			return true;
	return false;
}

// GETTERS
string Sala::getSalaAnexaNome(int i) {
	return salasAnexasNomes[i];
};


bool Sala::possuiObjeto(string nome) {
	for (int i = 0; i < objetos.size(); i++) {
		if (nome.compare(objetos[i].getName()) == 0)
			return true;
	}
	return false;
}

#include <stdexcept>
Objeto* Sala::getObjeto(string nome) {
	for (int i = 0; i < objetos.size(); i++) {
		if (nome.compare(objetos[i].getName()) == 0)
			return &objetos[i];
	}

	throw invalid_argument("There's no object with that name :(");
}


vector<string> Sala::getObjetoNomes() {
	return objetoNomes;
};
