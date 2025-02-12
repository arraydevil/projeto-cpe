#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int MAX_COLECOES = 10;
const int MAX_FLASHCARDS = 20;

// Estruturas
struct Flashcard {
    string pergunta;
    string resposta;
};

struct Colecao {
    string nome;
    vector<Flashcard> flashcards;
};

// Variáveis globais
vector<Colecao> colecoes;

// Funções

void menuPrincipal();
void adicionarColecao();
void gerenciarColecoes();
void visualizarColecoes();
void excluirColecao();
void adicionarFlashcard();
void visualizarFlashcards();
void editarFlashcard();
void deletarFlashcard();
void salvarFlashcards();
void carregarFlashcards();

int main() {
    carregarFlashcards();
    menuPrincipal();
    salvarFlashcards();
    return 0;
}

void menuPrincipal() {
    int opcao;
    do {
        cout << "\n--- Sistema de Flashcards ---\n";
        cout << "1. Adicionar Colecao\n";
        cout << "2. Gerenciar Colecoes\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            adicionarColecao();
            break;
        case 2:
            gerenciarColecoes();
            break;
        case 3:
            cout << "Saindo do programa...\n";
            break;
        default:
            cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 3);
}

void adicionarColecao() {
    if (colecoes.size() >= MAX_COLECOES) {
        cout << "Limite de colecoes atingido!\n";
        return;
    }
    Colecao novaColecao;
    cout << "Digite o nome da nova colecao: ";
    cin.ignore();
    getline(cin, novaColecao.nome);
    colecoes.push_back(novaColecao);
    cout << "Colecao adicionada com sucesso!\n";
}

void gerenciarColecoes() {
    if (colecoes.empty()) {
        cout << "Nenhuma colecao disponivel.\n";
        return;
    }
    int opcao;
    do {
        cout << "\n--- Gerenciamento de Colecoes ---\n";
        cout << "1. Visualizar Colecoes\n";
        cout << "2. Excluir Colecao\n";
        cout << "3. Adicionar Flashcard\n";
        cout << "4. Visualizar Flashcards\n";
        cout << "5. Editar Flashcard\n";
        cout << "6. Deletar Flashcard\n";
        cout << "7. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            visualizarColecoes();
            break;
        case 2:
            excluirColecao();
            break;
        case 3:
            adicionarFlashcard();
            break;
        case 4:
            visualizarFlashcards();
            break;
        case 5:
            editarFlashcard();
            break;
        case 6:
            deletarFlashcard();
            break;
        case 7:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 7);
}

void visualizarColecoes() {
    cout << "\n--- Colecoes Disponiveis ---\n";
    for (size_t i = 0; i < colecoes.size(); ++i) {
        cout << i + 1 << ". " << colecoes[i].nome << " ("
             << colecoes[i].flashcards.size() << " flashcards)\n";
    }
}

