#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int Maks_Reservasi = 5;
const int Maks_Kamar = 10;
const int Maks_Login = 3;

struct Reservasi {
    string nomor_kamar;
    string nama_pemesan;
    string tanggal_checkin;
    int durasi_menginap;
};

string Login_Username = "Robby_Pratama";
string Login_NIM = "2309106113";
Reservasi reservasi[Maks_Reservasi];
int Reservasi_Count = 0;
bool Status_Ruang[Maks_Kamar] = {false}; // false = kosong, true = penuh

void BinarySearchByName(string target) {
    int low = 0;
    int high = Reservasi_Count - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (reservasi[mid].nama_pemesan == target) {
            found = true;
            cout << "Data ditemukan:" << endl;
            cout << "Nomor Kamar: " << reservasi[mid].nomor_kamar << endl;
            cout << "Nama Pemesan: " << reservasi[mid].nama_pemesan << endl;
            cout << "Tanggal Check-in: " << reservasi[mid].tanggal_checkin << endl;
            cout << "Durasi Menginap: " << reservasi[mid].durasi_menginap << " hari" << endl;
            break;
        } else if (reservasi[mid].nama_pemesan < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Data tidak ditemukan." << endl;
    }
}

void BubbleSortByNameAscending() {
    for (int i = 0; i < Reservasi_Count - 1; ++i) {
        for (int j = 0; j < Reservasi_Count - i - 1; ++j) {
            if (reservasi[j].nama_pemesan > reservasi[j + 1].nama_pemesan) {
                swap(reservasi[j], reservasi[j + 1]);
            }
        }
    }


}

int FibonacciSearchByName(string target) {
    int fibM_minus_2 = 0; // Fib(m-2)
    int fibM_minus_1 = 1; // Fib(m-1)
    int fibM = fibM_minus_1 + fibM_minus_2; // Fib(m)

    int offset = -1; // Penyimpangan dari awal array

    while (fibM > 1) {
        int i = min(offset + fibM_minus_2, Reservasi_Count - 1);

        if (reservasi[i].nomor_kamar < target) {
            fibM = fibM_minus_1;
            fibM_minus_1 = fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
            offset = i;
        } else if (reservasi[i].nomor_kamar > target) {
            fibM = fibM_minus_2;
            fibM_minus_1 = fibM_minus_1 - fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
        } else {
            return i; // Data ditemukan
        }
    }

    if (fibM_minus_1 && offset < Reservasi_Count - 1 && reservasi[offset + 1].nomor_kamar == target) {
        return offset + 1; // Penanganan kasus terakhir
    }

    return -1; // Data tidak ditemukan
}

void FibonacciSearchAndPrint(string target) {
    int result = FibonacciSearchByName(target);
    if (result != -1) {
        cout << "Data ditemukan:" << endl;
        cout << "Nomor Kamar: " << reservasi[result].nomor_kamar << endl;
        cout << "Nama Pemesan: " << reservasi[result].nama_pemesan << endl;
        cout << "Tanggal Check-in: " << reservasi[result].tanggal_checkin << endl;
        cout << "Durasi Menginap: " << reservasi[result].durasi_menginap << " hari" << endl;
    } else {
        cout << "Data tidak ditemukan." << endl;
    }
}

void SelectionSortByRoomNumberDescending() {
    for (int i = 0; i < Reservasi_Count - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < Reservasi_Count; ++j) {
            int roomNumber1 = stoi(reservasi[j].nomor_kamar);
            int roomNumber2 = stoi(reservasi[max_idx].nomor_kamar);
            if (roomNumber1 > roomNumber2) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap(reservasi[i], reservasi[max_idx]);
        }
    }
}

void Merge(Reservasi arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Buat array sementara
    Reservasi Left[n1], Right[n2];

    // Salin data ke array sementara Left[] dan Right[]
    for (int i = 0; i < n1; i++)
        Left[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Right[j] = arr[mid + 1 + j];

    // Gabungkan array sementara kembali ke arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (Left[i].durasi_menginap <= Right[j].durasi_menginap) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    // Salin sisa elemen Left[], jika ada
    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    // Salin sisa elemen Right[], jika ada
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void MergeSortByDurationAscending(Reservasi arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Panggil rekursif untuk bagian kiri dan kanan
        MergeSortByDurationAscending(arr, left, mid);
        MergeSortByDurationAscending(arr, mid + 1, right);

        // Gabungkan hasil pengurutan
        Merge(arr, left, mid, right);
    }
}


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

            cout << "Masukkan nama pemesan :";
            cin.ignore();
            getline(cin, reservasi[Reservasi_Count].nama_pemesan);

            cout << "Masukkan tanggal check-in (format DD-MM-YYYY) :";
            cin >> reservasi[Reservasi_Count].tanggal_checkin;

            cout << "Masukkan durasi menginap (hari) :";
            cin >> reservasi[Reservasi_Count].durasi_menginap;

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
        cout << "Nama Pemesan: " << reservasi[i].nama_pemesan << endl;
        cout << "Tanggal Check-in: " << reservasi[i].tanggal_checkin << endl;
        cout << "Durasi Menginap: " << reservasi[i].durasi_menginap << " hari" << endl;
        cout << "-----------------------" << endl;
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
    string menu = "\nMenu:\n[1].Reservasi Hotel\n[2].Lihat Reservasi\n[3].Ubah Reservasi\n[4].Lihat Kamar\n[5].Batalkan Reservasi\n[6].Sortir berdasarkan Nama Pelanggan (Bubble Sort) ( ascending )\n[7].Sortir berdasarkan Nomor Kamar (Selection Sort) ( descending )\n[8].Sortir berdasarkan Durasi Menginap (Merge Sort) ( ascending )\n[9].Keluar";
    return menu;
}

void run(string* username, string* nim) {
    cout << Lihat_Menu() << endl;
    char pilihan;
    cout << "\nPilih Menu (1-9) :";
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
       case '6': {
            BubbleSortByNameAscending();
            cout << "Data berhasil diurutkan berdasarkan nama pelanggan secara menaik." << endl;
            cout << "Sekarang Anda dapat melakukan pencarian berdasarkan nama pelanggan." << endl;

            string target;
            cout << "Masukkan nama yang ingin dicari ( Binary Search ): ";
            cin >> target;
            BinarySearchByName(target);
            break;}

        case '7': {
            SelectionSortByRoomNumberDescending();
            cout << "Data berhasil diurutkan berdasarkan nama pelanggan secara menaik." << endl;
            cout << "Sekarang Anda dapat melakukan pencarian berdasarkan nama pelanggan." << endl;

            string target;
            cout << "Masukkan nama yang ingin dicari ( Fibonacci Search ): ";
            cin >> target;
            FibonacciSearchAndPrint(target);
            break;
        }

        case '8':
            MergeSortByDurationAscending(reservasi, 0, Reservasi_Count - 1);
            cout << "Data berhasil diurutkan berdasarkan durasi menginap secara menaik." << endl;
            break;
        case '9':
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
