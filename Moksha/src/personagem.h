#pragma once
#include "sala.h"
#include "inventario.h"
#include "dictionary.h"
#include "IObservable.h"
#include "actionEnum.h"

using namespace std;

class Personagem: public IObservable {
protected:
	string nome;
	string notifyText;
	set<string> notifyTargets;
	Dictionary<string> ultimoAvistamento;
	set<Sala*> salasChecadas;

	int gender;
	int strength;
	int dexterity;
	bool unconscious;
	bool dead;
	bool inConversation;
	
	Sala *salaAtual;
	Inventario inventario;

	vector<int> basicActions{ mover, descansar, mencionar, falar, conversar, interagir };
	void takeAction(int action, vector<string> args);
	virtual void move(string str);
	void move(Sala sala);
	virtual void mention(string obj, set<string> receivers);
	virtual void mention(string obj, string receiver);
	void attack(string target);
	void say(string topico, string str, set<string> receivers);
	void rest();
	void talk(string convo);
	virtual void interact(string action, string object);

public:
	Personagem(int gender, int strength, int dexterity) {
		this->gender = gender;
		this->strength = strength;
		this->dexterity = dexterity;
		unconscious = false;
		dead = false;
	}

	string getNome() { return nome; }

	vector<Item> getInventario() { return inventario.getItens(); }
	void addConceito(string nome) { inventario.addConceito(nome); }
	void addItem(string nome, set<string> acoes) { inventario.addItem(nome, acoes); }

	void setSalaAtual(Sala *sala) {	salaAtual = sala; }
	Sala* getSalaAtual() { return salaAtual; }
	int getGender() { return gender; }
	int getStrength() { return strength; }
	int getDexterity() { return dexterity; }
	bool isUnconscious() { return unconscious || dead; }
	bool isDead() { return dead; }
	bool inConversation() {	return inConversation; }
	void setInConversation(bool a) { inConversation = a; }

	bool isActionValid(int action);

	virtual void takeAction() {}
	void sayLine(string topico, string str, set<string> receivers) { say(topico, str, receivers); }
	void printText(string str);

	string getNotifyText() { return notifyText; }
	set<string> getNotifyTargets() { return notifyTargets; }

	virtual bool temCondicao(string info) { return false; }

	virtual void executarReacao(string topico, string frase, string remetente) {};
	virtual void verSala(vector<Personagem*> pessoasNaSala) {};
	virtual void verPessoaMovendo(Personagem* pessoa, string outraSala, bool entrando) {};
	virtual void serAtacado(Personagem* atacante) {
		if (atacante->getStrength() >= strength)
			unconscious = true;
	};

};
