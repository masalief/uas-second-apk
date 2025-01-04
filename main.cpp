#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

struct Mahasiswa {
    std::string NIM;
    std::string nama;
    double nilaiAkhir;
};

std::vector<Mahasiswa> dataMahasiswa;

void tambahDataMahasiswa() {
    int jumlah;
    std::cout << "Masukkan jumlah mahasiswa: ";
    std::cin >> jumlah;

    for (int i = 0; i < jumlah; ++i) {
        Mahasiswa mhs;
        std::cout << "Masukkan NIM Mahasiswa ke-" << i + 1 << ": ";
        std::cin >> mhs.NIM;
        std::cin.ignore(); // clear newline from buffer
        std::cout << "Masukkan Nama Mahasiswa ke-" << i + 1 << ": ";
        std::getline(std::cin, mhs.nama);
        std::cout << "Masukkan Nilai Akhir Mahasiswa ke-" << i + 1 << ": ";
        std::cin >> mhs.nilaiAkhir;
        dataMahasiswa.push_back(mhs);
    }

    std::cout << "Data berhasil ditambahkan!\n";
}

void tampilkanSemuaData() {
    if (dataMahasiswa.empty()) {
        std::cout << "Tidak ada data mahasiswa.\n";
        return;
    }

    std::cout << std::setw(10) << "NIM" << std::setw(20) << "Nama" << std::setw(15) << "Nilai Akhir" << "\n";
    for (const auto& mhs : dataMahasiswa) {
        std::cout << std::setw(10) << mhs.NIM << std::setw(20) << mhs.nama << std::setw(15) << mhs.nilaiAkhir << "\n";
    }
}

void cariDataMahasiswa() {
    std::string nim;
    std::cout << "Masukkan NIM yang ingin dicari: ";
    std::cin >> nim;

    for (const auto& mhs : dataMahasiswa) {
        if (mhs.NIM == nim) {
            std::cout << "Data ditemukan:\n";
            std::cout << "NIM: " << mhs.NIM << ", Nama: " << mhs.nama << ", Nilai Akhir: " << mhs.nilaiAkhir << "\n";
            return;
        }
    }

    std::cout << "Data dengan NIM " << nim << " tidak ditemukan.\n";
}

void urutkanData() {
    std::sort(dataMahasiswa.begin(), dataMahasiswa.end(), [](const Mahasiswa& a, const Mahasiswa& b) {
        return a.nilaiAkhir > b.nilaiAkhir;
    });

    std::cout << "Data berhasil diurutkan berdasarkan Nilai Akhir (descending).\n";
}

void simpanDataKeBerkas() {
    std::ofstream file("data_mahasiswa.txt");
    if (!file) {
        std::cerr << "Gagal membuka file untuk menulis.\n";
        return;
    }

    for (const auto& mhs : dataMahasiswa) {
        file << mhs.NIM << "," << mhs.nama << "," << mhs.nilaiAkhir << "\n";
    }

    file.close();
    std::cout << "Data berhasil disimpan ke data_mahasiswa.txt.\n";
}

void bacaDataDariBerkas() {
    std::ifstream file("data_mahasiswa.txt");
    if (!file) {
        std::cerr << "Gagal membuka file untuk membaca.\n";
        return;
    }

    dataMahasiswa.clear();
    Mahasiswa mhs;
    std::string line;
    while (std::getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 != std::string::npos && pos2 != std::string::npos && pos1 != pos2) {
            mhs.NIM = line.substr(0, pos1);
            mhs.nama = line.substr(pos1 + 1, pos2 - pos1 - 1);
            mhs.nilaiAkhir = std::stod(line.substr(pos2 + 1));
            dataMahasiswa.push_back(mhs);
        }
    }

    file.close();
    std::cout << "Data berhasil dibaca dari data_mahasiswa.txt.\n";
}

int main() {
    int pilihan;
    do {
        std::cout << "\nMenu Utama:\n";
        std::cout << "1. Tambah Data Mahasiswa\n";
        std::cout << "2. Tampilkan Semua Data\n";
        std::cout << "3. Cari Data Mahasiswa\n";
        std::cout << "4. Urutkan Data\n";
        std::cout << "5. Simpan Data ke Berkas\n";
        std::cout << "6. Baca Data dari Berkas\n";
        std::cout << "7. Keluar\n";
        std::cout << "Pilih opsi (1-7): ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahDataMahasiswa();
                break;
            case 2:
                tampilkanSemuaData();
                break;
            case 3:
                cariDataMahasiswa();
                break;
            case 4:
                urutkanData();
                break;
            case 5:
                simpanDataKeBerkas();
                break;
            case 6:
                bacaDataDariBerkas();
                break;
            case 7:
                std::cout << "Terima kasih telah menggunakan aplikasi ini!\n";
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
