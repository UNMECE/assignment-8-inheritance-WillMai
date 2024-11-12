#include <iostream>
#include <cmath>

const double EPSILON_0 = 8.854187817e-12;  // Permittivity of free space in F/m
const double MU_0 = 4 * M_PI * 1e-7;       // Permeability of free space in H/m

class Field {
protected:
    double value[3];  // Components of the field (x, y, z)

public:
    // Default constructor initializes components to zero
    Field() : value{0.0, 0.0, 0.0} {}

    // Constructor to initialize the field with given components
    Field(double x, double y, double z) : value{x, y, z} {}

    // Print the field's components
    virtual void printMagnitude() const {
        std::cout << "Field components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
    }

    // Virtual destructor for proper cleanup of derived classes
    virtual ~Field() {}
};

class ElectricField : public Field {
private:
    double calculatedField;  // Calculated electric field value

public:
    // Constructor to initialize electric field components
    ElectricField(double x, double y, double z) : Field(x, y, z), calculatedField(0.0) {}

    // Method to calculate the electric field based on Gauss' Law
    void calculateElectricField(double Q, double r) {
        calculatedField = Q / (4 * M_PI * r * r * EPSILON_0);
    }

    // Overload '+' operator for ElectricField addition
    ElectricField operator+(const ElectricField& other) const {
        return ElectricField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    // Copy constructor
    ElectricField(const ElectricField& other) : Field(other), calculatedField(other.calculatedField) {}

    // Print electric field's components and calculated field
    void printMagnitude() const override {
        Field::printMagnitude();
        std::cout << "Calculated Electric Field: " << calculatedField << " N/C\n";
    }

    // Overload '<<' operator
    friend std::ostream& operator<<(std::ostream& os, const ElectricField& e) {
        os << "Electric Field components: (" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
        return os;
    }
};

class MagneticField : public Field {
private:
    double calculatedField;  // Calculated magnetic field value

public:
    // Constructor to initialize magnetic field components
    MagneticField(double x, double y, double z) : Field(x, y, z), calculatedField(0.0) {}

    // Method to calculate the magnetic field based on Ampere's Law
    void calculateMagneticField(double I, double r) {
        calculatedField = (MU_0 * I) / (2 * M_PI * r);
    }

    // Overload '+' operator for MagneticField addition
    MagneticField operator+(const MagneticField& other) const {
        return MagneticField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    // Copy constructor
    MagneticField(const MagneticField& other) : Field(other), calculatedField(other.calculatedField) {}

    // Print magnetic field's components and calculated field
    void printMagnitude() const override {
        Field::printMagnitude();
        std::cout << "Calculated Magnetic Field: " << calculatedField << " T\n";
    }

    // Overload '<<' operator
    friend std::ostream& operator<<(std::ostream& os, const MagneticField& m) {
        os << "Magnetic Field components: (" << m.value[0] << ", " << m.value[1] << ", " << m.value[2] << ")";
        return os;
    }
};

int main() {
    // Create electric and magnetic field objects with specified components
    ElectricField e1(0, 1e5, 1e3);
    MagneticField m1(1e-4, 2e-4, 3e-4);

    // Print initial field components
    std::cout << "Initial Electric and Magnetic Field Components:\n";
    e1.printMagnitude();
    m1.printMagnitude();

    // Calculate electric field at a certain distance from charge Q
    double Q = 1e-6;    // Charge in Coulombs
    double r = 0.05;    // Distance in meters
    e1.calculateElectricField(Q, r);
    std::cout << "\nAfter calculating Electric Field:\n";
    e1.printMagnitude();

    // Calculate magnetic field at a certain distance from current I
    double I = 10.0;    // Current in Amperes
    m1.calculateMagneticField(I, r);
    std::cout << "\nAfter calculating Magnetic Field:\n";
    m1.printMagnitude();

    // Demonstrate overloaded '+' operator for electric field
    ElectricField e2(1e4, 2e4, 3e4);
    ElectricField e3 = e1 + e2;
    std::cout << "\nAfter adding two Electric Fields:\n" << e3 << std::endl;

    // Demonstrate overloaded '+' operator for magnetic field
    MagneticField m2(2e-4, 3e-4, 1e-4);
    MagneticField m3 = m1 + m2;
    std::cout << "\nAfter adding two Magnetic Fields:\n" << m3 << std::endl;

    return 0;
}
