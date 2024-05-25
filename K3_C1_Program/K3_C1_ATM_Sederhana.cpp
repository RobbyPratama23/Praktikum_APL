#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct UserData {
    string username;
    int pin;
    int saldo;
    string noRekening;
};

const int MAX_USERS = 100; // Ukuran maksimum array data pengguna
UserData users[MAX_USERS]; // Array untuk menyimpan data pengguna
int numUsers = 0; // Jumlah pengguna saat ini

int AutoNoRekening = 1001; // Membuat No.Rekening otomatis


void saveUsersToCSV() {
    ofstream file("users.csv");
    if (file.is_open()) {
        for (int i = 0; i < numUsers; ++i) {
            file << users[i].username << "," << users[i].pin << "," << users[i].saldo << "," << users[i].noRekening << "\n";
        }
        file.close();
    } else {
        cout << "Error opening file for writing.\n";
    }
}

void loadUsersFromCSV() {
    ifstream file("users.csv");
    string line;
    numUsers = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, users[numUsers].username, ',');
            getline(ss, token, ',');
            users[numUsers].pin = stoi(token);
            getline(ss, token, ',');
            users[numUsers].saldo = stoi(token);
            getline(ss, users[numUsers].noRekening, ',');

            numUsers++;
        }
        file.close();
    } else {
        cout << "Error opening file for reading.\n";
    }
}




void header()
{
    cout << "\n\n\n";
    cout << "\t\t===================================================\n"
            "\t\t               BANK MENDING TURU\n"
            "\t\t===================================================\n\n";
}

void registrasiUser() {
    if (numUsers >= MAX_USERS) {
        cout << "\n\n\n";
        cout << "\t\t===================================================\n"
                "\t\t|             USER TELAH MAKSIMAL                  |\n"
                "\t\t===================================================\n";
        return;
    }

    string username;
    int pin, saldo;

    header();
    cout << "\t\t        Masukkan Username Baru \n\n"
            "\t\t                   ";
    cin >> username;
    system("cls");

    // Periksa apakah nama pengguna sudah ada
    for (int i = 0; i < numUsers; ++i) {
        if (username == users[i].username) {
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|             NAMA PENGGUNA SUDAH ADA              |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");
            return;
        }
    }

    header();
    cout << "\t\t        Masukkan Pin Baru \n\n"
            "\t\t                 ";
    cin >> pin;
    system("cls");

    // Periksa format pin (misalnya, harus 4 digit)
    if (pin < 1000 || pin > 9999) {
        cout << "\n\n\n";
        cout << "\t\t===================================================\n"
                "\t\t|             FORMAT PIN TIDAK VALID               |\n"
                "\t\t|               (PIN HARUS 4 DIGIT)                |\n"
                "\t\t===================================================\n";
        system("pause");
        system("cls");
        return;
    }

    header();
    cout << "\t\t        Masukkan Saldo Awal \n\n"
            "\t\t             Rp. ";
    cin >> saldo;
    system("cls");

    // Periksa nilai saldo yang valid (misalnya, tidak boleh negatif)
    if (saldo < 0) {
        cout << "\n\n\n";
        cout << "\t\t===================================================\n"
                "\t\t|             SALDO TIDAK VALID                    |\n"
                "\t\t===================================================\n";
        system("pause");
        system("cls");
        return;
    }

    // Buat data pengguna baru
    users[numUsers].username = username;
    users[numUsers].pin = pin;
    users[numUsers].saldo = saldo;

    // Inisialisasi nomor rekening secara otomatis
    users[numUsers].noRekening = "KRMR" + to_string(AutoNoRekening);
    AutoNoRekening++; // Increment nomor rekening untuk pengguna berikutnya

    numUsers++; // Tambahkan jumlah pengguna

    header();
    cout << "\t\t               Rekening Telah Dibuat... \n"
            "\t\t===================================================\n"
            "\t\t|  Nomor Rekening | " << users[numUsers - 1].noRekening << "\n"
            "\t\t===================================================\n";
    system("pause");
    system("cls");

    saveUsersToCSV(); // Simpan Ke File csv
}



