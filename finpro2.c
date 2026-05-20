#include <stdio.h>
#include <string.h>

enum tingkatStress {
    RENDAH,
    SEDANG,
    TINGGI
};

union dataHasil {
    int skorTotal;
};

struct dataBase {
    char nama[100];
    union dataHasil hasil;
    enum tingkatStress kategori;
};

void tampilanDashboard(struct dataBase *data) {
    printf("===  Welcome Caretaker! :3  ===\n");
    printf("Masukkan nama pasien terlebih dahulu: ");
    scanf(" %[^\n]", data->nama);
    printf("[Sistem]: Silahkan Caretaker menilai kondisi %s berdasarkan 10 poin berikut.\n\n", data->nama);   
    printf("Silahkan isi pertanyaan dibawah ini dengan skala (0-5)\n");
    printf("0: Tidak Sama Sekali\n1: Sangat Rendah\n2: Rendah\n3: Sedang\n4: Tinggi\n5: Sangat Tinggi\n\n");
}

void prosesAsesmen(struct dataBase *data) {
    int totalSkor = 0, skala;
    char pertanyaan[10][200] = {
        "Seberapa sering orang tersebut merasa kesulitan mengendalikan hal-hal penting dalam hidupnya?",
        "Seberapa sering orang tersebut merasa gugup atau tertekan karena tugas dan aktivitas sehari-hari?",
        "Seberapa sering orang tersebut merasa tidak mampu menyelesaikan semua pekerjaan yang harus dilakukan?",
        "Seberapa sering orang tersebut merasa percaya diri dalam menghadapi masalah pribadi maupun akademik?",
        "Seberapa sering orang tersebut merasa bahwa masalah datang terlalu banyak sekaligus?",
        "Seberapa sering orang tersebut merasa marah atau kesal karena sesuatu yang tidak dapat dikendalikan?",
        "Seberapa sering orang tersebut merasa segala sesuatu berjalan sesuai harapan?",
        "Seberapa sering orang tersebut merasa kewalahan dengan tanggung jawab yang dimiliki?",
        "Seberapa sering orang tersebut merasa mampu mengatur waktu dan aktivitas dengan baik?",
        "Seberapa sering orang tersebut merasa stres memengaruhi kondisi belajar atau kehidupan sehari-hari?",
    };
    for(int i=0; i<10; i++) {
        printf("[%d/10] %s\n", i+1, pertanyaan[i]);
        printf("Skor Caretaker (0-5): ");
        scanf("%d", &skala);
        while(skala < 0 || skala > 5) {
            printf("Input invalid! Masukkan kembali skala (0-5): ");
            scanf("%d", &skala);
        }
        if(i == 3 || i == 6 || i == 8) {
            switch(skala) {
                case 0:
                    skala = 5;
                    break;
                case 1: 
                    skala = 4;
                    break;
                case 2:
                    skala = 3;
                    break;
                case 3:
                    skala = 2;
                    break;
                case 4:
                    skala = 1;
                    break;
                case 5:
                    skala = 0;
                    break;
            }
        }
        totalSkor += skala;
        printf("\n");
    }

    data->hasil.skorTotal = totalSkor;
    if (totalSkor <= 18) {
        data->kategori = RENDAH;
    } else if (totalSkor <= 32) {
        data->kategori = SEDANG;
    } else {
        data->kategori = TINGGI;
    }
}

void tampilHasilEvaluasi(struct dataBase data) {
    printf("==================================================================\n");
    printf("Hasil Evaluasi\n");
    printf("Nama yang diperiksa : %s\n", data.nama);
    printf("Total Skor PSS      : %d\n", data.hasil.skorTotal);
    
    if (data.kategori == RENDAH) {
        printf("Kategori            : Stres Rendah\n");
        printf("Saran Caretaker     : Kondisi yang bersangkutan relatif stabil. Tetap pantau\n");
        printf("                      dan berikan dukungan moral harian secara berkala.\n");
    } else if (data.kategori == SEDANG) {
        printf("Kategori            : Stres Sedang\n");
        printf("Saran Caretaker     : Dia mulai kewalahan. Bantu kurangi beban aktivitasnya,\n");
        printf("                      ajak bicara santai, dan ingatkan untuk istirahat.\n");
    } else {
        printf("Kategori            : Stres Tinggi (Butuh Perhatian Khusus)\n");
        printf("Saran Caretaker     : Tingkat stres parah. Mohon dampingi yang bersangkutan\n");
        printf("                      untuk segera berkonsultasi dengan psikolog atau profesional.\n");
        printf("-------------------------------------------------------------\n");
        printf("Layanan Dukungan & Kesehatan Mental untuk mahasiswa UI:\n");
        printf("1. Klinik Makara Satelite UI\n");
        printf("2. RS Universitas Indonesia\n");
        printf("3. LPT Fakultas Psikologi\n");
    }
}

int main(void) {
    struct dataBase pasien;
    tampilanDashboard(&pasien);
    prosesAsesmen(&pasien);
    tampilHasilEvaluasi(pasien);
    return 0;
}