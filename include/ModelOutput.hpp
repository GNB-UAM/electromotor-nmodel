#ifndef MODEL_OUTPUT_H_
#define MODEL_OUTPUT_H_

#include <iostream>

class ModelOutput{
private:
    std::string _oFileName;
    std::ofstream _oFile;

public:
    static const char endStep = {'\n'};
    static const bool endModelOutput = {'\0'};

    ModelOutput(std::string oFileName){
        _oFileName = oFileName;
        _oFile.open(_oFileName);
        if (_oFile.fail()) throw "ModelOutput: Problem opening ElectromotorModel output file.";
        if (_oFile.is_open()) {
          _oFile << "";
        }
    }

    template <class T>
    void operator<<(T data){
        if (data == endStep){
            _oFile << endStep;
            return;
        }

        if (data == endModelOutput){
            _oFile.close();
            return;
        }

        _oFile << data << " ";
    }


};

#endif