int loginuser() {
    int pin;
    string noRekening;
    int attempts = 0; // Jumlah percobaan login yang gagal

    do {
        header();
        cout << "\t\t        Masukkan No. Rekening \n\n"
                "\t\t                 ";
        cin >> noRekening;
        system("cls");

        header();
        cout << "\t\t        Masukkan Pin \n\n"
                "\t\t                 ";
        cin >> pin;
        system("cls");

        int index = -1;
        // Cari pengguna berdasarkan nomor rekening dan pin
        for (int i = 0; i < numUsers; ++i) {
            if (noRekening == users[i].noRekening && pin == users[i].pin) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // Login berhasil
            header();
            cout << "\t\t                 LOGIN BERHASIL\n";
            cout << "\t\t===================================================\n\n";
            system("pause");
            return index; // Kembalikan indeks pengguna yang berhasil login
        } else {
            attempts++; // Tambahkan jumlah percobaan login yang gagal
            header();
            cout << "\t\t        Login Gagal\n\n";
            cout << "\t\t===================================================\n\n";
            system("pause");
            system("cls");

            if (attempts >= 3) {
                header();
                cout << "\t\t           ERROR - REK DI BLOKIR\n\n"
                        "\t\t===================================================\n\n"
                        "\t\t           Kamu salah masukkan pin 3X\n\n"
                        "\t\t===================================================\n\n";
                system("pause");

                exit(0); // Keluar dari program jika limit percobaan melebihi batas
            }
        }
    } while (attempts < 3); // Mengulang login selama jumlah percobaan kurang dari 3

    return -1; // Kembalikan nilai -1 jika login gagal
}

void loginadmin()
{
    string username;
    string pin;
    int attempts = 0;

    do {
        header();
        cout << "\t\t        Masukkan Username \n\n"
                "\t\t                 ";
        cin >> username;
        system("cls");

        header();
        cout << "\t\t        Masukkan Pin \n\n"
                "\t\t                 ";
        cin >> pin;
        system("cls");

        if (username == "ADMIN" && pin == "ADMIN123") {
            header();
            cout << "\t\t                 LOGIN BERHASIL\n";
            cout << "\t\t===================================================\n\n";
            system("pause");
            break; // Keluar dari loop jika login berhasil
        } else {
            attempts++; // Tambahkan jumlah percobaan login yang gagal
            header();
            cout << "\t\t        Login Gagal\n\n";
            cout << "\t\t===================================================\n\n";
            system("pause");
            system("cls");

            if (attempts >= 3) {
                header();
                cout << "\t\t           ERROR - REK DI BLOKIR\n\n"
                        "\t\t===================================================\n\n"
                        "\t\t           Kamu salah masukkan pin 3X\n\n"
                        "\t\t===================================================\n\n";
                system("pause");

                exit(0); // Keluar dari program jika limit percobaan melebihi batas
            }
        }
    } while (attempts < 3); // Mengulang login selama jumlah percobaan kurang dari 3
}

void LihatDataUser() {
    // Cek apakah ada pengguna yang terdaftar
    if (numUsers == 0) {
        header();
        cout << "\t\t===================================================\n"
                "\t\t|             TIDAK ADA DATA PENGGUNA             |\n"
                "\t\t===================================================\n";
        system("pause");
        return;
    }
    cout << "\n\n\n";
    cout << "\t\t===================================================\n"
            "\t\t|              DAFTAR SELURUH USERNAME            |\n"
            "\t\t===================================================\n";
    for (int i = 0; i < numUsers; ++i) {
        cout << "\t\t|  Username       | " << users[i].username << "\n";
    }
    cout << "\t\t===================================================\n";
}





void DataUserDetail(int index) {
    cout << "\n\n\n";
    cout << "\t\t===================================================\n"
            "\t\t                Detail Pengguna \n"
            "\t\t===================================================\n"
            "\t\t|  Username       | " << users[index].username << "\n"
            "\t\t|-----------------|------------------------------\n"
            "\t\t|  PIN            | " << users[index].pin << "\n"
            "\t\t|-----------------|------------------------------\n"
            "\t\t|  Saldo          | Rp. " << users[index].saldo << "\n"
            "\t\t|-----------------|------------------------------\n"
            "\t\t|  Nomor Rekening | " << users[index].noRekening << "\n"
            "\t\t===================================================\n";
}


