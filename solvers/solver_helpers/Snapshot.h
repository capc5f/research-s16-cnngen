//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_SNAPSHOT_H
#define RESEARCHDNNGENERATOR_SNAPSHOT_H


#include <string>
#include <sstream>

enum SnapshotFormat {
    HDF5
};

class Snapshot {
private:
    int mSnapshotCount;
    SnapshotFormat mSnapshotFormat;
    std::string mSnapshotPrefix;

public:
    Snapshot(int snapshot, SnapshotFormat snapshot_format, std::string snapshot_prefix);
    ~Snapshot();
    int getSnapshotCount();
    std::string getSnapshotFormat();
    std::string getSnapshotPrefix();
};


#endif //RESEARCHDNNGENERATOR_SNAPSHOT_H
