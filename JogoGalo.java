package jogogalo;

public class JogoGalo {

    private Peca[][] _tabuleiro;

    /**
     * Construtor de um tabuleiro com tamanho 'n'.
     * Inicializa o tabuleiro com pecas livres.
     * @param Inteiro: tamanho do tabuleiro
     */
    public JogoGalo(int tamanho) {
        _tabuleiro = new Peca[tamanho][tamanho];
        Peca peca = new PecaLivre();

        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho; j++) {
                _tabuleiro[i][j] = peca;
            }
        }
    }



    /**
     * Efetua a jogada no tabuleiro.
     * Se houver uma peca na posicao é retornado "false"
     *	  e "true" caso contrário.
     * @param  Peca:    Peca jogada
     * @param  Inteiro: indice da linha.
     * @param  Inteiro: indice da coluna.
     * @return Boolean: retorna true se e' possivel jogar e "false" caso contrario.
     */
    public boolean joga(Peca peca, int linha, int coluna) {
        if (linha >= 1 && linha <= _tabuleiro.length && coluna >= 1 && coluna <= _tabuleiro[0].length &&
          _tabuleiro[linha - 1][coluna - 1].estaLivre()) {
            _tabuleiro[linha - 1][coluna - 1] = peca;
            return true;
        }

        return false;
    }



    /**
     * Verifica se e' possivel efetuar uma jogada.
     * @return Boolean: retorna "true" se houver jogadas possiveis e "false" caso contrario.
     */
    public boolean temJogadasDisponiveis() {
        for (Peca[] linha : _tabuleiro) {
            for (Peca p : linha) {
                if (p.estaLivre())
                    return true;
            }
        }
        
        return false;
    }



    /**
     * Dado as coordenadas de uma celula e' devolvido "true"
     *     ou "false", se na linha ou coluna da coordenada
     *     estiver preenchida com o mesmo simbolo (diferente
     *     de " ")
     * As diagonais pricipais sao verificadas do tabuleiro,
     *     mas apenas se a coordenada pertencer a uma delas.
     * @param  Inteiro: indice da linha.
     * @param  Inteiro: indice da coluna.
     * @return Boolean: retorna true se houver vitoria e "false" caso contrario.
     */
    public boolean ganhou(int linha, int coluna) {
        Peca jogada = _tabuleiro[--linha][--coluna];
        boolean resultado = true;
        int i;

        // verifica linha
        for (i = 0; i < _tabuleiro[linha].length; i++) {
            if (!_tabuleiro[linha][i].pertenceMesmoJogador(jogada)) {
                resultado = false;
                break;
            }
        }

        if (resultado)
            return true;

        resultado = true;
        // verifica coluna
        for (i = 0; i < _tabuleiro.length; i++) {
            if (!_tabuleiro[i][coluna].pertenceMesmoJogador(jogada)) {
                resultado = false;
                break;
            }
        }

        if (resultado)
            return true;

        // verifica diagonais.. Só é necessário se a peça estiver numa diagonal.
        if (linha == coluna) {             // verifica diagonal principal
            resultado = true;
            for (i = 0; i < _tabuleiro.length; i++) {
                if (!_tabuleiro[i][i].pertenceMesmoJogador(jogada)) {
                    resultado = false;
                    break;
                }
            }

            if (resultado)
                return true;
        }
        
        if (linha + coluna == _tabuleiro.length - 1) {             // verifica diagonal inversa
            resultado = true;
            int j;
            for (i = 0, j = _tabuleiro.length - 1; i < _tabuleiro.length; i++, j--) {
                if (!_tabuleiro[i][j].pertenceMesmoJogador(jogada)) {
                    resultado = false;
                    break;
                }
            }

            if (resultado)
                return true;
        }
        
        return false;
    }

    private String criaSeparadorLinha() {
        StringBuilder separador = new StringBuilder();

        for (int i = 0; i < _tabuleiro[0].length - 1; i++)
            separador.append("-+");

        separador.append("-\n");

        return separador.toString();
    }




    /**
     * //Por comentar!!
     */
    private String processaLinha(Peca[] linha) {
        StringBuilder res = new StringBuilder();
        int i;

        for(i = 0; i < linha.length - 1; i++) {
            res.append(linha[i].obtemSimbolo()).append("|");
        }

        res.append(linha[i].obtemSimbolo()).append("\n");
        return res.toString();
    }





	/**
     * //Por comentar!!
     */
    public String obtemEstadoJogo() {
        StringBuilder str = new StringBuilder();
        String separador = criaSeparadorLinha();
        int i;

        for (i = 0; i < _tabuleiro.length - 1; i++) {
            str.append(processaLinha(_tabuleiro[i]));
            str.append(separador);
        }

        str.append(processaLinha(_tabuleiro[i]));
        return str.toString();
    }

    public static void main(String[] args) {
        JogoGalo jogo = new JogoGalo(3);
        Peca p1 = new PecaJogador1();
        Peca p2 = new PecaJogador2();

        System.out.println("Estado Inicial\n" + jogo.obtemEstadoJogo());
        jogo.joga(p1, 1, 1);
        jogo.joga(p2, 1, 2);
        System.out.println("Após duas jogadas\n" + jogo.obtemEstadoJogo());
        
        System.out.println("P1 ganhou " + jogo.ganhou(1, 1));
        System.out.println("P2 ganhou " + jogo.ganhou(1, 2));

        jogo.joga(p1, 2, 2);
        jogo.joga(p2, 2, 3);
        System.out.println("Após 4  jogadas\n" + jogo.obtemEstadoJogo());
        System.out.println("P1 ganhou " + jogo.ganhou(2, 2));
        System.out.println("P2 ganhou " + jogo.ganhou(2, 3));

        jogo.joga(p1, 3, 3);
        jogo.joga(p2, 1, 3);
        System.out.println("Após 4  jogadas\n" + jogo.obtemEstadoJogo());
        System.out.println("P1 ganhou " + jogo.ganhou(3, 3));
        System.out.println("P2 ganhou " + jogo.ganhou(1, 3));

        jogo.joga(p1, 3, 1);
        jogo.joga(p1, 3, 2);
        System.out.println("Após 6  jogadas\n" + jogo.obtemEstadoJogo());
        System.out.println("P1 ganhou 3ª linha: " + jogo.ganhou(3, 2));

        jogo.joga(p1, 2, 1);
        System.out.println("Após 7  jogadas\n" + jogo.obtemEstadoJogo());
        System.out.println("P1 ganhou 1ª coluna: " + jogo.ganhou(2, 1));
        
    }
}

    
