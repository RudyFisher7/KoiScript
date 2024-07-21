//
// Created by rfish on 7/20/2024.
//

#ifndef KOI_SCRIPTING_RUNTIME_ERROR_HPP
#define KOI_SCRIPTING_RUNTIME_ERROR_HPP


namespace Koi {
namespace Scripting {
namespace Runtime {

enum Error : int {
    SCRIPTING_RUNTIME_ERROR_MIN = 0,
    SCRIPTING_RUNTIME_ERROR_OK = SCRIPTING_RUNTIME_ERROR_MIN,
    SCRIPTING_RUNTIME_ERROR_SIZE,
};

}
}
}


#endif //KOI_SCRIPTING_RUNTIME_ERROR_HPP
