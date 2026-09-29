# Automotive Simulator & Dashboard (C & Java)

This project is a hybrid application that brings together a real-time vehicle simulator written in C and a Java Swing-based control panel (dashboard) to read and display data instantly.

## 🚀 Project Goal & Architecture

Our goal is to synchronize a low-level simulation engine with a desktop GUI technology by optimizing the data flow between them.

* **C Simulator (`c_simulator`):** Simulates vehicle data (such as instant speed, engine temperature, fuel level, and system status) and writes them to a `car_log.csv` file at regular intervals.
* **Java Dashboard (`java_dashboard`):** Listens to (polls) this log file in real-time using `javax.swing.Timer` in the background. It captures file updates and updates the UI smoothly and without lag.

## 🛠️ Technologies Used

* **Languages:** C, Java (Java Swing)
* **Development Environments:** Visual Studio, IntelliJ IDEA
* **Data Flow / Synchronization:** File-based real-time logging (`car_log.csv`) and high-performance `BufferedReader` mechanism.

## 📂 Folder Structure

```text
OtomotivSimulator/
│
├── c_simulator/       # C-based vehicle simulation source code
├── java_dashboard/    # Java Swing GUI and log reader source code
└── .gitignore         # Filter list ignoring unnecessary build and system files

```

## ⚙️️ Setup and Running

1. Clone the repository to your local machine:
```bash
git clone https://github.com/nderya/OtomotivSimulator.git

```


2. **Start the C Simulator:** Compile and run the `c_simulator` code via Visual Studio to start generating logs.
3. **Start the Java Dashboard:** Open the `java_dashboard` project in IntelliJ IDEA, run the application, and watch the real-time data reflect on the interface.
