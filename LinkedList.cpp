#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


struct Player {
    string nickname;
    string id;
    string server;
};


struct TeamNode {
    string teamName;
    Player players[5];  
    int playerCount;    
    TeamNode* next;
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
                cout << "ID : ";
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

void managePlayersMenu(TeamNode* head, string teamName) {
    TeamNode* team = head;
    while (team != nullptr && team->teamName != teamName) {
        team = team->next;
    }

    if (team == nullptr) {
        cout << "Tim '" << teamName << "' tidak ditemukan!\n";
        return;
    }

    int choice;
    do {
        cout << "\n=== KELOLA PLAYER TIM " << teamName << " ===\n";
        cout << "Player saat ini: " << team->playerCount << "/5\n";

        if (team->playerCount > 0) {
            cout << "\nDaftar Player:\n";
            for (int i = 0; i < team->playerCount; i++) {
                cout << (i + 1) << ". " << team->players[i].nickname 
                     << " (ID: " << team->players[i].id 
                     << ", Server: " << team->players[i].server << ")\n";
            }
        }

        cout << "\n1. Tambah Player Satuan\n";
        cout << "2. Tambah 5 Player Sekaligus\n";
        cout << "3. Hapus Player\n";
        cout << "4. Ganti Player\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilih (1-5): ";
        cin >> choice;
        cin.ignore();

        string nickname, id, server;
        int playerNum;

        switch (choice) {
            case 1:
                if (team->playerCount >= 5) {
                    cout << "Tim sudah penuh!\n";
                } else {
                    cout << "Nickname Player " << (team->playerCount + 1) << " : ";
                    getline(cin, nickname);
                    cout << "ID & Server : ";
                    getline(cin, id);
                    cout << "Server : ";
                    getline(cin, server);
                    addPlayerToTeam(head, teamName, nickname, id, server);
                }
                break;

            case 2:
                addAllPlayersToTeam(head, teamName);
                break;

            case 3:
                if (team->playerCount == 0) {
                    cout << "Tidak ada player untuk dihapus!\n";
                } else {
                    cout << "Masukkan nomor player yang akan dihapus (1-" << team->playerCount << "): ";
                    cin >> playerNum;
                    removePlayerFromTeam(head, teamName, playerNum);
                }
                break;

            case 4:
                if (team->playerCount == 0) {
                    cout << "Tidak ada player untuk diganti!\n";
                } else {
                    cout << "Masukkan nomor player yang akan diganti (1-" << team->playerCount << "): ";
                    cin >> playerNum;
                    cin.ignore();
                    cout << "Nickname Player Baru : ";
                    getline(cin, nickname);
                    cout << "ID & Server Baru : ";
                    getline(cin, id);
                    cout << "Server Baru : ";
                    getline(cin, server);
                    replacePlayerInTeam(head, teamName, playerNum, nickname, id, server);
                }
                break;

            case 5:
                cout << "Kembali ke menu utama...\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

        if (choice != 5) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }

    } while (choice != 5);
}

int main() {
    TeamNode* head = nullptr;
    int choice;
    string teamName;

    cout << "Selamat datang di Sistem Pendaftaran Turnamen Mobile Legends!\n";

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Masukkan nama tim: ";
                getline(cin, teamName);
                addTeam(head, teamName);
                break;

            case 2:
                
                displayRegisteredTeams(head);

                
                if (head != nullptr) 
                    cout << "\nApakah Anda ingin menghapus tim? (y/n): ";
                    char pilihan;
                    cin >> pilihan;
                    cin.ignore(); 

                    if (pilihan == 'y' || pilihan == 'Y') {
                        cout << "Masukkan nama tim yang akan dihapus: ";
                        getline(cin, teamName);
                        removeTeam(head, teamName);
                    }
                
                break;

            case 3:
                cout << "Masukkan nama tim: ";
                getline(cin, teamName);
                cout << "Masukkan posisi (1-" << (head == nullptr ? 1 : 2) << "): ";
                int position;
                cin >> position;
                insertTeam(head, teamName, position);
                break;

            case 4:
                cout << "Masukkan nama tim yang akan dikelola playernya: ";
                getline(cin, teamName);
                managePlayersMenu(head, teamName);
                break;

            case 5:
                displayAllTeams(head);
                break;

            case 6:
                cout << "Masukkan nama tim: ";
                getline(cin, teamName);
                displayTeam(head, teamName);
                break;

            case 7:
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                break;

            default:
                cout << "Pilihan tidak valid! Silakan pilih 1-7.\n";
        }

        if (choice != 7) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }

    } while (choice != 7);

   
    while (head != nullptr) {
        TeamNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;

    }


