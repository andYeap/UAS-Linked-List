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
