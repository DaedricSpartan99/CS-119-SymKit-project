#ifndef SKERROR_H
#define SKERROR_H

#include <string>

/* struct contentant les infos necessaires pour la gestion d'un erreur */
namespace symkit
{

    enum SKErrorType
    {
        ERR_INIT = -7,
        ERR_EVOLVE,
        ERR_RENDER,
        ERR_NULL_POINTER,
        ERR_NUMERICAL,
        ERR_BOUND,
        ERR_OTHERS = -1
    };

    struct SKError
    {
        SKError(const SKErrorType&,
            const std::string &functionName,
            const std::string &className,
            const std::string &comment = "",
            bool fatal = true);

        SKErrorType type;

        std::string functionName;
        std::string className;

        std::string comment;

        bool fatal;
    };
}

#include <iosfwd>

//Surcharge de l'operateur << pour l'affichage d'un message d'erreur a appeler dans un catch
std::ostream& operator<<(std::ostream&, const symkit::SKError&);

#endif // SKERROR_H
