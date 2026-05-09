#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>

#include"Bill.h"
#include"Doctor.h"
#include"Patient.h"
#include"FileHandler.h"
#include"Validator.h"
#include"Person.h"
#include"Utils.h"
#include"Storage.h"
#include"SlotsUnavailableException.h"
#include"Prescription.h"
#include"InvalidInputException.h"
#include"InsufficientFundsException.h"
#include"HospitalException.h"
#include"FileNotFoundException.h"
#include"Admin.h"
#include<iostream>
#include<fstream>
#include "Appointment.h"
using namespace std;
using namespace sf;

enum class AppState {
    LOGIN,
    SIGNUP,
    DASHBOARD
};

enum class UserType {
    PATIENT = 1,
    DOCTOR = 2,
    ADMIN = 3
};

bool isClicked(FloatRect bounds, Vector2i mousePos) {
    Vector2f point(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return bounds.contains(point);
}

void adminMenu(Admin* current, Storage<Doctor>& dStorage, Storage<Patient>& pStorage) {
    int choice = 0;
    while (true) {
        cout << "Admin Menu. Enter your choice" << endl;
        cout << "1. Add Doctor" << endl;
        cout << "2. Add Patient (New)" << endl;
        cout << "3. View All Patients" << endl;
        cout << "4. View Security Log" << endl;
        cout << "5. Log Out" << endl;
        cin >> choice;
        if (choice == 1) {
            int id;
            char name[20], spec[25], pass[25];
            float fee;
            cout << "Enter Doctor ID:\t";
            cin >> id;
            if (dStorage.findByID(id) != nullptr) {
                cout << "Error! A doctor with this id already exists.";
                continue;
            }
            cout << "Enter Name:\t";
            cin.ignore();
            cin.getline(name, 20);
            cout << "Enter specialization:\t";
            cin.getline(spec, 25);
            cout << "Enter Fee:\t";
            cin >> fee;
            cout << "Enter Initial Password:\t";
            cin >> pass;
            Doctor newDoc(id, name, spec, fee, pass);
            dStorage.add(newDoc);

            FileHandler::saveNewDoctor(newDoc);
            cout << "New doctor added successfully" << endl;

        }
        else if (choice == 2) {
            int id, age;
            char name[30], gender, contact[15], pass[15];
            float bal;

            cout << "Enter Patient ID:\t";
            cin >> id;
            if (pStorage.findByID(id) != nullptr) {
                cout << "Error! A patient with this id already exists.";
                continue;
            }
            cout << "Enter Patient Name:\t";
            cin.ignore();
            cin.getline(name, 30);

            cout << "Enter Patient Age:\t";
            cin >> age;

            cout << "Enter Patient Gender:\t";
            cin >> gender;

            cout << "Enter Patient Balance:\t";
            cin >> bal;

            cout << "Enter Patient Contact:\t";
            cin.ignore();
            cin.getline(contact, 15);

            cout << "Enter Patient Password:\t";
            cin.ignore();
            cin.getline(pass, 15);

            Patient newPat(id, name, age, gender, contact, pass, bal);
            pStorage.add(newPat);
            FileHandler::savePatient(newPat);
            cout << "Patient registered successfully!" << endl;
        }
        else if (choice == 3) {
            cout << "Registered Patients" << endl;
            for (int i = 0; i < pStorage.size(); i++) {
                cout << *pStorage.getAt(i) << endl;
            }
        }
        else if (choice == 4) {
            cout << "Security Incidents" << endl;
            FileHandler::displaySecurityLog();
        }
        else if (choice == 5) {
            return;
        }
    }
}
void patientMenu(Patient* current, Storage<Doctor>& dStorage, Storage<Appointment>& aStorage, Storage<Bill>& bStorage) {
    int choice = 0;
    while (true) {
        cout << "      Patient Menue      " << endl;
        cout << "1. Book Appointment" << endl;
        cout << "2. View Bills" << endl;
        cout << "3. Log Out" << endl;
        cin >> choice;
        if (choice == 1) {
            char searchSpec[25];
            cout << "Enter Specialization:\t";
            cin.ignore();
            cin.getline(searchSpec, 25);
            bool found = false;
            cout << "\n Available Doctors:\n";
            for (int i = 0; i < dStorage.size(); i++) {
                Doctor* d = dStorage.getAt(i);
                if (isSame(d->getSpecialization(), searchSpec)) {
                    dStorage.getAt(i)->display();
                    found = true;
                }
            }
            if (found) {
                int docID = -1;
                cout << "Enter the doctor ID to book:\t" << endl;
                cin >> docID;
                Doctor* selected = (Doctor*)dStorage.findByID(docID);
                if (selected) {
                    if (current->getBalance() >= selected->getFee()) {
                        *current -= selected->getFee();
                        Appointment newApp(selected->getID(), current->getID(), "10-05-2026");
                        aStorage.add(newApp);
                        FileHandler::saveAppointment(newApp);
                        Bill newBill(current->getID(), selected->getFee(), "Consultation");
                        bStorage.add(newBill);
                        FileHandler::saveBill(newBill);
                        cout << "Appointment booked successfully!" << endl;
                    }
                    else {
                        cout << "Error! Insufficient Funds" << endl;
                    }
                }
            }
            else {
                cout << "Sorry We could not find the specified specialization" << endl;
            }
        }
        else if (choice == 2) {
            cout << "Your Bills" << endl;
            for (int i = 0; i < bStorage.size(); i++) {
                if (bStorage.getAt(i)->getPatientID() == current->getID()) {
                    cout << *bStorage.getAt(i) << endl;
                }
            }
        }
        else {
            return;
        }
    }
}
void DoctorMenu(Doctor* current, Storage<Appointment>& aStorage) {
    int choice = 0;
    while (true) {
        cout << "    Doctor Menu     " << endl;
        cout << "1. View Appointments" << endl;
        cout << "2. Write Prescription" << endl;
        cout << "3. LogOut" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Your Appointments" << endl;
            for (int i = 0; i < aStorage.size(); i++) {
                if (aStorage.getAt(i)->getDoctorID() == current->getID()) {
                    aStorage.getAt(i)->display();
                }
            }
        }
        else if (choice == 2) {
            int pID;
            char meds[100];
            cout << "Enter Patient ID:\t";
            cin >> pID;
            cout << "Enter Medicines / Prescription:\t";
            cin.ignore();
            cin.getline(meds, 100);
            Prescription P(current->getID(), pID, meds);
            FileHandler::savePrescription(P);
            cout << "Prescription saved successfully!" << endl;
        }
        else {
            return;
        }
    }
}
void handleLogin(int type, Storage<Patient>& p, Storage<Doctor>& d, Storage<Admin>& a, Storage<Appointment>& aStorage, Storage<Bill>& bStorage) {
    int id, attempts = 0;
    char pass[30];

    while (attempts < 4) {
        cout << "Enter ID:\t";
        cin >> id;
        cout << "Enter Password:\t";
        cin >> pass;

        if (type == 1) {
            Patient* pat = static_cast<Patient*>(p.findByID(id));
            if (pat && isSame(pat->getPassword(), pass)) {
                patientMenu(pat, d, aStorage, bStorage);
                return;
            }
        }
        else if (type == 2) {
            Doctor* doc = static_cast<Doctor*>(d.findByID(id));
            if (doc && isSame(doc->getPassword(), pass)) {
                DoctorMenu(doc, aStorage);
                return;
            }
        }
        else if (type == 3) {
            Admin* admin = static_cast<Admin*>(a.findByID(id));
            if (admin && isSame(admin->getPassword(), pass)) {
                adminMenu(admin, d, p);
                return;
            }
        }
        else if (type == 4) {
            int id2;
            char name2[20], pass2[15];
            cout << "Enter the Admin ID:\t";
            cin >> id2;
            if (a.findByID(id2) != nullptr) {
                cout << "Error! Admin ID already exists." << endl;
                continue;
            }
            cout << "Enter Admin Name:\t";
            cin.ignore();
            cin.getline(name2, 30);
            cout << "Enter Password:\t";
            cin.getline(pass2, 30);
            Admin newAd(id2, name2, pass2);
            a.add(newAd);
            FileHandler::saveAdmin(newAd);
            cout << "Admin registered successfully!" << endl;
            return;
        }
        attempts++;
        cout << "Invalid Credentials! Attempt No:\t" << attempts << endl;
    }
    FileHandler::logSecurityIncident(id, "Failed Login");
}

