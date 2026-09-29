#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

typedef struct {
    float speed;
    float fuel;
    float engineTemp;
    bool isEngineOn;
} Car;

void initializeCar(Car* car) {
    car->speed = 0.0f;
    car->fuel = 100.0f;
    car->engineTemp = 25.0f;
    car->isEngineOn = false;
}

void updateCar(Car* car, int throttlePressed) {
    if (!car->isEngineOn) return;

    if (car->engineTemp >= 110.0f) {
        car->isEngineOn = false;
        car->speed = 0.0f;
        return;
    }

    float fuelFactor = 1.0f;
    if (car->engineTemp < 70.0f) {
        fuelFactor = 1.3f;
    }
    else if (car->engineTemp > 95.0f) {
        fuelFactor = 1.4f;
    }

    if (throttlePressed) {
        car->speed += 4.0f;
        car->engineTemp += 1.2f;
        car->fuel -= (0.4f * fuelFactor);
    }
    else {
        if (car->speed > 0) car->speed -= 2.0f;
        if (car->engineTemp > 25.0f) car->engineTemp -= 0.8f;
    }

    car->fuel -= (0.05f * fuelFactor);

    if (car->speed < 0.0f) car->speed = 0.0f;
    if (car->fuel < 0.0f) car->fuel = 0.0f;
}

void logDataToFile(FILE* file, Car* car) {
    if (file != NULL) {
        fprintf(file, "%.1f,%.1f,%.1f,%d\n", car->speed, car->fuel, car->engineTemp, car->isEngineOn);
        fflush(file);
    }
}

void drawDashboard(Car* car) {
    system("cls");

    printf("==================================================\n");
    printf("               ARAC KONTROL PANELI                \n");
    printf("==================================================\n\n");

    printf(" [KONTROLLER]                 | [ANLIK GOSTERGELER]\n");
    printf(" [B] Araci/Kontagi Ac         | --------------------\n");
    printf(" [W] Gaza Bas                 | Hiz      : %6.1f km/s\n", car->speed);
    printf(" [S] Gazdan Cek / Fren        | Yakit    : %6.1f %%\n", car->fuel);
    printf(" [X] Simulasyondan Cik        | Sicaklik : %6.1f C\n", car->engineTemp);
    printf("                              | Motor    : %s\n", car->isEngineOn ? "CALISIYOR" : "KAPALI");
    printf("--------------------------------------------------\n");

    if (car->engineTemp >= 110.0f) {
        printf("[!] KRITIK: Motor hararet yapti ve guvenlik icin KAPANDI! Sogumasini bekleyin.\n");
    }
    else if (car->engineTemp > 95.0f) {
        printf("[!] DIKKAT: Motor asiri isindi! ( > 95 C )\n");
    }

    if (car->fuel < 15.0f && car->fuel > 0.0f) {
        printf("[!] UYARI: Yakit seviyesi kritik azaldi!\n");
    }
    if (car->fuel <= 0.0f) {
        printf("[X] Yakit bitti! Arac durdu.\n");
    }

    printf("\nBir tus secin (W/S/B/X): ");
}

int main() {
    Car myCar;
    initializeCar(&myCar);

    FILE* logFile = fopen("car_log.csv", "w");
    if (logFile != NULL) {
        fprintf(logFile, "Speed,Fuel,EngineTemp,IsEngineOn\n");
    }

    bool running = true;

    while (running) {
        drawDashboard(&myCar);

        if (_kbhit()) {
            char key = _getch();

            if (key == 'b' || key == 'B') {
                if (myCar.engineTemp >= 90.0f) {
                }
                else if (myCar.fuel <= 0.0f) {
                }
                else {
                    myCar.isEngineOn = true;
                }
            }
            else if (key == 'w' || key == 'W') {
                if (myCar.isEngineOn && myCar.fuel > 0) {
                    updateCar(&myCar, 1);
                }
            }
            else if (key == 's' || key == 'S') {
                if (myCar.isEngineOn) {
                    updateCar(&myCar, 0);
                }
            }
            else if (key == 'x' || key == 'X') {
                running = false;
            }
        }
        else {
            if (myCar.isEngineOn && myCar.fuel > 0) {
                updateCar(&myCar, 0);
            }
            else if (!myCar.isEngineOn && myCar.engineTemp > 25.0f) {
                myCar.engineTemp -= 0.5f;
                if (myCar.engineTemp < 25.0f) myCar.engineTemp = 25.0f;
            }
            Sleep(400);
        }

        logDataToFile(logFile, &myCar);
    }

    if (logFile != NULL) {
        fclose(logFile);
    }

    printf("\nSimulasyon sonlandirildi ve veriler 'car_log.csv' dosyasina kaydedildi.\n");
    return 0;
}