void excluirColecao() {
    visualizarColecoes();
    if (colecoes.empty()) return;

    int indice;
    cout << "Digite o numero da colecao a excluir: ";
    cin >> indice;

    if (indice < 1 || indice > colecoes.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    colecoes.erase(colecoes.begin() + (indice - 1));
    cout << "Colecao excluida com sucesso!\n";
}

void adicionarFlashcard() {
    visualizarColecoes();
    if (colecoes.empty()) return;

    int indice;
    cout << "Digite o numero da colecao para adicionar flashcards: ";
    cin >> indice;

    if (indice < 1 || indice > colecoes.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Colecao &colecao = colecoes[indice - 1];
    if (colecao.flashcards.size() >= MAX_FLASHCARDS) {
        cout << "Limite de flashcards atingido para esta colecao!\n";
        return;
    }

    Flashcard novoFlashcard;
    cout << "Digite a pergunta: ";
    cin.ignore();
    getline(cin, novoFlashcard.pergunta);
    cout << "Digite a resposta: ";
    getline(cin, novoFlashcard.resposta);

    colecao.flashcards.push_back(novoFlashcard);
    cout << "Flashcard adicionado com sucesso!\n";
}

void visualizarFlashcards() {
    visualizarColecoes();
    if (colecoes.empty()) return;

    int indice;
    cout << "Digite o numero da colecao para visualizar flashcards: ";
    cin >> indice;

    if (indice < 1 || indice > colecoes.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Colecao &colecao = colecoes[indice - 1];
    if (colecao.flashcards.empty()) {
        cout << "Nenhum flashcard nesta colecao.\n";
        return;
    }

    for (size_t i = 0; i < colecao.flashcards.size(); ++i) {
        cout << i + 1 << ". Pergunta: " << colecao.flashcards[i].pergunta
             << " | Resposta: " << colecao.flashcards[i].resposta << "\n";
    }
}

void editarFlashcard() {
    visualizarColecoes();
    if (colecoes.empty()) return;

    int indiceColecao;
    cout << "Digite o numero da colecao para editar flashcards: ";
    cin >> indiceColecao;

    if (indiceColecao < 1 || indiceColecao > colecoes.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Colecao &colecao = colecoes[indiceColecao - 1];
    if (colecao.flashcards.empty()) {
        cout << "Nenhum flashcard nesta colecao.\n";
        return;
    }

    visualizarFlashcards();

    int indiceFlashcard;
    cout << "Digite o numero do flashcard a editar: ";
    cin >> indiceFlashcard;

    if (indiceFlashcard < 1 || indiceFlashcard > colecao.flashcards.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Flashcard &flashcard = colecao.flashcards[indiceFlashcard - 1];
    cout << "Digite a nova pergunta: ";
    cin.ignore();
    getline(cin, flashcard.pergunta);
    cout << "Digite a nova resposta: ";
    getline(cin, flashcard.resposta);

    cout << "Flashcard editado com sucesso!\n";
}

void deletarFlashcard() {
    visualizarColecoes();
    if (colecoes.empty()) return;

    int indiceColecao;
    cout << "Digite o numero da colecao para deletar flashcards: ";
    cin >> indiceColecao;

    if (indiceColecao < 1 || indiceColecao > colecoes.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Colecao &colecao = colecoes[indiceColecao - 1];
    if (colecao.flashcards.empty()) {
        cout << "Nenhum flashcard nesta colecao.\n";
        return;
    }

    visualizarFlashcards();

    int indiceFlashcard;
    cout << "Digite o numero do flashcard a deletar: ";
    cin >> indiceFlashcard;

    if (indiceFlashcard < 1 || indiceFlashcard > colecao.flashcards.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    colecao.flashcards.erase(colecao.flashcards.begin() + (indiceFlashcard - 1));
    cout << "Flashcard deletado com sucesso!\n";
}

void salvarFlashcards() {
    ofstream arquivo("flashcards.csv");
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar os dados.\n";
        return;
    }

    for (const auto &colecao : colecoes) {
        arquivo << colecao.nome << "\n";
        for (const auto &flashcard : colecao.flashcards) {
            arquivo << flashcard.pergunta << ";" << flashcard.resposta << "\n";
        }
        arquivo << "#\n"; // Delimitador para diferenciar coleções
    }

    arquivo.close();
    cout << "Dados salvos com sucesso!\n";
}

void carregarFlashcards() {
    ifstream arquivo("flashcards.csv");
    if (!arquivo.is_open()) {
        cout << "Nenhum dado para carregar.\n";
        return;
    }

    string linha;
    Colecao colecaoAtual;

    while (getline(arquivo, linha)) {
        if (linha == "#") {
            colecoes.push_back(colecaoAtual);
            colecaoAtual = Colecao();
        } else if (colecaoAtual.nome.empty()) {
            colecaoAtual.nome = linha;
        } else {
            Flashcard flashcard;
            size_t pos = linha.find(";");
            flashcard.pergunta = linha.substr(0, pos);
            flashcard.resposta = linha.substr(pos + 1);
            colecaoAtual.flashcards.push_back(flashcard);
        }
    }

    if (!colecaoAtual.nome.empty()) {
        colecoes.push_back(colecaoAtual);
    }

    arquivo.close();
    cout << "Dados carregados com sucesso!\n";
}

