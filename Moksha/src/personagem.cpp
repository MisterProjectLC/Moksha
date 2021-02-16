#include "personagem.h"

void Personagem::takeAction(int action, vector<string> args) {
	// Trancado em conversa
	if (inConversation()) {
		setInConversation(false);
		return;
	}

	string zusammenArgs = "";
	if (args.size() >= 1)
		zusammenArgs = concatStrings(args, 0);

	switch(action) {
		case mencionar:
			mention(args.at(1), set<string>({ args.at(2) }));
			break;

		case mover:
			move(zusammenArgs);
			break;

		case atacar:
			attack(zusammenArgs);
			break;

		case descansar:
			rest();
			break;

		default:
			interact(args.at(0), zusammenArgs);
			break;
	}
}


void Personagem::printText(string str) {
	notifyText = str;
	notify(imprimir);
}

void Personagem::move(string str) {
	notifyText = str;
	notify(mover);
}

void Personagem::move(Sala sala) {
	move(sala.getNome());
}

void Personagem::mention(string obj, string receiver) {
	mention( obj, set<string>({ receiver }) );
}

void Personagem::mention(string obj, set<string> receivers) {
	if (inventario.temConceito(obj) || inventario.temItem(obj)) {
		notifyText = obj;
		notifyTargets = receivers;
		notify(mencionar);
	}
}

void Personagem::attack(string target) {
	notifyText = target;
	notify(atacar);
}

void Personagem::say(string topico, string str, set<string> receivers) {
	notifyText = topico + "|" + str;
	notifyTargets = receivers;
	notify(falar);
}

void Personagem::rest() {
	notify(descansar);
}

void Personagem::talk(string convo) {
	notifyText = convo;
	notify(conversar);
}

void Personagem::interact(string action, string object) {
	if (getSalaAtual()->possuiObjeto(object))
		getSalaAtual()->getObjeto(object)->takeAction(action, nome);
}

bool Personagem::isActionValid(int action) {
	for (int i = 0; i < basicActions.size(); i++)
		if (basicActions[i] == action)
			return true;

	for (int i = 0; i < getInventario().size(); i++)
		if (getInventario()[i].isActionValid(action))
			return true;

	return false;
}