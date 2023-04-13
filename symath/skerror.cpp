#include "skerror.h"
#include <ostream>
#include <iomanip>

using namespace std;
using namespace symkit;

SKError::SKError(const SKErrorType& type,
        const std::string &functionName,
        const std::string &className,
        const std::string &comment,
        bool fatal)

    : type(type), functionName(functionName), className(className), comment(comment), fatal(fatal)
{

}

//Surcharge de l'operateur << pour l'affichage d'un message d'erreur a appeler dans un catch
ostream& operator<<(ostream& os, const SKError &err)
{
    os << "Error ";

    switch (err.type)
    {
    case ERR_INIT:
        os << "initializing symkit ";
        break;

    case ERR_EVOLVE:
        os << "during scene evolution ";
        break;

    case ERR_RENDER:
        os << "in rendering process ";
        break;

    case ERR_NULL_POINTER:
        os << "caused by a NULL pointer dereferencing ";
        break;

    case ERR_NUMERICAL:
        os << "caused by a wrong numerical operation ";
        break;

    case ERR_OTHERS:
        os << "of unknown entity ";
        break;

    default:
        os << "of unknown entity ";
        break;
    }

    if (err.className != "")
        os << "in class " << err.className << ", ";

    os << ", " << "in function " << err.functionName << ": " << endl << endl;

    os << setw(4) << err.comment << setw(1) << endl;

    return os;
}
