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

bool removePlayerFromTeam(TeamNode* head, string teamName, int playerIndex) {
    TeamNode* current = head;
    while (current != nullptr) {
        if (current->teamName == teamName) {
            if (current->playerCount == 0) {
                cout << "Tim '" << teamName << "' tidak memiliki player!\n";
                return false;
            }

            if (playerIndex < 1 || playerIndex > current->playerCount) {
                cout << "Nomor player tidak valid! (1-" << current->playerCount << ")\n";
                return false;
            }

            string removedPlayer = current->players[playerIndex - 1].nickname;

            // Geser player setelah player yang dihapus
            for (int i = playerIndex - 1; i < current->playerCount - 1; i++) {
                current->players[i] = current->players[i + 1];
            }

            current->playerCount--;
            cout << "Player '" << removedPlayer << "' berhasil dihapus dari tim '" << teamName << "'!\n";
            return true;
        }
        current = current->next;
    }
    cout << "Tim '" << teamName << "' tidak ditemukan!\n";
    return false;
}

bool replacePlayerInTeam(TeamNode* head, string teamName, int playerIndex, string newNickname, string newId, string newServer) {
    TeamNode* current = head;
    while (current != nullptr) {
        if (current->teamName == teamName) {
            if (current->playerCount == 0) {
                cout << "Tim '" << teamName << "' tidak memiliki player!\n";
                return false;
            }

            if (playerIndex < 1 || playerIndex > current->playerCount) {
                cout << "Nomor player tidak valid! (1-" << current->playerCount << ")\n";
                return false;
            }

            string oldPlayer = current->players[playerIndex - 1].nickname;
            current->players[playerIndex - 1] = {newNickname, newId, newServer};

            cout << "Player '" << oldPlayer << "' berhasil diganti dengan '" << newNickname << "' di tim '" << teamName << "'!\n";
            return true;
        }
        current = current->next;
    }
    cout << "Tim '" << teamName << "' tidak ditemukan!\n";
    return false;
}

void displayAllTeams(TeamNode* head) {
    if (head == nullptr) {
        cout << "Belum ada tim yang terdaftar!\n";
        return;
    }

    cout << "\n=== DAFTAR TIM TURNAMEN MOBILE LEGENDS ===\n";
    TeamNode* current = head;
    int teamNumber = 1;

    while (current != nullptr) {
        cout << teamNumber << ". TIM: " << current->teamName << "\n";
        cout << "   Player Terdaftar: " << current->playerCount << "/5\n";

        if (current->playerCount > 0) {
            cout << "   " << setw(20) << left << "NICKNAME" 
                 << setw(15) << left << "ID" 
                 << setw(15) << left << "SERVER" << "\n";
            cout << "   " << string(50, '-') << "\n";

            for (int i = 0; i < current->playerCount; i++) {
                cout << "   " << setw(20) << left << current->players[i].nickname
                     << setw(15) << left << current->players[i].id
                     << setw(15) << left << current->players[i].server << "\n";
            }
        } else {
            cout << "   (Belum ada player yang terdaftar)\n";
        }
        cout << "\n";
        current = current->next;
        teamNumber++;
    }
}

void displayTeam(TeamNode* head, string teamName) {
    TeamNode* current = head;
    while (current != nullptr) {
        if (current->teamName == teamName) {
            cout << "\n=== DETAIL TIM ===\n";
            cout << "Nama Tim: " << current->teamName << "\n";
            cout << "Player Terdaftar: " << current->playerCount << "/5\n\n";

            if (current->playerCount > 0) {
                cout << setw(20) << left << "NICKNAME" 
                     << setw(15) << left << "ID" 
                     << setw(15) << left << "SERVER" << "\n";
                cout << string(50, '-') << "\n";

                for (int i = 0; i < current->playerCount; i++) {
                    cout << setw(20) << left << current->players[i].nickname
                         << setw(15) << left << current->players[i].id
                         << setw(15) << left << current->players[i].server << "\n";
                }
            } else {
                cout << "Belum ada player yang terdaftar dalam tim ini.\n";
            }
            cout << "\n";
            return;
        }
        current = current->next;
    }
    cout << "Tim '" << teamName << "' tidak ditemukan!\n";
}

bool insertTeam(TeamNode*& head, string teamName, int position) {
    TeamNode* newTeam = new TeamNode;
    newTeam->teamName = teamName;
    newTeam->playerCount = 0;
    newTeam->next = nullptr;

    if (position < 1) {
        cout << "Posisi harus minimal 1!\n";
        delete newTeam;
        return false;
    }

    if (position == 1) {
        newTeam->next = head;
        head = newTeam;
        cout << "Tim '" << teamName << "' berhasil dimasukkan di posisi " << position << "!\n";
        return true;
    }

    TeamNode* current = head;
    for (int i = 1; i < position - 1 && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Posisi terlalu besar! Menambahkan di akhir list.\n";
        delete newTeam;
        addTeam(head, teamName);
        return true;
    }

    newTeam->next = current->next;
    current->next = newTeam;
    cout << "Tim '" << teamName << "' berhasil dimasukkan di posisi " << position << "!\n";
    return true;
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
