package jogogalo;

public class PecaLivre extends Peca {

    public PecaLivre() {
    }

    public String obtemSimbolo() {
        return " ";
    }

    public boolean pertenceMesmoJogador(Peca p) {
        return false;
    }

    public boolean estaLivre() {
        return true;
    }

    public String devolveJogador() {
        return "Ninguém";
    }

}
