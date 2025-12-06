#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct RentalItem {
    int id;
    string nama;
    string jenis;
    int harga;
    bool tersedia;
};

vector<RentalItem> dataRental;

// ---------------------- LOAD DATA ----------------------
void loadData() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "File input.txt tidak ditemukan. Memulai dengan data kosong.\n";
        return;
    }

    dataRental.clear();
    RentalItem item;

    while (file >> item.id) {
        file.ignore();
        getline(file, item.nama);
        getline(file, item.jenis);
        file >> item.harga;
        file >> item.tersedia;
        dataRental.push_back(item);
    }
    file.close();
    cout << "Data berhasil dimuat dari input.txt\n";
}

// ---------------------- SAVE DATA ----------------------
void saveData() {
    ofstream file("output.txt");
    for (auto &item : dataRental) {
        file << item.id << endl;
        file << item.nama << endl;
        file << item.jenis << endl;
        file << item.harga << endl;
        file << item.tersedia << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke output.txt\n";
}

// ---------------------- TAMPILKAN DATA ----------------------
void tampilData() {
    if (dataRental.empty()) {
        cout << "Tidak ada data tersedia.\n";
        return;
    }

    cout << "\n=== DATA RENTAL ===\n";
    for (auto &item : dataRental) {
        cout << "ID: " << item.id << endl;
        cout << "Nama: " << item.nama << endl;
        cout << "Jenis: " << item.jenis << endl;
        cout << "Harga Sewa: " << item.harga << endl;
        cout << "Status: " << (item.tersedia ? "Tersedia" : "Disewa") << endl;
        cout << "----------------------\n";
    }
}

// ---------------------- TAMBAH DATA ----------------------
void tambahData() {
    RentalItem item;
    cout << "Masukkan ID: ";
    cin >> item.id;
    cin.ignore();

    cout << "Masukkan Nama Item: ";
    getline(cin, item.nama);

    cout << "Masukkan Jenis Item: ";
    getline(cin, item.jenis);

    cout << "Masukkan Harga: ";
    cin >> item.harga;

    item.tersedia = true;

    dataRental.push_back(item);
    cout << "Data berhasil ditambahkan.\n";
}

// ---------------------- EDIT DATA ----------------------
void editData() {
    int id;
    cout << "Masukkan ID yang ingin diedit: ";
    cin >> id;

    for (auto &item : dataRental) {
        if (item.id == id) {
            cin.ignore();
            cout << "Nama baru: ";
            getline(cin, item.nama);
            cout << "Jenis baru: ";
            getline(cin, item.jenis);
            cout << "Harga baru: ";
            cin >> item.harga;

            cout << "Data berhasil diperbarui.\n";
            return;
        }
    }
    cout << "Data dengan ID tersebut tidak ditemukan.\n";
}

// ---------------------- HAPUS DATA ----------------------
void hapusData() {
    int id;
    cout << "Masukkan ID yang ingin dihapus: ";
    cin >> id;

    for (int i = 0; i < dataRental.size(); i++) {
        if (dataRental[i].id == id) {
            dataRental.erase(dataRental.begin() + i);
            cout << "Data berhasil dihapus.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// ---------------------- TRANSAKSI SEWA ----------------------
void sewa() {
    int id;
    cout << "Masukkan ID item yang ingin disewa: ";
    cin >> id;

    for (auto &item : dataRental) {
        if (item.id == id) {
            if (!item.tersedia) {
                cout << "Item sedang disewa.\n";
                return;
            }
            item.tersedia = false;
            cout << "Transaksi sewa berhasil.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// ---------------------- TRANSAKSI PENGEMBALIAN ----------------------
void kembali() {
    int id;
    cout << "Masukkan ID item yang ingin dikembalikan: ";
    cin >> id;

    for (auto &item : dataRental) {
        if (item.id == id) {
            if (item.tersedia) {
                cout << "Item sudah tersedia.\n";
                return;
            }
            item.tersedia = true;
            cout << "Item berhasil dikembalikan.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// ---------------------- MENU UTAMA ----------------------
int main() {
    int pilihan;
    loadData();

    do {
        cout << "\n=== MENU RENTAL ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Tambah Data\n";
        cout << "3. Edit Data\n";
        cout << "4. Hapus Data\n";
        cout << "5. Transaksi Sewa\n";
        cout << "6. Transaksi Pengembalian\n";
        cout << "7. Simpan Data\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: tampilData(); break;
        case 2: tambahData(); break;
        case 3: editData(); break;
        case 4: hapusData(); break;
        case 5: sewa(); break;
        case 6: kembali(); break;
        case 7: saveData(); break;
        case 0: cout << "Keluar program...\n"; break;
        default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
