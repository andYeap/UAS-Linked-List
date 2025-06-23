#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Player {
    string nickname;
    string id;
    string server;
    
    Player() : nickname(""), id(""), server("") {}
    Player(string nick, string playerId, string srv) : nickname(nick), id(playerId), server(srv) {}
};

// Struktur untuk node tim dalam linked list
struct TeamNode {
    string teamName;
    Player players[5];  // Array 5 player per tim
    int playerCount;    // Jumlah player yang sudah terdaftar
    TeamNode* next;
    
    TeamNode(string name) : teamName(name), playerCount(0), next(nullptr) {}
};

void addTeam(TeamNode*& head, string teamName) {
    TeamNode* newTeam = new TeamNode;
    newTeam->teamName = teamName;
    newTeam->playerCount = 0;
    newTeam->next = nullptr;

    if (head == nullptr) {
        head = newTeam;
    } else {
        TeamNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTeam;
    }
    cout << "Tim '" << teamName << "' berhasil ditambahkan!\n";
}

void displayRegisteredTeams(TeamNode* head) {
    if (head == nullptr) {
        cout << "Tidak ada tim yang terdaftar!\n";
        return;
    }

    cout << "\n=== DAFTAR TIM TERDAFTAR ===\n";
    TeamNode* current = head;
    int number = 1;

    while (current != nullptr) {
        cout << number << ". " << current->teamName 
             << " (" << current->playerCount << "/5 player)\n";
        current = current->next;
        number++;
    }
    cout << "\nTotal tim terdaftar: " << number - 1 << "\n";
}

bool removeTeam(TeamNode*& head, string teamName) {
    if (head == nullptr) {
        cout << "Tidak ada tim yang terdaftar!\n";
        return false;
    }

    // Jika tim yang dihapus adalah head
    if (head->teamName == teamName) {
        TeamNode* temp = head;
        head = head->next;
        delete temp;
        cout << "\nTim '" << teamName << "' berhasil dihapus!\n";
        return true;
    }

    // Mencari tim di tengah atau akhir list
    TeamNode* current = head;
    while (current->next != nullptr && current->next->teamName != teamName) {
        current = current->next;
    }

    if (current->next != nullptr) {
        TeamNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "\nTim '" << teamName << "' berhasil dihapus!\n";
        return true;
    }

    cout << "\nTim '" << teamName << "' tidak ditemukan dalam daftar!\n";
    return false;
}

bool addPlayerToTeam(TeamNode* head, string teamName, string nickname, string id, string server) {
    TeamNode* current = head;
    while (current != nullptr) {
        if (current->teamName == teamName) {
            if (current->playerCount >= 5) {
                cout << "Tim '" << teamName << "' sudah penuh (5 player)!\n";
                return false;
            }
            current->players[current->playerCount] = {nickname, id, server};
            current->playerCount++;
            cout << "Player '" << nickname << "' berhasil ditambahkan ke tim '" << teamName << "'!\n";
            return true;
        }
        current = current->next;
    }
    cout << "Tim '" << teamName << "' tidak ditemukan!\n";
    return false;
}

bool addAllPlayersToTeam(TeamNode* head, string teamName) {
    TeamNode* current = head;
    while (current != nullptr) {
        if (current->teamName == teamName) {
            if (current->playerCount > 0) {
                cout << "Tim '" << teamName << "' sudah memiliki " << current->playerCount << " player.\n";
                cout << "Fitur ini hanya untuk tim kosong. Gunakan fitur tambah player satuan atau hapus semua player dulu.\n";
                return false;
            }

            cout << "\n=== TAMBAH 5 PLAYER SEKALIGUS ===\n";
            cout << "Tim: " << teamName << "\n\n";

            for (int i = 0; i < 5; i++) {
                string nickname, id, server;
                cout << "Nickname Player " << (i + 1) << " : ";
                getline(cin, nickname);
                cout << "ID & Server : ";
                getline(cin, id);
                cout << "Server : ";
                getline(cin, server);

                current->players[i] = {nickname, id, server};
                current->playerCount++;
                cout << "Player " << (i + 1) << " berhasil ditambahkan!\n\n";
            }

            cout << "Semua 5 player berhasil ditambahkan ke tim '" << teamName << "'!\n";
            return true;
        }
        current = current->next;
    }
    cout << "Tim '" << teamName << "' tidak ditemukan!\n";
    return false;
}



void showMenu() {
    cout << "\n=== SISTEM PENDAFTARAN TURNAMEN MOBILE LEGENDS ===\n";
    cout << "1. Tambah Tim Baru\n";
    cout << "2. Lihat & Hapus Tim\n";
    cout << "3. Insert Tim di Posisi Tertentu\n";
    cout << "4. Kelola Player Tim\n";
    cout << "5. Tampilkan Semua Tim (Detail)\n";
    cout << "6. Tampilkan Detail Tim Tertentu\n";
    cout << "7. Keluar\n";
    cout << "Pilih menu (1-7): ";
}
