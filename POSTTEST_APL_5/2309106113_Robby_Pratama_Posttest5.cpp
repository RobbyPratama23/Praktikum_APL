#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int Maks_Reservasi = 5;
const int Maks_Kamar = 10;
const int Maks_Login = 3;

struct Reservasi {
    string nomor_kamar;
};

string Login_Username = "Robby_Pratama";
string Login_NIM = "2309106113";
Reservasi reservasi[Maks_Reservasi];
int Reservasi_Count = 0;

bool Status_Ruang[Maks_Kamar] = {false}; // false = kosong, true = penuh

bool login(string* username, string* nim) {
    for (int coba_login = 0; coba_login < Maks_Login; ++coba_login) {
        cout << "Masukkan Nama:";
        cin >> *username;
        cout << "Masukkan NIM:";
        cin >> *nim;

        if (*username == "Robby_Pratama" && *nim == "2309106113") {
            cout << "Login Berhasil..." << endl;
            return true;
        } else {
            cout << "Login Gagal. Sisa Percobaan :" << Maks_Login - coba_login - 1 << endl;
        }
    }

    cout << "Login Gagal Sebanyak 3 kali..." << endl;
    cout << "[Program Berhenti]" << endl;
    return false;
}

void Pesanan() {
    if (Reservasi_Count < Maks_Reservasi) {
        cout << "Masukkan nomor kamar yang ingin dipesan :";
        int Nomor_Kamar;
        cin >> Nomor_Kamar;

        if (cin.fail() || Nomor_Kamar < 1 || Nomor_Kamar > Maks_Kamar) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Harap masukkan nomor kamar yang benar." << endl;
            return;
        }

        if (!Status_Ruang[Nomor_Kamar - 1]) {
            reservasi[Reservasi_Count].nomor_kamar = to_string(Nomor_Kamar);
            ++Reservasi_Count;
            Status_Ruang[Nomor_Kamar - 1] = true;
            cout << "Reservasi Berhasil..." << endl;
        } else {
            cout << "Kamar Sudah Terisi..." << endl;
        }
    } else {
        cout << "Anda Telah Mencapai Batas Maksimal Reservasi..." << endl;
    }
}

void Lihat_Reservasi() {
    cout << "[ Reservasi Anda ]" << endl;
    for (int i = 0; i < Reservasi_Count; ++i) {
        cout << "Nomor Kamar: " << reservasi[i].nomor_kamar << endl;
    }
}

void Ubah(string* kamar_lama, string* kamar_baru) {
    int Kamar_Lama = stoi(*kamar_lama);
    int Kamar_Baru = stoi(*kamar_baru);

    if (Kamar_Lama >= 1 && Kamar_Lama <= Maks_Kamar && Kamar_Baru >= 1 && Kamar_Baru <= Maks_Kamar) {
        if (!Status_Ruang[Kamar_Baru - 1]) {
            for (int i = 0; i < Reservasi_Count; ++i) {
                if (reservasi[i].nomor_kamar == *kamar_lama) {
                    Status_Ruang[Kamar_Lama - 1] = false;
                    reservasi[i].nomor_kamar = to_string(Kamar_Baru);
                    Status_Ruang[Kamar_Baru - 1] = true;
                    cout << "Reservasi Berhasil Diubah..." << endl;
                    return;
                }
            }
            cout << "Reservasi Tidak Ditemukan" << endl;
        } else {
            cout << "Kamar Baru Sudah Terisi. Pilih Kamar Lain" << endl;
        }
    } else {
        cout << "Nomor Kamar Tidak Valid..." << endl;
    }
}

void Lihat_Kamar() {
    cout << "Kamar Yang Kosong :";
    for (int i = 0; i < Maks_Kamar; ++i) {
        if (!Status_Ruang[i]) {
            cout << i + 1 << ", ";
        }
    }

    cout << "\nKamar Yang Sudah Terisi :";
    for (int i = 0; i < Maks_Kamar; ++i) {
        if (Status_Ruang[i]) {
            cout << i + 1 << ", ";
        }
    }
    cout << endl;
}

void Batal(string* kamar) {
    int Nomor_Kamar = stoi(*kamar);

    if (Nomor_Kamar >= 1 && Nomor_Kamar <= Maks_Kamar) {
        for (int i = 0; i < Reservasi_Count; ++i) {
            if (reservasi[i].nomor_kamar == *kamar) {
                Status_Ruang[Nomor_Kamar - 1] = false;
                for (int j = i; j < Reservasi_Count - 1; ++j) {
                    reservasi[j].nomor_kamar = reservasi[j + 1].nomor_kamar;
                }
                --Reservasi_Count;
                cout << "Reservasi Berhasil DiBatalkan..." << endl;
                return;
            }
        }
        cout << "Reservasi Tidak Ditemukan" << endl;
    } else {
        cout << "Nomor Kamar Tidak Valid." << endl;
    }
}

string Lihat_Menu() {
    string menu = "\nMenu:\n[1].Reservasi Hotel\n[2].Lihat Reservasi\n[3].Ubah Reservasi\n[4].Lihat Kamar\n[5].Batalkan Reservasi\n[6].Keluar";
    return menu;
}

void run(string* username, string* nim) {
    cout << Lihat_Menu() << endl;
    char pilihan;
    cout << "\nPilih Menu (1-6) :";
    cin >> pilihan;

    switch (pilihan) {
        case '1':
            Pesanan();
            break;
        case '2':
            Lihat_Reservasi();
            break;
        case '3': {
            string Kamar_Lama_Str, Kamar_Baru_Str;
            cout << "Masukkan Nomor Kamar Yang Ingin Diubah :";
            cin >> Kamar_Lama_Str;
            cout << "Masukkan Nomor Kamar Baru :";
            cin >> Kamar_Baru_Str;
            Ubah(&Kamar_Lama_Str, &Kamar_Baru_Str);
            break;
        }
        case '4':
            Lihat_Kamar();
            break;
        case '5': {
            string kamar;
            cout << "Masukkan Nomor Kamar Yang Ingin Dibatalkan :";
            cin >> kamar;
            Batal(&kamar);
            break;
        }
        case '6':
            cout << "Program Berhenti." << endl;
            return;
        default:
            cout << "Pilihan Tidak Valid. Silahkan Coba Lagi." << endl;
    }

    run(username, nim); // Rekursif
}

int main() {
    string username, nim;
    if (login(&username, &nim)) {
        run(&username, &nim);
    }
    return 0;
}