void managementSystem();
int main()
{
    managementSystem();
    return 0;
}
void managementSystem() {
    RenderWindow window(VideoMode({ 1920, 1080 }), "Medicore Hospital Mangement System");

    static Storage<Appointment>* appStorage = nullptr;
    static Storage<Bill>* billStorage = nullptr;
    static Storage<Patient>* patientStorage = nullptr;
    static Storage<Doctor>* doctorStorage = nullptr;
    static Storage<Admin>* adminStorage = nullptr;
    static Storage<Prescription>* presStorage = nullptr;


    if (!patientStorage) patientStorage = new Storage<Patient>();
    if (!doctorStorage) doctorStorage = new Storage<Doctor>();
    if (!adminStorage) adminStorage = new Storage<Admin>();
    if (!appStorage) appStorage = new Storage<Appointment>();
    if (!billStorage) billStorage = new Storage<Bill>();
    if (!presStorage) presStorage = new Storage<Prescription>();

    try {
        FileHandler::loadPatients(*patientStorage);
        FileHandler::loadDoctors(*doctorStorage);
        FileHandler::loadAdmins(*adminStorage);
        FileHandler::loadAppointments(*appStorage);
        FileHandler::loadBills(*billStorage);
        FileHandler::loadPrescriptions(*presStorage);
    }
    catch (const HospitalException& e) {
        cout << "Error!!" << e.what() << endl;
        cout << "Please Ensure files exist" << endl;
        delete patientStorage;
        patientStorage = nullptr;
        delete doctorStorage;
        doctorStorage = nullptr;
        delete adminStorage;
        adminStorage = nullptr;
        return;
    }

    Texture backgroundTex;
    if (!backgroundTex.loadFromFile("Assets/login_logo.png")) {
        cerr << "Failed to load Assets/login_logo.png" << endl;
    }
    Sprite background(backgroundTex);

    Font ft("Assets/myFont.otf");

    auto bgBounds = background.getGlobalBounds();
    float bgWidth = bgBounds.size.x;
    background.setPosition({ 960.f - (bgWidth / 2.f), 100.f });
    Vector2u windowSize = window.getSize();
    auto spriteBounds = background.getLocalBounds();
    background.setScale({ static_cast<float>(windowSize.x) / spriteBounds.size.x, static_cast<float>(windowSize.y) / spriteBounds.size.y });

    AppState currentState = AppState::LOGIN;
    UserType selectedType = UserType::PATIENT;

    string idInput = "";
    string passInput = "";
    Clock cursorClock;
    bool showCursor = true;
    string signupName = "";
    string signupContact = "";
    string signupAge = "";
    string signupPass = "";
    int activeField = 0;
    int dashboardView = 0;
    vector<string> menuOptions;
    bool typingID = true;
    bool showDropDown = false;
    void* loggedInUser = nullptr;

    Text uiText(ft,"", 24);
    uiText.setFillColor(Color::Black);

    RectangleShape dropdownBox(Vector2f(200, 40));
    dropdownBox.setFillColor(Color(200, 200, 200));
    dropdownBox.setOutlineThickness(2);
    dropdownBox.setOutlineColor(Color::Black);

    while (window.isOpen()) {

        Time elapsed = cursorClock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.5f) {
            showCursor = !showCursor;
            cursorClock.restart();
        }
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<Event::KeyReleased>()) {
                if (keyPressed->code == Keyboard::Key::Tab) {
                    typingID = !typingID;
                }
                if (keyPressed->code == Keyboard::Key::Backspace) {
                    if (typingID && !idInput.empty()) {
                        idInput.pop_back();
                    }
                    else if (!typingID && !passInput.empty()) {
                        passInput.pop_back();
                    }
                }
            }
            if (const auto* textEntered = event->getIf<Event::TextEntered>()) {
                if (textEntered->unicode < 128) {
                    char characterTyped = static_cast<char>(textEntered->unicode);
                    string* target = nullptr;

                    if (currentState == AppState::LOGIN) {
                        target = typingID ? &idInput : &passInput;
                    }
                    else if (currentState == AppState::SIGNUP) {
                        if (activeField == 0) {
                            target = &signupName;
                        }
                        else if (activeField == 1) {
                            target = &signupAge;
                        }
                        else if (activeField == 2) {
                            target = &signupContact;
                        }
                        else if (activeField == 3) {
                            target = &signupPass;
                        }
                    }
                    if (target) {
                        if (characterTyped == '\b' && !target->empty()) {
                            target->pop_back();
                        }
                        else if (characterTyped >= 32 && characterTyped <= 126) {
                            bool isNumeric = (target == &idInput || target == &signupAge);
                            if (isNumeric) {
                                if (isdigit(characterTyped)) {
                                    *target += characterTyped;
                                }
                            }
                            else {
                                *target += characterTyped;
                            }
                        }
                    }
                }
            }
            if (const auto* mousePressed = event->getIf<Event::MouseButtonPressed>()) {
                if (mousePressed->button == Mouse::Button::Left) {
                    Vector2i mPos = Mouse::getPosition(window);

                    if (currentState == AppState::LOGIN) {

                        if (isClicked(FloatRect({ 100.f, 100.f },{ 200.f, 40.f
                    }), mPos)) {
                            showDropDown = !showDropDown;
                        }

                        if (showDropDown) {
                            if (isClicked(FloatRect({ 100.f, 140.f },{ 200.f, 40.f
                        }), mPos)) {
                                selectedType = UserType::PATIENT;
                                showDropDown = false;
                            }
                            if (isClicked(FloatRect({ 100.f, 180.f },{ 200.f, 40.f
                        }), mPos)) {
                                selectedType = UserType::DOCTOR;
                                showDropDown = false;
                            }
                            if (isClicked(FloatRect({ 100.f, 220.f },{ 200.f, 40.f
                        }), mPos)) {
                                selectedType = UserType::ADMIN;
                                showDropDown = false;
                            }
                        }

                        if (isClicked(FloatRect({ 400, 400 },{280, 50
                    }), mPos)) {
                            try {
                                int id = idInput.empty() ? 0 : stoi(idInput);
                                if (selectedType == UserType::PATIENT) {
                                    Patient* p = patientStorage->findByID(id);
                                    if (p && p->getPassword() == passInput) {
                                        loggedInUser = p;
                                        currentState = AppState::DASHBOARD;
                                    }
                                }
                                else if (selectedType == UserType::DOCTOR) {
                                    Doctor* d = doctorStorage->findByID(id);
                                    if (d && d->getPassword() == passInput) {
                                        loggedInUser = d;
                                        currentState = AppState::DASHBOARD;
                                    }
                                }
                                else if (selectedType == UserType::ADMIN) {
                                    Admin* a = adminStorage->findByID(id);
                                    if (a && a->getPassword() == passInput) {
                                        loggedInUser = a;
                                        currentState = AppState::DASHBOARD;
                                    }
                                }
                            }
                            catch (const std::exception& e) {
                                cout << "Input Error!  " << e.what() << endl;
                            }
                        }
                        if (isClicked(FloatRect({ 400.f, 550.f }, { 200.f, 50.f }), mPos)) {
                            currentState = AppState::SIGNUP;
                            idInput = "";
                            passInput = "";
                        }
                    }
                    else if (currentState == AppState::SIGNUP) {
                        Vector2i mPos = Mouse::getPosition(window);
                        if (isClicked(FloatRect({ 400.f, 200.f }, { 400.f, 40.f }), mPos)) {
                            activeField = 0;
                        }
                        if (isClicked(FloatRect({ 400.f, 260.f }, { 400.f, 40.f }), mPos)) {
                            activeField = 1;
                        }
                        if (isClicked(FloatRect({ 400.f, 320.f }, { 400.f, 40.f }), mPos)) {
                            activeField = 2;
                        }
                        if (isClicked(FloatRect({ 400.f, 380.f }, { 400.f, 40.f }), mPos)) {
                            activeField = 3;
                        }

                        if (isClicked(FloatRect({ 400.f, 500.f }, { 200.f, 50.f }), mPos)) {
                            try {
                                int newID = patientStorage->size() + 101;
                                Patient newPat(newID, signupName.c_str(), stoi(signupAge), 'M', signupContact.c_str(), signupPass.c_str(), 500.0f);
                                patientStorage->add(newPat);
                                FileHandler::savePatient(newPat);

                                signupName = ""; signupAge = ""; signupContact = ""; signupPass = "";
                                currentState = AppState::LOGIN;

                            }
                            catch (...) {
                                cout << "Invalid Signup Data! Please chec age and name" << endl;
                            }
                        }
                    }
                    else if (currentState == AppState::DASHBOARD && selectedType == UserType::PATIENT && dashboardView == 1) {
                        
                            int docIndex = (mPos.y - 100) / 40;
                            if (docIndex >= 0 && docIndex < doctorStorage->size()) {
                                Doctor* selectedDoc = doctorStorage->getAt(docIndex);
                                Patient* cur = static_cast<Patient*>(loggedInUser);

                                if (cur->getBalance() >= selectedDoc->getFee()) {
                                    *cur -= selectedDoc->getFee();
                                    Appointment newApp(selectedDoc->getID(), cur->getID(), "10-05-2026");
                                    appStorage->add(newApp);
                                    FileHandler::saveAppointment(newApp);

                                    Bill newBill(cur->getID(), selectedDoc->getFee(), "Consultation Fee");
                                    billStorage->add(newBill);
                                    FileHandler::saveBill(newBill);
                                    cout << "Successfully Booked Appointment!" << endl;
                                    dashboardView = 2;
                                }
                                else {
                                    cout << "Error! Insufficient Funds" << endl;
                                }
                            }
     
                    }
                    else if (currentState == AppState::DASHBOARD) {
                        if (mPos.x < 250) {
                            int clickedIndex = (mPos.y - 100) / 60;
                            if (clickedIndex >= 0 && clickedIndex < menuOptions.size()) {
                                if (menuOptions[clickedIndex] == "Logout") {
                                    currentState = AppState::LOGIN;
                                    loggedInUser = nullptr;
                                    idInput = "";
                                    passInput = "";
                                    dashboardView = 0;
                                }
                                else {
                                    dashboardView = clickedIndex + 1;
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(Color::White);
        window.draw(background);
        string cursor = showCursor ? "|" : "";

        if (currentState == AppState::LOGIN) {
            uiText.setString("Login as:\t" + to_string((int)selectedType));
            uiText.setPosition({ 500, 100 });
            window.draw(uiText);

            uiText.setString("ID:\t" + idInput + (typingID ? cursor : ""));
            uiText.setPosition({ 400, 300 });
            window.draw(uiText);

            uiText.setString("PASSWORD:\t" + string(passInput.length(), '*') + (!typingID ? cursor : ""));
            uiText.setPosition({ 400, 350 });
            window.draw(uiText);

            RectangleShape loginButton(Vector2f(280, 50));
            loginButton.setPosition({ 400, 400 });
            loginButton.setFillColor(Color(70, 130, 180));

            Text loginBtnText(ft, "Login", 24);
            FloatRect textBounds = loginBtnText.getLocalBounds();
            loginBtnText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f, textBounds.position.y + textBounds.size.y / 2.0f });
            loginBtnText.setPosition({ loginButton.getPosition().x + 100.f, loginButton.getPosition().y + 25.f });

            window.draw(loginButton);
            window.draw(loginBtnText);


            RectangleShape signupBtn({ 200.f, 50.f });
            signupBtn.setPosition({ 400, 550.f }); 
            signupBtn.setFillColor(Color::Black);
            signupBtn.setOutlineThickness(2);
            signupBtn.setOutlineColor(Color::Blue);

            Text signupBtnText(ft, "Sign Up", 20);
            signupBtnText.setPosition({ 400 + 50.f, 560.f });
            signupBtnText.setFillColor(Color::White);
            window.draw(signupBtn);

            window.draw(signupBtnText);
            uiText.setCharacterSize(24);

            dropdownBox.setPosition({100, 100});
            window.draw(dropdownBox);
            string typeStr = (selectedType == UserType::PATIENT) ? "Patient" : (selectedType == UserType::DOCTOR) ? "Doctor" : "Admin";
            uiText.setString(typeStr);
            uiText.setFillColor(Color::Black);
            uiText.setPosition({ 110, 105 });
            window.draw(uiText);

            if (showDropDown) {
                for (int i = 1; i <= 3; i++) {
                    dropdownBox.setPosition({100, (float) (100 + i * 40)});
                    window.draw(dropdownBox);
                }
                uiText.setString("Patient");
                uiText.setPosition({110, 145});
                window.draw(uiText);
                uiText.setString("Doctor");
                uiText.setPosition({ 110, 185 });
                window.draw(uiText);
                uiText.setString("Admin");
                uiText.setPosition({ 110, 225 });
                window.draw(uiText);
            }
        }
        else if (currentState == AppState::DASHBOARD) {
            RectangleShape sidebar({ 250, 1080 });
            sidebar.setFillColor(Color(45, 52, 54));
            window.draw(sidebar);
            if (selectedType == UserType::PATIENT) {
                menuOptions = { "Book Appointment", "View Bills", "My Profile", "Logout" };
            }
            else if (selectedType == UserType::DOCTOR) {
                menuOptions = { "Appointments", "Prescriptions", "Logout" };
            }
            else if (selectedType == UserType::ADMIN) {
                menuOptions = { "Add Doctor", "View Patients", "Security Log", "Logout" };
            }

            for (int i = 0; i < menuOptions.size(); i++) {
                uiText.setString(menuOptions[i]);
                uiText.setPosition({ 30, (float)(100 + i * 60) });
                uiText.setFillColor(Color::White);
                window.draw(uiText);
            }

            if (dashboardView == 0) {
                uiText.setString("Welcome to Medicore Hospital.\nSelect an Option to Proceed");
                uiText.setPosition({300, 100});
                window.draw(uiText);
            }
            else if (dashboardView == 1 && selectedType == UserType::PATIENT) {
                uiText.setString("Available Doctors (Click to Book):");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                float yPos = 100;
                for (int i = 0; i < doctorStorage->size(); i++) {
                    Doctor* d = doctorStorage->getAt(i);

                    RectangleShape row({ 600, 35 });
                    row.setPosition({ 290, yPos });
                    row.setFillColor(Color(240, 240, 240, 50));
                    window.draw(row);

                    uiText.setString(to_string(d->getID()) + ". " + d->getName() + " (" + d->getSpecialization() + "). Fees:\t" + to_string(d->getFee()));
                    uiText.setPosition({300, yPos});
                    uiText.setFillColor(Color::Black);
                    window.draw(uiText);
                    yPos += 40;
                }
            }
            else if (dashboardView == 1 && selectedType == UserType::DOCTOR) {
                Doctor* cur = static_cast<Doctor*>(loggedInUser);
                uiText.setString("Your Scheduled Appointments");
                uiText.setPosition({ 300, 50 });
                uiText.setFillColor(Color::Black);
                window.draw(uiText);

                float yOffset = 120;
                bool found = false;
                for (int i = 0; i < appStorage->size(); i++) {
                    if (appStorage->getAt(i)->getDoctorID() == cur->getID()) {
                        string appInfo = "Patient ID: " + to_string(appStorage->getAt(i)->getPatientID()) +
                            " | Date: " + appStorage->getAt(i)->getDate();
                        uiText.setString(appInfo);
                        uiText.setPosition({ 300, yOffset });
                        window.draw(uiText);
                        yOffset += 40;
                        found = true;
                    }
                }
                if (!found) {
                    uiText.setString("No appointments scheduled.");
                    uiText.setPosition({ 300, 120 });
                    window.draw(uiText);
                }
            }
            else if (dashboardView == 1 && selectedType == UserType::ADMIN) {
                window.setVisible(false);
                adminMenu(static_cast<Admin*>(loggedInUser), *doctorStorage, *patientStorage);
                window.setVisible(true);
                dashboardView = 0;
            }
            else if (dashboardView == 2 && selectedType == UserType::ADMIN) {
                uiText.setFillColor(Color::Black);
                uiText.setString("Registered Patients List");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                if (patientStorage == nullptr || patientStorage->size() == 0) {
                    uiText.setString("No patients found in system.");
                    uiText.setPosition({ 300, 120 });
                    window.draw(uiText);
                }
                else {
                    float yOfset = 120;
                    for (int i = 0; i < patientStorage->size(); i++) {
                        Patient* p = patientStorage->getAt(i);
                        string info = to_string(p->getID()) + ". " + p->getName() +
                            " | Contact: " + p->getContact();

                        uiText.setString(info);
                        uiText.setPosition({ 300, yOfset });
                        window.draw(uiText);
                        yOfset += 40;

                        if (yOfset > window.getSize().y - 50) break;
                    }
                }
            }
            else if (dashboardView == 2 && selectedType == UserType::DOCTOR) {
                Doctor* curDoc = static_cast<Doctor*>(loggedInUser);
                uiText.setString("Issued Prescriptions:");
                uiText.setPosition({ 300, 50 });
                uiText.setFillColor(Color::Black);
                window.draw(uiText);

                float yOffset = 120;
                bool foundPres = false;
                for (int i = 0; i < presStorage->size(); i++) {
                    Prescription* p = presStorage->getAt(i);
                    if (p->getDoctorID() == curDoc->getID()) {
                        string info = "Patient ID: " + to_string(p->getPatientID()) +
                            " | Med: " + p->getMedicines() +
                            " | Dose: " + p->getNotes();
                        uiText.setString(info);
                        uiText.setPosition({ 300, yOffset });
                        window.draw(uiText);
                        yOffset += 40;
                        foundPres = true;
                    }
                }
                if (!foundPres) {
                    uiText.setString("No prescriptions issued by you.");
                    uiText.setPosition({ 300, 120 });
                    window.draw(uiText);
                }
            }
            else if (dashboardView == 2 && selectedType == UserType::PATIENT) {
                uiText.setString("Your Billing History");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                float yOfset = 120;
                Patient* curr = (Patient*)loggedInUser;

                for (int i = 0; i < billStorage->size(); i++) {
                    if (billStorage->getAt(i)->getPatientID() == curr->getID()) {
                        string billInfo = "Amount:\t" + to_string((int)billStorage->getAt(i)->getAmount()) + "\nReason:\t" + billStorage->getAt(i)->getDescription();
                        uiText.setString(billInfo);
                        uiText.setPosition({ 300, yOfset });
                        window.draw(uiText);
                        yOfset += 40;
                    }
                }
            }
            else if ((dashboardView == 3 && selectedType == UserType::PATIENT)) {
                Patient* cur = static_cast<Patient*>(loggedInUser);
                uiText.setString("      My Profile     ");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                string profileInfo = "ID:\t" + to_string(cur->getID()) + "\nName:\t" + cur->getName() + 
                    "\nAge:\t" + to_string(cur->getAge()) + "\nContact:\t" + cur->getContact()
                    + "\nCurrent Balance:\t" + to_string((int)cur->getBalance());
                uiText.setString(profileInfo);
                uiText.setPosition({300, 120});
                window.draw(uiText);
            }
            else if (dashboardView == 3 && selectedType == UserType::ADMIN) {
                uiText.setString("Security Incident Log");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                ifstream file("SecurityLog.txt");
                string line, content;
                int lineCount = 0;

                while (getline(file, line) && lineCount < 15) {
                    content += line + '\n';
                    lineCount++;
                }
                file.close();

                uiText.setCharacterSize(18);
                uiText.setString(content.empty() ? "No Incidents Recorded." : content);
                uiText.setPosition({300, 120});
                uiText.setFillColor(Color::Red);
                window.draw(uiText);
                uiText.setCharacterSize(24);
            }
            else if (dashboardView == 4 && selectedType == UserType::PATIENT) { 
                uiText.setString("Your Appointments:");
                uiText.setPosition({ 300, 50 });
                window.draw(uiText);

                float yOffset = 120;
                Patient* curr = (Patient*)loggedInUser;
                for (int i = 0; i < appStorage->size(); i++) {
                    if (appStorage->getAt(i)->getPatientID() == curr->getID()) {
                        uiText.setString("Doctor ID: " + to_string(appStorage->getAt(i)->getDoctorID()) + " Date: " + appStorage->getAt(i)->getDate());
                        uiText.setPosition({ 300, yOffset });
                        window.draw(uiText);
                        yOffset += 40;
                    }
                }
            }           

        }
        else if (currentState == AppState::SIGNUP) {
            uiText.setString("    Patient Registration    ");
            uiText.setPosition({500, 100});
            window.draw(uiText);
            
            uiText.setString("Name:\t" + signupName + (activeField == 0 ? "-" : ""));
            uiText.setPosition({ 400, 200 });
            window.draw(uiText);

            uiText.setString("Age:\t" + signupAge + (activeField == 1 ? "-" : ""));
            uiText.setPosition({ 400, 260 });
            window.draw(uiText);

            uiText.setString("Contact:\t" + signupContact + (activeField == 2 ? "-" : ""));
            uiText.setPosition({ 400, 320 });
            window.draw(uiText);

            uiText.setString("Password:\t" + string(signupPass.length(), '*') + (activeField == 3 ? "-" : ""));
            uiText.setPosition({ 400, 380 });
            window.draw(uiText);

            RectangleShape buttonSignup({200, 50});
            buttonSignup.setPosition({ 400, 500 });
            buttonSignup.setFillColor(Color::Green);
            window.draw(buttonSignup);

            uiText.setString("REGISTER");
            uiText.setPosition({410, 515});
            uiText.setFillColor(Color::Blue);
            window.draw(uiText);
        }

        window.display();

    }
    delete patientStorage;
    patientStorage = nullptr;
    delete doctorStorage;
    doctorStorage = nullptr;
    delete adminStorage;
    adminStorage = nullptr;
    delete appStorage;
    appStorage = nullptr;
    delete billStorage;
    billStorage = nullptr;
    delete presStorage;
    presStorage = nullptr;
}