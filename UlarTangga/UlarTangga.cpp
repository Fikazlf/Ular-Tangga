#include <iostream>
#include <cstdlib> // Library untuk fungsi rand() dan srand()
#include <ctime> // Library untuk fungsi time()

using namespace std;


// Fungsi untuk melempar dadu dan mengembalikan nilai dadu yang keluar
int LemparDadu() {
    return rand() % 6 + 1; // Menghasilkan nilai acak dari 1 hingga 6
}

// Fungsi untuk memindahkan pemain berdasarkan jumlah langkah dadu dan posisi ular/tangga
int pindahPosisi(int Posisi, int acakDadu, int UlarTangga[][2], int jumUlarTangga) {
    Posisi += acakDadu; // Menambahkan jumlah langkah dadu ke posisi pemain

    // Memeriksa apakah pemain berada pada posisi ular atau tangga
    for (int i = 0; i < jumUlarTangga; i++) {
        if (Posisi == UlarTangga[i][0]) { // Jika pemain berada pada posisi ular/tangga
            Posisi = UlarTangga[i][1]; // Pemain dipindahkan ke posisi tujuan ular/tangga

            // Menampilkan pesan apakah pemain naik tangga atau turun ular
            if (Posisi > UlarTangga[i][0]) {
                cout << "Pemain naik tangga ke posisi: " << Posisi << endl;
            } else {
                cout << "Pemain turun ular ke posisi: " << Posisi << endl;
            }
            break;
        }
    }

    return Posisi; // Mengembalikan posisi baru pemain setelah dipindahkan
}

int main() {
    srand(time(0)); // Menginisialisasi seed untuk fungsi rand() dengan waktu saat ini

    int JumPemain; // Variabel untuk menyimpan jumlah pemain
    cout << "Masukkan jumlah petualang : ";
    cin >> JumPemain; // Meminta input jumlah pemain dari pengguna
    cin.ignore(); // Membersihkan buffer

    // Memeriksa apakah jumlah pemain valid
    if (JumPemain <= 0) {
        cout << "Jumlah petualang tidak valid." << endl; // Menampilkan pesan kesalahan
        return 0; // Mengakhiri program
    }

    const int MaxPemain = JumPemain; // Batasan maksimal jumlah pemain
    int PosisiPemain[MaxPemain] = {0}; // Array untuk menyimpan posisi setiap pemain
    int PemainSelesai[MaxPemain] = {0}; // Array untuk menyimpan pemain yang telah selesai permainan
    int JumlahPemainSelesai = 0; // Variabel untuk menghitung jumlah pemain yang telah selesai

    cout << "=================== ULAR TANGGA ========================" << endl;
    cout << "================ Permainan dimulai! ====================" << endl;
    cout << endl;

    // Array dua dimensi untuk menyimpan posisi ular dan tangga
    int UlarTangga[][2] = {
        {3, 21},   // Tangga dari posisi 3 ke 21
        {8, 30},  // Tangga dari posisi 8 ke 30
        {17, 12},  // Ular dari posisi 17 ke 12
        {28, 84},  // Tangga dari posisi 28 ke 84
        {88, 18},   // Ular dari posisi 88 ke 18
        {58, 77},   // Tangga dari posisi 58 ke 77
        {97, 79},  // Ular dari posisi 97 ke 79
        {60, 20},  // Ular dari posisi 60 ke 20
        {54, 81},  // Tangga dari posisi 54 ke 81
    };
    int jumUlarTangga = sizeof(UlarTangga) / sizeof(UlarTangga[0]); // Menghitung jumlah ular/tangga

    bool gameSelesai = false; // Variabel untuk menandakan apakah permainan telah selesai

    // Loop utama permainan
    while (!gameSelesai) {
        for (int i = 0; i < JumPemain; i++) { // Iterasi untuk setiap pemain
            if (PosisiPemain[i] == 100)
                continue; // Skip iterasi jika pemain sudah mencapai posisi 100

            cout << "Giliran Petualang " << (i + 1) << endl; // Menampilkan pesan giliran pemain

            cout << "Tekan Enter untuk mengocok dadu...";
            cin.ignore(); // Menunggu input enter dari pengguna

            int acakDadu = LemparDadu(); // Melempar dadu untuk mendapatkan jumlah langkah
            cout << "Petualang " << (i + 1) << " mendapatkan angka dadu " << acakDadu << endl; // Menampilkan hasil lemparan dadu
        

            // Memindahkan pemain berdasarkan jumlah langkah dadu
            PosisiPemain[i] = pindahPosisi(PosisiPemain[i], acakDadu, UlarTangga, jumUlarTangga);

            // Memeriksa apakah pemain telah mencapai posisi 100
            if (PosisiPemain[i] == 100) {
                cout << "Petualang " << (i + 1) << " berhasil keluar hutan!" << endl; // Menampilkan pesan kemenangan
                PemainSelesai[JumlahPemainSelesai] = i; // Menyimpan indeks pemain yang telah selesai
                JumlahPemainSelesai++; // Menambah jumlah pemain yang telah selesai
            } else if (PosisiPemain[i] > 100) { // Jika pemain melewati posisi 100
                int sisa = PosisiPemain[i] - 100; // Menghitung jumlah langkah yang melewati 100
                PosisiPemain[i] = 100 - sisa; // Mundur ke posisi sebelum melewati 100
                cout << "Petualang melewati 100. Mundur ke posisi: " << PosisiPemain[i] << endl; // Menampilkan pesan
            }

            cout << "Posisi petualang " << (i + 1) << " sekarang: " << PosisiPemain[i] << endl; // Menampilkan posisi pemain
            cout << "===================================================" << endl;
        }

        // Memeriksa apakah semua pemain telah selesai permainan
        gameSelesai = (JumlahPemainSelesai == JumPemain);
    }

    system("cls"); //Menghapus layar jalannya game

    // Menampilkan ranking pemain berdasarkan urutan selesai
    cout << "================ Permainan Selesai!! ============="<< endl;
    cout << "================ Urutan Keluar Hutan ============="<< endl;
    cout << endl;
    for (int i = 0; i < JumlahPemainSelesai; i++) {
        int indeksPemain = PemainSelesai[i];
        cout << "Urutan keluar ke-" << (i + 1) << ": Petualang " << indeksPemain + 1 << endl;
    }

    return 0; // Mengakhiri program
}