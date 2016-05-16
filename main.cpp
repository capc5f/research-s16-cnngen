#include <iostream>
#include <vector>

#include "utils/UserInput.h"
#include "utils/GenerateLayers.h"
#include "utils/Utilities.h"

using namespace std;

int main(int argc, const char **argv) {

    UserInput in(false);
    if ( !in.isValidInput() ) {
        cout << "Exiting program.." << endl;
        return EXIT_FAILURE;
    }

    GenerateLayers gen(in);
    vector <LayerBase *> layers;
    layers = gen.getLayerList();
//    layers = getAlexNetLayers();

    if ( in.doGeneratePrototxt() ) {
        displayPrototxtOutput(in, layers);
    }

    layers.clear();
    if ( layers.empty() )
        cout << "Layers cleared.." << endl;

    return EXIT_SUCCESS;
}
