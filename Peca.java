package jogogalo;

public abstract class Peca {
	/**
	* Devolve o simbolo do jogador associado a peca
	*@return "Jogador nr"
	*/
    public abstract String obtemSimbolo();

    public boolean pertenceMesmoJogador(Peca p) {
        return getClass() == p.getClass();
    }

    public boolean estaLivre() {
        return false;
    }

    public abstract String devolveJogador();
}
