#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class SystemComponent {
protected:
    string componentCode;
    bool isOnline;

public:
    static int activeComponents;

    SystemComponent(string code) : componentCode(code), isOnline(true) {
        activeComponents++;
    }

    virtual ~SystemComponent() {
        activeComponents--;
    }

    virtual void runDiagnostics() = 0;
};

int SystemComponent::activeComponents = 0;

class PowerUnit : virtual public SystemComponent {
protected:
    double voltageLevel;

public:
    PowerUnit(string code, double voltage) : SystemComponent(code), voltageLevel(voltage) {}

    void checkPower() {
        cout << "Power unit [" << componentCode << "] stable at " << voltageLevel << "V." << endl;
    }
};

class CoolingUnit : virtual public SystemComponent {
protected:
    double coolantTempC;

public:
    CoolingUnit(string code, double temp) : SystemComponent(code), coolantTempC(temp) {}

    void checkCooling() {
        cout << "Cooling loop [" << componentCode << "] running at " << coolantTempC << " C." << endl;
    }
};

class MainframeServer : public PowerUnit, public CoolingUnit {
private:
    int activeConnections;

public:
    MainframeServer(string code, double voltage, double temp, int connections)
        : SystemComponent(code),
          PowerUnit(code, voltage),
          CoolingUnit(code, temp),
          activeConnections(connections) {}

    ~MainframeServer() {
        cout << "Mainframe " << componentCode << " safely shut down." << endl;
    }

    void runDiagnostics() override {
        cout << "\n--- Mainframe Diagnostics: " << componentCode << " ---" << endl;
        checkPower();
        checkCooling();
        cout << "Active Network Connections: " << activeConnections << endl;
        cout << "Status: Optimal Performance" << endl;
    }
};

int main() {
    SystemComponent* server = new MainframeServer("SRV-CORE-01", 48.0, 31.5, 1250);

    server->runDiagnostics();

    cout << "\nActive System Components: " << SystemComponent::activeComponents << endl;

    delete server;

    cout << "Active Components After Teardown: " << SystemComponent::activeComponents << endl;

    return 0;
}
