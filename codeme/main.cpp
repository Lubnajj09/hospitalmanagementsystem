#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string contact;
    string medicalHistory;
};

struct Doctor {
    int id;
    string name;
    string specialization;
    bool available;
};

struct Appointment {
    int patientId;
    int doctorId;
    string date;
    string time;
};

vector<Patient> patients;
vector<Doctor> doctors;
vector<Appointment> appointments;
int patientIdCounter = 1;
int doctorIdCounter = 1;

void savePatientsToFile();
void loadPatientsFromFile();
void saveDoctorsToFile();
void loadDoctorsFromFile();
void saveAppointmentsToFile();
void loadAppointmentsFromFile();

void addPatient();
void searchAndUpdatePatient();
void addDoctor();
void manageAppointments();

int main() {
    loadPatientsFromFile();
    loadDoctorsFromFile();
    loadAppointmentsFromFile();

    int choice;
    while (true) {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Search and Update Patient\n";
        cout << "3. Add Doctor\n";
        cout << "4. Manage Appointments\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            searchAndUpdatePatient();
            break;
        case 3:
            addDoctor();
            break;
        case 4:
            manageAppointments();
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void savePatientsToFile() {
    ofstream file("patients.txt");
    for (const auto &p : patients) {
        file << p.id << ',' << p.name << ',' << p.age << ',' << p.contact << ',' << p.medicalHistory << '\n';
    }
    file.close();
}

void loadPatientsFromFile() {
    ifstream file("patients.txt");
    if (!file) return;
    Patient p;
    while (file >> p.id) {
        file.ignore();
        getline(file, p.name, ',');
        file >> p.age;
        file.ignore();
        getline(file, p.contact, ',');
        getline(file, p.medicalHistory);
        patients.push_back(p);
        patientIdCounter = max(patientIdCounter, p.id + 1);
    }
    file.close();
}

void saveDoctorsToFile() {
    ofstream file("doctors.txt");
    for (const auto &d : doctors) {
        file << d.id << ',' << d.name << ',' << d.specialization << ',' << d.available << '\n';
    }
    file.close();
}

void loadDoctorsFromFile() {
    ifstream file("doctors.txt");
    if (!file) return;
    Doctor d;
    while (file >> d.id) {
        file.ignore();
        getline(file, d.name, ',');
        getline(file, d.specialization, ',');
        file >> d.available;
        doctors.push_back(d);
        doctorIdCounter = max(doctorIdCounter, d.id + 1);
    }
    file.close();
}

void saveAppointmentsToFile() {
    ofstream file("appointments.txt");
    for (const auto &a : appointments) {
        file << a.patientId << ',' << a.doctorId << ',' << a.date << ',' << a.time << '\n';
    }
    file.close();
}

void loadAppointmentsFromFile() {
    ifstream file("appointments.txt");
    if (!file) return;
    Appointment a;
    while (file >> a.patientId) {
        file.ignore();
        file >> a.doctorId;
        file.ignore();
        getline(file, a.date, ',');
        getline(file, a.time);
        appointments.push_back(a);
    }
    file.close();
}

void addPatient() {
    Patient p;
    p.id = patientIdCounter++;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter patient age: ";
    cin >> p.age;
    cout << "Enter contact details: ";
    cin.ignore();
    getline(cin, p.contact);
    cout << "Enter medical history: ";
    getline(cin, p.medicalHistory);
    patients.push_back(p);
    savePatientsToFile();
    cout << "Patient added successfully with ID: " << p.id << "\n";
}

void searchAndUpdatePatient() {
    int id;
    cout << "Enter patient ID to search: ";
    cin >> id;
    for (auto &p : patients) {
        if (p.id == id) {
            cout << "Patient found: \n";
            cout << "Name: " << p.name << "\nAge: " << p.age << "\nContact: " << p.contact << "\nMedical History: " << p.medicalHistory << "\n";
            cout << "Do you want to update this patient's details? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, p.name);
                cout << "Enter new age: ";
                cin >> p.age;
                cout << "Enter new contact details: ";
                cin.ignore();
                getline(cin, p.contact);
                cout << "Enter new medical history: ";
                getline(cin, p.medicalHistory);
                savePatientsToFile();
                cout << "Patient details updated successfully.\n";
            }
            return;
        }
    }
    cout << "Patient not found.\n";
}

void addDoctor() {
    Doctor d;
    d.id = doctorIdCounter++;
    cout << "Enter doctor name: ";
    cin.ignore();
    getline(cin, d.name);
    cout << "Enter specialization: ";
    getline(cin, d.specialization);
    d.available = true;
    doctors.push_back(d);
    saveDoctorsToFile();
    cout << "Doctor added successfully with ID: " << d.id << "\n";
}

void manageAppointments() {
    int patientId, doctorId;
    string date, time;
    cout << "Enter patient ID: ";
    cin >> patientId;
    cout << "Enter doctor ID: ";
    cin >> doctorId;
    cout << "Enter appointment date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter appointment time (HH:MM): ";
    cin >> time;
    appointments.push_back({patientId, doctorId, date, time});
    saveAppointmentsToFile();
    cout << "Appointment scheduled successfully.\n";
}
