#include <iostream>

using namespace std;

int main()
{
    double suhu, Hasil_Konversi;
    int Pilih_Suhu, Konversi_Suhu;
    string lanjut;

    string nama, nim;
    int Coba_Login = 0;
    bool Login_Berhasil = false;

    while (!Login_Berhasil && Coba_Login < 3) {

        cout << "Masukkan Nama :";
        cin >> nama;
        cout << "Masukkan NIM :";
        cin >> nim;

        // Nama : Robby_Pratama
        // NIM : 2309106113
        if (nama == "Robby_Pratama" && nim == "2309106113") {
            Login_Berhasil = true;
            cout << "Login Berhasil!!" << endl;

        } else {
            cout << "Login Gagal. Silahkan Ulangi lagi..." << endl;
            Coba_Login++;
        }
    }

    if (!Login_Berhasil) {
        cout << "Gagal login sebanyak 3 kali..." << endl;
        cout << endl;
        cout << "[Program Selesai]" << endl;
        return 0;
    }

    do {
    // Agar Output tidak kepanjangan
    system ("cls");

    cout << "Menu Suhu" << endl;
    cout << "[1]. Celcius" << endl;
    cout << "[2]. Reamur" << endl;
    cout << "[3]. Fahrenheit" << endl;
    cout << "[4]. Kelvin" << endl;
    cout << "Pilih Suhu (1/2/3/4) :";
    cin >> Pilih_Suhu;

    if (Pilih_Suhu == 1) {
        cout << "Konversi Suhu" << endl;
        cout << "[1]. Reamur" << endl;
        cout << "[2]. Fahrenheit" << endl;
        cout << "[3]. Kelvin" << endl;
        cout << "Pilih Suhu Untuk Di Konversi (1/2/3) :";
        cin >> Konversi_Suhu;

        if (Konversi_Suhu == 1) {
            cout << "Masukkan Suhu Dalam Celcius :";
            cin >> suhu;

            Hasil_Konversi = suhu * 4 / 5;
            cout << "Reamur :" << Hasil_Konversi << endl;

        } else if (Konversi_Suhu == 2) {
            cout << "Masukkan Suhu Dalam Celcius :";
            cin >> suhu;

            Hasil_Konversi = ( suhu * 9 / 5) + 32;
            cout << "Fahrenheit :" << Hasil_Konversi << endl;

        } else {
            cout << "Masukkan Suhu Dalam Celcius :";
            cin >> suhu;

            Hasil_Konversi = suhu + 273.15;
            cout << "Kelvin :" << Hasil_Konversi << endl;
        }

    } else if (Pilih_Suhu == 2) {
        cout << "Konversi Suhu" << endl;
        cout << "[1]. Celcius" << endl;
        cout << "[2]. Fahrenheit" << endl;
        cout << "[3]. Kelvin" << endl;
        cout << "Pilih Suhu Untuk Di Konversi (1/2/3) :";
        cin >> Konversi_Suhu;

        if (Konversi_Suhu == 1) {
            cout << "Masukkan Suhu Dalam Reamur :";
            cin >> suhu;

            Hasil_Konversi = suhu * 5 / 4;
            cout << "Celcius :" << Hasil_Konversi << endl;

        } else if (Konversi_Suhu == 2) {
            cout << "Masukkan Suhu Dalam Reamur :";
            cin >> suhu;

            Hasil_Konversi = ( suhu * 9 / 4) + 32;
            cout << "Fahrenheit :" << Hasil_Konversi << endl;

        } else {
            cout << "Masukkan Suhu Dalam Reamur :";
            cin >> suhu;

            Hasil_Konversi = (suhu * 5 / 4) + 273.15;
            cout << "Kelvin :" << Hasil_Konversi << endl;
        }

    } else if (Pilih_Suhu == 3) {
        cout << "Konversi Suhu" << endl;
        cout << "[1]. Celcius" << endl;
        cout << "[2]. Reamur" << endl;
        cout << "[3]. Kelvin" << endl;
        cout << "Pilih Suhu Untuk Di Konversi (1/2/3) :";
        cin >> Konversi_Suhu;

        if (Konversi_Suhu == 1) {
            cout << "Masukkan Suhu Dalam Fahrenheit :";
            cin >> suhu;

            Hasil_Konversi = (suhu - 32) * 5 / 9;
            cout << "Celcius :" << Hasil_Konversi << endl;

        } else if (Konversi_Suhu == 2) {
            cout << "Masukkan Suhu Dalam Fahrenheit :";
            cin >> suhu;

            Hasil_Konversi = ( suhu - 32) * 4 / 9;
            cout << "Reamur :" << Hasil_Konversi << endl;

        } else {
            cout << "Masukkan Suhu Dalam Fahrenheit :";
            cin >> suhu;

            Hasil_Konversi = (suhu - 32) * 5 / 9 + 273.15;
            cout << "Kelvin :" << Hasil_Konversi << endl;
        }

    } else {
        cout << "Konversi Suhu" << endl;
        cout << "[1]. Celcius" << endl;
        cout << "[2]. Reamur" << endl;
        cout << "[3]. Fahrenheit" << endl;
        cout << "Pilih Suhu Untuk Di Konversi (1/2/3) :";
        cin >> Konversi_Suhu;

        if (Konversi_Suhu == 1) {
            cout << "Masukkan Suhu Dalam Kelvin :";
            cin >> suhu;

            Hasil_Konversi = suhu - 273.15;
            cout << "Celcius :" << Hasil_Konversi << endl;

        } else if (Konversi_Suhu == 2) {
            cout << "Masukkan Suhu Dalam Kelvin :";
            cin >> suhu;

            Hasil_Konversi = (suhu - 273.15) * 4 / 5;
            cout << "Reamur :" << Hasil_Konversi << endl;

        } else {
            cout << "Masukkan Suhu Dalam Kelvin :";
            cin >> suhu;

            Hasil_Konversi = (suhu - 273.15) * 9 / 5 + 32;
            cout << "Fahrenheit :" << Hasil_Konversi << endl;
        }
    }

    cout << "Mau Lanjut (Ya/Tidak) :";
    cin >> lanjut;

    } while (lanjut == "Ya");
    cout << endl;
    cout << "[Program Selesai]" << endl;


    return 0;
}
