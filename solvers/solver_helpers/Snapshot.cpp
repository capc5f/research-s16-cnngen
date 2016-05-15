//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Snapshot.h"

Snapshot::Snapshot(int snapshot, SnapshotFormat snapshot_format, std::string snapshot_prefix) {
    this->mSnapshotCount = snapshot;
    this->mSnapshotFormat = snapshot_format;
    this->mSnapshotPrefix = snapshot_prefix;
}

Snapshot::~Snapshot() {

}

int Snapshot::getSnapshotCount() {
    return this->mSnapshotCount;
}

std::string Snapshot::getSnapshotPrefix() {
    return this->mSnapshotPrefix;
}

std::string Snapshot::getSnapshotFormat() {
    switch ( mSnapshotFormat ) {
        case HDF5:
            return "HDF5";

        default:
            return "";
    }
}
