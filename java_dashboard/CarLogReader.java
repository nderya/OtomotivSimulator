package com.example.carsim1java;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class CarLogReader {
    public static void main(String[] args) {
        String csvFile = "car_log.csv";
        String line;
        String lastLine = null;

        try (BufferedReader br = new BufferedReader(new FileReader(csvFile))) {
            String header = br.readLine(); // Başlığı atla

            while ((line = br.readLine()) != null) {
                lastLine = line;
            }

            if (lastLine != null) {
                String[] data = lastLine.split(",");
                String speed = data[0];
                String fuel = data[1];
                String temp = data[2];
                String status = data[3].equals("1") ? "CALISIYOR" : "KAPALI";

                System.out.printf("ANLIK -> Hız: %s km/s | Yakıt: %s%% | Sıcaklık: %s C | Motor: %s\n",
                        speed, fuel, temp, status);
            }

        } catch (IOException e) {
            System.out.println("[HATA] car_log.csv dosyası okunamadı.");
        }
    }
}