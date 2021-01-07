#ifndef MODEL_OUTPUT_H_
#define MODEL_OUTPUT_H_

#include <iostream>

class ModelOutput {
 private:
  std::string _oFileName;
  std::ofstream _oFile;

 public:
  static const char endStep = {'\n'};

  ModelOutput(std::string oFileName) {
    _oFileName = oFileName;
    _oFile.open(_oFileName);
    if (_oFile.fail() || !_oFile.is_open()) {
      std::cerr << "ModelOutput: Problem opening ElectromotorModel output file."
                << std::endl;
      exit(-1);
    }
    _oFile << "";
  }

  template <class T>
  ModelOutput& operator<<(T* data) {
    _oFile << data << " ";
    return *this;
  }

  template <class T>
  ModelOutput& operator<<(T data) {
    if (data == endStep) {
      _oFile << endStep;
      return *this;
    }

    _oFile << data << " ";
    return *this;
  }

  void close() { _oFile.close(); }
};

#endif