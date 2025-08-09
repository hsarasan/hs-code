#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

// Our C++ class
class Pet {
public:
    Pet(const std::string &name, int age) 
        : name(name), age(age) {}

    void setName(const std::string &new_name) { name = new_name; }
    std::string getName() const { return name; }

    void setAge(int new_age) { age = new_age; }
    int getAge() const { return age; }

    std::string info() const {
        return name + " is " + std::to_string(age) + " years old.";
    }

private:
    std::string name;
    int age;
};

// Bind C++ class to Python
PYBIND11_MODULE(example, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string&, int>(), "Constructor",
             py::arg("name"), py::arg("age"))
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("setAge", &Pet::setAge)
        .def("getAge", &Pet::getAge)
        .def("info", &Pet::info);
}

