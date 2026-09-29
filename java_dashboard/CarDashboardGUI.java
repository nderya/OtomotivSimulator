package com.example.carsim1java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class CarDashboardGUI extends JFrame {
    private JLabel lblSpeed;
    private JLabel lblFuel;
    private JLabel lblTemp;
    private JLabel lblStatus;

    public CarDashboardGUI() {
        setTitle("Otomotiv Simülasyon Paneli - Gerçek Zamanlı");
        setSize(450, 350);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(5, 1, 10, 10));

        JLabel lblTitle = new JLabel("--- GERÇEK ZAMANLI ARAÇ GÖSTERGELERİ ---", JLabel.CENTER);
        lblTitle.setFont(new Font("Arial", Font.BOLD, 14));
        add(lblTitle);

        lblSpeed = new JLabel("Hız: 0.0 km/s", JLabel.CENTER);
        lblSpeed.setFont(new Font("Arial", Font.BOLD, 18));
        lblSpeed.setForeground(Color.BLUE);
        add(lblSpeed);

        lblFuel = new JLabel("Yakıt: 100.0 %", JLabel.CENTER);
        lblFuel.setFont(new Font("Arial", Font.BOLD, 18));
        lblFuel.setForeground(new Color(0, 128, 0));
        add(lblFuel);

        lblTemp = new JLabel("Sıcaklık: 25.0 C", JLabel.CENTER);
        lblTemp.setFont(new Font("Arial", Font.BOLD, 18));
        lblTemp.setForeground(Color.RED);
        add(lblTemp);

        lblStatus = new JLabel("Motor: KAPALI", JLabel.CENTER);
        lblStatus.setFont(new Font("Arial", Font.BOLD, 16));
        add(lblStatus);

        Timer timer = new Timer(300, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateDataFromLog();
            }
        });
        timer.start();
    }

    private void updateDataFromLog() {
        String csvFile = "C:\\Users\\derya\\source\\repos\\CarSim1\\CarSim1\\car_log.csv";
        String line;
        String lastLine = null;

        try (BufferedReader br = new BufferedReader(new FileReader(csvFile))) {
            String header = br.readLine();
            while ((line = br.readLine()) != null) {
                lastLine = line;
            }

            if (lastLine != null) {
                String[] data = lastLine.split(",");
                if (data.length >= 4) {
                    String speed = data[0];
                    String fuel = data[1];
                    String temp = data[2];
                    String status = data[3].equals("1") ? "ÇALIŞIYOR" : "KAPALI";

                    lblSpeed.setText("Hız: " + speed + " km/s");
                    lblFuel.setText("Yakıt: " + fuel + " %");
                    lblTemp.setText("Sıcaklık: " + temp + " C");
                    lblStatus.setText("Motor: " + status);
                }
            }
        } catch (IOException ex) {
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new CarDashboardGUI().setVisible(true);
        });
    }
}