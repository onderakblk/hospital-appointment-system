#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    char tc[12];
} Patient;

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    char tc[12];
    char date[11];
    char clinic_name[50];
} Appointment;

Patient patients[MAX_PATIENTS];
Appointment appointments[MAX_APPOINTMENTS];


int appointment_count = 0;



void saveAppointmentsToFile() {
    FILE* file = fopen("appointments.txt", "w");
    if (file == NULL) {
        printf("Dosya olusturulurken bir hata olustu.\n");
        return;
    }

    for (int i = 0; i < appointment_count; i++) {
        fprintf(file, "%s,%s,%d,%s,%s,%s\n", appointments[i].first_name, appointments[i].last_name, appointments[i].age, appointments[i].tc, appointments[i].date, appointments[i].clinic_name);
    }

    fclose(file);
}

void loadAppointmentsFromFile() {
    FILE* file = fopen("appointments.txt", "r");
    if (file == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        strcpy(appointments[appointment_count].first_name, token);

        token = strtok(NULL, ",");
        strcpy(appointments[appointment_count].last_name, token);

        token = strtok(NULL, ",");
        appointments[appointment_count].age = atoi(token);

        token = strtok(NULL, ",");
        strcpy(appointments[appointment_count].tc, token);

        token = strtok(NULL, ",");
        strcpy(appointments[appointment_count].date, token);

        token = strtok(NULL, "\n");
        strcpy(appointments[appointment_count].clinic_name, token);

        appointment_count++;
    }

    fclose(file);
}


void addAppointment() {
    if (appointment_count >= MAX_APPOINTMENTS) {
        printf("Randevu eklemek icin yer yok.\n");
        return;
    }

    printf("Hasta adi: ");
    scanf("%s", appointments[appointment_count].first_name);

    printf("Hasta soyadi: ");
    scanf("%s", appointments[appointment_count].last_name);

    printf("Hasta yas: ");
    scanf("%d", &appointments[appointment_count].age);

    printf("Hasta TC kimlik numarasi: ");
    scanf("%s", appointments[appointment_count].tc);

    printf("Randevu tarihi (GG.AA.YYYY): ");
    scanf("%s", appointments[appointment_count].date);

    printf("Gelinen klinik adi: ");
    scanf("%s", appointments[appointment_count].clinic_name);

    appointment_count++;

    saveAppointmentsToFile();

    printf("Randevu basariyla kaydedildi.\n");
}



void listAppointments() {
    printf("----- Randevu Listesi -----\n");
    for (int i = 0; i < appointment_count; i++) {
        printf("Ad: %s\n", appointments[i].first_name);
        printf("Soyad: %s\n", appointments[i].last_name);
        printf("Yas: %d\n", appointments[i].age);
        printf("TC Kimlik No: %s\n", appointments[i].tc);
        printf("Tarih: %s\n", appointments[i].date);
        printf("Klinik: %s\n", appointments[i].clinic_name);
        printf("---------------------------\n");
    }
}
void searchAppointment() {
    printf("Randevu aramak icin secenekleri kullanin:\n");
    printf("1. Tarihe gore arama\n");
    printf("2. Klinik adina gore arama\n");
    printf("Seciminizi yapin: ");
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1: {
            char searchDate[11];
            printf("Randevu tarihini girin (GG.AA.YYYY): ");
            scanf("%s", searchDate);

            printf("----- Arama Sonuclari -----\n");
            for (int i = 0; i < appointment_count; i++) {
                if (strcmp(appointments[i].date, searchDate) == 0) {
                    printf("Ad: %s\n", appointments[i].first_name);
                    printf("Soyad: %s\n", appointments[i].last_name);
                    printf("Yas: %d\n", appointments[i].age);
                    printf("TC Kimlik No: %s\n", appointments[i].tc);
                    printf("Tarih: %s\n", appointments[i].date);
                    printf("Klinik: %s\n", appointments[i].clinic_name);
                    printf("---------------------------\n");
                }
            }
            break;
        }
        case 2: {
            char searchClinic[50];
            printf("Klinik adini girin: ");
            scanf("%s", searchClinic);

            printf("----- Arama Sonuclari -----\n");
            for (int i = 0; i < appointment_count; i++) {
                if (strcmp(appointments[i].clinic_name, searchClinic) == 0) {
                    printf("Ad: %s\n", appointments[i].first_name);
                    printf("Soyad: %s\n", appointments[i].last_name);
                    printf("Yas: %d\n", appointments[i].age);
                    printf("TC Kimlik No: %s\n", appointments[i].tc);
                    printf("Tarih: %s\n", appointments[i].date);
                    printf("Klinik: %s\n", appointments[i].clinic_name);
                    printf("---------------------------\n");
                }
            }
            break;
        }
        default:
            printf("Gecersiz secim. Ana menuye donuluyor...\n");
            break;
    }
}


int main() {
    loadAppointmentsFromFile();

    int choice;
    do {
        printf("----- Hasta Takip Otomasyonu -----\n");
        printf("1. Yeni randevu kaydi\n");
        printf("2. Randevu listesi\n");
        printf("3. Randevu arama\n");
        printf("0. Cikis\n");

        printf("Seciminizi yapin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                listAppointments();
                break;
            case 3:
                searchAppointment();
                break;

            case 0:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Geçersiz seçim. Tekrar deneyin.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
