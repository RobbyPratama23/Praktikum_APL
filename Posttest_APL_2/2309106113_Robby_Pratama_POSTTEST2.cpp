#include <iostream>

using namespace std;

const int Maks_Reservasi = 5;
const int Maks_Kamar = 10;
const int Maks_Login = 3;

string Login_Username = "Robby_Pratama";
string Login_NIM = "2309106113";
string reservasi[Maks_Reservasi];
int Reservasi_Count = 0;

bool Status_Ruang[Maks_Kamar] = {false}; // false = kosong, true = penuh

bool login() {
    for (int coba_login = 0; coba_login < Maks_Login; ++coba_login) {
        // Nama : Robby_Pratama
        // NIM : 2309106113
        cout << "Masukkan Nama:";
        cin >> Login_Username;
        cout << "Masukkan NIM:";
        cin >> Login_NIM;

        if (Login_Username == "Robby_Pratama" && Login_NIM == "2309106113") {
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

        if (!(cin >> Nomor_Kamar) || Nomor_Kamar < 1 || Nomor_Kamar > Maks_Kamar) {
            cout << "Input tidak valid. Harap masukkan nomor kamar yang benar." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            return;
            }

        if (Nomor_Kamar >= 1 && Nomor_Kamar <= Maks_Kamar) {
            if (!Status_Ruang[Nomor_Kamar - 1]) {
                reservasi[Reservasi_Count] = to_string(Nomor_Kamar);
                ++Reservasi_Count;
                Status_Ruang[Nomor_Kamar - 1] = true;
                cout << "Reservasi Berhasil..." << endl;
            } else {
                cout << "Kamar Sudah Terisi..." << endl;
            }
        } else {
            cout << "Nomor Kamar Tidak Valid..." << endl;
        }
    } else {
        cout << "Anda Telah Mencapai Batas Maksimal Reservasi..." << endl;
    }
}

void Lihat_Reservasi() {
    cout << "Reservasi Anda :";
    for (int i = 0; i < Reservasi_Count; ++i) {
        cout << reservasi[i] << ", ";
    }
    cout << endl;
}

void Ubah() {
    string Kamar_Lama_Str, Kamar_Baru_Str;
    cout << "Masukkan Nomor Kamar Yang Ingin Diubah :";
    cin >> Kamar_Lama_Str;
    cout << "Masukkan Nomor Kamar Baru :";
    cin >> Kamar_Baru_Str;

    int Kamar_Lama = stoi(Kamar_Lama_Str);
    int Kamar_Baru = stoi(Kamar_Baru_Str);

    if (Kamar_Lama >= 1 && Kamar_Lama <= Maks_Kamar && Kamar_Baru >= 1 && Kamar_Baru <= Maks_Kamar) {
        if (!Status_Ruang[Kamar_Baru - 1]) {
            for (int i = 0; i < Reservasi_Count; ++i) {
                if (reservasi[i] == to_string(Kamar_Lama)) {
                    Status_Ruang[Kamar_Lama - 1] = false;
                    reservasi[i] = to_string(Kamar_Baru);
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

void Batal() {
    string kamar;
    cout << "Masukkan Nomor Kamar Yang Ingin Dibatalkan :";
    cin >> kamar;

    int Nomor_Kamar = stoi(kamar);

    if (Nomor_Kamar >= 1 && Nomor_Kamar <= Maks_Kamar) {
        for (int i = 0; i < Reservasi_Count; ++i) {
            if (reservasi[i] == kamar) {
                Status_Ruang[Nomor_Kamar - 1] = false;
                for (int j = i; j < Reservasi_Count - 1; ++j) {
                    reservasi[j] = reservasi[j + 1];
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

void Lihat_Menu() {
    cout << "\nMenu:\n[1].Reservasi Hotel\n[2].Lihat Reservasi\n[3].Ubah Reservasi\n[4].Lihat Kamar\n[5].Batalkan Reservasi\n[6].Keluar";
}

void run() {
    if (login()) {
        while (true) {
            Lihat_Menu();
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
                case '3':
                    Ubah();
                    break;
                case '4':
                    Lihat_Kamar();
                    break;
                case '5':
                    Batal();
                    break;
                case '6':
                    cout << "Program Berhenti." << endl;
                    return;
                default:
                    cout << "Pilihan Tidak Valid. Silahkan Coba Lagi." << endl;
            }
        }
    }
}

int main() {
    run();
    return 0;
}