void bubbleSortUsers() {
    for (int i = 0; i < numUsers - 1; ++i) {
        for (int j = 0; j < numUsers - i - 1; ++j) {
            if (users[j].username > users[j + 1].username) {
                // Tukar posisi
                UserData temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

void searchUserByUsername() {
    string username;
    cout << "\t\tMasukkan username yang ingin Anda cari: ";
    cin >> username;
    system("cls");

    // Urutkan array users berdasarkan username
    bubbleSortUsers();

    // Lakukan binary search untuk mencari username
    bool found = false;
    int low = 0, high = numUsers - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (users[mid].username == username) {
            found = true;
            DataUserDetail(mid); // Memanggil fungsi untuk menampilkan detail pengguna
            break;
        } else if (users[mid].username < username) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        header();
        cout << "\t\tPengguna dengan username '" << username << "' tidak ditemukan.\n";
    }

    system("pause");
}


void deleteUserByUsername(const string& username) {
    int index = -1;
    for (int i = 0; i < numUsers; ++i) {
        if (users[i].username == username) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < numUsers - 1; ++i) {
            users[i] = users[i + 1];
        }
        numUsers--;
        cout << "\n\n\n";
        cout << "\t\t===================================================\n"
                "\t\t|           Pengguna berhasil dihapus             |\n"
                "\t\t===================================================\n";

        system("pause");
        saveUsersToCSV();
    } else {
        cout << "\n\n\n";
        cout << "\t\t===================================================\n"
                "\t\t|            Pengguna tidak ditemukan             |\n"
                "\t\t===================================================\n";

        system("pause");
    }
}




void transfer(int index) {
    string noRekTujuan;
    int jumlahUang;

    header();
    cout << "\t\t        Masukkan No. Rek yang dituju \n\n"
            "\t\t                 ";
    cin >> noRekTujuan;
    system("cls");

    bool rekeningValid = false;
    int indexTujuan = -1; // Menyimpan indeks data pengguna dengan nomor rekening tujuan
    for (int i = 0; i < numUsers; ++i) {
        if (noRekTujuan == users[i].noRekening) {
            rekeningValid = true;
            indexTujuan = i;
            break;
        }
    }

    if (!rekeningValid) {
        header();
        cout << "\t\t       No. Rekening Tujuan Tidak Valid\n\n";
        cout << "\t\t===================================================\n\n";
        system("pause");
        system("cls");
        return;
    }

    header();
    cout << "\t\t          Masukkan Nominal Uangnya \n\n"
            "\t\t               Rp. ";
    cin >> jumlahUang;
    system("cls");

    header();

    if (jumlahUang <= 0) {
        cout << "\t\t           Nominal Uang Tidak Valid \n\n";
        system("pause");
        system("cls");
    } else if (jumlahUang >= users[index].saldo) {
        cout << "\t\t           Saldo Anda Tidak Mencukupi \n\n";
        cout << "\t\t Sisa Saldo : Rp. " << users[indexTujuan].saldo << "\n\n";
        system("pause");
        system("cls");
    } else {
        users[indexTujuan].saldo += jumlahUang;
        users[index].saldo -= jumlahUang;
        cout << "\t\t           Transfer Berhasil \n\n"
                "\t\t No Rek Tujuan   : " << noRekTujuan << "\n"
                "\t\t Nominal Uang    : Rp. " << jumlahUang << "\n\n"
                "\t\t===================================================\n\n";
        system("pause");
        system("cls");

        saveUsersToCSV(); // File csv
    }
}



void cekSaldo(int index) {
    cout << "\n\n\n";
    cout << "\t\t===================================================\n"
            "\t\t               Saldo Anda Saat Ini\n"
            "\t\t===================================================\n"
            "\t\t|  Saldo          | Rp. " << users[index].saldo << "\n";
    cout << "\t\t===================================================\n\n";
    system("pause");
    system("cls");
}



void tarikUang(int index)
{
    int tarik, nominal;
    header();
    cout << "\t\t       [1] 100.000     [3] 500.000\n\n"
            "\t\t       [2] 200.000     [4] 1.000.000\n\n"
            "\t\t              [5] Tulis Nominal   \n\n"
            "\t\t===================================================\n"
            "\t\t   pilih : ";
    cin >> tarik;

    system("cls");

    // Handling Error
    while (!(cin >> tarik)) {
            cin.clear(); // Mengembalikan status input stream ke normal
            cin.ignore(); // Menghapus karakter yang tidak valid dari input buffer
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|     Input tidak valid. Masukkan angka!           |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");



            header();
            cout << "\t\t       [1] 100.000     [3] 500.000\n\n"
                    "\t\t       [2] 200.000     [4] 1.000.000\n\n"
                    "\t\t              [5] Tulis Nominal   \n\n"
                    "\t\t===================================================\n"
                    "\t\t   pilih : ";
        }


    if (tarik == 1)
    {
        tarik = 100000;
    }
    else if (tarik == 2)
    {
        tarik = 200000;
    }
    else if (tarik == 3)
    {
        tarik = 500000;
    }
    else if (tarik == 4)
    {
        tarik = 1000000;
    }
    else if (tarik == 5)
    {
        cout << "\t\t Masukkan Nominal : Rp. ";
        cin >> nominal;
        tarik = nominal;
    }

    system("cls");
    cout << "\n\n\n";

    if (users[index].saldo <= tarik)
    {
        cout << "\t\t===================================================\n"
                "\t\t           Saldo Anda Tidak Mencukupi \n"
                "\t\t===================================================\n\n";
        cout << "\t\t Sisa Saldo : Rp. " << users[index].saldo << "\n\n"
                "\t\t===================================================\n\n";
        system("pause");
        system("cls");
    }
    else
    {
        users[index].saldo -= tarik;
        cout << "\t\t===================================================\n"
                "\t\t           Anda Berhasil Menarik Uang \n"
                "\t\t===================================================\n\n"
                "\t\t Nominal Uang : Rp. " << tarik << "\n\n"
                "\t\t===================================================\n\n";
        saveUsersToCSV();
        system("pause");
        system("cls");
    }
}

void setor(int index)
{
    int nominalUang;

    header();
    cout << "\t\t Masukkan nominal uang : Rp. ";
    cin >> nominalUang;
    users[index].saldo += nominalUang;

    system("cls");
    cout << "\n\n\n";
    cout << "\t\t===================================================\n";
    cout << "\t\t               Setor Uang Berhasil \n"
            "\t\t===================================================\n\n"
            "\t\t Nominal Uang : Rp. " << nominalUang << "\n\n"
            "\t\t===================================================\n\n";
    saveUsersToCSV();
    system("pause");
    system("cls");
}

void menuUser(int index) {
    int pilihMenu;
    int pilih;

    do {
        system("cls");
        header();
        cout << "\t\t             1. TRANSFER UANG\n"
                "\t\t             2. CEK SALDO\n"
                "\t\t             3. TARIK SALDO\n"
                "\t\t             4. SETOR UANG\n\n"
                "\t\t===================================================\n\n";
        cout << "\t\t  pilih : ";

        // Validasi input untuk memastikan bahwa input adalah angka
        while (!(cin >> pilihMenu)) {
            cin.clear(); // Mengembalikan status input stream ke normal
            cin.ignore(); // Menghapus karakter yang tidak valid dari input buffer
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|     Input tidak valid. Masukkan angka!           |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");

            header();
            cout << "\t\t             1. TRANSFER UANG\n"
                    "\t\t             2. CEK SALDO\n"
                    "\t\t             3. TARIK SALDO\n"
                    "\t\t             4. SETOR UANG\n\n"
                    "\t\t===================================================\n\n";
            cout << "\t\t  pilih : ";
        }

        system("cls");

        switch (pilihMenu) {
            case 1:
                transfer(index);
                break;
            case 2:
                cekSaldo(index);
                break;
            case 3:
                tarikUang(index);
                break;
            case 4:
                setor(index);
                break;
            default:
                header();
                cout << "\t\t===================================================\n\n"
                        "\t\t              Pilihan tidak valid!\n\n"
                        "\t\t===================================================\n\n";
                system("pause");
                system("cls");
                continue; // Ulangi loop jika pilihan tidak valid
        }

        header();
        cout << "\t\t       Ingin melakukan transaksi kembali? \n\n"
                "\t\t              1. Ya       2. Tidak \n\n"
                "\t\t===================================================\n\n"
                "\t\t pilih : ";

        // Validasi input untuk memastikan bahwa input adalah angka
        while (!(cin >> pilih)) {
            cin.clear(); // Mengembalikan status input stream ke normal
            cin.ignore(); // Menghapus karakter yang tidak valid dari input buffer
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|     Input tidak valid. Masukkan angka!           |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");

            header();
            cout << "\t\t       Ingin melakukan transaksi kembali? \n\n"
                    "\t\t              1. Ya       2. Tidak \n\n"
                    "\t\t===================================================\n\n";
            cout << "\t\t  pilih : ";
        }

        system("cls");

    } while (pilih == 1);
}

int menuAdmin() {
    int pilihMenu = -1;
    while (true) {
        system("cls");
        header();
        cout << "\t\t             1. LIHAT DATA USER\n"
                "\t\t             2. HAPUS DATA USER\n"
                "\t\t             3. KEMBALI KE MENU UTAMA\n\n"
                "\t\t===================================================\n\n";
        cout << "\t\t  pilih : ";

        // Validasi input untuk memastikan bahwa input adalah angka
        while (!(cin >> pilihMenu)) {
            cin.clear(); // Mengembalikan status input stream ke normal
            cin.ignore(); // Menghapus karakter yang tidak valid dari input buffer
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|     Input tidak valid. Masukkan angka!           |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");

            header();
            cout << "\t\t             1. LIHAT DATA USER\n"
                    "\t\t             2. HAPUS DATA USER\n"
                    "\t\t             3. KEMBALI KE MENU UTAMA\n\n"
                    "\t\t===================================================\n\n";
            cout << "\t\t  pilih : ";
        }

        if (pilihMenu == 1) {
            system("cls");
            LihatDataUser();
            searchUserByUsername();
        } else if (pilihMenu == 2) {
            system("cls");
            LihatDataUser();
            string usernameToDelete;
            cout << "\t\t Masukkan username yang ingin dihapus: ";
            cin >> usernameToDelete;
            system("cls");
            deleteUserByUsername(usernameToDelete);
        } else if (pilihMenu == 3) {
            system("cls");
            return 0; // Kembali ke menu utama
        } else {
            cout << "\t\t===================================================\n\n"
                    "\t\t              Pilihan tidak valid!\n\n"
                    "\t\t===================================================\n\n";
            system("pause");
        }
    }

    return pilihMenu;
}


void menuUtama() {
    int pilihMenu;
    int i = 0;
    int index = -1; // Tambahkan variabel index untuk menyimpan indeks pengguna yang login

    do {
        header();
        cout << "\t\t             1. REGISTRASI\n"
                "\t\t             2. LOGIN USER\n"
                "\t\t             3. LOGIN ADMIN\n"
                "\t\t             4. KELUAR\n\n"
                "\t\t===================================================\n\n";
        cout << "\t\t  pilih : ";

        // Validasi input untuk memastikan bahwa input adalah angka
        while (!(cin >> pilihMenu)) {
            cin.clear(); // Mengembalikan status input stream ke normal
            cin.ignore(); // Menghapus karakter yang tidak valid dari input buffer
            cout << "\n\n\n";
            cout << "\t\t===================================================\n"
                    "\t\t|     Input tidak valid. Masukkan angka!           |\n"
                    "\t\t===================================================\n";
            system("pause");
            system("cls");

            header();
            cout << "\t\t             1. REGISTRASI\n"
                    "\t\t             2. LOGIN USER\n"
                    "\t\t             3. LOGIN ADMIN\n"
                    "\t\t             4. KELUAR\n\n"
                    "\t\t===================================================\n\n";
            cout << "\t\t  pilih : ";
        }

        system ("cls");

        if (pilihMenu == 1) {
            registrasiUser();

        } else if (pilihMenu == 2) {
            index = loginuser(); // Simpan indeks pengguna yang berhasil login
            if (index != -1) { // Cek apakah login berhasil
                menuUser(index); // Panggil menuUser dengan indeks pengguna yang berhasil login
            }
        } else if (pilihMenu == 3) {
            loginadmin();
            menuAdmin();

        } else if (pilihMenu == 4) {
            saveUsersToCSV();
            break;

        } else {
            cout << "\t\t===================================================\n\n"
                    "\t\t              Pilihan tidak valid!\n\n"
                    "\t\t===================================================\n\n";
            system("pause");
            system("cls");
            i++; // Tambahkan nilai i setiap kali pilihan tidak valid
        }
    } while (i < 3); // Melanjutkan perulangan selama i kurang dari 3

    if (i >= 3) {
        cout << "Limit percobaan melebihi batas." << endl;
        exit(0); // Keluar dari program jika limit percobaan melebihi batas
    }
}


int main()
{
    loadUsersFromCSV();
    menuUtama();
    saveUsersToCSV();
    return 0;
}
